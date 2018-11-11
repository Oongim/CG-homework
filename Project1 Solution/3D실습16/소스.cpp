#include <GL/freeglut.h>
#include<time.h>
#include<stdlib.h>
#include<math.h>
#define PI 3.14
#define RADIAN PI/180

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

int Shape_mode = 0,Rotate_mode=0;
int Rotate_object=0, Rotate_object1 = 0, Rotate_object2 = 0;
bool Projection = true;
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
		Rotate_mode = 1;
		break;
	case 'X':
		Rotate_mode = -1;
		break;
	case 'y':
		Rotate_mode = 2;
		break;
	case 'Y':
		Rotate_mode = -2;
		break;
	case 'z':
		Rotate_mode = 3;
		break;
	case 'Z':
		Rotate_mode = -3;
		break;
	case 'o':
		Rotate_object += 5;
		break;
	case 'l':
		Rotate_object1 += 5;
		break;
	case 'r':
		Rotate_object2 += 5;
		break;
	case 'c':
		Shape_mode ++;
		if (Shape_mode == 4)
			Shape_mode = 0;
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

	if (Rotate_mode == 1) {
		glRotatef(5, 1.0, 0.0, 0.0);
	}
	else if (Rotate_mode == 2) {
		glRotatef(5, 0.0, 1.0, 0.0);
	}
	else if (Rotate_mode == 3) {
		glRotatef(5, 0.0, 0.0, 1.0);
	}
	else if (Rotate_mode == -1) {
		glRotatef(-5, 1.0, 0.0, 0.0);
	}
	else if (Rotate_mode == -2) {
		glRotatef(-5, 0.0, 1.0, 0.0);
	}
	else if (Rotate_mode == -3) {
		glRotatef(-5, 0.0, 0.0, 1.0);
	}
	Rotate_mode = 0;
	/****************************************************/
		glPushMatrix();
			glScalef(800,1, 1);
			glColor3f(1.0, 0.0, 0.0);
			glutSolidCube(1);
		glPopMatrix();
		glPushMatrix();
			glScalef(1, 600, 1);
			glColor3f(0.0, 1.0, 0.0);
			glutSolidCube(1);
		glPopMatrix();
		glPushMatrix();
			glScalef(1, 1, 600);
			glColor3f(0.0, 0.0, 1.0);
			glutSolidCube(1);
		glPopMatrix();
	/****************************************************/
		glPushMatrix(); // 바닥
			glScalef(400, 1, 300);
			glTranslatef(0, -150, 0);
			glColor3f(1.0, 1.0, 0.0);
			glutSolidCube(1);
		glPopMatrix();

			
			glColor3f(0.0, 1.0, 1.0);
			if (Shape_mode ==0)
			{
				glPushMatrix();
					glRotatef(Rotate_object, 0.0, 1.0, 0.0);
					glTranslatef(100, -100, 0);
					glRotatef(Rotate_object1, 0.0, 1.0, 0.0);
					glutWireTeapot(50);
				glPopMatrix();
				glPushMatrix();
					glRotatef(Rotate_object, 0.0, 1.0, 0.0);
					glTranslatef(-100, -100, 0);
					glRotatef(Rotate_object2, 0.0, 1.0, 0.0);
					glutSolidTeapot(50);
				glPopMatrix();
			}
			else if (Shape_mode == 1)
			{
				glPushMatrix();
				glRotatef(Rotate_object, 0.0, 1.0, 0.0);
				glTranslatef(100, -100, 0);
				glRotatef(Rotate_object1, 0.0, 1.0, 0.0);
					glutWireSphere(50, 10, 10);
				glPopMatrix();
				glPushMatrix();
				glRotatef(Rotate_object, 0.0, 1.0, 0.0);
				glTranslatef(-100, -100, 0);
				glRotatef(Rotate_object2, 0.0, 1.0, 0.0);
					glutSolidSphere(50, 10, 10);
				glPopMatrix();
			}
			else if (Shape_mode == 2)
			{
				glPushMatrix();
				glRotatef(Rotate_object, 0.0, 1.0, 0.0);
				glTranslatef(100, -150, 0);
				glRotatef(Rotate_object1, 0.0, 1.0, 0.0);
				glRotatef(-90, 1.0, 0.0, 0.0);
					glutWireCone(50, 100, 10, 10);
				glPopMatrix();
				glPushMatrix();
				glRotatef(Rotate_object, 0.0, 1.0, 0.0);
				glTranslatef(-100, -150, 0);
				glRotatef(Rotate_object2, 0.0, 1.0, 0.0);
				glRotatef(-90, 1.0, 0.0, 0.0);
					glutSolidCone(50, 100, 10, 10);
				glPopMatrix();
			}
			else if (Shape_mode == 3)
			{
				glPushMatrix();
				glRotatef(Rotate_object, 0.0, 1.0, 0.0);
				glTranslatef(100, -100, 0);
				glRotatef(Rotate_object1, 0.0, 1.0, 0.0);
					glutWireCube(50);
				glPopMatrix();
				glPushMatrix();
				glRotatef(Rotate_object, 0.0, 1.0, 0.0);
				glTranslatef(-100, -100, 0);
				glRotatef(Rotate_object2, 0.0, 1.0, 0.0);
					glutSolidCube(50);
				glPopMatrix();
			}
		
	/****************************************************/
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
