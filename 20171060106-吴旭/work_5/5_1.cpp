#include <windows.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
void init(void)
{
    glClearColor(1.0,1.0,1.0,0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0,800.0,0.0,800.0);
}

int round(const float a)
{
    return int(a+0.5);
}

void putpixel( int x, int y )
{
    glColor3f(0.0, 0.4, 1.0);
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
    glFlush();
}

void circlePoint( int x0, int y0, int x, int y )
{
    putpixel(x0+x,y0+y);
    putpixel(x0+x,y0-y);
    putpixel(x0-x,y0+y);
    putpixel(x0-x,y0-y);
    putpixel(x0+y,y0+x);
    putpixel(x0-y,y0+x);
    putpixel(x0+y,y0-x);
    putpixel(x0-y,y0-x);
}


void circleMidpoint( int x0,int y0,int r )
{
    int d = 1-r;
    int x = 0;
    int y = r;
    circlePoint(x0,y0,x,y);
    while(x<y)
    {
        if (d<0) d+=2*x+3;
        else
        {
            d+=2*(x-y)+5;
            y--;
        }
        x++;
        circlePoint(x0,y0,x,y);
    }
}

void Display(void)
{
    int r=100;
    //printf("r=?\n",r);
    glClear(GL_COLOR_BUFFER_BIT);
    //scanf("%d",&r);
    circleMidpoint(500,500,r);
}

int main(int argc,char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(200,100);
    glutInitWindowSize(360,360);
    glutCreateWindow("中点Bresenham画圆算法");

    init();
    glutDisplayFunc(Display);
    glutMainLoop();

    return 0;
}
