•	#include <windows.h>
•	#include <GL/glut.h>
•	#include <stdlib.h>
•	#include <math.h>
•	#include <stdio.h>
•	/*
•	 * GLUT Shapes Demo
•	 *
•	 * Written by Nigel Stewart November 2003
•	 *
•	 * This program is test harness for the sphere, cone
•	 * and torus shapes in GLUT.
•	 *
•	 * Spinning wireframe and smooth shaded shapes are
•	 * displayed until the ESC or q key is pressed.  The
•	 * number of geometry stacks and slices can be adjusted
•	 * using the + and - keys.
•	 */
•	
•	/*#ifdef __APPLE__
•	#include <GLUT/glut.h>
•	#else
•	#include <GL/glut.h>
•	#endif
•	
•	#include <stdlib.h>
•	
•	static int slices = 16;
•	static int stacks = 16;
•	*/
•	
•	
•	/* GLUT callback Handlers */
•	
•	inline int round (const float a) {return int (a+0.5);}
•	
•	void SetPixel(GLint x, GLint y)
•	{
•	    glBegin(GL_POINTS);
•	    glVertex2i(x,y);
•	    glEnd();
•	}
•	
•	void LineDDA(int x0, int y0, int xEnd, int yEnd)
•	{
•	    int dx = xEnd-x0, dy = yEnd-y0, steps, k;
•	    float xIncrement, yIncrement, x=x0, y=y0;
•	
•	    if(fabs(dx)>fabs(dy))//斜率小于等于1，则以X为间隔
•	        steps = fabs(dx);
•	    else
•	        steps = fabs(dy);
•	    xIncrement = float(dx) / float(steps);
•	    yIncrement = float(dy) / float(steps);
•	
•	    SetPixel(round(x),round(y));
•	    for(k=0;k<steps;k++)
•	    {
•	        x += xIncrement;
•	        y += yIncrement;
•	        SetPixel(round(x),round(y));
•	    }
•	}
•	
•	
•	void init (void)
•	{
•	    glClearColor (1.0, 1.0, 1.0, 0.0);  // 指定清空颜色（背景色）为白色
•	    gluOrtho2D (0.0, 200.0, 0.0, 150.0);   //指定二维坐标系中被显示的区域
•	}
•	
•	void display(void)
•	{
•	    glClear (GL_COLOR_BUFFER_BIT);  // 清空显示窗口
•	    glColor3f (0.0, 0.0, 1.0);
•	    LineDDA(10,15,180,100);
•	    LineDDA(160,10,10,130);
•	    glFlush();
•	}
•	int main(int argc, char** argv)
•	{
•	    glutInit(&argc, argv);
•	    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
•	    glutInitWindowPosition(50,100);
•	    glutInitWindowSize(400,300);
•	    glutCreateWindow("DDA Line");
•	    init();
•	    glutDisplayFunc(display);
•	    glutMainLoop();
•	    return 0;
•	}
