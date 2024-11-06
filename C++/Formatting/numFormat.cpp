#include <iostream>
#include <string>
//New libraries for handling numbers
#include <iomanip> 
#include <bitset>

using namespace std;

int main(){
    cout << "Integer formatting: " << endl;
    int i1 = 42;
    int i2 = 127;
    int i3 = 5555;

    cout << "default: " << i1 << " " << i2 << " " << i3 << endl;
    //Prints these numbers as  8-bit numbers
    cout << "bit: " << bitset<8>(i1) << " " << bitset<8>(i2) << " " << bitset<8>(i3) << endl;
    //Prints these numbers as hexadecimals
        //Everything after hex should be converted to a hexadecimal, especially after we've already used the bitset function in code
    cout << "hex: " << hex << i1 << " " << i2 << " " << i3 << endl;

    //Showbase shows the 0x for hex and stuff for others in a nice string
    cout << "hex with showbase: " << showbase << hex << i1 << " " << i2 << " " << i3 << endl;

    //noshowbase removes the shown base from all numbers and dec converts the numbers from this point back to decimals
    cout << "Back to default again: " << noshowbase << dec << i1 << " " << i2 << " " << i3 << endl;
    }