#include <iostream>
#include <string>

using namespace std;

void display(char *c){
    cout << c << endl;
}

int main(){
    string s = "This is a string";
    //Although we start from the beginning of the string
    //cout handles strings and so will keep printing out the following
    //characters past s[0] until a delimiter or EOF is found
    display(&s[0]);
    string s2 = "This is another string";
    //Comparing the strings and adjusting the output using a ternary operator
    cout << "is s == s2: " << (s == s2 ? "yes" : "no") << endl;

    s.insert(5, "X");
    cout << s << endl;

    s.erase(5,3);

    s.replace(5,2,"ain't");

    //size_t can store even the largest int value which can be stored , I think. Double check this

    //Finds the first occurence of s in a string from the front
    size_t pos = s.find("s");

    //Finds the first occurernce of s in a string from the back
    size_t backPOs = s.rfind("s");
    return 0;
}