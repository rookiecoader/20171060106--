#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>


void SetPixel(GLint x, GLint y)
{
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
}

void lineBres(int x0, int y0, int xend, int yend)
{
    int dx = fabs(xend-x0), dy = fabs(yend-y0);//fabs用于求双精度浮点数的绝对值
    int p = 2*dy-dx;//初始决策参数的值
    int twody = 2*dy, twodyminusdx = 2*(dy-dx);
    int x,y;

    if(x0 > xend)
    {
        x = xend;
        y = yend;
        xend = x0;
    }
    else
    {
        x = x0;
        y = y0;
    }

    SetPixel(x,y);

    while(x<xend)
    {
        x++;
        if(p<0)
            p+=twody;
        else
        {
            y++;
            p+=twodyminusdx;
        }

        SetPixel(x,y);
    }
}

void init (void)
{
    glClearColor (1.0, 1.0, 1.0, 0.0);  // 指定清空颜色（背景色）为白色
    gluOrtho2D (0.0, 200.0, 0.0, 150.0);   //指定二维坐标系中被显示的区域
}
void display(void)

{
    glClear (GL_COLOR_BUFFER_BIT);  // 清空显示窗口
    glColor3f (0.0, 0.0, 1.0);
    lineBres(10,15,180,50);
    //lineBres(160,10,10,130);
    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(50,100);
    glutInitWindowSize(400,300);
    glutCreateWindow("bresen Line");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
