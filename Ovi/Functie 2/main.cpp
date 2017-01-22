#include <iostream>
#include <graphics.h>
#include <math.h>
#define PI 3.1415

using namespace std;

double f(int x) {return 5*exp(-0.3*x)+15*exp(-0.1*x)-20*exp(-0.2*x);}

int main(){
    initwindow(1350,700);
    int t[200], r[200], c[400], sx=5, sy=80, k=0;

    for(double i=0.1; i<50; i+=0.5) {
        int x=200+(int)i*sx;
        int y=270+(int)(f(i)*sy);
        t[k++]=x; t[k++]=y;
    }
    int n=k/2;
    //drawpoly(n,t);

    // centru
    int xc=0, yc=0;
    for(int i=0; i<n; i++) {
        xc+=t[2*i];
        yc+=t[2*i+1];
    }
    xc/=n; yc/=n;
    circle(xc, yc, 5);

    // rotatia
    double a=PI;
    for(int i=0; i<n; i++) {
        int x=t[2*i], y=t[2*i+1];
        r[2*i]  = xc+(x-xc)*cos(a)-(y-yc)*sin(a);
        r[2*i+1]= yc+(x-xc)*sin(a)-(y-yc)*cos(a);
    }

    // oglindire
    for(int i=0; i<n; i++) {
        r[2*i+1]= 2*yc-r[2*i+1];
    }
    //drawpoly(n,r);

    for(int i=0; i<n; i++) {
        r[2*i+1]=r[2*i+1]-200;
    }
    //drawpoly(n,r);

    for(int i=0; i<n; i++){
        c[2*i] = t[2*i];
        c[2*i+1] = t[2*i+1];
        c[2*n+2*i] = r[2*i];
        c[2*n+2*i+1] = r[2*i+1];
    }
    drawpoly(k,c);

    while(!kbhit()){
        for(int i=0; i<k; i++){
            if(kbhit()){exit(0);}
            setcolor(RED);
            circle(c[2*i],c[2*i+1],5);
            delay(50);
            setcolor(BLACK);
            circle(c[2*i],c[2*i+1],5);
        }
    }

    while(!kbhit());
    return 0;
}
