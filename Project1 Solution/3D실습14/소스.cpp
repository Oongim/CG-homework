#include <GL/freeglut.h>
#include<time.h>
#include<stdlib.h>
#include<math.h>
#define PI 3.14
#define RADIAN PI/180
#define POT 0
#define SPHERE 1
#define SOLCONE 2
#define CUBE 3
#define TORUS 4

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

struct Object
{
	int x, y;
	int size;
	double col_R, col_G, col_B;
	double scale;
	int mode;
	int r_x,r_y,r_z;
	int rotate;
	int rotate_mode = -1;
	int shape;
};

Object arr[20];
int count=0;

void Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'r':
		for (int i = 0; i < 20; ++i)
		{
			if (arr[i].mode == true)
			{
				arr[i].rotate_mode *= -1;
			}
		}
		break;
	case 'q':
		exit(0);
		break;
	default:
		break;
	}

}

void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		arr[count].x = x-400;
		arr[count].y = 300-y;

		arr[count].size = rand() % 200 + 100;

		arr[count].col_R = (rand() % 11) *0.1;
		arr[count].col_G = (rand() % 11) *0.1;
		arr[count].col_B = (rand() % 11) *0.1;

		arr[count].scale = 100;
		arr[count].mode = true;

		arr[count].r_x = rand() % 2;
		arr[count].r_y = rand() % 2;
		arr[count].r_z = rand() % 2;

		arr[count].shape = rand()%5;
		count++;
		if (count == 20)
			count = 0;
		glutPostRedisplay();
	}
}
void TimerFunction(int value)
{
	for (int i = 0; i < 20; ++i)
	{
		if (arr[i].mode == true)
		{
			if(arr[i].rotate_mode==-1)
				arr[i].rotate += 10;
			else
				arr[i].rotate -= 10;
			arr[i].scale -= 1;
			if (arr[i].scale <= 0)
				arr[i].mode = false;
		}
	}
	glutPostRedisplay();
	glutTimerFunc(200, TimerFunction, 1);
}
void main(int argc, char *argv[])
{
	srand(time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정
	glutCreateWindow("실습1"); // 윈도우 생성 (윈도우 이름)
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

	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
	/****************************************************/
	for (int i = 0; i < 20; ++i)
	{
		if (arr[i].mode == true)
		{
			glPushMatrix();
			glColor3f(arr[i].col_R, arr[i].col_G, arr[i].col_B);

			glTranslatef(arr[i].x, arr[i].y, 0);
			glRotatef(arr[i].rotate, arr[i].r_x, arr[i].r_y, arr[i].r_z);
			glScalef(arr[i].scale*0.01, arr[i].scale*0.01, arr[i].scale*0.01);

			if (arr[i].shape == POT)
			{
					glutWireTeapot(arr[i].size);
			}
			if (arr[i].shape == SPHERE)
			{
				glutWireSphere(arr[i].size,10,10);
			}
			if (arr[i].shape == SOLCONE)
			{
				glutWireCone(arr[i].size, arr[i].size,10,10);
			}
			if (arr[i].shape == CUBE)
			{
				glutWireCube(arr[i].size);
			}
			if (arr[i].shape == TORUS)
			{
				glutWireTorus(arr[i].size/2, arr[i].size,10,10);
			}
			glPopMatrix();
		}
	}

	/****************************************************/
	glPopMatrix();

	glFlush();

}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(-400.0, 400.0, -300.0, 300.0, -300.0, 300.0);
}
