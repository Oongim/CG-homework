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
pos camera;
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
	camera.y = 100;
	camera.z = 100;
	Init_array(rotate);
}
bool isLight1 = true;
bool isLight2 = true;
bool isrotate = false;
float diffuse_num = 1;
float Specular_num = 1;
float rotate1;
float rotate2;
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
		if (Specular_num > 0)
			Specular_num -= 0.1;
		break;
	case 'S':
		if (Specular_num < 2)
			Specular_num += 0.1;
		break;
	case 'a':
		if (isrotate)
			isrotate = false;
		else
			isrotate = true;
		break;
	case 'd':
		if (diffuse_num > 0)
			diffuse_num -= 0.1;
		break;
	case 'D':
		if (diffuse_num < 1)
			diffuse_num += 0.1;
		break;
	case '+':
		camera.z -= 2;
		break;
	case '-':
		camera.z += 2;
		break;
	case '1':
		if (isLight1)
			isLight1 = false;
		else
			isLight1 = true;
		break;
	case '2':
		if (isLight2)
			isLight2 = false;
		else
			isLight2 = true;
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
	if (isrotate) {
		rotate1++;
		rotate2++;
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
	glBegin(GL_QUADS);
	//윗면
	glVertex3f(-size / 2, size / 2, -size / 2); //1
	glVertex3f(-size / 2, size / 2, size / 2);// 2
	glVertex3f(size / 2, size / 2, size / 2);// 3
	glVertex3f(size / 2, size / 2, -size / 2);//4
	//앞면		 
	glVertex3f(-size / 2, size / 2, size / 2);//2
	glVertex3f(-size / 2, -size / 2, size / 2);//6
	glVertex3f(size / 2, -size / 2, size / 2);//7
	glVertex3f(size / 2, size / 2, size / 2);//3
	//오른쪽옆면
	glVertex3f(size / 2, size / 2, size / 2);//3
	glVertex3f(size / 2, -size / 2, size / 2);//7
	glVertex3f(size / 2, -size / 2, -size / 2);//8
	glVertex3f(size / 2, size / 2, -size / 2);//4
	//왼쪽옆면
	glVertex3f(-size / 2, size / 2, -size / 2);//1
	glVertex3f(-size / 2, -size / 2, -size / 2);//5
	glVertex3f(-size / 2, -size / 2, size / 2);//6
	glVertex3f(-size / 2, size / 2, size / 2);//2
	//뒷면
	glVertex3f(size / 2, size / 2, -size / 2);//4
	glVertex3f(size / 2, -size / 2, -size / 2);//8
	glVertex3f(-size / 2, -size / 2, -size / 2);//5
	glVertex3f(-size / 2, size / 2, -size / 2);//1

	//바닥면
	glVertex3f(-size / 2, -size / 2, size / 2);//6
	glVertex3f(-size / 2, -size / 2, -size / 2);//5
	glVertex3f(size / 2, -size / 2, -size / 2);//8
	glVertex3f(size / 2, -size / 2, size / 2);//7

	glEnd();
}
GLvoid drawScene(GLvoid)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();

	gluLookAt(0 + camera.x, 200 + camera.y, 500, 0.0 + camera.x, 0.0 + camera.y, 0.0 + camera.z, 0.0, 1, 0.0);
	glMultMatrixd(rotate);
	/****************************************************/

	GLfloat ambientLight[] = { 0.1f, 0.1f, 0.1f, 1.0f };
	GLfloat DiffuseLight[] = { diffuse_num, diffuse_num,diffuse_num, 1.0f };
	GLfloat SpecularLight[] = { Specular_num, Specular_num, Specular_num, 1.0 }; // 백색조명
	GLfloat lightPos1[] = { 300.0, 0.0, 0.0, 1.0 };
	GLfloat lightPos2[] = { -300.0, 0.0, 0.0, 1.0 };

	GLfloat gray[] = { 0.75f, 0.75f, 0.75f, 1.0f };
	GLfloat specref[] = { Specular_num, Specular_num, Specular_num, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, gray);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
	glMateriali(GL_FRONT, GL_SHININESS, 128);
	//glEnable(GL_AUTO_NORMAL);
	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);



	glutSolidSphere(100, 40, 40);

	glPushMatrix(); {
		glRotated(rotate1, 0, 1, 0);
		glEnable(GL_LIGHT0);

		glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight);
		glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularLight);
		glLightfv(GL_LIGHT0, GL_POSITION, lightPos1);
		if (!isLight1) {
			glDisable(GL_LIGHT0);
		}
		glColor3f(1.0f, 0.0f, 0.0f);
		glTranslated(200, 0, 0);
		glRotated(90, 0, 1, 0);
		glutSolidCone(20, 20, 20, 20);
	}glPopMatrix();

	glPushMatrix(); {
		glRotated(rotate2, 0, 0, 1);
		glEnable(GL_LIGHT1);

		glLightfv(GL_LIGHT1, GL_AMBIENT, ambientLight);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, DiffuseLight);
		glLightfv(GL_LIGHT1, GL_SPECULAR, SpecularLight);
		glLightfv(GL_LIGHT1, GL_POSITION, lightPos2);
		if (!isLight2) {
			glDisable(GL_LIGHT1);
		}
		glColor3f(1.0f, 0.0f, 0.0f);
		glTranslated(-200, 0, 0);
		glRotated(-90, 0, 1, 0);
		glutSolidCone(20, 20, 20, 20);
	}glPopMatrix();

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
	gluPerspective(60.0f, w / h, 1.0, 2000.0);
	glTranslatef(0.0, 0.0, -500.0);
	glMatrixMode(GL_MODELVIEW);
}
