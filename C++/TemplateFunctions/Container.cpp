#include <iostream>
#include <string>
#include <vector>

using namespace std;

//STL - standard template library

//Sequence containers (vectors, lists, deques)
//Associate containers (sets, maps, hash_maps) - random Access containers where we don't have to loop through the whole thing every time
//Container adaptors (queue, priority queue)

int* add_array_elements(int *array, int size, int newValue){
    //Make a temp array with new size
    int *newArray = new int[size+1];
    //Copy old array to new one
    for(int i=0;i<size;i++){
        newArray[i] = array[i];
    }
    //Add new value
    newArray[size+1] = newValue;
    //As it's in the heap, we can delete the old useless array
    delete [] array;

    return newArray;
}

int main(){
    //Has to be dynamically allocated for this function to like it
    int array = new int[3];

    //The annoying thing about dynamically allocated arrays is that each value has to be manually inserted by code
    array[0] = 1;
    array[1] = 2;
    array[2] = 3;
    array = add_array_elements(array, 3, 10);

    //This creates a 10-unit long vector where each value is 100
    vector<int> myVector(10,100);
    vector<int> otherVector(2,400);

    cout << "size: " << myVector.size() << endl;
    cout << "front: " << myVector.front() << endl;
    cout << "back: " << myVector.back() << endl;
    cout << "Element at 5: " << myVector[5] << endl;
    //This version users an iterator to 'loop' to the index which I want
    cout << "Element at 5: " << myVector.at(5) << endl;

    //Puts stuff at the start of my vector
        //.begin() is an iterator which acts like a pointer to the start of the vector
    myVector.insert(myVector.begin(), otherVector.begin() + 1, otherVector.end());

    myVector.erase(myVector.begin() + 5);

    //Adds value 47 to the back of the vector
    myVector.push_back(47);
    myVector.pop_back();
}