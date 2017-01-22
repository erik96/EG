#include <graphics.h>

int xmin=120, ymin=110, xmax=360, ymax=280;
int xi1,yi1,xi2,yi2;

void waitForLeftMouseClick();
int codif(int x, int y);
int CohenSutherland(int x1i,int y1i,int x2i,int y2i,int* x1d,int* y1d, int* x2d,int* y2d);

struct Casa{
    int x,y;
    Casa *next;
};

int main(){
    int x1,y1,x2,y2;
    initwindow(540,480);
    setcolor(GREEN);
    rectangle(xmin,ymin,xmax,ymax);

    Casa *cap,*q,*p;
    cap=new Casa;
    cap->x=140;
    cap->y=300;
    cap->next=NULL;
    p=cap;

    q=new Casa;
    q->x=140;
    q->y=130;
    q->next=NULL;
    p->next=q;
    p=q;

    q=new Casa;
    q->x=240;
    q->y=50;
    q->next=NULL;
    p->next=q;
    p=q;

    q=new Casa;
    q->x=340;
    q->y=130;
    q->next=NULL;
    p->next=q;
    p=q;

    q=new Casa;
    q->x=340;
    q->y=300;
    q->next=NULL;
    p->next=q;
    p=q;

    q=new Casa;
    q->x=320;
    q->y=300;
    q->next=NULL;
    p->next=q;
    p=q;

    q=new Casa;
    q->x=320;
    q->y=260;
    q->next=NULL;
    p->next=q;
    p=q;

    q=new Casa;
    q->x=280;
    q->y=260;
    q->next=NULL;
    p->next=q;
    p=q;

    q=new Casa;
    q->x=280;
    q->y=300;
    q->next=NULL;
    p->next=q;
    p=q;

    p->next=cap;

    p=cap;


    while(p){
        waitForLeftMouseClick();
        CohenSutherland(p->x,p->y,p->next->x,p->next->y,&x1,&y1,&x2,&y2);
        line(x1,y1,x2,y2);
        p=p->next;
    }

    waitForLeftMouseClick();
    line(140,130,340,130);

    while(!kbhit());
    closegraph(); //close graphics window
    return 0;
}

void waitForLeftMouseClick(){
    clearmouseclick(WM_LBUTTONDOWN);
    const int DELAY = 50; // Milliseconds of delay between checks
//int x, y;
    while (!ismouseclick(WM_LBUTTONDOWN))
        delay(DELAY);

}


int codif(int x, int y){
    int cod;
    cod=(x < xmin) ? 1:0;
    if(x > xmax) cod=2;
    if(y < ymin) cod |=4;
    if(y > ymax) cod |=8;
    return cod;
}


int CohenSutherland(int x1i,int y1i,int x2i,int y2i,int* x1d,int* y1d, int* x2d,int* y2d){
    int acceptat,rejectat,vertical;
    float m, x1=x1i, y1=y1i, x2=x2i, y2=y2i;
    int cod1,cod2;
    float t;
    acceptat=rejectat=vertical=0;
    if (x1i != x2i)
    m=(y2-y1)/(x2-x1);
    else
    vertical=1;
    do{
        cod1=codif((int)x1,(int)y1);
        cod2=codif((int)x2,(int)y2);
        if(cod1==0 && cod2==0) { acceptat=1; break;}
        if((cod1 & cod2) !=0 ) { rejectat=1; break;}
        if(cod1==0){
            t=x1;x1=x2;x2=t; t=y1;y1=y2;y2=t; //inversare capete
            cod1=cod2;
        }
        if(cod1 & 1){
            y1+=(xmin-x1)*m;
            x1=xmin;
        }
        else
            if(cod1 & 2){
                y1+=(xmax-x1)*m;
                x1=xmax;}
            else
                if(cod1 & 4){
                    if (!vertical)
                        x1+=(ymin-y1)/m;
                    y1=ymin;
                }
                else{
                    if (!vertical)
                        x1+=(ymax-y1)/m;
                    y1=ymax;
                }
    }while ( acceptat==rejectat);
    if(acceptat){
        *x1d=(int)x1; *y1d=(int)y1;
        *x2d=(int)x2; *y2d=(int)y2;
        return 1;
    }
    return 0;
}




