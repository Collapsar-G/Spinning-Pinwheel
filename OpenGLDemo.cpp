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

double Rdgr = 0;//rotate degree
double velocityAcc = 0;//acceleration of velocity
double incresement = 0.3;


//function part(speed constro & spining direction reverse)
void reverse()
{
    velocityAcc = -velocityAcc;
}

void speedUp()
{
    if (velocityAcc >= 0)velocityAcc += incresement;
    else velocityAcc -= incresement;
}

void speedDown()
{
    if (velocityAcc >= 0) velocityAcc -= incresement;
    else velocityAcc += incresement;
}

void rotate()
{
    Rdgr += velocityAcc;
    if (Rdgr > 360) Rdgr = 0;
    glutPostRedisplay();
}

//button part
void printCharater(const char* str)
{
    glRasterPos2f(-0.06, 0.74);
    for (int i = 0; i < strlen(str); i++) glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *(str + i));
}

void mouseFunc(GLint btn, GLint sta, int x, int y)
{
    if (btn == GLUT_LEFT_BUTTON && sta == GLUT_DOWN)
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
    glRotatef(Rdgr, 0, 0, 1);
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

    //button text
    glColor3f(0, 0, 0);
    printCharater("Reverse");

    //button
    glColor3f(1, 1, 1);
    glBegin(GL_QUADS);
    glVertex3f(-0.1, 0.8, 0);
    glVertex3f(0.1, 0.8, 0);
    glVertex3f(0.1, 0.7, 0);
    glVertex3f(-0.1, 0.7, 0);
    glEnd();

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
}

int main(int argc, char* argv[]) //
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(300, 30);
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
