#include <cstudio>
#include <vector>
#include <iostream>

using namespace std;

//This is me basically re-writing how I define classes in this code for pure convenience
    //Basically, I can replace vector<int>::iterator with VIT everywhere in my code
typedef vector<int>::iterator VIT;
typedef vector<int>::reverse_iterator VRIT;

int main(){
    vector<int> v1 = {1,2,3,4,5};
    //These :: help to signal that this'll be an interator
        //The iterator is an interface within the class
    VIT itbegin = v1.begin();
    //This won't result the last value in v1 but rather the value past the last element
        //That's because the function looks for the next thing after each element, even the last one
        //Subtract 1 to get theactual last element in the vector
    VIT itend = v1.end();

    //However, these iterators cannot be easily displayed on the console without dereferencing them
    cout << *itbegin << endl;

    //Startingfrom itbegin, we'll iterate 3 places across the vector/iterable thing
        //auto is a loose defintion of a datatype which can handle all types of returned values/variables
    auto newIterator = next(itbegin, 3);
    //advance() does the same as next but doesn't return the iterator
    advance(itbegin, 1);

    //Goes back 1 place in the iterable
    VIT otherIterator = prev(newIterator, 1);

    //Vectors have a unidirectional iterator by default
        //As such, to reverse, I would have to use a reverse iterator to go backwards
        //Iterating across the whole iterable
    for(VIT i=v1.begin(); i != v1.end(); i++){
        cout << *i << endl;
    }
    //Iterating across the whole iterable using a reverse iterator
    for(VRIT i=v1.rbegin(); i != v1.rend(); i++){
        cout << *i << endl;
    }

    vector<int> v2 = {6,7,8,9,10};
    VIT itv2 = v2.begin();

    //Basically copies all of the values in v1 into v2, starting from the beginning of v2
    copy(v1.begin(), v1.end(), inserter(v2, itv2));

    //To get the values by reference as o[pposed to copying the values in memory, we use the & to get the OG address of each value
    for(int &i2 : v2){
        cout << i2 << endl;
    }

}