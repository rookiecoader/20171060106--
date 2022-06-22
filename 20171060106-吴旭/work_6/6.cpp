#include<Windows.h>
#include<GL/glut.h>
#include<math.h>
#include<iostream>
#include<stdlib.h>
#define PI acos(-1)
using namespace std;
GLsizei winWidth = 500, winHeight = 500;
GLuint regHex;//显示表标识
class wcPt2D
{
public:
	GLfloat x, y;
	wcPt2D(GLfloat x=0,GLfloat y=0)
	{
		this->x = x;
		this->y = y;
	}
};
wcPt2D verts[4] = { wcPt2D(80.0, 80.0), wcPt2D(80.0, 200.0),wcPt2D(200.0, 200.0), wcPt2D(200, 80.0)};
GLfloat sx; GLfloat sy;//缩放系数
GLfloat xr; GLfloat yr;//基准点
GLdouble theta;//旋转角度

GLfloat tx; GLfloat ty;
void Move(wcPt2D *verts,GLfloat tx,GLfloat ty)
{
	//平移函数，作为例子平移四边形
	GLint nverts = 4;
	GLint k;
	wcPt2D newVerts[4];//使用一个新的顶点对象集，方便观察平移效果
	for (k = 0; k < nverts;++k)
	{
		newVerts[k].x = verts[k].x + tx;
		newVerts[k].y = verts[k].y + ty;
	}

	glBegin(GL_QUADS);
	for (k = 0; k < nverts; ++k)
	{
		glVertex2f(verts[k].x, verts[k].y);
	}
	for (k = 0; k < nverts; ++k)
	{
		glVertex2f(newVerts[k].x, newVerts[k].y);
	}
	glEnd();

	glFlush();
}
void rotate(wcPt2D *verts,GLfloat xr,GLfloat yr,GLdouble theta)
{
	//旋转函数，作为例子平移四边形
	GLint nverts = 4;
	GLint k;
	wcPt2D newVerts[4];//使用一个新的顶点对象集，方便观察平移效果
	for (k = 0; k < nverts;++k)
	{
		newVerts[k].x = xr + (verts[k].x - xr)*cos(theta) - (verts[k].y - yr)*sin(theta);
		newVerts[k].y = yr + (verts[k].x - xr)*sin(theta) + (verts[k].y - yr)*cos(theta);
	}

	glBegin(GL_QUADS);
	for (k = 0; k < nverts; ++k)
	{
		glVertex2f(verts[k].x, verts[k].y);
	}
	for (k = 0; k < nverts; ++k)
	{
		glVertex2f(newVerts[k].x, newVerts[k].y);
	}
	glEnd();

	glFlush();
}
void scale(wcPt2D *verts,GLfloat sx,GLfloat sy)
{
	//缩放函数，作为例子平移四边形
	GLint nverts = 4;
	wcPt2D fixedPt = verts[0];//选择左下的点作为基准点
	GLint k;
	wcPt2D newVerts[4];//使用一个新的顶点对象集，方便观察平移效果
	for (k = 0; k < nverts;++k)
	{
		newVerts[k].x = verts[k].x*sx+fixedPt.x*(1-sx)+200;//加200是为了水平平移200个像素，方便比较
		newVerts[k].y = verts[k].y*sy + fixedPt.y*(1 - sy);
	}

	glBegin(GL_QUADS);
	for (k = 0; k < nverts; ++k)
	{
		glVertex2f(verts[k].x, verts[k].y);
	}
	for (k = 0; k < nverts; ++k)
	{
		glVertex2f(newVerts[k].x, newVerts[k].y);
	}
	glEnd();

	glFlush();
}
void funcscale()
{
	glClear(GL_COLOR_BUFFER_BIT);
	scale(verts,sx,sy);
}

void funcrotate()
{
	glClear(GL_COLOR_BUFFER_BIT);
	rotate(verts,xr,yr,theta);
}

void funcPlot()
{
	glClear(GL_COLOR_BUFFER_BIT);
	Move(verts,tx,ty);
}

static void init(void)
{
	//初始化函数，并加入表

	glClearColor(1.0, 1.0, 1.0, 0.0);//设置为白色背景
	regHex = glGenLists(1);//获得一个标识
	glColor3f(0.0, 0.0,0.0);
	glPointSize(2);


}



void winReshapeFcn(int newWidth, int newHeight)
{
	//窗口重定形函数
	//glColor3f(1.0, 0.0,0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();//将当前的用户坐标系的原点移到了屏幕中心：类似于一个复位操作
	gluOrtho2D(0.0, (GLdouble)newWidth, 0.0, (GLdouble)newWidth);
	glClear(GL_COLOR_BUFFER_BIT);


} int main(int argc, char**argv)
{
    int i,t;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Example");
	cout <<"平移请按1，旋转请按2，缩放请按3："<< endl;
	cin >> i;
	if(i==1)
	{
	    cout << "输入x,y偏移量（范围为0-200,0-200)：" << endl;
	    cin >> tx >> ty;
	    init();
	    glutDisplayFunc(funcPlot);
	}
	else if(i==2)
    {
        cout << "输入x,y基准点（范围为0-200,0-200)：" << endl;
	    cin >> xr >> yr;
	    cout << "输入旋转角度：" << endl;
	    cin >> t;
	    theta = t*(PI/180);
	    init();
	    glutDisplayFunc(funcrotate);
    }
    else
    {
        cout << "输入缩放系数：" << endl;
	    cin >> sx >> sy;
	    init();
	    glutDisplayFunc(funcscale);
    }
	glutReshapeFunc(winReshapeFcn);
	glutMainLoop();
	return 0;
}
