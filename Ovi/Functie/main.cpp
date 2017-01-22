#include <iostream>
#include <graphics.h>
#include <math.h>
#define PI 3.1415

using namespace std;

double f(double x) {return 5*exp(-0.3*x)+15*exp(-0.1*x)-20*exp(-0.2*x);}

int main()
{
    initwindow(1200,600);
    setcolor(BLUE);

    int points[200], points2[200], points3[800], k = 0, sx=4, sy=40;

    for(double i=0.1; i<50; i+=0.5) {
        points[k++] = 250 + (int)sx*i;
        points[k++] = 240 + (int)sy*f(i);
    }
    int n=k/2;
    //drawpoly(n,points);

    // rotatie
    double xc = points[0], yc = points[1];
    double alfa = PI;
    for(int i=0; i<n; i++) {
        double x=points[2*i], y=points[2*i+1];
        points2[2*i]   = xc + (x-xc) * cos(alfa) - (y-yc) * sin(alfa);
        points2[2*i+1] = yc + (x-xc) * sin(alfa) + (y-yc) * cos(alfa);
    }
    //drawpoly(n,points2);

    for(int i=0; i<n; i++) {
        points3[2*i] = points2[2*(n-i-1)];
        points3[2*i+1]=points2[2*(n-i-1)+1];
        points3[2*n+2*i] = points[2*i];
        points3[2*n+2*i+1] = points[2*i+1];

    }
    //drawpoly(2*n,points3);

    int dx = points3[k-2] - points3[0];

    for(int i=k,j=0; i<2*k; i++,j++) {
        points3[2*i] = points3[2*j] + 2*dx;
        points3[2*i+1] = points3[2*j+1];
    }
    drawpoly(4*n,points3);


    int cx=0, cy=0;
    for(int i=0; i<2*k; i++) {
        cx+=points3[2*i];
        cy+=points3[2*i+1];

    }
    cx/=2*k;
    cy/=2*k;

    int romb[10], R=10;
    for(int i=0; i<5; i++) {
        double a=2*i*PI/4;
        romb[2*i] = (int)(R*cos(a))+cx;
        romb[2*i+1] = (int)(R*sin(a))+cy;
    }

    setwritemode(XOR_PUT);
    for(int i=k; i<2*k-1; i++) {
        for(int j=0; j<5; j++) {
            romb[2*j]   = romb[2*j] + points3[2*i+2] - points3[2*i];
            romb[2*j+1] = romb[2*j+1] + points3[2*i+3] - points3[2*i+1];
        }
        if(kbhit()) {exit(0);}
        xc = points3[2*i+2];
        drawpoly(5,romb);
        delay(30);
        drawpoly(5,romb);
    }



    while(1) {
        if(kbhit()) {exit(0);}
        for(int i=2*k-1; i>=0; i--) {
            for(int j=0; j<5; j++) {
                romb[2*j]   = romb[2*j] + points3[2*i-2] - points3[2*i];
                romb[2*j+1] = romb[2*j+1] + points3[2*i-3] - points3[2*i-1];
            }
            if(kbhit()) {exit(0);}
            xc = points3[2*i+2];
            drawpoly(5,romb);
            delay(30);
            drawpoly(5,romb);
        }
        for(int i=0; i<2*k-1; i++) {
            for(int j=0; j<5; j++) {
                romb[2*j]   = romb[2*j] + points3[2*i+2] - points3[2*i];
                romb[2*j+1] = romb[2*j+1] + points3[2*i+3] - points3[2*i+1];
            }
            if(kbhit()) {exit(0);}
            xc = points3[2*i+2];
            drawpoly(5,romb);
            delay(30);
            drawpoly(5,romb);
    }


    }


    while(!kbhit());
    return 0;
}
