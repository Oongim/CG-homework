#include <GL/freeglut.h>
#include<time.h>
#include<stdlib.h>
#include<math.h>
#define PI 3.14
#define RADIAN PI/180
#define MAX 5
#define PLUS 1
#define MINUS 0
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
struct pos {
	float x, y, z;
};
struct BALL {
	float x, y, z;
	int x_dir, y_dir, z_dir;
};
struct REC {
	float x, y, z;
	int x_dir, y_dir, z_dir;
	int size;
};
pos camera;
BALL ball[MAX];
REC rec[3];
int rotate_y;
int rotate_z;
bool left_button;
bool rotate_mode;
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
	srand(time(NULL));
	camera.x = 0;
	camera.y = 0;
	camera.z = 0;
	Init_array(rotate);
	for (int i = 0; i < MAX; ++i)
	{
		ball[i].x = rand() % 92 - 46;
		ball[i].y = rand() % 92 - 46;
		ball[i].z = rand() % 92 - 46;
		ball[i].x_dir = rand() % 7 - 3;
		ball[i].y_dir = rand() % 7 - 3;
		ball[i].z_dir = rand() % 7 - 3;
		while (ball[i].x_dir == 0 && ball[i].y_dir == 0 && ball[i].z_dir == 0)
		{
			ball[i].x_dir = rand() % 7 - 3;
			ball[i].y_dir = rand() % 7 - 3;
			ball[i].z_dir = rand() % 7 - 3;
		}
	}

	rec[0].z = 12;
	rec[1].z = 0;
	rec[2].z = -14;
	for (int i = 0; i < 3; ++i) {
		rec[i].size = 10 + 2 * i;
		rec[i].x = -1;
		//rec[i].y = -50 + rec[i].size / 2;
	}
	
}
void Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'b':
		for (int i = 0; i < MAX; ++i)
		{
			ball[i].x = rand() % 92 - 46;
			ball[i].y = rand() % 92 - 46;
			ball[i].z = rand() % 92 - 46;
			ball[i].x_dir = rand() % 7 - 3;
			ball[i].y_dir = rand() % 7 - 3;
			ball[i].z_dir = rand() % 7 - 3;
			while (ball[i].x_dir == 0 && ball[i].y_dir == 0 && ball[i].z_dir == 0)
			{
				ball[i].x_dir = rand() % 7 - 3;
				ball[i].y_dir = rand() % 7 - 3;
				ball[i].z_dir = rand() % 7 - 3;
			}
		}
		break;
	case 'y':
		rotate_y++;
		break;
	case 'Y':
		rotate_y--;
		break;
	case 'z':
		rotate_z++;
		break;
	case 'Z':
		rotate_z--;
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
	default:
		break;
	}

}
void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		left_button = true;
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		left_button = false;
	}
	glutPostRedisplay();
}
void Motion(int x, int y) {
	static double prev_mx = 0;
	if (left_button == true)
	{
		if (x > prev_mx) {
			rotate_z+=3;
			rotate_mode = PLUS;
		}
		else if (x < prev_mx) {
			rotate_z-=3;
			rotate_mode = MINUS;
		}
		rotate_z = rotate_z % 360;
		glutPostRedisplay();
		prev_mx = x;
	}
}
void TimerFunction(int value)
{
	for (int i = 0; i < MAX; ++i)
	{
		ball[i].x += ball[i].x_dir;
		ball[i].y += ball[i].y_dir;
		ball[i].z += ball[i].z_dir;
		if (ball[i].x >= 46 || ball[i].x <= -46)
		{
			ball[i].x_dir *= -1;
			if (ball[i].x >= 46)
				ball[i].x = 46;
			else
				ball[i].x = -46;
		}
		if (ball[i].y >= 46 || ball[i].y <= -46)
		{
			ball[i].y_dir *= -1;
			if (ball[i].y >= 46)
				ball[i].y = 46;
			else		
				ball[i].y = -46;
		}
		if (ball[i].z >= 46 || ball[i].z <= -46)
		{
			ball[i].z_dir *= -1;
			if (ball[i].z >= 46)
				ball[i].z = 46;
			else		
				ball[i].z = -46;
		}
	}
	int R = rotate_z;
	if (R < 0)
		R *= -1;
	R = R % 360;
	for (int i = 0; i < 3; ++i) {
		if (rec[i].y >= -(50 - rec[i].size / 2) && rec[i].y <= (50 - rec[i].size / 2)
			&& rec[i].x >= -(50 - rec[i].size / 2) && rec[i].x <= (50 - rec[i].size / 2)) 
		{
			if (rotate_mode == PLUS) {
				if (rec[i].y < rec[i].x&&rec[i].y<=-rec[i].x&&R<=90) {
					rec[i].y -= R / 4;
					rec[i].x -= (R / 4);
				}
				else if (rec[i].y >= rec[i].x&&rec[i].y < -rec[i].x&&R<=180)
				{
						rec[i].y += (R - 90) / 4;
						rec[i].x -= ((R - 90) / 4);
				}
				else if (rec[i].y > rec[i].x&&rec[i].y >= -rec[i].x&&R <= 270)
				{
					rec[i].y += (R -180) / 4;
					rec[i].x += ((R - 180) / 4);
				}
				else if (rec[i].y <= rec[i].x&&rec[i].y > -rec[i].x&&R <= 360)
				{
					rec[i].y -= (R - 270) / 4;
					rec[i].x += ((R - 270) / 4);
				}
			}
			/*else if (rotate_mode == MINUS) {
				if (R > 0 && R < 90)
				{
					rec[i].y -= R / 4;
					rec[i].x += (R / 4);
				}
				else if (R > 90 && R < 180)
				{
					rec[i].y += (R - 90) / 4;
					rec[i].x += ((R - 90) / 4);
				}
				if (R > 180 && R < 270)
				{
					rec[i].y += (R - 180) / 4;
					rec[i].x -= ((R - 180) / 4);
				}
				else if (R > 270 && R < 360)
				{
					rec[i].y -= (R - 270) / 4;
					rec[i].x -= ((R - 270) / 4);
				}
			}*/
			if (rec[i].y < -(50 - rec[i].size / 2))
				rec[i].y = -(50 - rec[i].size / 2);
			if(rec[i].y > (50 - rec[i].size / 2))
				rec[i].y = (50 - rec[i].size / 2);
			if (rec[i].x < -(50 - rec[i].size / 2))
				rec[i].x = -(50 - rec[i].size / 2);
			if (rec[i].x > (50 - rec[i].size / 2))
				rec[i].x = (50 - rec[i].size / 2);

		}
	}
	glutPostRedisplay();
	glutTimerFunc(50, TimerFunction, 1);
}
void main(int argc, char *argv[])
{
	Init();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정
	glutCreateWindow("실습1"); // 윈도우 생성 (윈도우 이름)
	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutTimerFunc(50, TimerFunction, 1);
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}
// 윈도우 출력 함수
void drawRec(float size)
{
	glBegin(GL_QUADS);
	//윗면
	glColor3f(1, 0, 0);
	glVertex3f(-size / 2, size / 2, -size / 2); //1
	glVertex3f(-size / 2, size / 2, size / 2);// 2
	glVertex3f(size / 2, size / 2, size / 2);// 3
	glVertex3f(size / 2, size / 2, -size / 2);//4
	//앞면		 
	glColor3f(0.9, 0, 0);
	glVertex3f(-size / 2, size / 2, size / 2);//2
	glVertex3f(-size / 2, -size / 2, size / 2);//6
	glVertex3f(size / 2, -size / 2, size / 2);//7
	glVertex3f(size / 2, size / 2, size / 2);//3
	//오른쪽옆면
	glColor3f(0.8, 0, 0);
	glVertex3f(size / 2, size / 2, size / 2);//3
	glVertex3f(size / 2, -size / 2, size / 2);//7
	glVertex3f(size / 2, -size / 2, -size / 2);//8
	glVertex3f(size / 2, size / 2, -size / 2);//4
	//왼쪽옆면
	glColor3f(0.7, 0, 0);
	glVertex3f(-size / 2, size / 2, -size / 2);//1
	glVertex3f(-size / 2, -size / 2, -size / 2);//5
	glVertex3f(-size / 2, -size / 2, size / 2);//6
	glVertex3f(-size / 2, size / 2, size / 2);//2
	//뒷면
	glColor3f(0.6, 0, 0);
	glVertex3f(size / 2, size / 2, -size / 2);//4
	glVertex3f(size / 2, -size / 2, -size / 2);//8
	glVertex3f(-size / 2, -size / 2, -size / 2);//5
	glVertex3f(-size / 2, size / 2, -size / 2);//1

	//바닥면
	glColor3f(1, 0, 0);
	glVertex3f(-size / 2, -size / 2, size / 2);//6
	glVertex3f(-size / 2, -size / 2, -size / 2);//5
	glVertex3f(size / 2, -size / 2, -size / 2);//8
	glVertex3f(size / 2, -size / 2, size / 2);//7

	glEnd();
}
void drawRecBOX(float size)
{
	glFrontFace(GL_CW);
	glBegin(GL_QUADS);
	//윗면
	glColor3f(0.5, 0.5, 0.5);
	glVertex3f(-size / 2, size / 2, -size / 2); //1
	glVertex3f(-size / 2, size / 2, size / 2);// 2
	glVertex3f(size / 2, size / 2, size / 2);// 3
	glVertex3f(size / 2, size / 2, -size / 2);//4
	//앞면		 
	glColor3f(0.9, 0.9, 0.9);
	glVertex3f(-size / 2, size / 2, size / 2);//2
	glVertex3f(-size / 2, -size / 2, size / 2);//6
	glVertex3f(size / 2, -size / 2, size / 2);//7
	glVertex3f(size / 2, size / 2, size / 2);//3
	//오른쪽옆면
	glColor3f(0.2, 0.2, 0.2);
	glVertex3f(size / 2, size / 2, size / 2);//3
	glVertex3f(size / 2, -size / 2, size / 2);//7
	glVertex3f(size / 2, -size / 2, -size / 2);//8
	glVertex3f(size / 2, size / 2, -size / 2);//4
	//왼쪽옆면
	glColor3f(0.4, 0.4, 0.4);
	glVertex3f(-size / 2, size / 2, -size / 2);//1
	glVertex3f(-size / 2, -size / 2, -size / 2);//5
	glVertex3f(-size / 2, -size / 2, size / 2);//6
	glVertex3f(-size / 2, size / 2, size / 2);//2
	//뒷면
	glColor3f(0.8, 0.8, 0.8);
	glVertex3f(size / 2, size / 2, -size / 2);//4
	glVertex3f(size / 2, -size / 2, -size / 2);//8
	glVertex3f(-size / 2, -size / 2, -size / 2);//5
	glVertex3f(-size / 2, size / 2, -size / 2);//1

	//바닥면
	glColor3f(0.6, 0.6, 0.6);
	glVertex3f(-size / 2, -size / 2, size / 2);//6
	glVertex3f(-size / 2, -size / 2, -size / 2);//5
	glVertex3f(size / 2, -size / 2, -size / 2);//8
	glVertex3f(size / 2, -size / 2, size / 2);//7

	glEnd();
	glFrontFace(GL_CCW);
}
GLvoid drawScene(GLvoid)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();

	gluLookAt(0 + camera.x, camera.y, 100, 0.0 + camera.x, 0.0 + camera.y, 0.0 + camera.z, 0.0, 1, 0.0);
	glRotatef(rotate_y, 0.0, 1.0, 0.0);
	glRotatef(rotate_z, 0.0, 0.0, 1.0);
	/****************************************************/
	drawRecBOX(100);

	for (int i = 0; i < 3; ++i) {
		glPushMatrix();
		glTranslatef(rec[i].x, rec[i].y, rec[i].z);
		drawRec(rec[i].size);
		glPopMatrix();
	}

	/********************공***************************/
	for (int i = 0; i < MAX; ++i)
	{
		glPushMatrix();
		glColor3f(0, 0, 1);
		glTranslatef(ball[i].x, ball[i].y, ball[i].z);
		glutSolidSphere(4, 10, 10);
		glPopMatrix();
	}
	/****************************************************/
	glPopMatrix();
	glEnable(GL_CULL_FACE);
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
	glTranslatef(0.0, 0.0, -200.0);
	glMatrixMode(GL_MODELVIEW);
}
