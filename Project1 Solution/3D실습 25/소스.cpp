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
struct SPRING {
	double h;
	int upper_r;
	int mode;
};
pos camera;
SPRING spr;
bool CULL, DEPTH,SHADE;
int front = 0;
int front_r = 0;
int front_mode = -1;
GLdouble rotate[16]
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
void Init()
{
	camera.x = 0;
	camera.y = 0;
	camera.z = 0;
	CULL = 1;
	DEPTH = 1;
	SHADE = 1;
	spr.h = 0.025;
	spr.mode = -1;
	Init_array(rotate);

	
}
void Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
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
		camera.y += 2;
		break;
	case 's':
		camera.y -= 2;
		break;
	case 'a':
		camera.x -= 2;
		break;
	case 'd':
		camera.x += 2;
		break;
	case '+':
		camera.z -= 2;
		break;
	case '-':
		camera.z += 2;
		break;
	case '1':
		if(CULL)
			CULL = false;
		else
			CULL = true;
		break;
	case '2':
		if (DEPTH)
			DEPTH = false;
		else
			DEPTH = true;
		break;
	case '3':
		if (SHADE)
			SHADE = false;
		else
			SHADE = true;
		break;
	case '4':
		spr.mode*=-1;
		break;
	case '5':
		front_mode *= -1;
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
	if (spr.mode == 1) {
		if (spr.upper_r <= 90)
		{
			spr.upper_r+=3;
		}
		else if (spr.h < 0.2)
			spr.h += 0.01;
	}
	else {
		if (spr.h >= 0.025)
			spr.h -= 0.01;
		else if(spr.upper_r >= 0)
		{
			spr.upper_r-=3;
		}
	}
	if (front_mode == 1) {
		if (front_r <= 90)
		{
			front_r += 3;
		}
		else if (front < 360)
			front += 5;
	}
	else {
		if (front >= 0)
			front -= 5;
		else if (front_r >= 0)
		{
			front_r -= 3;
		}
	}
	glutPostRedisplay();
	glutTimerFunc(50, TimerFunction, 1);
}
void main(int argc, char *argv[])
{
	Init();
	srand(time(NULL));
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
void drawRec(float size)
{
	if(SHADE)
		glShadeModel(GL_SMOOTH);
	else
		glShadeModel(GL_FLAT);
	
	
	//윗면
	glPushMatrix(); {
		glTranslatef(0, 50, -50);
		glRotatef(-spr.upper_r, 1.0, 0.0, 0.0);
		glTranslatef(0, 0, 50);
		glScalef(100, 100, 100);
		glBegin(GL_QUADS);
		glColor3f(0, 1, 0);
		glVertex3f(-size / 2, 0, -size / 2); //1
		glColor3f(1, 1, 0);
		glVertex3f(-size / 2, 0, size / 2);// 2
		glColor3f(1, 1, 1);
		glVertex3f(size / 2, 0, size / 2);// 3
		glColor3f(0, 1, 1);
		glVertex3f(size / 2, 0, -size / 2);//4
		glEnd();
	}glPopMatrix();

	//앞면		 
	glPushMatrix(); {
		glTranslatef(0, -50, 50);
		glRotatef(front_r, 1.0, 0.0, 0.0);
		glTranslatef(0, 50, 0);
		glScalef(100, 100, 100);
		glBegin(GL_QUADS);
		glColor3f(1, 1, 0);
		glVertex3f(-size/2, size/2, 0);//2
		glColor3f(1, 0, 0);
		glVertex3f(-size/2, -size/2, 0);//6
		glColor3f(1, 0, 1);
		glVertex3f(size/2, -size/2, 0);//7
		glColor3f(1, 1, 1);
		glVertex3f(size/2, size/2, 0);//3
		glEnd();
	}glPopMatrix();
	glScalef(100, 100, 100);
	glBegin(GL_QUADS);
	//오른쪽옆면
	glColor3f(1, 1, 1);
	glVertex3f(size/2, size/2, size/2);//3
	glColor3f(1, 0, 1);
	glVertex3f(size/2, -size/2, size/2);//7
	glColor3f(0, 0, 1);
	glVertex3f(size/2, -size/2, -size/2);//8
	glColor3f(0, 1, 1);
	glVertex3f(size/2, size/2, -size/2);//4
	//왼쪽옆면
	glColor3f(0, 1, 0);
	glVertex3f(-size/2, size/2, -size/2);//1
	glColor3f(0, 0, 0);
	glVertex3f(-size/2, -size/2, -size/2);//5
	glColor3f(1, 0, 0);
	glVertex3f(-size/2, -size/2, size/2);//6
	glColor3f(1, 1, 0);
	glVertex3f(-size/2, size/2, size/2);//2
	//뒷면
	glColor3f(0, 1, 1);
	glVertex3f(size / 2, size / 2, -size / 2);//4
	glColor3f(0, 0, 1);
	glVertex3f(size / 2, -size / 2, -size / 2);//8
	glColor3f(0, 0, 0);
	glVertex3f(-size/2, -size/2, -size/2);//5
	glColor3f(0, 1, 0);
	glVertex3f(-size/2, size/2, -size/2);//1
	//바닥면
	glColor3f(1, 0, 0);
	glVertex3f(-size/2, -size/2, size/2);//6
	glColor3f(0, 0, 0);
	glVertex3f(-size/2, -size/2, -size/2);//5
	glColor3f(0, 0, 1);
	glVertex3f(size/2, -size/2, -size/2);//8
	glColor3f(1, 0, 1);
	glVertex3f(size/2, -size/2, size/2);//7

	glEnd();
}
GLvoid drawScene(GLvoid)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	if(CULL==1)
		glEnable(GL_CULL_FACE);
	else
		glDisable(GL_CULL_FACE);
	if (DEPTH==1)
		glEnable(GL_DEPTH_TEST);
	else
		glDisable(GL_DEPTH_TEST);
	glPushMatrix();

	gluLookAt(0 + camera.x, 200 + camera.y, 500 + camera.z, 0.0 + camera.x, 0.0 + camera.y, 0.0, 0.0, 1, 0.0);
	glMultMatrixd(rotate);
	/****************************************************/
	glRotatef(30, 1.0, 0.0, 0.0);
	glRotatef(45, 0.0, 1.0, 0.0);
	
	glPushMatrix();
	drawRec(1);
	glPopMatrix();
	glPushMatrix();
	glPushMatrix(); {
		glColor3f(1, 0, 0);
		glTranslatef(0, spr.h * 1800-20, 0);
		glutWireSphere(30, 20, 20);
	}glPopMatrix();
	glTranslatef(0, -50, 0);
	glColor3f(0.5, 0.5, 0.5);
	for (float i = 0; i < 2160; i++)
	{
		glBegin(GL_LINES);

		glVertex3d(30 * cos(RADIAN*(i)), 30 * sin(RADIAN*i*0.1) + i * spr.h, 30 * sin(RADIAN*(i)));
		glVertex3d(30 * cos(RADIAN*(i + 1)), 30 * sin(RADIAN*((i + 1)*0.1)) + (i + 1)*spr.h, 30 * sin(RADIAN*((i + 1))));
		glEnd();
	}
	glPopMatrix();
	glPushMatrix(); {
		glColor3f(1, 0, 0);

		glTranslatef(0, -15, 30 * PI * 2 * front / 360);
		glRotatef(front, 1.0, 0.0, 0.0);
		glutWireSphere(30, 20, 20);
	}glPopMatrix();
	/****************************************************/
	glPopMatrix();
	
	glFlush();
	glutSwapBuffers();
}
GLvoid Reshape(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(60.0f, w / h, 1.0, 2000.0);
	glTranslatef(0.0, 0.0, -500.0);
	glMatrixMode(GL_MODELVIEW);
}
