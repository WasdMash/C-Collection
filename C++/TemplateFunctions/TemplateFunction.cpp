#include <iostream>
#include <string>

using namespace std;

//Beginning of a template function
    //with a class/type with a variable name
    //As such, this function will work for any data type - ints, strings, etc

    //Here R can be replaced by any type
template<class R>
void print_Array(R *arr, int size){
    for(int i=0;i<size;i++){
        cout << arr[i] << endl;
    }
}
//In practice, during compilation, the compliler will automatically produce type-specific overloads of this function when necessary for us
template<class T>
T maxof(T el, T el2){
    if(el > el2) return el;
    return el2;
}

//We can even use templates in class definitions too
template<class T>
class myClass{
    public:
        T e;
        myclass(T value){
            e = value;
        }

        //Remember that this is a pointer to the current object instantiated from this class
        T getE(){ return this->e;}
};

//We can use two different data types too
template<class T1, class T2>
class myOtherClass{
    public:
        T1 el;
        T2 el2;

        myOtherClass(T1 value1, T2 value2){
            el = value1;
            el2 = value2;
        }
};

int main(){
    int arr[4] = {1,2,3,4};
    string arr2[4] = {"hi","how","are","you"};

    //Now, the same template function works for both arrays of strings and integers
    print_array(arr, 4);
    print_array(arr2, 4);

    float m = maxof(2.2,3.3);
    cout << "Max is: " << m << endl;

    //Some compilers might throw a hissy fit without the explicit class mention inside <>
    myClass<string> mc1("Hi");
    cout << "get value from mc1: " << mc1.getE() << endl;

    myOtherClass<string, int> mc2("Hello", 5);
}