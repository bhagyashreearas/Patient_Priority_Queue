// Author Name: Bhagyashree Aras
// File name: Patient.h
// Date: 3 November 2020
// Purpose: Specification file for Patient class.

#ifndef P3X_PATIENT_H
#define P3X_PATIENT_H

#include <string>
#include <iomanip>
#include "sstream"
using namespace std;
const string MINIMAL = "minimal";
const string URGENT = "urgent";
const string EMERGENCY = "emergency";
const string IMMEDIATE = "immediate";
const int MIN = 4;
const int URG = 3;
const int EMER = 2;
const int IMM = 1;
class Patient
{
public:

    Patient(string = "");
    // Constructor that takes two arguments as string
    // Pre condition: it should be a string
    // Post condition: strings will be initialized

    bool operator < (Patient);
    // Overloaded < operator
    // Pre condition: none
    // Post condition: return true if condition is true else false

    bool operator > (Patient);
    // Overloaded > operator
    // Pre condition: none
    // Post condition: return true if condition is true else false

    void setArrivalOrder(int);
    // setArrivalOrder method
    // Pre condition: order > 0
    // Post condition: arrival order is updated

    string to_string() const;
    // to_string method returns string
    // Pre condition: none
    // Post condition: returns string

    int getArrivalOrder()const;
    // getArrivalOrder method returns arrival order
    // Pre condition: none
    // Post condition: returns arrival order

    int getPriorityCode()const;
    // getPriorityCode method returns Priority Code
    // Pre condition: none
    // Post condition: returns Priority Code

    void setPriorityCode(int);
    // setPriorityCode method sets priorityCode
    // Pre condition: none
    // Post condition: none

    string getName()const;
    // getName method returns name
    // Pre condition: none
    // Post condition: returns name

private:
    int arrivalOrder;       // Assigned arrival number
    int priorityCode;      // Patient's assigned priority
    string name;            // Patient's full name
};


Patient::Patient(string name)
{

    this -> name = name;
}


bool Patient::operator < (Patient right) {

    if (this->priorityCode <
        right.priorityCode)
        return true;

    else if (this->priorityCode ==
             right.priorityCode)
        return (this->getArrivalOrder() < right.getArrivalOrder());

    return false;
}
bool Patient::operator > (Patient right) {

    if (this->priorityCode > right.priorityCode)
        return true;

    else if(this->priorityCode == right.priorityCode)
        return (this->getArrivalOrder() > right.getArrivalOrder());

    return false;
}

string Patient::to_string() const {
    stringstream ss;
    string priCode;

    if (getPriorityCode() == IMM)
        priCode = IMMEDIATE;
    else if (getPriorityCode() == URG)
        priCode = URGENT;
    else if (getPriorityCode() == EMER)
        priCode = EMERGENCY;
    else if (getPriorityCode() == MIN)
        priCode = MINIMAL;

    ss << setw(5) << getArrivalOrder() << "           " << left
       << setw(14) << priCode << getName() << "\n";
    return ss.str();
}

void Patient::setArrivalOrder(int order)
{
    arrivalOrder = order;
}

int Patient::getArrivalOrder()const
{
    return arrivalOrder;
}

int Patient::getPriorityCode() const
{
    return priorityCode;
}

void Patient::setPriorityCode(int code)
{
    priorityCode = code;
}

string Patient::getName() const
{
    return name;
}
#endif //P3_PATIENT_H

