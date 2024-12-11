#include <iostream>
#include <string>

using namespace std;

class Base{
    private:
        int b;
    public: 
        Base():b(0){ }; //default constructor - b defaults to 0
        Base(int i): b(i) {} //General constructor
        Base(const Base &clone):b(clone.b) {} // Copy constructor
        ~Base(){}; //Destructor

        //Clone function - not necessary
        Base* clone() const {return new Base(*this);}

        //Not necessary
            //virtual - only applicable for dynamic binding
            //This method shouldn't be used for any dynamic binding situation
            //Only the case class hsold be used when objects of this class only call it, forcing the dynicamlly binded child classes to use their overloaded versions of this function
        virtual string name() const {return string("Base" + to_string(b));}
};

//This derived class inherits from the base class
    //However, I'll need to define the privileges from this inheritance
        //E.g all stuff from the superclass is public to the derived class and accessible to outside class referring to the class
        //It can also be private or protected
class DerivedClass : private Base{
    //Although this class inherits from Base, we cannot access the Base functions from outside the class as we use private inheritance here
    private:
        int d1;
    public:
    //I have to allocate space for memory for super class which this inherits from too by calling the consutrctor
        DerivedClass():Base(), d1(0) {} //Default constructor
        DerivedClass(int i): Base(i), d1(i) { } //General constructor
        DerivedClass(const DerivedClass &clone): Base(clone), d1(clone.d1){ } // COpy constructor
        ~DerivedClass(){};

        //Have to make a function override to use name()
        string name() const {return string("Private derived " + to_string(d1));}

};

class DerivedClass2 : public Base{
    private:
        int d2;
    public:
    //I have to allocate space for memory for super class which this inherits from too by calling the consutrctor
        DerivedClass2():Base(), d2(0) {} //Default constructor
        DerivedClass2(int i): Base(i), d2(i) {} //General constructor
        DerivedClass2(const DerivedClass2 &clone): Base(clone), d2(clone.d2){} // COpy constructor
        ~DerivedClass2(){};

        //Function overriding
        string name() const {return string("Derived class 2 - " + to_string(d2));}
};

int main(){
    Base daBased(13);
    DerivedClass firstInherit(4);
    DerivedClass2 inherited2(21);

    cout << "The name of the firs inherited class is " << daBased.name() << endl;
    //Can't use public functions from privately inheriting classes
    //cout << firstInherit.name() << endl;
    cout << "The name of the second inherited class is " <<inherited2.name() << endl;

    //Pointers in inheritance can be handled fine when the type of binding is already set - static or dynamic
    Base* basePointer;
    basePointer = &inherited2;
    //Returns the values of the base as the superclass definition for name is being called - static binding
    cout << "The name of my pointed class object is " <<basePointer->name() << endl;

    //This exists but is inaccessible due to the private inheritance
    DerivedClass* p1 = new DerivedClass(123);
    Base* p2 = new DerivedClass2(2232);

    cout << "\nObject list \n"<< p2->name() << endl;

    //Dynamic allocation using inheritance
    Base* p22 = p2->clone();
    cout << "Derived Class2 object comparison: " << endl
        << "Object address:" << p2
        << "\nClone address:" << p22
        << "\nObject Class name:" << p2->name()
        << "\nClone Class name:" << p2->name() << endl;
}