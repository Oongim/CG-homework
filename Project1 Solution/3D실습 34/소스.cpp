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
	int mode;
	int speed;
};

pos O;
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
struct Running {
	int r_run;
	int r_leg;
	int r_vel;
};

int bottom_color[50][50] = { 0 };
int snow_arr[100][4];
bool isLight1 = true;
bool isLight2 = true;
bool isrotate = false;
bool isVector = true;
bool isSnow = true;
float diffuse_num = 1;
float Specular_num = 1;
float ambient_num = 0;
float rotate1;
float rotate2;
float rotatemoon;
Running R;
void init_snow()
{
	for (int i = 0; i < 100; ++i)
	{
		snow_arr[i][0] = rand() % 999 - 500;
		snow_arr[i][1] = rand() % 999 - 500;
		snow_arr[i][2] = rand() % 100 + 500;
		snow_arr[i][3] = rand() % 6 + 4;
	}
}
void update_snow()
{
	for (int i = 0; i < 100; ++i)
	{
		snow_arr[i][2] -= snow_arr[i][3];
		if (snow_arr[i][2] <= -250)
		{
			bottom_color[(snow_arr[i][0] +500) / 20][(snow_arr[i][1] +500) / 20] += 2;
			snow_arr[i][0] = rand() % 999 - 500;
			snow_arr[i][1] = rand() % 999 - 500;
			snow_arr[i][2] = rand() % 100 + 500;
			snow_arr[i][3] = rand() % 6 + 4;
		}
	}
}
void draw_snow()
{
	glColor3f(1, 1, 1);
	for (int i = 0; i < 100; ++i)
	{
		glPushMatrix(); {
			glTranslated(snow_arr[i][0], snow_arr[i][2], snow_arr[i][1]);
			glutSolidSphere(5, 10, 10);
		}glPopMatrix();
	}
}
void Init()
{
	camera.x = 0;
	camera.y = 0;
	camera.z = 50;
	Init_array(rotate);
	init_snow();
	O.dir = 5;
	O.z = -200;
	O.mode = 0;
	R.r_vel = 5;
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
		O.mode = 180;


		break;
	case 's':
		O.mode = 0;

		break;
	case 'a':
		O.mode = 270;

		break;
	case 'd':
		O.mode = 90;

		break;
	case '+':
		camera.x -= 2;
		break;
	case '-':
		camera.x += 2;
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
	case'3':
		if (isSnow)
			isSnow = false;
		else {
			isSnow = true;
			init_snow();
		}
		break;
	case 'o':
		if (isVector)
			isVector = false;
		else
			isVector = true;
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
	if (O.mode == 0)
	{
		O.z += O.dir;
		if (O.z >= 450 || O.z <= -450 ) {
			O.z -= O.dir;
		}
	}
	else if (O.mode == 90)
	{
		O.x += O.dir;
		if (O.x >= 450 || O.x <= -450 ) {
			O.x -= O.dir;
		}
	}
	else if (O.mode == 180)
	{
		O.z -= O.dir;
		if (O.z >= 450 || O.z <= -450 ) {
			O.z += O.dir;
		}
	}
	else if (O.mode == 270)
	{
		O.x -= O.dir;
		if (O.x >= 450 || O.x <= -450 ) {
			O.x += O.dir;
		}
	}
	R.r_run += 5;
	R.r_leg += R.r_vel;
	if (R.r_leg > 45 || R.r_leg < -45)
		R.r_vel *= -1;
		rotate1++;
		rotate2++;
	rotatemoon -= 3;
	if (isSnow)
		update_snow();
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
void pyramid(float size)
{
	glBegin(GL_TRIANGLES);
	if (isVector)
		glNormal3f(0, 0, 1);
	glVertex3f(0, size / 2, 0);//2
	glVertex3f(-size / 2, -size / 2, size / 2);//6
	glVertex3f(size / 2, -size / 2, size / 2);//7
	if (isVector)
		glNormal3f(1, 0, 0);
	glVertex3f(0, size / 2, 0);//2
	glVertex3f(size / 2, -size / 2, size / 2);//7
	glVertex3f(size / 2, -size / 2, -size / 2);//8
	if (isVector)
		glNormal3f(-1, 0, 0);
	glVertex3f(0, size / 2, 0);//2
	glVertex3f(-size / 2, -size / 2, -size / 2);//5
	glVertex3f(-size / 2, -size / 2, size / 2);//6
	if (isVector)
		glNormal3f(0, 0, -1);
	glVertex3f(0, size / 2, 0);//2
	glVertex3f(size / 2, -size / 2, -size / 2);//8
	glVertex3f(-size / 2, -size / 2, -size / 2);//5
	glEnd();
	glBegin(GL_QUADS);
	glNormal3f(0, -1, 0);
	glVertex3f(-size / 2, -size / 2, size / 2);//6
	glVertex3f(-size / 2, -size / 2, -size / 2);//5
	glVertex3f(size / 2, -size / 2, -size / 2);//8
	glVertex3f(size / 2, -size / 2, size / 2);//7
	glEnd();
}

void draw_bottom(float size)
{
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	for (int i = 0; i < 50; ++i)
	{
		for (int j = 0; j < 50; ++j)
		{
			glColor3f(0.1*bottom_color[i][j]+0.1, 0.1*bottom_color[i][j] + 0.1, 0.1*bottom_color[i][j] + 0.1);
			glVertex3f(-size / 2 + size / 50 * i, -250, -size / 2 + size / 50 * j);//5
			glVertex3f(-size / 2 + size / 50 * i, -250, -size / 2 + size / 50 * (j + 1));//6
			glVertex3f(-size / 2 + size / 50 * (i + 1), -250, -size / 2 + size / 50 * (j + 1));//7
			glVertex3f(-size / 2 + size / 50 * (i + 1), -250, -size / 2 + size / 50 * j);//8
		}
	}

	glEnd();
}
void drawRobot(float x,float y,float z)
{
	glPushMatrix();//맨아래

	glTranslatef(O.x, y, O.z);
	glRotatef(O.mode, 0.0, 1.0, 0.0);
	/**************************************************/
	glPushMatrix(); {
		glTranslatef(0, 100, 0);
		glPushMatrix(); {
			glTranslatef(0 + 15, -50, 0);
			glRotatef(-R.r_leg, 1.0, 0.0, 0.0);
			glTranslatef(0, -50, 0);

			glScalef(30, 100, 30);
			glColor3f(1, 0, 0);
			glutSolidCube(1);
		}glPopMatrix();
		glPushMatrix(); {
			glTranslatef(0 - 15, -50, 0);
			glRotatef(R.r_leg, 1.0, 0.0, 0.0);
			glTranslatef(0, -50, 0);

			glScalef(30, 100, 30);
			glColor3f(1, 0, 0);
			glutSolidCube(1);
		}glPopMatrix();
		/*****************************************************/
		glPushMatrix(); {
			glTranslatef(0 + 50, 50, 0);
			glRotatef(R.r_leg, 1.0, 0.0, 0.0);
			glTranslatef(0, -50, 0);

			glScalef(30, 100, 30);
			glColor3f(0, 1, 0);
			glutSolidCube(1);
		}glPopMatrix();
		glPushMatrix(); {
			glTranslatef(0 - 50, 50, 0);
			glRotatef(-R.r_leg, 1.0, 0.0, 0.0);
			glTranslatef(0, -50, 0);

			glScalef(30, 100, 30);
			glColor3f(0, 1, 0);
			glutSolidCube(1);
		}glPopMatrix();
		/*******************************************************/
		glPushMatrix(); {
			glTranslatef(0, 0, 0);

			glScalef(70, 100, 50);
			glColor3f(0, 0, 1);
			glutSolidCube(1);
		}glPopMatrix();
		glPushMatrix(); {
			glTranslatef(0, 70, 0);

			glScalef(2, 2, 2);
			glColor3f(1, 0.4, 0.5);
			glutSolidCube(20);
			glPushMatrix(); {
				glTranslatef(0, 0, 13);

				glScalef(1, 2, 1);
				glColor3f(0.9, 0.9, 0.9);
				glutSolidCube(5);
			}glPopMatrix();
		}glPopMatrix();
	}glPopMatrix();
	glPopMatrix();
}
GLvoid drawScene(GLvoid)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();

	gluLookAt(0 ,  100, 500, 0.0 , 0.0 , 0.0 , 0.0, 1, 0.0);
	glMultMatrixd(rotate);
	/****************************************************/
	glDisable(GL_LIGHTING);
	if (isSnow)
		draw_snow();
	
	GLfloat ambientLight[] = { 0.0f, ambient_num, 0.0f, 1.0f };
	GLfloat DiffuseLightr[] = { diffuse_num + 1, diffuse_num,diffuse_num, 1.0f };
	GLfloat DiffuseLightb[] = { diffuse_num , diffuse_num,diffuse_num + 1, 1.0f };
	GLfloat DiffuseLight[] = { 1, 1,1, 1.0f };
	GLfloat SpecularLight[] = { Specular_num, Specular_num, Specular_num, 1.0 }; // 백색조명
	GLfloat lightPos1[] = { 500.0, 0.0, 0.0, 1.0 };
	GLfloat lightPos2[] = { -500.0, 0.0, 0.0, 1.0 };
	GLfloat lightPos3[] = { O.x, 100, O.z };

	GLfloat gray[] = { 0.75f, 0.75f, 0.75f, 1.0f };
	GLfloat specref[] = { Specular_num, Specular_num, Specular_num, 1.0f };
	GLfloat lightVector[] = { 0,-1,0 };

	GLfloat radian[] = { 60 };
	GLfloat exponent[] = {30};
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, gray);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
	glMateriali(GL_FRONT, GL_SHININESS, 128);
	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	
	glPushMatrix(); {
		glTranslated(0, -200, 0);
		pyramid(300);
	}glPopMatrix();
	glPushMatrix(); {
		glRotated(rotatemoon, 0, 1, 0);
		glTranslated(100, 200, 0);
		glutSolidSphere(50, 40, 40);
	}glPopMatrix();
	/*glPushMatrix(); {
		glRotated(rotate1, 0, 1, 0);
		glEnable(GL_LIGHT0);

		glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLightr);
		glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularLight);
		glLightfv(GL_LIGHT0, GL_POSITION, lightPos1);

		if (!isLight1) {
			glDisable(GL_LIGHT0);
		}
	}glPopMatrix();

	glPushMatrix(); {
		glRotated(rotate2, 0, 1, 0);
		glEnable(GL_LIGHT1);

		glLightfv(GL_LIGHT1, GL_AMBIENT, ambientLight);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, DiffuseLightb);
		glLightfv(GL_LIGHT1, GL_SPECULAR, SpecularLight);
		glLightfv(GL_LIGHT1, GL_POSITION, lightPos2);

		if (!isLight2) {
			glDisable(GL_LIGHT1);
		}
	}glPopMatrix();*/
	glPushMatrix(); {
		glTranslated(O.x, 100, O.z);
		glEnable(GL_LIGHT2);
		glLightfv(GL_LIGHT2, GL_POSITION, lightPos3);
		glLightfv(GL_LIGHT2, GL_AMBIENT, ambientLight);
		glLightfv(GL_LIGHT2, GL_DIFFUSE, DiffuseLight);
		glLightfv(GL_LIGHT2, GL_SPECULAR, SpecularLight);
						  
		glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, lightVector);
		glLightfv(GL_LIGHT2, GL_SPOT_CUTOFF, radian);
		glLightfv(GL_LIGHT2, GL_SPOT_EXPONENT, exponent);

	}glPopMatrix();
	
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specref); 
	glMateriali(GL_FRONT, GL_SHININESS, 128);
	draw_bottom(1000);
	drawRobot(100, -200, 100);
	glDisable(GL_COLOR_MATERIAL);
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
