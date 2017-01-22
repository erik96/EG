#include <iostream>
#include <graphics.h>
#include <math.h>

using namespace std;

int xmin=120, ymin=110, xmax=360, ymax=280;

int codif(int x, int y)
{
    int cod;
    cod=(x < xmin) ? 1:0;
    if(x > xmax) cod=2;
    if(y < ymin) cod |=4;
    if(y > ymax) cod |=8;
    return cod;
}

int CohenSutherland(int x1i,int y1i,int x2i,int y2i,int* x1d,int* y1d, int* x2d,int* y2d)
{
    int acceptat,rejectat,vertical;
    float m, x1=x1i, y1=y1i, x2=x2i, y2=y2i;
    int cod1,cod2;
    float t;
    acceptat=rejectat=vertical=0;
    if (x1i != x2i)
        m=(y2-y1)/(x2-x1);
    else
        vertical=1;
    do
    {
        cod1=codif((int)x1,(int)y1);
        cod2=codif((int)x2,(int)y2);
        if(cod1==0 && cod2==0)
        {
            acceptat=1;
            break;
        }
        if((cod1 & cod2) !=0 )
        {
            rejectat=1;
            break;
        }
        if(cod1==0)
        {
            t=x1;
            x1=x2;
            x2=t;
            t=y1;
            y1=y2;
            y2=t; //inversare capete
            cod1=cod2;
        }
        if(cod1 & 1)
        {
            y1+=(xmin-x1)*m;
            x1=xmin;
        }
        else if(cod1 & 2)
        {
            y1+=(xmax-x1)*m;
            x1=xmax;
        }
        else if(cod1 & 4)
        {
            if (!vertical)
                x1+=(ymin-y1)/m;
            y1=ymin;
        }
        else
        {
            if (!vertical)
                x1+=(ymax-y1)/m;
            y1=ymax;
        }
    }
    while ( acceptat==rejectat);
    if(acceptat)
    {
        *x1d=(int)x1;
        *y1d=(int)y1;
        *x2d=(int)x2;
        *y2d=(int)y2;
        return 1;
    }
    return 0;
}

int main()
{
    int a[]= {2,1, 12,1, 14,3, 1,3, 2,1};
    int b[]= {2,4, 6,9, 6,4, 2,4};
    int c[]= {12,4, 7,4, 7,11, 12,4};

    initwindow(800,800);

    int xc = 0, yc = 0;

    for (int i=0; i<5; i++)
    {
        a[2*i] = 100 + a[2*i]*9;
        a[2*i+1] = 100 - a[2*i+1]*9;
        xc+=a[2*i];
        yc+=a[2*i+1];
    }

    for (int i=0; i<4; i++)
    {
        b[2*i] = 100 + b[2*i]*9;
        b[2*i+1] = 100 - b[2*i+1]*9;
        xc+=b[2*i];
        yc+=b[2*i+1];
    }

    for (int i=0; i<4; i++)
    {
        c[2*i] = 100 + c[2*i]*9;
        c[2*i+1] = 100 - c[2*i+1]*9;
        xc+=c[2*i];
        yc+=c[2*i+1];
    }
    xc/=13;
    yc/=13;

    drawpoly(5,a);
    drawpoly(4,b);
    drawpoly(4,c);
    circle(xc,yc,3);

    int xm = 200, XM=600, ym=150, YM=450;
    xmin = xm;
    xmax = XM;
    ymin = ym;
    ymax = YM;
    line(xm,ym,xm,YM);
    line(xm,YM,XM,YM);
    line(XM,YM,XM,ym);
    line(XM,ym,xm,ym);

    int xo = xm + (XM-xm)/2;
    int yo = ym + (YM-ym)/2;

    circle(xo,yo,3);
    int dx = xo - xc;
    int dy = yo - yc;

    // translatia
    for(int i=0; i<5; i++)
    {
        a[2*i] += dx;
        a[2*i+1] += dy;
    }
    for(int i=0; i<4; i++)
    {
        b[2*i] += dx;
        b[2*i+1] += dy;
    }
    for(int i=0; i<4; i++)
    {
        c[2*i] += dx;
        c[2*i+1] += dy;
    }

    // oglindirea
    for(int i=0; i<5; i++)
    {
        a[2*i] = 2*xo - a[2*i];
    }
    for(int i=0; i<4; i++)
    {
        b[2*i] = 2*xo - b[2*i];
    }
    for(int i=0; i<4; i++)
    {
        c[2*i] = 2*xo - c[2*i];
    }

    // rotatia
    double alfa = 3.1415/8;
    for(int i=0; i<5; i++)
    {
        int xi = a[2*i], yi = a[2*i+1];
        a[2*i]   = xo + (xi-xo) * cos(alfa) - (yi-yo) * sin(alfa);
        a[2*i+1] = yo + (xi-xo) * sin(alfa) + (yi-yo) * cos(alfa);
    }

    for(int i=0; i<4; i++)
    {
        int xi = b[2*i], yi = b[2*i+1];
        b[2*i]   = xo + (xi-xo) * cos(alfa) - (yi-yo) * sin(alfa);
        b[2*i+1] = yo + (xi-xo) * sin(alfa) + (yi-yo) * cos(alfa);
    }

    for(int i=0; i<4; i++)
    {
        int xi = c[2*i], yi = c[2*i+1];
        c[2*i]   = xo + (xi-xo) * cos(alfa) - (yi-yo) * sin(alfa);
        c[2*i+1] = yo + (xi-xo) * sin(alfa) + (yi-yo) * cos(alfa);
    }
    drawpoly(5,a);
    drawpoly(4,b);
    drawpoly(4,c);

    // scalarea
    int sc = 4;
    for(int i=0; i<5; i++)
    {
        a[2*i]= xo + (a[2*i]-xo)*sc;
        a[2*i+1]= yo + (a[2*i+1]-yo)*sc;
    }
    for(int i=0; i<4; i++)
    {
        b[2*i] = xo + (b[2*i]-xo)*sc;
        b[2*i+1] = yo + (b[2*i+1]-yo)*sc;
    }
    for(int i=0; i<4; i++)
    {
        c[2*i]= xo + (c[2*i]-xo)*sc;
        c[2*i+1]= yo + (c[2*i+1]-yo)*sc;
    }

    for(int i=0; i<4; i++)
    {
        int x1,y1,x2,y2;
        CohenSutherland(a[2*i],a[2*i+1],a[2*i+2],a[2*i+3],&x1,&y1,&x2,&y2);
        line(x1,y1,x2,y2);
    }
    for(int i=0; i<3; i++)
    {
        int x1,y1,x2,y2;
        CohenSutherland(b[2*i],b[2*i+1],b[2*i+2],b[2*i+3],&x1,&y1,&x2,&y2);
        line(x1,y1,x2,y2);
    }
    for(int i=0; i<3; i++)
    {
        int x1,y1,x2,y2;
        CohenSutherland(c[2*i],c[2*i+1],c[2*i+2],c[2*i+3],&x1,&y1,&x2,&y2);
        line(x1,y1,x2,y2);
    }

    while(!kbhit());
    return 0;
}
