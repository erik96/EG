#include <graphics.h>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <iostream>

using namespace std;

void waitForLeftMouseClick() {
    clearmouseclick(WM_LBUTTONDOWN);
    const int DELAY = 50; // Milliseconds of delay between checks
    int x, y;
    while (!ismouseclick(WM_LBUTTONDOWN))
        delay(DELAY);
    getmouseclick(WM_LBUTTONDOWN, x, y);
}

typedef struct Puncte {
    float x,y;
    struct Puncte *urm;
};

struct point { float x; float y; };
// simple linear interpolation between two points
void lerp(point& dest, const point& a, const point& b, const float t) {
dest.x = a.x + (b.x-a.x)*t; dest.y = a.y + (b.y-a.y)*t;
}

// evaluate a point on a bezier-curve. t goes from 0 to 1.0
void bezier(point &dest, const point& a, const point& b, const point& c, const point& d, const float t) {
    point ab,bc,cd,abbc,bccd;
    lerp(ab, a,b,t);
    lerp(bc, b,c,t);
    lerp(cd, c,d,t);
    lerp(abbc, ab,bc,t);
    lerp(bccd, bc,cd,t);
    lerp(dest, abbc,bccd,t);
}

int main() {
    initwindow(450,300);
    point a = { 40, 100 }; point b = { 40, 20 };
    point c = { 150, 90 }; point d = { 200, 90 };

    float x,y;

    point p;

    Puncte *r,*primul,*q,*primulCp;
    primul= new Puncte;

    float t = static_cast<float>(0)/99.0;
    bezier(p,a,b,c,d,t);
    putpixel(p.x, p.y, BLUE);

    primul->x=p.x;
    primul->y=p.y;
    primul->urm=NULL;

    q=primul;

    for (int i=1; i<100; ++i) {
        float t = static_cast<float>(i)/99.0;
        bezier(p,a,b,c,d,t);
        putpixel(p.x, p.y, BLUE);
        r=new Puncte;
        r->x=p.x;
        r->y=p.y;
        r->urm=q;
        primul=r;
        q=r;
    }

    x=r->x;
    y=r->y;

    primulCp=primul;

    q=r;

    while(primulCp){
        r=new Puncte;
        r->x=2*x-primulCp->x;
        r->y=primulCp->y;
        r->urm=q->urm;
        q->urm=r;
        primulCp=primulCp->urm;
    }

    /*r=primul;
    while(r) {
        cout<<r->x<<" "<<r->y<<endl;
        putpixel(r->x, r->y, BLUE);
        r=r->urm;
    }*/

    primulCp=primul;

    q=r;

    while(primulCp){
        r=new Puncte;
        r->x=primulCp->x;
        r->y=2*y-primulCp->y;
        r->urm=q->urm;
        q->urm=r;
        primulCp=primulCp->urm;
    }

    r=primul;
    while(r) {
        cout<<r->x<<" "<<r->y<<endl;
        putpixel(r->x, r->y, CYAN);
        r=r->urm;
    }

    waitForLeftMouseClick();
    return 0;
}

