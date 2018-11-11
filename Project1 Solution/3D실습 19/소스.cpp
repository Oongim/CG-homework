#include <GL/freeglut.h>
#include<time.h>
#include<stdlib.h>
#include<math.h>
#define PI 3.14
#define RADIAN PI/180

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
struct pos {
	float x, y, z;
};
int Shape_mode = 0, Rotate_mode = 0;
int Rotate_object = 0, Rotate_object1 = 0, Rotate_object2 = 0;
bool Projection = true;
pos circle;
int speedR = 2;
int r = 50;
double speed = r * PI * 2 * speedR / 360;
GLdouble rotate[16]
= { 1,0,0,0,
0,1,0,0,
0,0,1,0,
0,0,0,1 };
GLdouble rotateC[16]
= { 1,0,0,0,
0,1,0,0,
0,0,1,0,
0,0,0,1 };
void Keyboard(unsigned char key, int x, int y)
{
	
	switch (key) {
	case'f':
		int w, h;
		w = 800;
		h = 600;
		if (Projection)
		{
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glViewport(0, 0, w, h);
			glOrtho(-400.0, 400.0, -300.0, 300.0, -300.0, 300.0);
			glMatrixMode(GL_MODELVIEW);
			Projection = false;
		}
		else
		{
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glViewport(0, 0, w, h);
			gluPerspective(60.0f, w / h, 1.0, 1000.0);
			glTranslatef(0.0, 0.0, -500.0);
			glMatrixMode(GL_MODELVIEW);
			Projection = true;
		}

		break;
	case 'x':
		glPushMatrix();
		glRotatef(5, 1.0, 0.0, 0.0);
		glMultMatrixd(rotate);
		glGetDoublev(GL_MODELVIEW_MATRIX, rotate);
		glPopMatrix();
		break;
	case 'X':
		glPushMatrix();
		glRotatef(-5, 1.0, 0.0, 0.0);
		glMultMatrixd(rotate);
		glGetDoublev(GL_MODELVIEW_MATRIX, rotate);
		glPopMatrix();
		break;
	case 'y':
		glPushMatrix();
		glRotatef(5, 0.0, 1.0, 0.0);
		glMultMatrixd(rotate);
		glGetDoublev(GL_MODELVIEW_MATRIX, rotate);
		glPopMatrix();
		break;
	case 'Y':
		glPushMatrix();
		glRotatef(-5, 0.0, 1.0, 0.0);
		glMultMatrixd(rotate);
		glGetDoublev(GL_MODELVIEW_MATRIX, rotate);
		glPopMatrix();
		break;
	case 'z':
		glPushMatrix();
		glRotatef(5, 0.0, 0.0, 1.0);
		glMultMatrixd(rotate);
		glGetDoublev(GL_MODELVIEW_MATRIX, rotate);
		glPopMatrix();
		break;
	case 'Z':
		glPushMatrix();
		glRotatef(-5, 0.0, 0.0, 1.0);
		glMultMatrixd(rotate);
		glGetDoublev(GL_MODELVIEW_MATRIX, rotate);
		glPopMatrix();
		break;
	case 'w':
		if ((circle.z - speed) > -200)
			circle.z -= speed;
		glPushMatrix();
		glRotatef(-2, 1.0, 0.0, 0.0);
		glMultMatrixd(rotateC);
		glGetDoublev(GL_MODELVIEW_MATRIX, rotateC);
		glPopMatrix();
		break;
	case 's':
		if ((circle.z + speed) < 200)
			circle.z += speed;
		glPushMatrix();
		glRotatef(2, 1.0, 0.0, 0.0);
		glMultMatrixd(rotateC);
		glGetDoublev(GL_MODELVIEW_MATRIX, rotateC);
		glPopMatrix();
		break;
	case 'd':
		if ((circle.x + speed) < 300)
			circle.x += speed;
		glPushMatrix();
		glRotatef(-2, 0.0, 0.0, 1.0);
		glMultMatrixd(rotateC);
		glGetDoublev(GL_MODELVIEW_MATRIX, rotateC);
		glPopMatrix();
		break;
	case 'a':
		if ( (circle.x-speed) > -300)
			circle.x -= speed;
		glPushMatrix();
		glRotatef(2, 0.0, 0.0, 1.0);
		glMultMatrixd(rotateC);
		glGetDoublev(GL_MODELVIEW_MATRIX, rotateC);
		glPopMatrix();
		break;
	case 'r':
		glPushMatrix();
		glRotatef(2, 0.0, 1.0, 0.0);
		glMultMatrixd(rotateC);
		glGetDoublev(GL_MODELVIEW_MATRIX, rotateC);
		glPopMatrix();
		break;
	case 'i':
		circle.x = 0;
		circle.y = -100;
		circle.z = 0;
		rotate[0] = 1; rotate[1] = 0; rotate[2] = 0; rotate[3] = 0;
		rotate[4] = 0; rotate[5] = 1; rotate[6] = 0; rotate[7] = 0;
		rotate[8] = 0; rotate[9] = 0; rotate[10] = 1; rotate[11] = 0;
		rotate[12] = 0; rotate[13] = 0; rotate[14] = 0; rotate[15] = 1;
		rotateC[0] = 1; rotateC[1] = 0; rotateC[2] = 0; rotateC[3] = 0;
		rotateC[4] = 0; rotateC[5] = 1; rotateC[6] = 0; rotateC[7] = 0;
		rotateC[8] = 0; rotateC[9] = 0; rotateC[10] = 1; rotateC[11] = 0;
		rotateC[12] = 0; rotateC[13] = 0; rotateC[14] = 0; rotateC[15] = 1;
		break;
	default:
		break;
	}

}
void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{

		glutPostRedisplay();
	}
}
void TimerFunction(int value)
{
	glutPostRedisplay();
	glutTimerFunc(50, TimerFunction, 1);
}
void main(int argc, char *argv[])
{
	circle.y -= 100;
	srand(time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정
	glutCreateWindow("실습"); // 윈도우 생성 (윈도우 이름)
	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutTimerFunc(50, TimerFunction, 1);
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}
// 윈도우 출력 함수

GLvoid drawScene(GLvoid)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
	gluLookAt(0, 10,10, 0.0, 0.0, 0.0, 0.0, 1, 0.0);
	glMultMatrixd(rotate);
	glPushMatrix();
	glScalef(100, 1, 1);
	glColor3f(1.0, 0.0, 0.0);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glScalef(1, 100, 1);
	glColor3f(0.0, 1.0, 0.0);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glScalef(1, 1, 100);
	glColor3f(0.0, 0.0, 1.0);
	glutSolidCube(1);
	glPopMatrix();
	
	/****************************************************/
	glPushMatrix(); // 바닥
	glScalef(600, 1, 400);
	glTranslatef(0, -150, 0);
	glColor3f(1.0, 1.0, 0.0);
	glutSolidCube(1);
	glPopMatrix();


	glColor3f(0.0, 1.0, 1.0);
	
		glPushMatrix();
		
		glTranslatef(circle.x, circle.y, circle.z);
		glMultMatrixd(rotateC);
		glutWireSphere(r, 10, 10);
		glPopMatrix();
	/****************************************************/
		glPopMatrix();
	glEnable(GL_DEPTH_TEST);
	glFlush();
	glutSwapBuffers();
}
GLvoid Reshape(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	if (Projection) {
		gluPerspective(60.0f, w / h, 1.0, 1000.0);
		glTranslatef(0.0, 0.0, -500.0);
	}
	else
		glOrtho(-400.0, 400.0, -300.0, 300.0, -300.0, 300.0);
	glMatrixMode(GL_MODELVIEW);
}
