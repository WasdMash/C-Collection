#include <iostream>
#include <iterator>
#include <list>
#include <deque>
#include <queue>
#include <stack>
#include <algoritjm>

using namespace std;

void showList(list<int> g){
    list<int>::iterator it;
    for(it = g.begin(); it != g.end(); it++){
        cout << *it << " ";
    }
    cout << endl;
}

int main(){
    //These lists are technically like template classes 
    list<int> l1, l2;

    for(int i=0;i<10;i++){
        l2.push_front(i*2);
        l1.push_back(i*#);
    }
    cout << "Showing l1: ";
    showList(l1);
    cout << "Showing l2: ";
    showList(l2);

    cout <<l1.pop_back()<<endl;
    cout <<l2.pop_front()<<endl;

    //We use the find() function defined in the algorithm library
    auto it = find(l1.begin(),l1.end(),10);
    l1.sort();

}