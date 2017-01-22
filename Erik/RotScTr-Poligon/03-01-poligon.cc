#include <cmath>
#include <graphics.h>
#include <iostream>

#define PI 3.14
using namespace std;

int N = 4;
int main()
{

    int a[] = {120,120, 160,120, 160,160, 120,160, 120,120}; ///coordonate dreptunghi
    initwindow(800,600);

    drawpoly(5,a);

    //translatie
    int tx = 230, ty = 170;
    for(int i=0;i<N+1;i++){
            a[2*i] = a[2*i] + tx;
            a[2*i+1]= a[2*i+1] + ty;
    }
    drawpoly(5,a);

    // centru de greutate
    double xc=0, yc=0;
    for(int i=0;i<N;i++){
            xc += a[2*i];
            yc += a[2*i+1];
    }
    xc/=N;yc/=N;

    //scalare
    tx = ty = 0;
    double Xc = xc+tx, Yc=yc+ty;
    double Sx=2.5, Sy=2.5;
    for(int i=0;i<N+1;i++){
            a[2*i]   = Xc + (-Xc+a[2*i])   * Sx;
            a[2*i+1] = Yc + (-Yc+a[2*i+1]) * Sy;
    }
    drawpoly(N+1,a);

    //rotire
    double cosa = cos(PI/4), sina = sin(PI/4);
    for(int i=0;i<N+1;i++){
            double xi,yi;
            xi = a[2*i];
            yi = a[2*i+1];
            a[2*i]   = Xc + (xi-Xc)*cosa - (yi-Yc)*sina;
            a[2*i+1] = Yc + (xi-Xc)*sina + (yi-Yc)*cosa;
    }

    setcolor(CYAN);
    drawpoly(N+1,a);

    while(!kbhit());

    closegraph();
	return 0;
}





