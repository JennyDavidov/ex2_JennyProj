#ifndef EX2_EX2_H
#define EX2_EX2_H

#include <unordered_map>
#include <list>
#include <iterator>
#include <iostream>
#include <fstream>

using namespace std;

template<class T>
class CacheManager {
public:
    unsigned _capacity;
    unordered_map<string, std::pair<T, std::list<string>::iterator>> _cache;
    list<string> _lru;

public:
    CacheManager(int capacity) {
        this->_capacity = capacity;
    }

    void insert(string key, T obj) {
        //if the key exist - update obj
        auto item = _cache.find(key);
        if (item != _cache.end()) {
            used(item);
            _cache[key] = {obj, _lru.begin()};
            //UPDATE IN FILE
            std::ofstream in_file;
            string filename = key + obj.class_name;
            in_file.open(filename, std::ios::binary);
            if (!in_file) {
                //if the opening file failed
                throw "Error opening file";
            }
            in_file.write((char *) &obj, sizeof(obj));
            if (!in_file.good()) {
                //if writing didn't succeed
                throw "Error opening file";
            }
            in_file.close();
            return;
        }
            //if the key is not exist - WRITE TO FILE AND CACHE
        else {
            //if there is still place in map
            if (_cache.size() == this->_capacity) {
                _cache.erase(_lru.back());
                _lru.pop_back();
            }
            _lru.push_front(key);
            _cache.insert({key, {obj, _lru.begin()}});
            //write to FILE
            std::ofstream in_file;
            string filename = key + obj.class_name;
            in_file.open(filename, std::ios::binary);
            if (!in_file) {
                //if the opening file failed
                throw "Error opening file";
            }
            in_file.write((char *) &obj, sizeof(obj));
            if (!in_file.good()) {
                //if writing didn't succeed
                throw "Error opening file";
            }
            in_file.close();
        }
    }

    T get(string key) {
        auto item = _cache.find(key);
        if (item != _cache.end()) {
//return the value - which is the first from the pair
            //update the LRU that there was a USED value.
            used(item);
            return item->second.first;
        } else {
            //check if exist in filesystem
            string filename = key + T::class_name;
            ifstream ifstream1(filename);
            if (ifstream1) {
                // The file exists, and is open for input
                //read from file and load to object T
                //T obj = ifstream1.read((char *) &obj, sizeof(obj));
                T obj;
                ifstream1.read((char *) &obj, sizeof(obj));
                ifstream1.close();
                insert(key, obj);
                auto iterator1 = _cache.find(key);
                used(iterator1);
                return obj;
            } else {
                throw "Error reading file";
            }

        }
        used(item);
    }

    void used(typename unordered_map<string, std::pair<T, std::list<string>::iterator>>::iterator &it) {
        //change from 1 - 2 - 3 to 2 - 1 - 3 for example, in accordance to the use of key.
        //erase in O(1) time
        _lru.erase(it->second.second);
        //push it in front
        _lru.push_front(it->first);
        //update thr iterator in the map
        it->second.second = _lru.begin();
    }

    template<class Predicate>
    void foreach(Predicate p) {
        list<string>::iterator begin = _lru.begin();
        while (begin != _lru.end()) {
            p(_cache[*begin].first);
            begin++;
        }
    }

    virtual ~CacheManager() {

    }
};


#endif

