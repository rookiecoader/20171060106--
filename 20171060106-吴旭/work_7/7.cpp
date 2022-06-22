#include<windows.h>
#include<gl/glut.h>
#include<math.h>
#define x_Screen 800
#define y_Screen    600
#define little 50
#define middle 20
#define large   8

void myBackground()
{
glClearColor(0.0,0.0,0.0,1.0);
glColor3f(1.0,1.0,1.0);
}
void myDisplay()
{
glEnable ( GL_DEPTH_TEST );
//如果没有抗锯齿，则点为方形的。如果我们启动抗锯齿设置，则点是一个圆点。
glEnable(GL_POINT_SMOOTH);
glEnable(GL_LINE_SMOOTH);
glHint(GL_POINT_SMOOTH_HINT, GL_NICEST); // Make round points, not square points
glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);  // Antialias the lines
glEnable(GL_BLEND);
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
int i;

glPointSize(8);
glBegin(GL_POINTS);
for(i=0;i<large;i++)
glVertex2f(50.0+rand()%x_Screen,50.0+rand()%y_Screen);
glEnd();


glutSwapBuffers();
}
void myChange(int w,int h)
{
glViewport(0,0,w,h);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluOrtho2D(0.0,x_Screen,0.0,y_Screen);
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
}


int main()
{
glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
glutInitWindowSize(x_Screen,y_Screen);
glutCreateWindow("Star");
glutDisplayFunc(myDisplay);
glutReshapeFunc(myChange);
myBackground();
glutMainLoop();
return 0;
}
