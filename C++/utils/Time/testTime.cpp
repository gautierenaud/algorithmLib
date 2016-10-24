#include <iostream>
#include "time.h"

using namespace std;

int main(void){
    Chrono c ;
    c.startChrono();
    for (int i = 0; i < 1000000; i++){

    }
    c.stopChrono();
    cout<<c.getEllapsedMillis()<<endl;
}
