#include <iostream>
#include <exception>

using namespace std;

//Standard exception classes in C++

/*
    logic error
        invalid_argument
        length_Error
        out_of_range

    runtime_error
        overflow_error
        underflow_error

    other exceptions
        bad_alloc - thrown by "new" when memory allocation fails 
        bad_typeid - thrown when typeid is applied to a null pointer
        bad_cast - thrown by "dynamic_cast" when the cast fails
*/

class Exception{}; //empty class to use as something to handle myClass exceptions
//Written a class which inherits from the base Exception class
class E : public Exception{
    protected:
        const char *msg;
    public:
        E();
        //Have to call throw first as their functionality as exception handling relies on this throe
        E(const char *msg) throw(): msg(msg){}
        const char *what() const throw(){
            return msg;
        }
};
class myClass{
    public:
        myClass(){
            cout << "Constructor" << endl;
        }
        ~myClass() 
        {
            cout << "Destructor" << endl;
            throw Exception;
        }
};

int main(){
    int x = -1;
    cout << "Before error: " << x << endl;
    try{
        //I'm using the throw keyword to manually trigger the catch block
        if(x < 0) throw invalid_argument;
    }
    catch(int x){
        //I can catch anything really - just depends on what was thrown in the try block
        cout << x << endl;
    }
    catch(...){
        //This is built to catch the default exception
        cout << "Default exception" << endl;
    }

    //Basic version of personalised exception class
    try{
        myClass* m = new myClass();
        delete m;
    }
    catch(Exception&){
        //This is the object thrown by the destructor, lol
        cout << "Cool, I threw an emtpy exception class" << endl;
    }

    //Messing with using personalised exception classes
    try{
        throw E("Boy, you goofed up, fr");
    }
    catch(E& e){
        cout << e.what() << endl;
    }
}