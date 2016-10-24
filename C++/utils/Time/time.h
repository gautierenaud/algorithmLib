#ifndef _TIME_H_
#define _TIME_H_

#include <iostream>
#include <sys/time.h>

class Chrono{
    private:
        struct timeval start, end;
    public:
        Chrono();
        ~Chrono();

        // put actual time in start
        void startChrono();
        // put actual time in end
        void stopChrono();
        // diff between the two times
        double getEllapsedMillis();
};

Chrono::Chrono(){
}

Chrono::~Chrono(){
}

void Chrono::startChrono(){
    gettimeofday(&start, NULL);
}

void Chrono::stopChrono(){
    gettimeofday(&end, NULL);
}

double Chrono::getEllapsedMillis(){
    struct timeval t;
    t.tv_sec = end.tv_sec - start.tv_sec;
    t.tv_usec = end.tv_usec - start.tv_usec;

    return t.tv_sec + t.tv_usec/1000000.0f;
}

#endif
