#include <GL/freeglut.h>
#include<time.h>
#include<stdlib.h>
#include<math.h>
#define PI 3.14
#define RADIAN PI/180

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
struct Point {
	double x, y, z;
};
int Rotate_mode = 0;
int spd_arr[6][2] = { 0 };
bool Projection = true;
Point camera, pos;
float theta=0, phi=0;

int up_v = 1;
double r = 0;
double win_w = 800, win_h = 600;
int change = 0;

void Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case'p':
		if (Projection)
			Projection = false;
		else
			Projection = true;
		Reshape(win_w, win_h);
		break;
	case 'i':
		pos.x = 0;
		pos.y = 0;
		pos.z = 0;
		camera.x = 1;
		camera.y = 1;
		camera.z = 100;
		phi = 0;
		theta = 0;
		up_v = 1;
		break;
	case 'x':
		phi += 2;
		break;
	case 'X':
		phi -= 2;
		break;
	case 'y':
		theta += 2;
		break;
	case 'Y':
		theta -= 2;
		break;
	case 'z':
		pos.z += 2;
		break;
	case 'Z':
		pos.z -= 2;
		break;
	case 'w':
		pos.y += 2;
		break;
	case 's':
		pos.y -= 2;
		break;
	case 'a':
		pos.x -= 2;
		break;
	case 'd':
		pos.x += 2;
		break;
	case '+':
		pos.z += 2;
		break;
	case '-':
		pos.z -= 2;
		break;
	case 'c':
		change = 1;
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
	for (int i = 0; i < 6; ++i)
		spd_arr[i][1] += spd_arr[i][0];


	glutPostRedisplay();
	glutTimerFunc(50, TimerFunction, 1);
}
void main(int argc, char *argv[])
{
	srand(time(NULL));
	for (int i = 0; i < 6; ++i)
		spd_arr[i][0] = rand() % 9 + 1;
	pos.x = 0;
	pos.y = 0;
	pos.z = 0;
	camera.x = 0;
	camera.y = 0;
	camera.z = 10;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // 디스플레이 모드 설정
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
	r = sqrt(pow(camera.x, 2) + pow(camera.y, 2) + pow(camera.z, 2));
	if (phi >= 91) {
		up_v = -1;
	}
	if (phi >= 271)
	{
		up_v = 1;
		phi = -90;
	}
	

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
	glScalef(800, 1, 1);
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

	glPushMatrix();
	/****************************************************/
	//glPushMatrix();
	
	glTranslatef(pos.x, pos.y,pos.z);

	camera.x = r * cos(phi*RADIAN) * cos(theta*RADIAN);
	camera.y = r * sin(phi*RADIAN);
	camera.z = r * cos(phi*RADIAN) * sin(theta*RADIAN);
	gluLookAt(camera.x, camera.y, camera.z, 0.0, 0.0, 0.0, 0.0, up_v, 0.0);
	//glPopMatrix();
	glColor3f(1, 0.3, 0);
	if(change==0)
		glutSolidSphere(100, 30, 30);
	else
		glutWireSphere(100, 30, 30);
	glColor3f(0, 0.0, 1);
	glutWireSphere(200, 1, 20);
	glutWireSphere(-200, 1, 20);
	glPushMatrix();
	glRotatef(spd_arr[0][1], 0.0, 1.0, 0.0);
	glTranslatef(200, 0, 0);
	glColor3f(1, 0.8, 0);
	if (change == 0)
		glutSolidSphere(30, 30, 30);
	else
		glutWireSphere(30, 30, 30);
	glColor3f(0, 0.0, 1);
	glutWireSphere(50, 1, 20);
	glutWireSphere(-50, 1, 20);

	glRotatef(spd_arr[1][1], 0.0, 1.0, 0.0);
	glTranslatef(50, 0, 0);
	glColor3f(0, 0.8, 0);
	if (change == 0)
		glutSolidSphere(10, 20, 20);
	else
		glutWireSphere(10, 20, 20);
	glPopMatrix();
	glPushMatrix();
	glColor3f(0, 0.0, 1);
	glRotatef(-45, 0.0, 0.0, 1.0);
	glutWireSphere(200, 1, 20);
	glutWireSphere(-200, 1, 20);

	glRotatef(spd_arr[2][1], 0.0, 1.0, 0.0);
	glTranslatef(200, 0, 0);
	glColor3f(1, 0.8, 0);
	if (change == 0)
		glutSolidSphere(30, 30, 30);
	else
		glutWireSphere(30, 30, 30);
	glColor3f(0, 0.0, 1);
	glutWireSphere(50, 1, 20);
	glutWireSphere(-50, 1, 20);

	glRotatef(spd_arr[3][1], 0.0, 1.0, 0.0);
	glTranslatef(50, 0, 0);
	glColor3f(0, 0.8, 0);
	if (change == 0)
		glutSolidSphere(10, 20, 20);
	else
		glutWireSphere(10, 20, 20);
	glPopMatrix();
	glPushMatrix();
	glColor3f(0, 0.0, 1);
	glRotatef(45, 0.0, 0.0, 1.0);
	glutWireSphere(200, 1, 20);
	glutWireSphere(-200, 1, 20);

	glRotatef(spd_arr[4][1], 0.0, 1.0, 0.0);
	glTranslatef(200, 0, 0);
	glColor3f(1, 0.8, 0);
	if (change == 0)
		glutSolidSphere(30, 30, 30);
	else
		glutWireSphere(30, 30, 30);
	glColor3f(0, 0.0, 1);
	glutWireSphere(50, 1, 20);
	glutWireSphere(-50, 1, 20);

	glRotatef(spd_arr[5][1], 0.0, 1.0, 0.0);
	glTranslatef(50, 0, 0);
	glColor3f(0, 0.8, 0);
	if (change == 0)
		glutSolidSphere(10, 20, 20);
	else
		glutWireSphere(10, 20, 20);
	glPopMatrix();
	/****************************************************/
	glPopMatrix();
	glEnable(GL_DEPTH_TEST);
	glFlush();
	glutSwapBuffers();

}
GLvoid Reshape(int w, int h)
{
	win_w = w;
	win_h = h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (Projection) {
		gluPerspective(60.0f, w / h, 1.0, 1000.0);
		glTranslatef(0.0, 0.0, -500.0);
	}
	else
		glOrtho(-400.0, 400.0, -300.0, 300.0, -300.0, 300.0);
	//glMatrixMode(GL_MODELVIEW);

}
