#include <set>
#include <iterator>
#include <iostream>
#include <algorithm> //set_intersection is found in this

using namespace std;

int main(){
    set<int> s1;

    s1.insert(10);
    s1.insert(20);
    s1.insert(30);
    s1.insert(40);

    set<int> s2;
    s1.insert(40);
    s1.insert(50);
    s1.insert(60);
    s1.insert(10);
    //inserter function helps me to store the output of my intersection function
    set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(), inserter(s2, s2.begin()));

    set<int> s3;
    set_union(s1.begin(), s1.end(), s2.begin(), s2.end(), inserter(s3, s3.begin()));

    //Multi sets are like sets which we can get repeated elemnents in union operations
    multiset<int> multi_1;
}