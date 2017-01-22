#include <iostream>
#include <cmath>
#include <graphics.h>

using namespace std;

#define scalX 30
#define scalY 30
#define PI 3.14


struct Node {
    double x;
    double fx;
    Node *next;
};

double f(double x) {
    //return pow(x,3) + pow(x,2);
    return pow(x,2);
}
int main () {

    Node *root = new Node();
    Node *it = root;
    for (double x = -2; x<=2; x=x+0.1) {
        it->x = x;
        it->fx = f(x);
        if (x+0.1 == 50) {
            it->next = NULL;
        } else {
            it->next = new Node();
            it = it->next;
        }
    }

    int i;
    double x,y;
    initwindow(640,480);
    setcolor(GREEN);
    moveto(150, 420);
    lineto(150,100);
    linerel(-3,10);
    moverel(3,-10);
    linerel(3,10);
    moveto(30, 300);
    lineto(600,300);
    linerel(-10,3);
    moverel(10,-3);
    linerel(-10,-3);

    setcolor(CYAN);


    it = root;
    x = -2;
    moveto( 150+(int)(x*scalX), 300-(int)((f(x)*scalY)) );
    while (it->next != NULL) {
        Node *nodeToDelete = it;
        lineto( 150+(int)((it->x)*scalX), 300-(int)((it->fx)*scalY) );
        cout<<it->x<<" "<<it->fx<<endl;
        it = it->next;
        //delete nodeToDelete;
    }

    setcolor(RED);
    it = root;
    moveto( 150+(int)(x*scalX), 300-(int)(((-2) * f(x)*scalY)) );
    while (it->next != NULL) {
        Node *nodeToDelete = it;
        lineto( 150+(int)((it->x)*scalX), 300-(int)(((-2) * it->fx)*scalY) );
        //cout<<it->x<<" "<<it->fx<<endl;
        it = it->next;
        delete nodeToDelete;
    }


    while (!kbhit());
    return 0;
}
