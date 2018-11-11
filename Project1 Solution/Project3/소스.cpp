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
int Shape_mode = 0, Rotate_mode = 0;
int Rotate_object = 0, Rotate_object1 = 0, Rotate_object2 = 0;
int angle = 0;
double win_w = 800, win_h = 600;
bool Projection = true;
Point camera;
float theta, phi;

double r = 0;
GLdouble rotate[16]
= { 1,0,0,0,
	0,1,0,0,
	0,0,1,0,
	0,0,0,1 };
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
	case 'g':                             //초기화
		camera.x = 0;
		camera.y = 0;
		camera.z = 500;
		theta = 0;
		rotate[0] = 1;rotate[1] = 0; rotate[2] = 0; rotate[3] = 0;
		rotate[4] = 0;rotate[5] = 1; rotate[6] = 0; rotate[7] = 0;
		rotate[8] = 0; rotate[9] = 0; rotate[10] = 1; rotate[11] = 0;
		rotate[12] = 0; rotate[13] = 0; rotate[14] = 0; rotate[15] = 1;

		break;
	case '+':
		theta += 2;

		break;
	case '-':
		theta -= 2;
		break;
	case 'i':
		r -= 5;
		break;
	case 'o':
		r += 5;
		break;
	case 'w':
		Rotate_object += 5;
		break;
	case 'q':
		Rotate_object1 += 5;
		break;
	case 'r':
		Rotate_object2 += 5;
		break;
	case 'c':
		Shape_mode++;
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
	Rotate_object += 5;
	glutPostRedisplay();
	glutTimerFunc(50, TimerFunction, 1);
}
void main(int argc, char *argv[])
{
	camera.x = 0;
	camera.y = 100;
	r = 500;
	theta = 0;
	phi = 0;
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
	/*r = sqrt(pow(camera.x, 2) + pow(camera.y, 2) + pow(camera.z, 2));
	camera.x = r * cos(phi*RADIAN) * cos(theta*RADIAN);
	camera.y = r * sin(phi*RADIAN);
	camera.z = r * cfos(phi*RADIAN) * sin(theta*RADIAN);*/
	camera.x = r*cos(theta*RADIAN);
	camera.z = r * sin(theta*RADIAN);
	/****************************************************/
	
	glPushMatrix();
	gluLookAt(camera.x, camera.y, camera.z, 0.0, 0.0, 0.0, 0.0, 1, 0.0);
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
	glMultMatrixd(rotate);
	
	
	/****************************************************/
	glPushMatrix(); // 바닥
	glScalef(400, 1, 300);
	glTranslatef(0, -150, 0);
	glColor3f(1.0, 1.0, 0.0);
	glutSolidCube(1);
	glPopMatrix();


	glColor3f(0.0, 1.0, 1.0);
	if (Shape_mode == 0)
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
	glPopMatrix();
	glEnable(GL_DEPTH_TEST);
	glFlush();
	glutSwapBuffers();
}
GLvoid Reshape(int w, int h)
{
	win_w = w;
	win_h = h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	if (Projection) {
		gluPerspective(60.0f, w / h, 1.0, 1000.0);
		glTranslatef(0.0, 0.0, -100.0);
	}
	else
		glOrtho(-400.0, 400.0, -300.0, 300.0, -300.0, 300.0);
	glMatrixMode(GL_MODELVIEW);
}
