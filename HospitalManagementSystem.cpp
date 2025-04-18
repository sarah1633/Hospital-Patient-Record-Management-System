#include <iostream>
using namespace std;

// Arrays and Linked Lists for patient records.//

// struct to store patient info
const int MAX_TREATMENTS = 20;

struct Patient
{
    int id;
    string name;
    string condition;
    int age;
    string treatments[MAX_TREATMENTS];
    int treatmentCount = 0;
    Patient *next;
};

// Head pointer for the patient linked list
Patient *head = nullptr;

// Function to add a new patient
void addPatient(int id, string name, string condition, int age)
{
    Patient *newPatient = new Patient{id, name, condition, age, {}, 0, nullptr};

    if (!head)
    {
        head = newPatient;
    }
    else
    {
        Patient *temp = head;
        while (temp->next)
            temp = temp->next;
        temp->next = newPatient;
    }

    cout << "Patient " << name << " added successfully.\n";
}

// Search for a patient by ID
Patient* searchPatient(int id) {
    Patient* temp = head;
    while (temp) {
        if (temp->id == id)
            return temp;
        temp = temp->next;
    }
    return nullptr;
}