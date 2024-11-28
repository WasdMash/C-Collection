#include <map>
#include <iterator>
#include <iostream>

using namespace std;

template<class T1, class T2>
void printMap(map<T1, T2>){
    typename map<T1, T2>::iterator it;
    for(it = mp.begin();it!=mp.end();it++){
        //it->first gets the value of the id of this map variable as indicated by the it pointer
        cout << "\t " << it->first << "\t" << it->second << endl;
    }
}

int main(

    //In the form of <id,value>
    map<int,int> mp1;
    mp1[10] = 2;
    mp1[2] = 4;

    //Inserting values into the map with an id of i and value of i*10
    for(int i=1;i<11;i++){
        mp1.insert(pair<int,int>(i,i*10));
    }
    mp1.erase(10);

    cout << mp1[3] << endl;
)