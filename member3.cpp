#include <iostream>
#include <stack> // for undo feature
using namespace std;

// Inside the Patient struct (add this line)
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
    stack<string> treatmentHistory; // 🔁 for undo
    Patient *next;
};

// Head pointer for the patient linked list
Patient *head = nullptr;

// Function to add a new patient
void addPatient(int id, string name, string condition, int age)
{
    Patient *newPatient = new Patient;
    newPatient->id = id;
    newPatient->name = name;
    newPatient->condition = condition;
    newPatient->age = age;
    newPatient->treatmentCount = 0;
    newPatient->next = nullptr;

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
    patient->treatmentHistory.push(treatmentName); // 🔁 Track for undo
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

void undoTreatment(int id)
{
    Patient *patient = searchPatient(id);

    if (!patient)
    {
        cout << "Patient not found.\n";
        return;
    }

    if (patient->treatmentHistory.empty())
    {
        cout << "No treatment to undo.\n";
        return;
    }

    string last = patient->treatmentHistory.top();
    patient->treatmentHistory.pop();
    patient->treatmentCount--;

    cout << "Last treatment removed: " << last << " from " << patient->name << ".\n";
}



int main()
{
    int choice;

    while (true)
    {
        cout << "\n--- Hospital Patient Management ---\n";
        cout << "1. Add Patient\n";
        cout << "2. Search Patient by ID\n";
        cout << "3. Add Treatment(or appointment) to Patient\n";
        cout << "4. View Treatments(or appointments) of Patient\n";
        cout << "5. Undo Last Treatment\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1)
        {
            int id, age;
            string name, condition;
            cout << "Enter Patient ID: ";
            cin >> id;
            cout << "Enter Name: ";
            cin >> name;
            cout << "Enter Condition: ";
            cin >> condition;
            cout << "Enter Age: ";
            cin >> age;
            addPatient(id, name, condition, age);
        }
        else if (choice == 2)
        {
            int id;
            cout << "Enter Patient ID to search: ";
            cin >> id;
            Patient *found = searchPatient(id);
            if (found)
            {
                cout << "\nPatient Found:\n";
                cout << "ID: " << found->id << "\n";
                cout << "Name: " << found->name << "\n";
                cout << "Condition: " << found->condition << "\n";
                cout << "Age: " << found->age << "\n";
                cout << "Treatments/appointments Count: " << found->treatmentCount << "\n";
            }
            else
            {
                cout << "Patient with ID " << id << " not found.\n";
            }
        }
        else if (choice == 3)
        {
            int id;
            string treatment;
            cout << "Enter Patient ID: ";
            cin >> id;
            cin.ignore();
            cout << "Enter Treatment(or appointment) Description: ";
            getline(cin, treatment);
            addTreatment(id, treatment);
        }
        else if (choice == 4)
        {
            int id;
            cout << "Enter Patient ID: ";
            cin >> id;
            viewTreatments(id);
        }
        else if (choice == 5)
        {
            int id;
            cout << "Enter Patient ID to undo treatment: ";
            cin >> id;
            undoTreatment(id);
        }
        else if (choice == 6)
        {
            cout << "Exiting...\n";
            break;
        }
        else
        {
            cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}