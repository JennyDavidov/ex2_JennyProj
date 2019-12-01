//
// Created by Daniela Stepanov on 11/16/19.
//
#include "ex2.h"
#include <iostream>
#include <string>

using namespace std;
// Testing Class
class Student
{
    int id;
    int value;
    const char* data;
public:
    static const string class_name; //every class will have a class static name called: class_name
    Student(int _key, int _value, const char* _data): id(_key), value(_value), data(_data) {}
    Student() {}; //every class will have a default constructor
    void print() {
        cout<<"Student Object: "<<id<<", "<<value<<", "<<data<<endl;
    };
    ~Student(){};

};
const string Student::class_name = "StudentClass";

using namespace std;
class Employee
{
    const char* name;
public:
    static const string class_name; //every class will have a class static name called: class_name
    Employee(const char* _name): name(_name) {};
    Employee(){}; //every class will have a default constructor
    void print() {
        cout<<"Employee Object: "<<name<<endl;
    };
    ~Employee(){};

};
const string Employee::class_name = "EmployeeClass";

// another testing class

using namespace std;
class Teacher
{
    const char* name;
    const char* course;
    int year;
public:
    static const string class_name; //every class will have a class static name called: class_name
    Teacher(){}; //every class will have a default constructor
    Teacher(const char* _name, const char* _course, int _year): name(_name),
                                                                course(_course), year(_year){};
    void print() {
        cout<<"Teacher Object: "<<name<<", "<<course<<", "<<year<<endl;
    };
    ~Teacher(){};
};

const string Teacher::class_name = "TeacherClass";


int main() {
    CacheManager<Student> my_cache(3);

    try {
        my_cache.insert("0", Student(0,22,"student1"));
        my_cache.insert("1", Student(1,23,"student2"));
        my_cache.insert("2", Student(2,25,"student3"));
        my_cache.insert("3", Student(3,29,"student4"));
    } catch  (const char * e) {
        cout << e << endl;
    }

    my_cache.foreach([](Student& s){s.print();}); //prints all students in cache

    try {
        Student return_obj = my_cache.get("0");//not in cache but in filesystem
    } catch (const char * e) {
        cout << e << endl;
    }
    try {
        auto return_obj2 = my_cache.get("1");
    } catch (const char * e) {
        cout << e << endl;
    }
    try {
        auto return_obj3 = my_cache.get("2");
    } catch (const char * e) {
        cout << e << endl;
    }
    try {
        auto return_obj4 = my_cache.get("3");
    } catch (const char * e) {
        cout << e << endl;
    }

    CacheManager<Employee> my_2nd_cache(5);
    try {
        my_2nd_cache.insert("0", Employee("emp1"));
        my_2nd_cache.insert("1", Employee("emp2"));
        my_2nd_cache.insert("2",Employee("emp3"));
        my_2nd_cache.insert("3", Employee("emp4"));
    } catch  (const char * e) {
        cout << e << endl;
    }

    try {
        auto emp3 = my_2nd_cache.get("2");
    } catch (const char * e) {
        cout << e << endl;
    }
    try {
        auto error_obj = my_cache.get("4");
    } catch (const char * e) {
        cout << e << endl;
    }

    try {
        my_2nd_cache.insert("emp_key", Employee("emp5"));
        my_2nd_cache.insert("hello", Employee("emp6"));
        my_2nd_cache.insert("bye", Employee("emp7"));
        my_2nd_cache.insert("some_key", Employee("emp8"));
    } catch (const char * e) {
        cout << e << endl;
    }

    try {
        auto emp1 = my_2nd_cache.get("0");
    } catch (const char * e) {
        cout << e << endl;
    }


    try {
        auto emp5 = my_2nd_cache.get("emp_key");
    } catch (const char * e) {
        cout << e << endl;
    }
    try {
        auto emp6 = my_2nd_cache.get("hello");
    } catch (const char * e) {
        cout << e << endl;
    }


    //*** ---- I will also perform a check that the files have indeed
    // been created in the same directory as the program-------------***


    // another tests

    CacheManager<Teacher> teacherCache(5);

    try {
        teacherCache.insert("0", Teacher("Reznikov", "LinearAlgebra", 1));
        teacherCache.insert("1", Teacher("Doron", "Infi", 1));
        teacherCache.insert("2", Teacher("Erez", "Algebraic structures", 2));
        teacherCache.insert("3", Teacher("Arye", "Discrete mathematics", 1));
        teacherCache.insert("4", Teacher("Noa", "Introduction to CS", 1));
        teacherCache.insert("5", Teacher("Adi", "LinearAlgebra", 1));
        teacherCache.insert("6", Teacher("Tsvi Kopelowitz", "Algorithms1", 2));
    } catch  (const char * e) {
        cout << e << endl;
    }

    teacherCache.foreach([](Teacher& s){s.print();}); //prints all students in cache
    cout << endl;

    //Teacher Object: Tsvi Kopelowitz, Algorithms1, 2
    //Teacher Object: Adi, LinearAlgebra, 1
    //Teacher Object: Noa, Introduction to CS, 1
    //Teacher Object: Arye, Discrete mathematics, 1
    //Teacher Object: Erez, Algebraic structures, 2


    try {
        Teacher return_obj = teacherCache.get("0");//not in cache but in filesystem
        return_obj.print();
        cout << endl;
        //Teacher Object: Reznikov, LinearAlgebra, 1
    } catch (const char * e) {
        cout << e << endl;
    }

    teacherCache.foreach([](Teacher& s){s.print();}); //prints all students in cache
    cout << endl;

    //Teacher Object: Reznikov, LinearAlgebra, 1
    //Teacher Object: Tsvi Kopelowitz, Algorithms1, 2
    //Teacher Object: Adi, LinearAlgebra, 1
    //Teacher Object: Noa, Introduction to CS, 1
    //Teacher Object: Arye, Discrete mathematics, 1


    try {
        auto error_obj2 = teacherCache.get("7"); // not in both, throwing the
        //error string
    } catch (const char * e) {
        cout << e << endl;
        cout << endl;
    }
    try {
        auto return_obj3 = teacherCache.get("5"); // in cache
        return_obj3.print();
        cout << endl;
        //Teacher Object: Adi, LinearAlgebra, 1
    } catch (const char * e) {
        cout << e << endl;
    }
    try {
        auto return_obj4 = teacherCache.get("4"); // in cache
        return_obj4.print();
        cout << endl;
        //Teacher Object: Noa, Introduction to CS, 1
    } catch (const char * e) {
        cout << e << endl;
    }

    try {
        teacherCache.insert("0", Teacher("Plutkin", "LinearAlgebra", 1));
        teacherCache.foreach([](Teacher& s){s.print();}); //prints all students in cache
        cout << endl;

        //Teacher Object: Plutkin, LinearAlgebra, 1
        //Teacher Object: Noa, Introduction to CS, 1
        //Teacher Object: Adi, LinearAlgebra, 1
        //Teacher Object: Tsvi Kopelowitz, Algorithms1, 2
        //Teacher Object: Arye, Discrete mathematics, 1

        // Filling the cache so Plutkin will be only in file

        teacherCache.insert("2", Teacher("Erez", "Algebraic structures", 2));
        teacherCache.insert("3", Teacher("Arye", "Discrete mathematics", 1));
        teacherCache.insert("4", Teacher("Noa", "CS Introduction", 1));
        teacherCache.insert("5", Teacher("Adi", "LinearAlgebra", 1));
        teacherCache.insert("6", Teacher("Tsvi Kopelowitz", "Algorithms1", 2));

        teacherCache.foreach([](Teacher& s){s.print();}); //prints all students in cache
        cout << endl;

        //Teacher Object: Tsvi Kopelowitz, Algorithms1, 2
        //Teacher Object: Adi, LinearAlgebra, 1
        //Teacher Object: Noa, CS Introduction, 1
        //Teacher Object: Arye, Discrete mathematics, 1
        //Teacher Object: Erez, Algebraic structures, 2

        auto return_obj = teacherCache.get("0"); // checks if updated in file
        return_obj.print();
        cout << endl;
        //Teacher Object: Plutkin, LinearAlgebra, 1
    } catch  (const char * e) {
        cout << e << endl;
    }

    return 0;
}