//Basically a main library we can import in C for basic functionality
#include <stdio.h>
//Annoyingly, you need this library to use booleans
#include <stdbool.h>

//Main is the main function which every executable will run
int main(){
    printf("Hello, world!\n");

    /*
    Format specifiers are used together with the printf() function to tell the compiler what type of data the variable is storing. It is basically a placeholder for the variable value.

    A format specifier starts with a percentage sign %, followed by a character.

    For example, to output the value of an int variable, you must use the format specifier %d or %i surrounded by double quotes, inside the printf() function:
    */

   // Create variables
    const double PI = 3.1415926; //Generally good to put constants in uppercase letters
    int myNum = 15;            // Integer (whole number) - stores 2 or 4 bytes
    float myFloatNum = 5.99;   // Floating point number - stores 4 bytes for storing 6/7 decimal places unless specified otherwise
    double myDoubleNum = 8.70;  // stores 8 bytes for storing 15 decimal places
    char myLetter = 'D';       // Character - stores 1 byte
    bool working = false;

    //Explicit conversion is done manually by placing the type in parentheses () in front of the value.
    myDoubleNum = (double) 8.3;

    // Print variables
    printf("The variable myNum stores the variable: %d and look at the number of decimal places on %.4f \n", myNum, myFloatNum);
    printf("I'm printing the character %c next to the double %lf\n", myLetter, myDoubleNum);

    //Operators
    myNum >>= 3; // >> is the bitwise operator which shifts the bits in the binary representation of the number to the right by n places

    if (myFloatNum < myNum && myLetter == "D" ||!working){
        printf("Hurrah. You can use an if statement.");
        //&& - and; == - equals; || - or; ! - not
    }
    else {
        printf("You somehow botched it");
    }

    //As main is a function, which must return an integer, we can put a placeholder 0 to return to avoid any errors
    return 0;
}
