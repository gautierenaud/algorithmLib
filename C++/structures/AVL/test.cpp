#include <iostream>
#include "intUtils.h"
#include "avl.h"
#include "time.h"

#define NUM 10000

using namespace std;

void printTree(Avl<int> tree){
    
}


int main(int argc, char* argv[]){
    Avl<int> testAvl;
    Chrono insertion, deleteMin, deleteMax, getSorted;

    // inserting time
    insertion.startChrono();
    for (int i = 0; i < NUM; i++){
        testAvl.insert(i);
    }
    insertion.stopChrono();

    // deleting Min time
    int answer;
    deleteMin.startChrono();
    for (int i=0; i < NUM; i++){
        if (!testAvl.removeMin(&answer))
            exit(-1);
    }
    deleteMin.stopChrono();

    // deleting Max time
    for (int i=0; i < NUM; i++){
        testAvl.insert(i);
    }
    deleteMax.startChrono();
    for (int i=0; i < NUM; i++){
        if (!testAvl.removeMax(&answer))
            exit(-1);
    }
    deleteMax.stopChrono();

    for (int i = 0; i < NUM; i++){
        testAvl.insert(i);
    }
    getSorted.startChrono();
    vector<int> sortedList = testAvl.getSortedArray();  
    getSorted.stopChrono();

    cout<<"insertion : "<<insertion.getEllapsedMillis()<<" s"<<endl;
    cout<<"deleteMin : "<<deleteMin.getEllapsedMillis()<<" s"<<endl;
    cout<<"deleteMax : "<<deleteMax.getEllapsedMillis()<<" s"<<endl;
    cout<<"getSorted : "<<getSorted.getEllapsedMillis()<<" s"<<endl;
}
