#include "Manager.h"
#include <iostream>

using namespace std;

// Constructor for the Manager class
Manager::Manager(const string &name, int regNo) : Person(name), name(name), regNo(regNo){}

// Getter for registration number
int Manager::getRegNo() const{
    return regNo;
}

