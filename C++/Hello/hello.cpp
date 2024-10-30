#include <iostream>

using namespace std;

class HelloWorld{
    public:
    void displayHi(){
        // << operator sends values to be output to a stream - can be chained
        cout << endl << "Hello world!" << endl;
    }
}; //Have to use semi-colons in C++ to terminate class definitions

int main(){
   HelloWorld my_hello;
    my_hello.displayHi();

    //ptr is a pointer and the integer value found at this pointer (*ptr) is 10
    int *ptr = new int(10);

    cout << *ptr << endl;
    //ptr will only exist betwween the initialisation and deletion of ptr usually
        //If I try to access this later on, then I'd be accessing something else instead close to the original memeoory location
    delete ptr;

}