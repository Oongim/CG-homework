#include <GL/freeglut.h>
#include<time.h>
#include<stdlib.h>
#include<math.h>
#define PI 3.14
#define RADIAN PI/180

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

int Rotate = 0;
double scale = 0;
int size = 30;
int Size = 200;
double T_arr[3] = { 0 };

void Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'y':
		Rotate += 5;
		break;
	case 'Y':
		Rotate -= 5;
		break;
	case 's':
		scale += 0.1;

		break;
	case 'S':
		scale += -0.1;

		break;
	default:
		break;
	}

}
void TimerFunction(int value)
{
	if (T_arr[3] == 0) {
		T_arr[0] += 2;
		T_arr[1] -= 4;
		if (T_arr[0] == Size)
			T_arr[3] = 1;
	}
	else if (T_arr[3] == 1)
	{
		T_arr[0] -= 4;
		if (T_arr[0] == -Size)
			T_arr[3] = 2;
	}
	else if (T_arr[3] == 2)
	{
		T_arr[0] += 2;
		T_arr[1] += 4;
		if (T_arr[0] == 0)
			T_arr[3] = 0;
	}


	glutPostRedisplay();
	glutTimerFunc(50, TimerFunction, 1);
}
void main(int argc, char *argv[])
{
	srand(time(NULL));
	T_arr[0] = 0;
	T_arr[1] = Size;
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정
	glutCreateWindow("실습1"); // 윈도우 생성 (윈도우 이름)
	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutTimerFunc(50, TimerFunction, 1);
	glutKeyboardFunc(Keyboard);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}
// 윈도우 출력 함수

GLvoid drawScene(GLvoid)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	///////////////////////////////  좌표축
	glLineWidth(1);
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINES);
	glVertex2f(-400.0, 0.0);
	glVertex2f(400.0, 0.0);
	glVertex2f(0.0, -300.0);
	glVertex2f(0.0, 300.0);
	glEnd();
	///////////////////////////////
	glPushMatrix();
		glRotatef(Rotate, 0.0, 1.0, 0.0);
		
		/********************************************************************/
		glPushMatrix();
			glScalef(1.0f + scale, 1.0f + scale, 1.0f + scale);
			glLineWidth(3);
			
			glColor3f(0.0, 0.0, 1.0);

			glBegin(GL_LINES);
			glVertex2d(0,  0+ Size);
			glVertex2d(0 - Size, 0 - Size);

			glVertex2d(0 - Size, 0 - Size);
			glVertex2d(0 + Size, 0 - Size);

			glVertex2d(0 + Size, 0 - Size);
			glVertex2d(0, 0 + Size);
			glEnd();

			glBegin(GL_LINES);
			glVertex3d(0,0+Size, 0);
			glVertex3d(0, 0 - Size , 0 - Size);

			glVertex3d(0, 0 - Size , 0 - Size);
			glVertex3d(0, 0 - Size , 0 + Size);
					   
			glVertex3d(0, 0 - Size , 0 + Size);
			glVertex3d(0, 0 + Size, 0);
			glEnd();
		glPopMatrix();
		/*************************************************/
			glPushMatrix();
				glTranslatef(T_arr[0]*(scale), T_arr[1] * ( scale), 0);
				glTranslatef(T_arr[0], T_arr[1], 0);
				glColor3f(0.0, 0.0, 1.0);
				glBegin(GL_TRIANGLES);
				glVertex2d(0,  0+ size);
				glVertex2d(0 - size, 0 - size);
				glVertex2d(0 + size, 0 - size);
				glEnd();
				glColor3f(0.0, 0.0, 0.0);
				glBegin(GL_LINES);
				glVertex2d(0, 0 + size);
				glVertex2d(0 - size, 0 - size);

				glVertex2d(0 - size, 0 - size);
				glVertex2d(0 + size, 0 - size);

				glVertex2d(0 + size, 0 - size);
				glVertex2d(0, 0 + size);
				glEnd();
			glPopMatrix();

			glPushMatrix();
				glTranslatef(0, T_arr[1] * ( scale), T_arr[0] * (scale));
				glTranslatef(0, T_arr[1], T_arr[0]);

				glColor3f(0.0, 0.0, 1.0);
				glBegin(GL_TRIANGLES);
				glVertex3d(0, 0 + size, 0);
				glVertex3d(0, 0 - size, 0 - size);
				glVertex3d(0, 0 - size, 0 + size);
				glEnd();

				glColor3f(0.0, 0.0, 0.0);
				glBegin(GL_LINES);
				glVertex3d(0,0+size, 0);
				glVertex3d(0, 0 - size , 0 - size);

				glVertex3d(0, 0 - size , 0 - size);
				glVertex3d(0, 0 - size , 0 + size);
						   
				glVertex3d(0, 0 - size , 0 + size);
				glVertex3d(0, 0 + size, 0);
				glEnd();
			glPopMatrix();

		/********************************************************************/
	glPopMatrix();
	glFlush();

}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(-400.0, 400.0, -300.0, 300.0, -300.0, 300.0);
}
