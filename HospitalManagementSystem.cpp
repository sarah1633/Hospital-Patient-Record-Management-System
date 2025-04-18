#include <iostream>
using namespace std;

//Arrays and Linked Lists for patient records.

struct Patient {
    int id;
    string name;
    string condition;
    int age;
    Patient* next;
};

