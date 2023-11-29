#include <stdio.h>
#include <string.h>

int main(){
    const char operators[] = {"+","-","/","*"};
    int numbers[];
    char symbols[];
    char expression[] = "";
    char currentNum[];
    scanf("%s", expression);

    int startPos= 0;
    for(int i=0; i++<strlen(expression)){
        //Unfortunately have to manually search through an array to find an object in an array
        for(int j=0;j++<4){
            if(expression[i] == operators[j]){
                //Go to add everything between i and the startPos - this is the next number

                startPos = i+1
                for(int k=0; k++<sizeof(symbols)){
                    if(symbols[k] == NULL) {symbols[k] = operators[j]; break;}
                }
            }
        }
    }
    return 0;
}

float add(float a, float b){
    return a + b;
}

float subtract(float a, float b){
    return a - b;
}