#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string.h>
#include <stdarg.h>
#include <math.h>
#include <GL/glut.h>

#pragma warning(disable:4996)
#define GL_GLEXT_PROTOTYPES
#define PI 3.141592654
#define SHARPNESS_FACTOR 500

double world_y = 0;
double wing_z = 0;
double r_step = 5.0;
double scale = 1.0;
double world_y_trans = 0.0;
double wing_speed = 0.0;
double wind_acc_factor = .8;
double turbine_factor = 0.005;
double progoffset = 0.0;
double progstep = 0.000;
double progstep_acc = .0005;


void specialKeys(int key, int x, int y) //�ӽ���ת
{
	if (key == GLUT_KEY_RIGHT)
		world_y += r_step;
	if (key == GLUT_KEY_LEFT)
		world_y -= r_step;
	if (key == GLUT_KEY_UP)
		world_y_trans += 0.05;
	if (key == GLUT_KEY_DOWN)
		world_y_trans -= 0.05;
	glutPostRedisplay();
}

void rotate() //��ת�ٶȿ���
{
	double acc = progstep * wind_acc_factor - wing_speed * turbine_factor;
	wing_speed += acc;
	wing_z += wing_speed;
	progoffset += progstep;
	glutPostRedisplay();
}

void rotateWind(unsigned char key, int x, int y) //�糵��ת����
{
	if (key == 'c')
		if (progstep < 0)
			progstep -= progstep_acc;
		else
			progstep += progstep_acc;
	if (key == 'z')
		if (progstep < 0)
			progstep += progstep_acc;
		else if (progstep > 0)
			progstep -= progstep_acc;
	if (key == 'x')
		progstep = -progstep;
}


void print_bitmap_string(void* font, char* s) //��ʾ����

{

	if (s && strlen(s))
	{
		while (*s)
		{
			glutBitmapCharacter(font, *s);
			s++;
		}
	}
}

struct Button //��ť�ؼ�
{

	char* st = new char[100];
	bool click;
	void Turn()
	{


		if (click)
		{
			glScalef(0.85, 0.85, 0.9);

		}

		glBegin(GL_QUADS);
		glColor3f(0.804, 0.883, 0.922);
		glVertex3f(-0.2f, 0, 0);
		glVertex3d(0.2f, 0, 0);
		glVertex3d(0.2f, 0, 0.2 * sqrt(3) * 30 / 100);
		//glVertex3d(0.1f, 0, 0.1 * sqrt(3) * 30 / 100);
		//glVertex3f(-0.1f, 0, 0);
		glVertex3d(-0.2f, 0, 0.2 * sqrt(3) * 30 / 100);
		glEnd();

		glLoadIdentity();
		glOrtho(-250, 250, -250, 250, -250.0, 250.0);
		if (click)
		{
			glRasterPos2f(-43, 329.0);
		}
		else {
			glRasterPos2f(-43, 330.0);
		}

		glColor3f(0.1, 0.1, 0.1);
		strcpy(st, "ChangeDir");
		glRasterPos2f(-1, 0.74);
		print_bitmap_string(GLUT_BITMAP_HELVETICA_18, st);


	}
	bool OnMouseDown(int mousex, int mousey)
	{

		if (mousex > 450 && mousex < 550 &&
			mousey > 130 && mousey < 150)
		{
			click = true;

			return true;
		}
		return false;
	}
	void OnMouseUp()
	{
		click = false;
	}
};
Button* pBtn;

void init(void) //��ť��ʼ��
{
	glClearColor(0.77, 0.80, 0.84, 0.19);
	glShadeModel(GL_FLAT);
	pBtn = new Button;
	pBtn->click = false;
}


void drawWindMill() //��ģ�糵
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity(); //�ָ���ʼ����ϵ
	glScalef(scale, scale, scale); //ͨ��scale�����������ӽǰ�
	glRotatef(world_y, 0, 1.0, world_y_trans); //ͨ��world_y��world_y_trans��������ת������
	glTranslatef(.0, -0.03, 0); //ƽ�ƶ���
	glRotatef(-wing_z, 0.0, 0.0, 1.0);  //ͨ��wing_z�ѷ���ת����
	glRotatef(90, 1.0, 0.0, 0.0); //��ʼ�Ƕ�
	glColor3f(1, 1, 0); //��Ⱦ��ɫ
	glBegin(GL_TRIANGLES); //�����ε���
	glVertex3f(-0.1f, 0, -0.2 * sqrt(3) / 6);
	glVertex3d(0.1f, 0, -0.2 * sqrt(3) / 6);
	glVertex3d(0.0f, 0, 0.1 * sqrt(3) - 0.2 * sqrt(3) / 6);
	glEnd();

	glLoadIdentity();
	glScalef(scale, scale, scale);
	glRotatef(world_y, 0.0, 1.0, world_y_trans);
	glTranslatef(.0, -0.03, 0);
	glRotatef(-wing_z, 0.0, 0.0, 1.0);
	glRotatef(90, 1.0, 0.0, 0.0);
	glColor3f(1, 0, 0);
	glBegin(GL_TRIANGLES);
	glVertex3f(-0.1f, 0, -0.2 * sqrt(3) / 6);
	glVertex3d(0.1f, 0, -0.2 * sqrt(3) / 6);
	glVertex3d(0.0f, 0, -0.2 * 147 / 113 - 0.2 * sqrt(3) / 6);
	glVertex3d(0.1f, 0, -0.2 * sqrt(3) / 6);
	glVertex3d(0.0f, 0, -0.2 * 147 / 113 - 0.2 * sqrt(3) / 6);
	glVertex3d(0.2f, 0, -0.2 * 147 / 113 - 0.2 * sqrt(3) / 6);
	glVertex3d(0.0f, 0, -0.2 * 147 / 113 - 0.2 * sqrt(3) / 6);
	glVertex3d(0.2f, 0, -0.2 * 147 / 113 - 0.2 * sqrt(3) / 6);
	glVertex3d(-0.1 * 27 / 52, 0, -0.2 * 147 / 113 / 146 * 230 - 0.2 * sqrt(3) / 6);
	glEnd();

	glLoadIdentity();
	glScalef(scale, scale, scale);
	glRotatef(world_y, 0.0, 1.0, world_y_trans);
	glTranslatef(.0, -0.03, 0);
	glRotatef(-wing_z + 120, 0.0, 0.0, 1.0);
	glRotatef(90, 1.0, 0.0, 0.0);
	glColor3f(0, 1, 0);
	glBegin(GL_TRIANGLES);
	glVertex3f(-0.1f, 0, -0.2 * sqrt(3) / 6);
	glVertex3d(0.1f, 0, -0.2 * sqrt(3) / 6);
	glVertex3d(0.0f, 0, -0.2 * 147 / 113 - 0.2 * sqrt(3) / 6);
	glVertex3d(0.1f, 0, -0.2 * sqrt(3) / 6);
	glVertex3d(0.0f, 0, -0.2 * 147 / 113 - 0.2 * sqrt(3) / 6);
	glVertex3d(0.2f, 0, -0.2 * 147 / 113 - 0.2 * sqrt(3) / 6);
	glVertex3d(0.0f, 0, -0.2 * 147 / 113 - 0.2 * sqrt(3) / 6);
	glVertex3d(0.2f, 0, -0.2 * 147 / 113 - 0.2 * sqrt(3) / 6);
	glVertex3d(-0.1 * 27 / 52, 0, -0.2 * 147 / 113 / 146 * 230 - 0.2 * sqrt(3) / 6);
	glEnd();

	glLoadIdentity();
	glScalef(scale, scale, scale);
	glRotatef(world_y, 0.0, 1.0, world_y_trans);
	glTranslatef(.0, -0.03, 0);
	glRotatef(-wing_z + 240, 0.0, 0.0, 1.0);
	glRotatef(90, 1.0, 0.0, 0.0);
	glColor3f(0, 0, 1);
	glBegin(GL_TRIANGLES);
	glVertex3f(-0.1f, 0, -0.2 * sqrt(3) / 6);
	glVertex3d(0.1f, 0, -0.2 * sqrt(3) / 6);
	glVertex3d(0.0f, 0, -0.2 * 147 / 113 - 0.2 * sqrt(3) / 6);
	glVertex3d(0.1f, 0, -0.2 * sqrt(3) / 6);
	glVertex3d(0.0f, 0, -0.2 * 147 / 113 - 0.2 * sqrt(3) / 6);
	glVertex3d(0.2f, 0, -0.2 * 147 / 113 - 0.2 * sqrt(3) / 6);
	glVertex3d(0.0f, 0, -0.2 * 147 / 113 - 0.2 * sqrt(3) / 6);
	glVertex3d(0.2f, 0, -0.2 * 147 / 113 - 0.2 * sqrt(3) / 6);
	glVertex3d(-0.1 * 27 / 52, 0, -0.2 * 147 / 113 / 146 * 230 - 0.2 * sqrt(3) / 6);
	glEnd();

	glLoadIdentity();
	glScalef(scale, scale, scale);
	glRotatef(world_y, 0.0, 1.0, world_y_trans);
	glTranslatef(.0, -0.03, -0.01);
	glRotatef(90, 1.0, 0.0, 0.0);
	glColor3f(1, 0, 1);
	glBegin(GL_TRIANGLES);
	glVertex3f(-0.1f * 33 / 118, 0, 0);
	glVertex3d(0.1f * 33 / 118, 0, 0);
	glVertex3d(0.1f * 33 / 118, 0, 0.1 * sqrt(3) * 324 / 100);
	glVertex3d(0.1f * 33 / 118, 0, 0.1 * sqrt(3) * 324 / 100);
	glVertex3f(-0.1f * 33 / 118, 0, 0);
	glVertex3d(-0.1f * 33 / 118, 0, 0.1 * sqrt(3) * 324 / 100);
	glEnd();

	glLoadIdentity();
	glScalef(scale, scale, scale);
	glTranslatef(.0, 0.7, 0.05);
	glRotatef(90, 1.0, 0.0, 0.0);
	glColor3f(0.5, 0.5, 0.4);
	pBtn->Turn();

	glFlush();
	glutSwapBuffers();
}

void processMenuEvents(int option)  //�˵���
{
	switch (option) {
	case 0:
		progstep = -progstep;
		break;
	case 1:
		if (progstep < 0)
			progstep -= progstep_acc;
		else
			progstep += progstep_acc;
		break;
	case 2:
		if (progstep < 0)
			progstep += progstep_acc;
		else if (progstep > 0)
			progstep -= progstep_acc;
		break;
	}
}

void createGLUTMenus() //�����˵��ؼ�
{

	int menu;
	menu = glutCreateMenu(processMenuEvents);
	glutAddMenuEntry("ChangeDire", 0);
	glutAddMenuEntry("Accelerate", 1);
	glutAddMenuEntry("Decelerate", 2);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}


void mouse(int button, int dir, int x, int y) //��갴����
{
	if (button == 3)
	{
		// Zoom in
		if (scale <= 3.0)
			scale += 0.03;
	}
	else if (button == 4)
	{
		// Zoom out
		if (scale >= 0.5)
			scale -= 0.03;
	}

	if (button == GLUT_LEFT_BUTTON)
		switch (dir)
		{
		case GLUT_DOWN:
			if (pBtn->OnMouseDown(x, y))
			{
				progstep = -progstep;
			}
			break;

		case GLUT_UP:
			pBtn->OnMouseUp();
			break;
		}


	glutPostRedisplay();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Spinning Pinwheel");
	glEnable(GL_DEPTH_TEST | GL_LINE_SMOOTH | GL_POLYGON_SMOOTH | GL_POLYGON_STIPPLE);


	init();
	//createGLUTMenus();
	//glutDisplayFunc(drawWindMill);
	//glutIdleFunc(rotate);
	//glutSpecialFunc(specialKeys);
	//glutKeyboardFunc(rotateWind);
	//glutMouseFunc(mouse);
	glutMainLoop();
}
