#include <iostream>
#include <string> 
#include <limits> 
#include <stack> 
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
    stack<string> treatmentHistory; // for undo 
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
    patient->treatmentHistory.push(treatmentName); // Tracking undo 
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

void displayAllPatients() {
    Patient* temp = head;
    if (!temp) {
        std::cout << "No patients in the system.\n";
        return;
    }

    std::cout << "\n--- All Patients ---\n";
    while (temp) {
        std::cout << "ID: " << temp->id << ", Name: " << temp->name << ", Condition: " << temp->condition << ", Age: " << temp->age << std::endl;
        temp = temp->next;
    }
    std::cout << "--------------------\n";
}
struct QueueNode {
    Patient* patient;
    QueueNode* next;

    // Constructor
    QueueNode(Patient* p) : patient(p), next(nullptr) {}
};

// Queue class for Emergency Room (FIFO)
class Queue {
private:
    QueueNode* front;
    QueueNode* rear;

public:
    Queue();  // Constructor
    ~Queue(); // Destructor

    void enqueue(Patient* patient);
    Patient* dequeue();
    bool isEmpty();
    void displayQueue();
};

Queue::Queue() : front(nullptr), rear(nullptr) {}

Queue::~Queue() {
    while (!isEmpty()) {
        dequeue(); // Dequeueing deletes the node
    }
}

void Queue::enqueue(Patient* patient) {
    QueueNode* newNode = new QueueNode(patient);
    if (isEmpty()) {
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
    std::cout << patient->name << " checked into the Emergency Room queue.\n";
}

Patient* Queue::dequeue() {
    if (isEmpty()) {
        std::cout << "Emergency Room queue is empty.\n";
        return nullptr;
    }
    QueueNode* temp = front;
    Patient* patient = temp->patient;
    front = front->next;
    if (!front) {
        rear = nullptr; // If queue becomes empty
    }
    delete temp; // Delete the node, but not the patient object it points to
    return patient;
}

bool Queue::isEmpty() {
    return front == nullptr;
}

void Queue::displayQueue() {
    if (isEmpty()) {
        std::cout << "Emergency Room queue is empty.\n";
        return;
    }
    std::cout << "\n--- Emergency Room Queue ---\n";
    QueueNode* temp = front;
    int position = 1;
    while (temp) {
        std::cout << position++ << ". ID: " << temp->patient->id << ", Name: " << temp->patient->name << ", Condition: " << temp->patient->condition << std::endl;
        temp = temp->next;
    }
    std::cout << "----------------------------\n";
}

// Node structure for the Priority Queue
struct PriorityQueueNode {
    Patient* patient;
    int priority; // Lower number = Higher priority
    PriorityQueueNode* next;

    // Constructor
    PriorityQueueNode(Patient* p, int pri) : patient(p), priority(pri), next(nullptr) {}
};

// Priority Queue class for Critical Patients (using a sorted linked list)
class PriorityQueue {
private:
    PriorityQueueNode* head;

public:
    PriorityQueue();  // Constructor
    ~PriorityQueue(); // Destructor

    void enqueue(Patient* patient, int priority); // Inserts based on priority
    Patient* dequeue(); // Removes highest priority patient
    bool isEmpty();
    void displayQueue();
};

PriorityQueue::PriorityQueue() : head(nullptr) {}

PriorityQueue::~PriorityQueue() {
    while (!isEmpty()) {
        dequeue(); // Dequeueing deletes the node
    }
}

void PriorityQueue::enqueue(Patient* patient, int priority) {
    PriorityQueueNode* newNode = new PriorityQueueNode(patient, priority);

    if (isEmpty() || priority < head->priority) {
        newNode->next = head;
        head = newNode;
    } else {
        PriorityQueueNode* temp = head;
        while (temp->next && temp->next->priority <= priority) {
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;
    }
    std::cout << patient->name << " added to Critical Patient queue with priority " << priority << ".\n";
}

Patient* PriorityQueue::dequeue() {
    if (isEmpty()) {
        std::cout << "Critical Patient queue is empty.\n";
        return nullptr;
    }
    PriorityQueueNode* temp = head;
    Patient* patient = temp->patient;
    head = head->next;
    delete temp; // Delete the node, but not the patient object
    return patient;
}

bool PriorityQueue::isEmpty() {
    return head == nullptr;
}

void PriorityQueue::displayQueue() {
    if (isEmpty()) {
        std::cout << "Critical Patient queue is empty.\n";
        return;
    }
    std::cout << "\n--- Critical Patient Queue ---\n";
    PriorityQueueNode* temp = head;
    int position = 1;
    while (temp) {
        std::cout << position++ << ". ID: " << temp->patient->id << ", Name: " << temp->patient->name << ", Condition: " << temp->patient->condition << " (Priority: " << temp->priority << ")\n";
        temp = temp->next;
    }
    std::cout << "------------------------------\n";
}
int main()
{
    int choice;

    Queue emergencyQueue;
    PriorityQueue criticalQueue;

    while (true)
    {
        cout << "\n--- Hospital Patient Management ---\n";
        cout << "1. Add Patient\n";
        cout << "2. Search Patient by ID\n";
        cout << "3. Add Treatment(or appointment) to Patient\n";
        cout << "4. View Treatments(or appointments) of Patient\n";
        cout << "5. Undo Last Treatment\n";
        cout << "6. Display All Patients\n";
        cout << "--- Emergency Room Queue ---\n";
        cout << "7. Check-in to ER\n";
        cout << "8. Call Next ER Patient\n";
        cout << "9. Display ER Queue\n";
        cout << "--- Critical Patient Queue ---\n";
        cout << "10. Add Critical Patient\n";
        cout << "11. Call Next Critical Patient\n";
        cout << "12. Display Critical Queue\n";
        cout << "13. Exit\n";
        cout << "Enter your choice: ";

        while (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 1)
        {
            int id, age;
            string name, condition;
            cout << "Enter Patient ID: ";
            while (!(cin >> id)) {
                cout << "Invalid input. Please enter a number for ID: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
             cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Enter Name: ";
            getline(cin, name);

            cout << "Enter Condition: ";
            getline(cin, condition);

            cout << "Enter Age: ";
             while (!(cin >> age)) {
                cout << "Invalid input. Please enter a number for age: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            addPatient(id, name, condition, age);
        }
        else if (choice == 2)
        {
            int id;
            cout << "Enter Patient ID to search: ";
             while (!(cin >> id)) {
                cout << "Invalid input. Please enter a number for ID: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

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
             while (!(cin >> id)) {
                cout << "Invalid input. Please enter a number for ID: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Enter Treatment(or appointment) Description: ";
            getline(cin, treatment);
            addTreatment(id, treatment);
        }
        else if (choice == 4)
        {
            int id;
            cout << "Enter Patient ID: ";
             while (!(cin >> id)) {
                cout << "Invalid input. Please enter a number for ID: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
            displayAllPatients();
        }
        else if (choice == 7) {
            int id;
            cout << "Enter Patient ID to check into ER: ";
             while (!(cin >> id)) {
                cout << "Invalid input. Please enter a number for ID: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
             cin.ignore(numeric_limits<streamsize>::max(), '\n');

            Patient* patient = searchPatient(id);
            if (patient) {
                emergencyQueue.enqueue(patient);
            } else {
                cout << "Patient with ID " << id << " not found in the system.\n";
            }
        } else if (choice == 8) {
            Patient* nextER = emergencyQueue.dequeue();
            if (nextER) {
                cout << "Calling next patient from ER: ID " << nextER->id << ", Name: " << nextER->name << endl;
            }
        } else if (choice == 9) {
            emergencyQueue.displayQueue();
        } else if (choice == 10) {
            int id, priority;
            cout << "Enter Patient ID to add to Critical Queue: ";
             while (!(cin >> id)) {
                cout << "Invalid input. Please enter a number for ID: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            Patient* patient = searchPatient(id);
            if (patient) {
                cout << "Enter priority for critical patient (lower number = higher priority): ";
                 while (!(cin >> priority)) {
                    cout << "Invalid input. Please enter a number for priority: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                 cin.ignore(numeric_limits<streamsize>::max(), '\n');

                criticalQueue.enqueue(patient, priority);
            } else {
                cout << "Patient with ID " << id << " not found in the system.\n";
            }
        } else if (choice == 11) {
            Patient* nextCritical = criticalQueue.dequeue();
            if (nextCritical) {
                cout << "Calling next critical patient: ID " << nextCritical->id << ", Name: " << nextCritical->name << " (Priority: " << /* Add code to display priority if needed */ ")\n";
            }
        } else if (choice == 12) {
            criticalQueue.displayQueue();
        }
        else if (choice == 13)
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