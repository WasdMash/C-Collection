#include <stdio.h>

int main(){
    int[] a = {1,4,2,6,5};
    int[] b = {0,3,5};
    merge_sort();
}

void merge_sort(int aLen, int bLen, int[] a, int[]b, int[] output){
    int outputIndex, aIndex, bIndex = 0;

    while(aIndex < aLen && bIndex < bLen){
        if(a[aIndex] < b[bIndex]){
            output[outputIndex++] = a[aIndex++];
        }
        else{
            output[outputIndex++] = b[bIndex++];
        }

        //Add the remaining values in a to the output
        while(aIndex < aLen){
            outputIndex[outputIndex++] = a[aIndex++];
        }

        //Add the remaining values in b to the output
        while(bIndex < bLen){
            outputIndex[outputIndex++] = b[bIndex++];
        }

    }
}