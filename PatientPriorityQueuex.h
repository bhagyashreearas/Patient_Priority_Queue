// Author Name: Bhagyashree Aras
// File name: PatientPriorityQueuex.h
// Date: 3 November 2020
// Purpose: Specification file for PatientPriorityQueuex class.

#include "Patient.h"
#include <cassert>
#include <sstream>
#include <vector>
#include <fstream>


using namespace std;
#ifndef P3X_PATIENTPRIORITYQUEUE_H
#define P3X_PATIENTPRIORITYQUEUE_H


class PatientPriorityQueuex {
public:
    PatientPriorityQueuex();
    // Constructor
    // Pre condition: none
    // Post condition: nextPatientNumber will be 0

    void add(int, string);
    // add method will add patient to vector
    // Pre condition: none
    // Post condition: patients will be added to vector

    void remove();
    // remove method that removes value from vector
    // Pre condition: none
    // Post condition: patient will be removed

    Patient peek() const;
    // peek that takes returns value at index 0
    // Pre condition: none
    // Post condition: value at index 0 will be returned

    string to_string();
    // to_string method returns string
    // Pre condition: none
    // Post condition: returns string

    int size();
    // size that returns size of patient vector
    // Pre condition: none
    // Post condition: size of vector is returned

    bool change(int, int);
    // change that changes priority
    // Pre condition: none
    // Post condition: returns true if changed

    void save(string);
    // save that changes writes to file
    // Pre condition: none
    // Post condition: file is written

private:
    vector<Patient> data;
    int nextPatientNumber;

    void siftUp(int);
    // siftUp that takes int value
    // Pre condition: none
    // Post condition: none

    void siftDown(int);
    // siftDown that takes int value
    // Pre condition: none
    // Post condition: none

    int getParent(int) const;
    // getParent that takes int value of index
    // Pre condition: none
    // Post condition: return index of parent

    int getLeftChild(int) const;
    // getLeftChild that takes int value of index
    // Pre condition: none
    // Post condition: return index of left child

    int getRightChild(int) const;
    // getRightChild that takes int value of index
    // Pre condition: none
    // Post condition: return index of right child

    bool empty() const;
    // empty that checks for empty vector
    // Pre condition: none
    // Post condition: none
};

//*********************
// PUBLIC FUNCTIONS   *
//*********************

PatientPriorityQueuex::PatientPriorityQueuex()
{
    nextPatientNumber = 0;
}

void PatientPriorityQueuex::add(int var, string str)
{
    Patient item(str);
    item.setPriorityCode(var);
    item.setArrivalOrder(nextPatientNumber + 1);
    data.push_back(item);
    siftUp(size() - 1);
    nextPatientNumber++;
}

void PatientPriorityQueuex::remove() {
    assert(!empty());
    data[0] = data[size() - 1];
    data.pop_back();
    if (size() > 1){
        siftDown(0);
    }
}


Patient PatientPriorityQueuex::peek() const {
    assert(!empty());
    return data[0];
}


bool PatientPriorityQueuex::empty() const
{
    return data.size() == 0;
}

bool PatientPriorityQueuex::change(int code, int priCode)
{
    int index = -1;
    for (int i = 0; i < size(); i++) {
        if (data[i].getArrivalOrder() == code) {
            index = i;
        }
    }

    if (index < 0) {
        return false;
    } else {
        if (data[index].getPriorityCode() > priCode) {
            data[index].setPriorityCode(priCode);
            siftUp(index);
        } else if (data[index].getPriorityCode() < priCode) {
            data[index].setPriorityCode(priCode);
            siftDown(index);
        }

        return true;
    }
}

void PatientPriorityQueuex::save(string fileName)
{
    vector<Patient> sorted(data);
    for (int i = 0; i < size() - 1; i++) {
        for (int j = 0; j < size() - 1 - i; j++) {
            if (sorted[j].getArrivalOrder() > sorted[j+1].getArrivalOrder()) {
                // swap
                Patient temp = sorted[j];
                sorted[j] = sorted[j+1];
                sorted[j+1] = temp;
            }
        }
    }

    ofstream ofs;
    ofs.open(fileName);
    string passString;

    for (int i = 0; i < size(); i++) {
        string priCode;
        if (sorted[i].getPriorityCode() == IMM)
            priCode = IMMEDIATE;
        else if (sorted[i].getPriorityCode() == URG)
            priCode = URGENT;
        else if (sorted[i].getPriorityCode() == EMER)
            priCode = EMERGENCY;
        else if (sorted[i].getPriorityCode() == MIN)
            priCode = MINIMAL;

        passString = "add " + priCode + " " + sorted[i].getName();
        ofs << passString << endl;
    }

    ofs.close();
}

//*********************
// PRIVATE FUNCTIONS  *
//*********************

void PatientPriorityQueuex::siftUp(int index) {
    int parentIdx;
    Patient temp;
    if (index != 0) {
        parentIdx = getParent(index);

        if (data[parentIdx] > data[index]) {
            temp = data[parentIdx];
            data[parentIdx] = data[index];
            data[index] = temp;
            siftUp(parentIdx);
        }
    }
}

void PatientPriorityQueuex::siftDown(int index)
{
    int leftIdx, rightIdx, minIdx;
    Patient temp;
    leftIdx = getLeftChild(index);
    rightIdx = getRightChild(index);

    // find minIdx
    if (rightIdx > size() - 1)
    {
        if (leftIdx > size() - 1)
        {
            return;
        }
        else {
            minIdx = leftIdx;
        }
    } else {
        if (data[leftIdx] < data[rightIdx])
        {
            minIdx = leftIdx;
        }
        else {
            minIdx = rightIdx;
        }
    }

    // swap?
    if (data[index] > data[minIdx])
    {
        temp = data[minIdx];
        data[minIdx] = data[index];
        data[index] = temp;
        siftDown(minIdx);
    }
}

int PatientPriorityQueuex::getParent(int index) const
{
    return (index - 1) / 2;
}

int PatientPriorityQueuex::getLeftChild(int index) const
{
    return 2 * index + 1;
}


int PatientPriorityQueuex::getRightChild(int index) const
{
    return 2 * index + 2;
}

int PatientPriorityQueuex::size()
{
    return data.size();
}

string PatientPriorityQueuex::to_string()
{
    stringstream ss;
    for(int i = 0; i < size(); i++)
    {
        ss << data[i].to_string();
    }
    return ss.str();
}
#endif //P3_PATIENTPRIORITYQUEUE_H
