#include <iostream>

using namespace std;

//This is an annoying way of passing arrays by reference
    //We start by passing the address of the first element in the array
void print_array(int (&arr)[5]){
    //sizeof(arr) will give us the size of the whole array but in bytes
        //This sizeOf will throw a hissy fit when the size of an item isn't clearly pre-defined
            //That's what the 5 in the parameters above is doing
    int size = sizeof(arr) / sizeof(arr[0]);
    for(int i=0;i<size;i++){
        cout << arr[i] << " ";
    }
}

//Arrays are like basically already a pointer to a bunch of variables next to each other in memory, so we must deference the array to get the actual values stored in those memory locations
void print_array(char *array, int size){
    for(int i=0;i<size;i++){
        //*(array) starts from the first value of the array and then increments to the next
        cout << array[i] << endl;
    }
    cout << endl;
}

void print_array(string &array, int size){
    for(int i=0;i<size;i++){
        //*(array) starts from the first value of the array and then increments to the next
        cout << array[i] << endl;
    }
    cout << endl;
}

int main(){
    int array[] = {1,2,3,4,5};
    char word[] = {'a','b','c','d','e'};
    print_array(array);
    print_array(word,5);

    int *ptr_array = new int[5];
    //When creating an array from a pointer like this, the values have to be manually set as opposed to the nicer format
    ptr_array[0] = 1;
    ptr_array[1] = 2;
    ptr_array[2] = 3;
    ptr_array[3] = 6;
    ptr_array[4] = 8;

    //Just like before, we can delete the whole array using the array pointer
    delete []ptr_array;
}