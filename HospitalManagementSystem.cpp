#include <iostream>
using namespace std;

//Arrays and Linked Lists for patient records.//

//struct to store patient info
const int MAX_TREATMENTS = 20;

struct Patient {
    int id;
    string name;
    string condition;
    int age;
    string treatments[MAX_TREATMENTS];
    int treatmentCount = 0;
    Patient* next;
};

// Head pointer for the patient linked list
Patient* head = nullptr;

