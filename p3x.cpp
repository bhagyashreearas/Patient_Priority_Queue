// Name: Bhagyashree Aras
// Filename: p3x.cpp
// Date: 3 November 2020
// Purpose: The interface of the program will determine the patient's
//          priority based on their injury or illness and enter the patient's
//          full name along with the urgency level based on the table above
//          to indicate the priority, as well as added new functionality
//          of changing priority and saving to file
//
// Input:   one .txt file(commands)
// Process: Takes file to read and upload to vector.
//          Use Patient Priority Queue object to enable functionalities
//
// Output:  Display output according to following commands:list,next, peek,
//          load, help, save, change.

#include "PatientPriorityQueuex.h"
#include "Patient.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;
const string ADD = "add";
const string CHANGE = "change";
const string SAVE = "save";
void welcome();
// This function displays welcome message.
// IN : none
// Modify : none
// OUT : print welcome message

void goodbye();
// This function displays good bye message.
// IN : none
// Modify : none
// OUT : print good bye message

void help();
// This function displays menu of commands which can be used.
// IN : none
// Modify : none
// OUT : check for command

bool processLine(string, PatientPriorityQueuex &);
// Process the line entered from the user or read from the file.
// IN : PatientPriorityQueue object and a string
// MODIFY : none
// OUT : lead to another function according to choices

void addPatientCmd(string, PatientPriorityQueuex &);
// Adds the patient to the waiting room.
// IN : PatientPriorityQueue object and a string
// MODIFY : added patient to vector
// OUT : none

void peekNextCmd(PatientPriorityQueuex &);
// Displays the next patient in the waiting room that will be called.
// IN : PatientPriorityQueue object
// MODIFY : none
// OUT : displays the value at index 0

void removePatientCmd(PatientPriorityQueuex &);
// Removes a patient from the waiting room and displays the name on the screen.
// IN : PatientPriorityQueue object
// MODIFY : remove patient from list
// OUT : display next patient

void showPatientListCmd(PatientPriorityQueuex &);
// Displays the list of patients in the waiting room.
// IN : PatientPriorityQueue object
// MODIFY : remove patient from list
// OUT : display next patient

void execCommandsFromFileCmd(string, PatientPriorityQueuex &);
// Reads a text file with each command on a separate line and executes the
// lines as if they were typed into the command prompt.
// IN : PatientPriorityQueue object and string
// MODIFY : none
// OUT : access file otherwise displays error message

string delimitBySpace(string &);
// Delimits (by space) the string from user or file input.
// IN : string
// MODIFY : remove spaces from string
// OUT : return string

void changePatientPriority(string , PatientPriorityQueuex &);
// changePatientPriority enable to change priority of patient
// IN : string and PatientPriorityQueuex object
// MODIFY : priority is modified
// OUT : none

void saveToFile(string, PatientPriorityQueuex &);
// saveToFile enable to save the vector data to file so that it can be reused
// IN : string and PatientPriorityQueuex object
// MODIFY : file is written by data
// OUT : none

int main() {
    // declare variables
    string line;

    // welcome message
    welcome();

    // process commands
    PatientPriorityQueuex priQueue;
    do {
        cout << "\ntriage> ";
        getline(cin, line);
    } while (processLine(line, priQueue));

    // goodbye message
    goodbye();
}

bool processLine(string line, PatientPriorityQueuex &priQueue) {
    // get command
    string cmd = delimitBySpace(line);
    if (cmd.length() == 0) {
        cout << "Error: no command given.";
        return false;
    }

    // process user input
    if (cmd == "help")
        help();
    else if (cmd == "add")
        addPatientCmd(line, priQueue);
    else if (cmd == "peek")
        peekNextCmd(priQueue);
    else if (cmd == "next")
        removePatientCmd(priQueue);
    else if (cmd == "list")
        showPatientListCmd(priQueue);
    else if (cmd == "load")
        execCommandsFromFileCmd(line, priQueue);
    else if (cmd == "change")
        changePatientPriority(line, priQueue);
    else if (cmd == "save")
        saveToFile(line, priQueue);
    else if (cmd == "quit")
        return false;
    else
        cout << "Error: unrecognized command: " << cmd << endl;

    return true;
}

void saveToFile(string line, PatientPriorityQueuex &priQueue)
{
    string fileName;
    // get priority and name
    fileName = delimitBySpace(line);
    if (fileName.length() == 0 || fileName == SAVE) {
        cout << "Error: No valid filename provided\n";
        return;
    }

    priQueue.save(fileName);
    cout << "Saved "<< priQueue.size() << " patients to file " << fileName <<
    endl;
}

void changePatientPriority(string line, PatientPriorityQueuex &priQueue) {
    string arrivalOrder;
    string newPriority;

    // get priority and name
    arrivalOrder = delimitBySpace(line);
    if (arrivalOrder.length() == 0 || arrivalOrder == CHANGE) {
        cout << "Error: No patient id provided\n";
        return;
    }

    newPriority = line;

    if (newPriority.length() == 0) {
        cout << "Error: No priority code given.\n";
        return;
    }
    else if (newPriority.length() > 0) {
        if (newPriority == MINIMAL) {

            priQueue.change(stoi(arrivalOrder), MIN);
            cout << "Changed priority \"" << newPriority << "\" the priority "
                                                            "system\n";
        } else if (newPriority == URGENT) {

            priQueue.change(stoi(arrivalOrder), URG);
            cout << "Changed priority \"" << newPriority << "\" in the "
                                                            "priority "
                                                            "system\n";
        } else if (newPriority == EMERGENCY) {
            priQueue.change(stoi(arrivalOrder), EMER);
            cout << "Changed priority \"" << newPriority << "\" in the "
                                                            "priority "
                                                            "system\n";
        } else if (newPriority == IMMEDIATE) {
            priQueue.change(stoi(arrivalOrder), IMM);
            cout << "Changed priority \"" << newPriority << "\" in the "
                                                            "priority "
                                                            "system\n";
        } else {
            cout << "Error: Invalid Changed Priority";
        }
    }
}

void addPatientCmd(string line, PatientPriorityQueuex &priQueue)
{
    string priority, name;

    // get priority and name
    priority = delimitBySpace(line);

    if (priority.length() == 0 || priority == ADD) {
        cout << "Error: no priority code given.\n";
        return;
    }

    name = line;
    if (name.length() == 0) {
        cout << "Error: no patient name given.\n";
        return;
    }
    if(name == IMMEDIATE || name == EMERGENCY
    || name == URGENT || name == MINIMAL ) {
        cout << "Error: no patient name given.\n";
        return;
    }
    else if(name.length() > 0)
    {
        if (priority == MINIMAL)
        {
            priQueue.add(MIN, name);
            cout << "Added patient \"" << name << "\" to the priority system\n";
        }
        else if (priority == URGENT)
        {
            priQueue.add(URG, name);
            cout << "Added patient \"" << name << "\" to the priority system\n";
        }
        else if (priority == EMERGENCY)
        {
            priQueue.add(EMER, name);
            cout << "Added patient \"" << name << "\" to the priority system\n";
        }
        else if (priority == IMMEDIATE)
        {
            priQueue.add(IMM, name);
            cout << "Added patient \"" << name << "\" to the priority system\n";
        }
        else
        {
            cout << "Error: Invalid priority";
        }
    }
}

void peekNextCmd(PatientPriorityQueuex &priQueue)
{
    int count = 1;
    string firstName;
    string lastName;
    string value = priQueue.peek().to_string();
    istringstream ss(value);
    string word;
    while (ss >> word)
    {
        if (count == 3)
            firstName = word;
        if (count == 4)
            lastName = word;
        count++;
    }
    cout << "Highest priority patient to be called next: "
         << firstName + " " + lastName << "\n";
}

void removePatientCmd(PatientPriorityQueuex &priQueue) {
    int count = 1;
    string firstName;
    string lastName;

    if (priQueue.size() == 0)
        cout << "There are no patients in the waiting area.\n";
    else {
        string value = priQueue.peek().to_string();
        istringstream ss(value);
        string word;
        while (ss >> word)
        {
            if (count == 3)
                firstName = word;
            if (count == 4)
                lastName = word;
            count++;
        }
        cout << "This patient will now be seen: "
             << firstName + " " + lastName  << "\n";
        priQueue.remove();
    }

}

void showPatientListCmd(PatientPriorityQueuex &priQueue) {
    cout << "# patients waiting: " << priQueue.size() << endl;
    cout << "  Arrival #   Priority Code   Patient Name\n"
         << "+-----------+---------------+--------------+\n";

    cout << priQueue.to_string();
}

void execCommandsFromFileCmd(string filename, PatientPriorityQueuex &priQueue) {
    ifstream infile;
    string line;

    // open and read from file
    infile.open(filename);
    if (infile)
    {
        while (getline(infile, line))
        {
            cout << "\ntriage> " << line << endl;
            // process file input
            processLine(line, priQueue);
        }
    } else
    {
        cout << "Error: could not open file.\n";
    }
    // close file
    infile.close();
}

string delimitBySpace(string &s) {
    unsigned pos = 0;
    char delimiter = ' ';
    string result = "";

    pos = s.find(delimiter);
    if (pos != string::npos) {
        result = s.substr(0, pos);
        s.erase(0, pos + 1);
    }
    return result;
}

void welcome() {
    cout << "The interface of the program will determine the\n"
            "patient's priority based on their injury or\n"
            "illness and enter the patient's full name along\n"
            "with the urgency level based on the table above\n"
            "to indicate the priority as well as added new functionality\n"
            "of changing priority and saving to file"<< endl;
}

void goodbye() {
    cout << "Thanks for using this program.";
}

void help() {
    cout << "add <priority-code> <patient-name>\n"
         << "            Adds the patient to the triage system.\n"
         << "            <priority-code> must be one of the 4 accepted \n"
         << "             priority codes:\n"
         << "                1. immediate 2. emergency 3. urgent 4. minimal\n"
         << "            <patient-name>: patient's full legal name \n"
         << "            (may contain spaces)\n"
         << "next        Announces the patient to be seen next. \n"
         << "            Takes into account the type of emergency \n"
         << "            and the patient's arrival order.\n"
         << "peek        Displays the patient that is next in line, but keeps\n"
         << "            in queue\n"
         << "list        Displays the list of all patients that are still \n"
         << "            waiting in the order that they have arrived.\n"
         << "load <file> Reads the file and executes the command on each line\n"
         << "help        Displays this menu\n"
         << "change      Change the priority of patient\n"
         << "save        Saved the data to a file\n"
         << "quit        Exits the program\n";
}
