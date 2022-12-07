/*

Given a logical address, (p, d), 
write a program to implement paging to transform it into the physical address, (f, d), 
where p is the page number, f is the frame number, and d is the displacement. 
You need to use graphics to show your implementation.

Name : Muniba Rahman
Faculty no. : 20COB275
Sr no. : A3CO-36

**TO BE RUN ON TURBOC**

*/

#include <conio.h>
#include <stdio.h>
#include <graphics.h>
#include <stdlib.h>
#include <iostream.h>

int msize, psize, np;

void drawLM()
{
    int h = msize * 20;
    int y1 = 100, ld = h / np, pd = ld / psize, y2, nline;
    char *text;
    int i;
    int l = 0, nl = 0;
    if (msize % psize == 0)
        nline = np - 1;
    else
        nline = np;
    for (i = 0; i < msize; i++)
    {
        y2 = y1 + pd;
        rectangle(20, y1, 200, y2);
        sprintf(text, "%d", i);
        outtextxy(20 + 10, y1 + 5, text);
        sprintf(text, "%c", 97 + i);
        outtextxy(20 + 110, y1 + 4, text);
        y1 = y2;
        l++;
        if (l == psize && nl != nline)
        {
            nl++;
            setlinestyle(0, 0, 3);
            line(15, y1, 205, y1);
            setlinestyle(0, 0, 0);
            l = 0;
        }
    }
    line(70, 100, 70, y1);
    outtextxy(48, y1 + 5, "Logical Memory");
}

void drawPT(int np)
{
    int y1 = 120, y2;
    char *text;
    int i;
    for (i = 0; i < np; i++)
    {
        y2 = y1 + 25;
        rectangle(250, y1, 400, y2);
        sprintf(text, "%d", i);
        outtextxy(250 + 10, y1 + 10, text);
        y1 = y2;
    }
    line(325, 120, 325, y1);
    outtextxy(290, y1 + 5, "Page Table");
}

void setPT(int *pt, int n)
{
    int i;
    char *text;
    int y1 = 120;
    for (i = 0; i < n; i++)
    {
        sprintf(text, "%d", pt[i]);
        outtextxy(325 + 10, y1 + 10, text);
        y1 += 25;
    }
}

void drawIObox(int io, int num, int disp)
{
    char *text;
    int x1 = 250, y1 = 300, x2 = 400, y2 = 330;
    if (io == 0)
    {
        y1 = y2 + 50;
        y2 = y1 + 30;
    }

    if (io == 1)
        outtextxy(x1 + 37, y1 - 10, "P");
    else if (io == 0)
        outtextxy(x1 + 37, y1 - 10, "F");
    outtextxy(x1 + 112, y1 - 10, "D");
    rectangle(x1, y1, x2, y2);
    sprintf(text, "%d", num);
    outtextxy(x1 + 37, y1 + 10, text);
    line(325, y1, 325, y2);
    sprintf(text, "%d", disp);
    outtextxy(x1 + 112, y1 + 10, text);
    if (io == 1)
        outtextxy(x1 + 10, y2 + 5, "Logical Address");
    else if (io == 0)
        outtextxy(x1 + 10, y2 + 5, "Physical Address");
}

void LMhighlight(int n)
{
    char *text;
    int h = msize * 20;
    int x = 20, ld = h / np, pd = ld / psize, y = 100 + n * pd;
    setfillstyle(SOLID_FILL, BLUE);
    setcolor(WHITE);
    bar(x, y, x + 180, y + pd);
    sprintf(text, "%d", n);
    outtextxy(x + 10, y + 5, text);
    sprintf(text, "%c", 97 + n);
    outtextxy(x + 110, y + 4, text);
}

void PThighlight(int *pt, int n)
{
    char *text;
    int x = 250, y = 120 + n * 25;
    setfillstyle(SOLID_FILL, GREEN);
    setcolor(WHITE);
    bar(x, y, x + 150, y + 25);
    sprintf(text, "%d", n);
    outtextxy(x + 10, y + 10, text);
    sprintf(text, "%d", pt[n]);
    outtextxy(325 + 10, y + 10, text);
}

void drawMM(int p, int f)
{
    int y1 = 15, y2, nline;
    char *text;
    int i;
    int xx = 0;
    if (p * psize >= 28)
    {
        while (1)
        {
            xx = (--p) * psize;
            if (xx < 28)
                break;
        }
    }
    int l = 0;
    if (msize % psize == 0)
        nline = np - 1;
    else
        nline = np;
    for (i = xx; i < xx + 28; i++)
    {
        y2 = y1 + 15;
        rectangle(450, y1, 600, y2);
        if (i == f)
        {
            setfillstyle(SOLID_FILL, RED);
            setcolor(WHITE);
            bar(450, y1, 600, y2);
        }
        sprintf(text, "%d", i);
        outtextxy(450 + 10, y1 + 4, text);
        y1 = y2;
        l++;
        if (l == psize)
        {
            setlinestyle(0, 0, 3);
            line(445, y1, 605, y1);
            setlinestyle(0, 0, 0);
            l = 0;
        }
    }
    line(510, 15, 510, y1);
    outtextxy(468, y1 + 10, "Physical Memory");
}

void setMM(int *pt, int p)
{
    int i, j, xi, x, y, xx;
    char *text;
    int y1 = 15;
    if (p * psize >= 28)
    {
        while (1)
        {
            xx = (--p) * psize;
            if (xx < 28)
                break;
        }
    }
    for (i = 0; i < msize;)
    {
        y1 = 15;
        x = i / psize;
        y = pt[x];
        for (j = xx; j < xx + 28; j++)
        {
            if (j / psize == y)
            {
                sprintf(text, "%c", 97 + (i++));
                outtextxy(550 + 5, y1 + 4, text);
            }
            y1 += 15;
        }
    }
}

int main()
{
    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char *)"");
    cleardevice();
    cout << "Enter the size of logical memory : ";
    cin >> msize;
    cout << "Enter the page size : ";
    cin >> psize;
    if (psize > msize)
    {
        cout << "\n\nInvalid page size!!";
        closegraph();
    }
    np = msize / psize;
    // drawLM();
    // getch();

    initgraph(&gd, &gm, (char *)"");
    cout << "LOGICAL MEMORY SIZE : " << msize << "\tPAGE SIZE : " << psize << endl;
    drawLM();
    int n;
    if (msize % psize == 0)
        n = np;
    else
        n = np + 1;

    int *pt = new int[n];
    int i;
    drawPT(n);
    cout << "\nEnter frame corresponding to page ";
    for (i = 0; i < n; i++)
    {
        cout << "P" << i << " ";
    }
    cout << "respectively :";
    for (i = 0; i < n; i++)
    {
        cin >> pt[i];
    }

    initgraph(&gd, &gm, (char *)"");
    cout << "LOGICAL MEMORY SIZE : " << msize << "\tPAGE SIZE : " << psize << endl;
    drawLM();
    drawPT(n);
    setPT(pt, n);

    int p, d, f;
    cout << "\nEnter the logical address :\n";
    cout << "--Page number : ";
    cin >> p;
    cout << "--Displacement : ";
    cin >> d;
    if (p >= np || d >= psize)
    {
        cout << "\n\nInvalid Page Number or displacement";
        getch();
        closegraph();
    }
    drawIObox(1, p, d);
    LMhighlight(p * psize + d);
    PThighlight(pt, p);
    getch();
    f = pt[p] * psize + d;
    drawIObox(0, f, d);
    /*int max=0;
    for(i=0; i<n; i++)
        if(pt[i]>max)
            max=pt[i];*/
    drawMM(pt[p], f);
    setMM(pt, pt[p]);
    getch();
    closegraph();
    return 0;
}