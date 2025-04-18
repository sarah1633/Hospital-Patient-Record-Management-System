#include <iostream>
using namespace std;

// Arrays and Linked Lists for patient records.//

// struct to store patient info
#define MAX_TREATMENTS 100

struct Patient
{
    int id;
    string name;
    string condition;
    int age;
    string treatments[MAX_TREATMENTS]; // treatment or appointment
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
Patient *searchPatient(int id)
{
    Patient *temp = head;
    while (temp)
    {
        if (temp->id == id)
            return temp;
        temp = temp->next;
    }
    return nullptr;
}

// Add a treatment(or appointment) to a patient
void addTreatment(int id, string treatmentName)
{
    Patient *patient = searchPatient(id);

    if (!patient)
    {
        cout << "Patient not found.\n";
        return;
    }

    if (patient->treatmentCount >= MAX_TREATMENTS)
    {
        cout << "Max treatments reached for this patient.\n";
        return;
    }

    patient->treatments[patient->treatmentCount++] = treatmentName;
    cout << "Treatment '" << treatmentName << "' added to " << patient->name << ".\n";
}

// View all treatments(or appointments) for a patient
void viewTreatments(int id)
{
    Patient *patient = searchPatient(id);

    if (!patient)
    {
        cout << "Patient not found.\n";
        return;
    }

    cout << "\nTreatment History for " << patient->name << ":\n";
    if (patient->treatmentCount == 0)
    {
        cout << "No treatments recorded.\n";
        return;
    }

    for (int i = 0; i < patient->treatmentCount; i++)
    {
        cout << i + 1 << ". " << patient->treatments[i] << endl;
    }
}