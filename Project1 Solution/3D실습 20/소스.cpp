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
	int dir;
};
struct Rotate {
	double Rx, Ry, Rz;
};
bool Projection = true;
pos O;
Rotate O2, O3;
GLdouble rotate[16]
= { 1,0,0,0,
0,1,0,0,
0,0,1,0,
0,0,0,1 };
GLdouble rotateO1[16]
= { 1,0,0,0,
0,1,0,0,
0,0,1,0,
0,0,0,1 };
GLdouble rotateO2[16]
= { 1,0,0,0,
0,1,0,0,
0,0,1,0,
0,0,0,1 };
GLdouble rotateO3[16]
= { 1,0,0,0,
0,1,0,0,
0,0,1,0,
0,0,0,1 };
void Init_array(GLdouble arr[])
{
	arr[0] = 1; arr[1] = 0; arr[2] = 0; arr[3] = 0;
	arr[4] = 0; arr[5] = 1; arr[6] = 0; arr[7] = 0;
	arr[8] = 0; arr[9] = 0; arr[10] = 1; arr[11] = 0;
	arr[12] = 0; arr[13] = 0; arr[14] = 0; arr[15] = 1;
}
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
	case 'q':
		glPushMatrix();
		glRotatef(5, 0.0, 1.0, 0.0);
		glMultMatrixd(rotateO1);
		glGetDoublev(GL_MODELVIEW_MATRIX, rotateO1);
		glPopMatrix();
		break;
	case 'w':
		O2.Ry += 5;
		break;
	case 'e':
		O2.Rx += 5;
		break;
	case 'E':
		O2.Rx -= 5;
		break;
	case 'r':
		O3.Rx += 5;
		break;
	case 't':
		O3.Rz += 5;
		break;
	case 'i':
		O.x = 0;

		Init_array(rotate);
		Init_array(rotateO1);
		Init_array(rotateO2);
		Init_array(rotateO3);
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
	O.x+=O.dir;
	if (O.x >= 100 || O.x <= -100)
		O.dir *= -1;
	glutPostRedisplay();
	glutTimerFunc(50, TimerFunction, 1);
}
void main(int argc, char *argv[])
{
	O.dir = 2;
	srand(time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정
	glutCreateWindow("실습20"); // 윈도우 생성 (윈도우 이름)
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
		gluLookAt(0, 50, 100, 0.0, 0.0, 0.0, 0.0, 1, 0.0);
		glMultMatrixd(rotate);
		/**************************************************/
		glPushMatrix();       //좌표축
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
		/*****************************************************/
		glPushMatrix();//맨아래
		
			glTranslatef(O.x, -100, 0);
			glMultMatrixd(rotateO1);
			glPushMatrix(); {
				glColor3f(1.0, 0.0, 0.0);
				glScalef(2, 1, 1);
				glutSolidCube(100);
				glColor3f(0.0, 0.0, 0.0);
				glutWireCube(100);
				glPopMatrix(); }
			glPushMatrix();//중간
			
				glTranslatef(0, 50, 0);
				
				glRotatef(O2.Rx, 1.0, 0.0, 0.0);
				glRotatef(O2.Ry, 0.0, 1.0, 0.0);
				
				glTranslatef(0, 50, 0);

				glPushMatrix(); {
					glColor3f(0.0, 1.0, 0.0);
					glScalef(0.5, 1, 0.5);
					glutSolidCube(100);
					glColor3f(0.0, 0.0, 0.0);
					glutWireCube(100);
				glPopMatrix(); }
				glPushMatrix();//맨위
					glTranslatef(0, 50, 0);
					
					glRotatef(O3.Rx, 1.0, 0.0, 0.0);
					glRotatef(O3.Rz, 0.0, 0.0, 1.0);

					glTranslatef(0, 50, 0);

					glColor3f(0.0, 0.0, 1.0);
					glScalef(0.25, 1, 0.25);
					glutSolidCube(100);
					glColor3f(0.0, 0.0, 0.0);
					glutWireCube(100);
				glPopMatrix();
			glPopMatrix();

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
