#include <cstudio>
#include <vector>
#include <iostream>
#include <algorithm> // sort, find, for_each
#include <numeric> // acummulate

using namespace std;

//This is me basically re-writing how I define classes in this code for pure convenience
    //Basically, I can replace vector<int>::iterator with VIT everywhere in my code
typedef vector<int>::iterator VIT;
typedef vector<int>::reverse_iterator VRIT;

//Creating a template function
template<class T>
void printvec(vector<T> v){
    cout << '<' ;
    //Creating a iterator which can nicely handle the vector
        //Typename is used as a placeholder for a variable of an unknown class undefined until runtime, similar to typedef
            //In this case, it's unknown because the T class is unknown until the time of compilation
    typename vector<T>::const_iterator it = v.begin();
    while(it != v.end()){
        cout << *it;
        if(++it != v.end()) cout << ' ';
    }
    cout << '>' << endl;
}

int multiplication(int i){
    cout << i*2 << endl;
}

int multi(int x, int y){
    return x*y;
}

int main(){
    vector<int> v1;
    v1.push_back(30);
    v1.push_back(7);
    printvec(v1);

    vector<string> v2 = {"Yo","what","is","good","my","homie"};
    printvec(v2);

    //Algorithms time, I guess
        //Printing the sorted v1 vector
    sort(v1.begin(), v1.end());
    printvec(v1);

    //Printing the sorted v2 vector
        //It'll be in reverse order if I use the rbegin() and rend()
    sort(v2.rbegin(), v2.rend());
    printvec(v2);

    //Searching through v1 from the start to the end, trying to find 7
        //It should return the ierator. If not, I can just use auto here to be safe
    auto foundItem = find(v1.begin(), v2.end(), 7);

    string s = "Hey, dude. How are you doing?";
    string::iterator period = find(s.begin(), s.end(), '.');

    //Using for_each to run a function for each value in a iterable
        //In this case, I'm using multiplication for each value
        //However, this only works for procedures with no return value
    vector<int> v3 = {1,2,3,4,5};
    for_each(v3.begin(), v3.end(), multiplication);
    printvec(v3);

    int sum = 0;
    //From te start to end of v3, I will sum up the values of this accumulation and add them in the sum variable
    cout << " Accumulate example: " << accumulate(v3.begin(), v3.end(), sum) << endl;

    //I'll need to add another function on the end to do multpilication here
    int multivar = 1;
    cout << accumulate(v3.begin(), v3.end(), multivar, multi) << endl;
}