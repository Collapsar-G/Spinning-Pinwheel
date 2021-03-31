/*********************************************************************************
  *Copyright(C),None
  *FileName:  OpenGLDemo.cpp
  *Author:  Collapsar-G
  *Version:  1.0.0
  *Date:  2021.3.31
  *Description:  实现了
     1. 构建且渲染一个3D风车模型（如下图所例示）。其中，三个叶片（包括中间的黄色三角形）在一个2D平面上，手柄在另外一个离相机更近的2D平面上。三个叶片、中心的三角形、手柄分别用不同的颜色显示。
     2. 实现风车的旋转动画。要求风车的三个叶片以及中间的黄色三角形（在其所在平面上）一起绕着中心一点不停旋转，且将此动画渲染出来。
     3.	实现通过键盘对动画的交互控制，包括切换旋转方向、增大旋转速度以及减小旋转速度。
     4.	设计按钮和菜单两个控件，用于动画的交互控制：点击按钮可以切换旋转方向；选择三个菜单项分别可以切换旋转方向、增大旋转速度以及减小旋转速度。

  *Others:  转载请备注出处，代码部分参考 https://github.com/Goden-Yang/OpenGL-WindMill
  * function:
    1. 
 
**********************************************************************************/
#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <cmath>
#include <Windows.h>
#include <Gl/glut.h> 
#define MAX_CHAR 128
#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )
using namespace std;

double angle = 0;
double speed = 0.3;
double Acceleration = 0.3;



void reverse()
{
    speed = -speed;
}

void speedUp()
{
    if (speed >= 0)speed += Acceleration;
    else speed -= Acceleration;
}

void speedDown()
{
    if (speed >= 0) speed -= Acceleration;
    else speed += Acceleration;
}

void rotate()
{
    angle += speed;
    if (angle > 360) angle = 0;
    glutPostRedisplay();
}

//button part

void printCharater(const char* str)
{
    glRasterPos2f(-0.06, 0.74);
    for (int i = 0; i < strlen(str); i++) glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *(str + i));
}
struct button
{
    char* str = new char[100];
    bool cleck;
    void rev() {
       
        glPushMatrix();
        
        if (cleck)
        {
            glScalef(0.98, 0.98, 1.0);
        }
        //button
        glColor3f(0, 0, 0);
        printCharater("Reverse");
        glColor3f(1, 1, 1);
        glBegin(GL_QUADS);
        glVertex3f(-0.1, 0.8, 0);
        glVertex3f(0.1, 0.8, 0);
        glVertex3f(0.1, 0.7, 0);
        glVertex3f(-0.1, 0.7, 0);
        glEnd();

        
        glPopMatrix();
    }
    

};
button* pBtn;
void mouseFunc(GLint btn, GLint sta, int x, int y)
{

    if (btn == GLUT_LEFT_BUTTON)
        switch (sta)
        {
            case GLUT_DOWN:
            {
                if (x >= 360 && x <= 440 && y >= 40 && y <= 80) {
                    reverse();
                    pBtn->cleck = true;
                }
                break;
            }
            case GLUT_UP:
            {
                pBtn->cleck = false;
            }
        }
        if (x >= 360 && x <= 440 && y >= 40 && y <= 80) { 
            reverse();
        }
    glutPostRedisplay();
}


//menu part
void subFunc(GLint data)
{
    switch (data)
    {
    case 1:speedUp(); break;
    case 2:speedDown(); break;
    case 3:reverse(); break;
    }
}


void creatMenu()
{
    //创建菜单
    GLint sub = glutCreateMenu(subFunc);
    glutAddMenuEntry("Speed Up", 1);
    glutAddMenuEntry("Speed Down", 2);
    glutAddMenuEntry("Reverse", 3);
    //鼠标右键唤醒菜单
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}


//keyboard part
void keyBoard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'q':reverse(); break;//key "q" for reverse
    case 'w':speedUp(); break;//key "w" for speed up
    case 's':speedDown(); break;//key "s" for speed down
    case 27:exit(0);
    }
}


//drawing part
void drawPinwheel()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    glRotatef(angle, 0, 0, 1);
    glScalef(1, 1, 1);
    //中心黄色部分
    glColor3f(1, 1, 0);
    glBegin(GL_TRIANGLES);
    glVertex3f(-0.1f, -0.2 * sqrt(3) / 6, 0);
    glVertex3d(0.1f, -0.2 * sqrt(3) / 6, 0);
    glVertex3d(0.0f, 0.1 * sqrt(3) - 0.2 * sqrt(3) / 6, 0);
    glEnd();

    //red wind
    glColor3f(1, 0, 0);
    glBegin(GL_TRIANGLES);
    glVertex3f(-0.1f, -0.2 * sqrt(3) / 6, 0);
    glVertex3d(0.1f, -0.2 * sqrt(3) / 6, 0);
    glVertex3d(0.0f, -0.2 * 147 / 113 - 0.2 * sqrt(3) / 6, 0);

    glVertex3d(-0.1f, -0.2 * sqrt(3) / 6, 0);
    glVertex3d(0.0f, -0.2 * 147 / 113 - 0.2 * sqrt(3) / 6, 0);
    glVertex3d(-0.2f, -0.2 * 147 / 113 - 0.2 * sqrt(3) / 6, 0);

    glVertex3d(0.0f, -0.2 * 147 / 113 - 0.2 * sqrt(3) / 6, 0);
    glVertex3d(-0.2f, -0.2 * 147 / 113 - 0.2 * sqrt(3) / 6, 0);
    glVertex3d(0.1 * 27 / 52, -0.2 * 147 / 113 / 146 * 230 - 0.2 * sqrt(3) / 6, 0);
    glEnd();

    //blue wind
    glRotatef(120, 0, 0, 1);
    glColor3f(0, 0, 1);
    glBegin(GL_TRIANGLES);
    glVertex3f(-0.1f, -0.2 * sqrt(3) / 6, 0);
    glVertex3d(0.1f, -0.2 * sqrt(3) / 6, 0);
    glVertex3d(0.0f, -0.2 * 147 / 113 - 0.2 * sqrt(3) / 6, 0);

    glVertex3d(-0.1f, -0.2 * sqrt(3) / 6, 0);
    glVertex3d(0.0f, -0.2 * 147 / 113 - 0.2 * sqrt(3) / 6, 0);
    glVertex3d(-0.2f, -0.2 * 147 / 113 - 0.2 * sqrt(3) / 6, 0);

    glVertex3d(0.0f, -0.2 * 147 / 113 - 0.2 * sqrt(3) / 6, 0);
    glVertex3d(-0.2f, -0.2 * 147 / 113 - 0.2 * sqrt(3) / 6, 0);
    glVertex3d(0.1 * 27 / 52, -0.2 * 147 / 113 / 146 * 230 - 0.2 * sqrt(3) / 6, 0);
    glEnd();

    //green wind
    glRotatef(120, 0, 0, 1);
    glColor3f(0, 1, 0);
    glBegin(GL_TRIANGLES);
    glVertex3f(-0.1f, -0.2 * sqrt(3) / 6, 0);
    glVertex3d(0.1f, -0.2 * sqrt(3) / 6, 0);
    glVertex3d(0.0f, -0.2 * 147 / 113 - 0.2 * sqrt(3) / 6, 0);

    glVertex3d(-0.1f, -0.2 * sqrt(3) / 6, 0);
    glVertex3d(0.0f, -0.2 * 147 / 113 - 0.2 * sqrt(3) / 6, 0);
    glVertex3d(-0.2f, -0.2 * 147 / 113 - 0.2 * sqrt(3) / 6, 0);

    glVertex3d(0.0f, -0.2 * 147 / 113 - 0.2 * sqrt(3) / 6, 0);
    glVertex3d(-0.2f, -0.2 * 147 / 113 - 0.2 * sqrt(3) / 6, 0);
    glVertex3d(0.1 * 27 / 52, -0.2 * 147 / 113 / 146 * 230 - 0.2 * sqrt(3) / 6, 0);
    glEnd();

    glPopMatrix();

    //bar
    glScalef(1, 1, 1);
    glColor3f(1, 0, 1);
    glBegin(GL_POLYGON);
    glVertex3f(0.05, 0, 0.1);
    glVertex3f(-0.05, 0, 0.1);
    glVertex3f(-0.05, -0.7, 0.1);
    glVertex3f(0.05, -0.7, 0.1);
    glEnd();

    glPopMatrix();

    //button 
    pBtn->rev();

    glPopMatrix();



    glFlush();
    glutSwapBuffers();
}


//initialize
void Init()
{
    glEnable(GL_DEPTH_TEST );//开启更新深度缓冲区的功能
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//清除色彩缓存和深度缓存
    glClearColor(0.77, 0.80, 0.84, 0.19);
    glMatrixMode(GL_PROJECTION);//声明接下来对投影进行操作
    glLoadIdentity();//用一个4x4的单位矩阵来替换当前矩阵,但不会改变矩阵模式
    gluPerspective(20, 1, 1, 50);
    glMatrixMode(GL_MODELVIEW);//声明接下来对模型进行操作
    glLoadIdentity();
    gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);//设置相机
    glShadeModel(GL_SMOOTH);
    pBtn = new button;
    pBtn->cleck = false;
}

int main(int argc, char* argv[]) //
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(700, 700);
    glutInitWindowPosition(300, 100);
    glutCreateWindow("Spinning Pinwheel");
    glEnable(GL_DEPTH_TEST | GL_LINE_SMOOTH | GL_POLYGON_SMOOTH | GL_POLYGON_STIPPLE);

    Init();
    creatMenu();
    glutDisplayFunc(&drawPinwheel);
    glutIdleFunc(&rotate);
    glutKeyboardUpFunc(&keyBoard);
    glutMouseFunc(&mouseFunc);
    glutMainLoop();

    return 0;
}
