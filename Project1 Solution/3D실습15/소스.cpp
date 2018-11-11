#include <GL/freeglut.h>
#include<time.h>
#include<stdlib.h>
#include<math.h>

#define PI 3.14
#define RADIAN PI/180
#define Size 20

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
int Rotate = 0;

tm curr_time;
time_t now;
int arr[6][7][4] = { {{-355,100},{-335,100,90},{-275,100},{-335,20,90},{-355,20}, {-335,-60,90},{-275,20}},
					 {{-355+110,100},{-335 + 110,100,90},{-275 + 110,100},{-335 + 110,20,90},{-355 + 110,20}, {-335 + 110,-60,90},{-275 + 110,20}},
					 {{-355+250,100},{-335 + 250,100,90},{-275 + 250,100},{-335 + 250,20,90},{-355 + 250,20}, {-335 + 250,-60,90},{-275 + 250,20}},
					 {{-355+360,100},{-335 + 360,100,90},{-275 + 360,100},{-335 + 360,20,90},{-355 + 360,20}, {-335 + 360,-60,90},{-275 + 360,20}},
					 {{-355+500,100},{-335 + 500,100,90},{-275 + 500,100},{-335 + 500,20,90},{-355 + 500,20}, {-335 + 500,-60,90},{-275 + 500,20}},
					 {{-355+610,100},{-335 + 610,100,90},{-275 + 610,100},{-335 + 610,20,90},{-355 + 610,20}, {-335 + 610,-60,90},{-275 + 610,20}}};

int point[4][3] = { {-355+220,80},{-355 + 220,0},{-355 + 470,80},{-355 + 470,0}};
void Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'y':
		Rotate += 5;
		break;
	case 'Y':
		Rotate -= 5;
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

		glutPostRedisplay();
	}
}
void TimerFunction(int value)
{
	if(curr_time.tm_sec%2==0)
		for (int i = 0; i < 4; ++i)
		{
			point[i][2] = 0;
		}
	else
		for (int i = 0; i < 4; ++i)
		{
			point[i][2] = 1;
		}
	for(int j=0;j<6;++j)
	{
		for(int i=0;i<7;++i)
		{
			arr[j][i][3] = 0;
		}
	}
	localtime_s(&curr_time, &now);
	now = time(0);
	/***********************************************************************/
	 if (curr_time.tm_hour / 10 == 1)
	{
		arr[0][2][3] = 1;
		arr[0][6][3] = 1;
	}
	 else if (curr_time.tm_hour / 10 == 2)
	 {
		 arr[1][1][3] = 1;
		 arr[1][2][3] = 1;
		 arr[1][3][3] = 1;
		 arr[1][4][3] = 1;
		 arr[1][5][3] = 1;
	 }
	/***********************************************************************/
	if (curr_time.tm_hour % 10 == 0)
	{
		arr[1][0][3] = 1;
		arr[1][1][3] = 1;
		arr[1][2][3] = 1;
		arr[1][4][3] = 1;
		arr[1][5][3] = 1;
		arr[1][6][3] = 1;
	}
	else if (curr_time.tm_hour % 10 == 1)
	{
		arr[1][2][3] = 1;
		arr[1][6][3] = 1;
	}
	else if (curr_time.tm_hour % 10 == 2)
	{
		arr[1][1][3] = 1;
		arr[1][2][3] = 1;
		arr[1][3][3] = 1;
		arr[1][4][3] = 1;
		arr[1][5][3] = 1;
	}
	else if (curr_time.tm_hour % 10 == 3)
	{
		arr[1][1][3] = 1;
		arr[1][2][3] = 1;
		arr[1][3][3] = 1;
		arr[1][6][3] = 1;
		arr[1][5][3] = 1;
	}
	else if (curr_time.tm_hour % 10 == 4)
	{
		arr[1][0][3] = 1;
		arr[1][3][3] = 1;
		arr[1][2][3] = 1;
		arr[1][6][3] = 1;
	}
	else if (curr_time.tm_hour % 10 == 5)
	{
		arr[1][1][3] = 1;
		arr[1][0][3] = 1;
		arr[1][3][3] = 1;
		arr[1][6][3] = 1;
		arr[1][5][3] = 1;
	}
	else if (curr_time.tm_hour % 10 == 6)
	{
		arr[1][0][3] = 1;
		arr[1][3][3] = 1;
		arr[1][4][3] = 1;
		arr[1][5][3] = 1;
		arr[1][6][3] = 1;
	}
	else if (curr_time.tm_hour % 10 == 7)
	{
		arr[1][1][3] = 1;
		arr[1][2][3] = 1;
		arr[1][6][3] = 1;
	}
	else if (curr_time.tm_hour % 10 == 8)
	{
		arr[1][0][3] = 1;
		arr[1][1][3] = 1;
		arr[1][2][3] = 1;
		arr[1][3][3] = 1;
		arr[1][4][3] = 1;
		arr[1][5][3] = 1;
		arr[1][6][3] = 1;
	}
	else if (curr_time.tm_hour % 10 == 9)
	{
		arr[1][0][3] = 1;
		arr[1][1][3] = 1;
		arr[1][2][3] = 1;
		arr[1][3][3] = 1;
		arr[1][6][3] = 1;
	}
	/************************************************************************/
	if (curr_time.tm_min / 10 == 0)
	{
		arr[2][0][3] = 1;
		arr[2][1][3] = 1;
		arr[2][2][3] = 1;
		arr[2][4][3] = 1;
		arr[2][5][3] = 1;
		arr[2][6][3] = 1;
	}
	else if (curr_time.tm_min / 10 == 1)
	{
		arr[2][2][3] = 1;
		arr[2][6][3] = 1;
	}
	else if (curr_time.tm_min / 10 == 2)
	{
		arr[2][1][3] = 1;
		arr[2][2][3] = 1;
		arr[2][3][3] = 1;
		arr[2][4][3] = 1;
		arr[2][5][3] = 1;
	}
	else if (curr_time.tm_min / 10 == 3)
	{
		arr[2][1][3] = 1;
		arr[2][2][3] = 1;
		arr[2][3][3] = 1;
		arr[2][6][3] = 1;
		arr[2][5][3] = 1;
	}
	else if (curr_time.tm_min / 10 == 4)
	{
		arr[2][0][3] = 1;
		arr[2][3][3] = 1;
		arr[2][2][3] = 1;
		arr[2][6][3] = 1;
	}
	else if (curr_time.tm_min / 10 == 5)
	{
		arr[2][1][3] = 1;
		arr[2][0][3] = 1;
		arr[2][3][3] = 1;
		arr[2][6][3] = 1;
		arr[2][5][3] = 1;
	}
	/************************************************************************/
	if (curr_time.tm_min % 10 == 0)
	{
		arr[3][0][3] = 1;
		arr[3][1][3] = 1;
		arr[3][2][3] = 1;
		arr[3][4][3] = 1;
		arr[3][5][3] = 1;
		arr[3][6][3] = 1;
	}
	else if (curr_time.tm_min % 10 == 1)
	{
		arr[3][2][3] = 1;
		arr[3][6][3] = 1;
	}
	else if (curr_time.tm_min % 10 == 2)
	{
		arr[3][1][3] = 1;
		arr[3][2][3] = 1;
		arr[3][3][3] = 1;
		arr[3][4][3] = 1;
		arr[3][5][3] = 1;
	}
	else if (curr_time.tm_min % 10 == 3)
	{
		arr[3][1][3] = 1;
		arr[3][2][3] = 1;
		arr[3][3][3] = 1;
		arr[3][6][3] = 1;
		arr[3][5][3] = 1;
	}
	else if (curr_time.tm_min % 10 == 4)
	{
		arr[3][0][3] = 1;
		arr[3][3][3] = 1;
		arr[3][2][3] = 1;
		arr[3][6][3] = 1;
	}
	else if (curr_time.tm_min % 10 == 5)
	{
		arr[3][1][3] = 1;
		arr[3][0][3] = 1;
		arr[3][3][3] = 1;
		arr[3][6][3] = 1;
		arr[3][5][3] = 1;
	}
	else if (curr_time.tm_min % 10 == 6)
	{
		arr[3][0][3] = 1;
		arr[3][3][3] = 1;
		arr[3][4][3] = 1;
		arr[3][5][3] = 1;
		arr[3][6][3] = 1;
	}
	else if (curr_time.tm_min % 10 == 7)
	{
		arr[3][1][3] = 1;
		arr[3][2][3] = 1;
		arr[3][6][3] = 1;
	}
	else if (curr_time.tm_min % 10 == 8)
	{
		arr[3][0][3] = 1;
		arr[3][1][3] = 1;
		arr[3][2][3] = 1;
		arr[3][3][3] = 1;
		arr[3][4][3] = 1;
		arr[3][5][3] = 1;
		arr[3][6][3] = 1;
	}
	else if (curr_time.tm_min % 10 == 9)
	{
		arr[3][0][3] = 1;
		arr[3][1][3] = 1;
		arr[3][2][3] = 1;
		arr[3][3][3] = 1;
		arr[3][6][3] = 1;
	}
	/************************************************************************/
	if (curr_time.tm_sec / 10 == 0)
	{
		arr[4][0][3] = 1;
		arr[4][1][3] = 1;
		arr[4][2][3] = 1;
		arr[4][4][3] = 1;
		arr[4][5][3] = 1;
		arr[4][6][3] = 1;
	}
	else if (curr_time.tm_sec / 10 == 1)
	{
		arr[4][2][3] = 1;
		arr[4][6][3] = 1;
	}
	else if (curr_time.tm_sec / 10 == 2)
	{
		arr[4][1][3] = 1;
		arr[4][2][3] = 1;
		arr[4][3][3] = 1;
		arr[4][4][3] = 1;
		arr[4][5][3] = 1;
	}
	else if (curr_time.tm_sec / 10 == 3)
	{
		arr[4][1][3] = 1;
		arr[4][2][3] = 1;
		arr[4][3][3] = 1;
		arr[4][6][3] = 1;
		arr[4][5][3] = 1;
	}
	else if (curr_time.tm_sec / 10 == 4)
	{
		arr[4][0][3] = 1;
		arr[4][3][3] = 1;
		arr[4][2][3] = 1;
		arr[4][6][3] = 1;
	}
	else if (curr_time.tm_sec / 10 == 5)
	{
		arr[4][1][3] = 1;
		arr[4][0][3] = 1;
		arr[4][3][3] = 1;
		arr[4][6][3] = 1;
		arr[4][5][3] = 1;
	}

	/************************************************************************/
	if (curr_time.tm_sec % 10 == 0)
	{
		arr[5][0][3] = 1;
		arr[5][1][3] = 1;
		arr[5][2][3] = 1;
		arr[5][4][3] = 1;
		arr[5][5][3] = 1;
		arr[5][6][3] = 1;
	}
	else if (curr_time.tm_sec % 10 == 1)
	{
		arr[5][2][3] = 1;
		arr[5][6][3] = 1;
	}
	else if (curr_time.tm_sec % 10 == 2)
	{
		arr[5][1][3] = 1;
		arr[5][2][3] = 1;
		arr[5][3][3] = 1;
		arr[5][4][3] = 1;
		arr[5][5][3] = 1;
	}
	else if (curr_time.tm_sec % 10 == 3)
	{
		arr[5][1][3] = 1;
		arr[5][2][3] = 1;
		arr[5][3][3] = 1;
		arr[5][6][3] = 1;
		arr[5][5][3] = 1;
	}
	else if (curr_time.tm_sec % 10 == 4)
	{
		arr[5][0][3] = 1;
		arr[5][3][3] = 1;
		arr[5][2][3] = 1;
		arr[5][6][3] = 1;
	}
	else if (curr_time.tm_sec % 10 == 5)
	{
		arr[5][1][3] = 1;
		arr[5][0][3] = 1;
		arr[5][3][3] = 1;
		arr[5][6][3] = 1;
		arr[5][5][3] = 1;
	}
	else if (curr_time.tm_sec % 10 == 6)
	{
		arr[5][0][3] = 1;
		arr[5][3][3] = 1;
		arr[5][4][3] = 1;
		arr[5][5][3] = 1;
		arr[5][6][3] = 1;
	}
	else if (curr_time.tm_sec % 10 == 7)
	{
		arr[5][1][3] = 1;
		arr[5][2][3] = 1;
		arr[5][6][3] = 1;
	}
	else if (curr_time.tm_sec % 10 == 8)
	{
		arr[5][0][3] = 1;
		arr[5][1][3] = 1;
		arr[5][2][3] = 1;
		arr[5][3][3] = 1;
		arr[5][4][3] = 1;
		arr[5][5][3] = 1;
		arr[5][6][3] = 1;
	}
	else if (curr_time.tm_sec % 10 == 9)
	{
		arr[5][0][3] = 1;
		arr[5][1][3] = 1;
		arr[5][2][3] = 1;
		arr[5][3][3] = 1;
		arr[5][6][3] = 1;
	}
	/*************************************************************************/
	//curr_time.tm_min;
	//curr_time.tm_sec;
	glutPostRedisplay();
	glutTimerFunc(50, TimerFunction, 1);
}
void main(int argc, char *argv[])
{
	srand(time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA|GLUT_DEPTH); // 디스플레이 모드 설정
	glutInitWindowPosition(300,100); // 윈도우의 위치지정
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

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
	/****************************************************/
	glRotatef(Rotate, 0.0, 1.0, 0.0);
	glRotatef(30, 1.0, 1.0, 0.0);
	for (int j = 0; j < 6; ++j) {
		for (int i = 0; i < 7; ++i) {
			glPushMatrix();
			glTranslatef(arr[j][i][0], arr[j][i][1], 0);
			glRotatef(arr[j][i][2], 0.0, 0.0, 1.0);
			if(arr[j][i][3]==1)
				glColor3f(0.0, 1.0, 0.0);
			else
				glColor3f(0.0, 0.0, 0.0);
			glBegin(GL_QUADS);
			glVertex3i(0, 0, 0);
			glVertex3i(0 + Size, 0, 0);
			glVertex3i(0 + Size, 0, Size);
			glVertex3i(0, 0, Size);

			glVertex3i(0, 0, 0);
			glVertex3i(0, 0 - Size, 0);
			glVertex3i(0 + Size, 0 - Size, 0);
			glVertex3i(0 + Size, 0, 0);

			glVertex3i(0 + Size, 0, 0);
			glVertex3i(0 + Size, 0 - Size * 3, 0);
			glVertex3i(0 + Size, 0 - Size * 3, Size);
			glVertex3i(0 + Size, 0, Size);

			glVertex3i(0 + Size, 0, Size);
			glVertex3i(0 + Size, 0 - Size * 3, Size);
			glVertex3i(0, 0 - Size * 3, Size);
			glVertex3i(0, 0, Size);

			glVertex3i(0, 0, Size);
			glVertex3i(0, 0 - Size * 3, Size);
			glVertex3i(0, 0 - Size * 3, 0);
			glVertex3i(0, 0, 0);

			glVertex3i(0, 0 - Size * 3, Size);
			glVertex3i(0, 0 - Size * 3, 0);
			glVertex3i(0 + Size, 0 - Size * 3, 0);
			glVertex3i(0 + Size, 0 - Size * 3, Size);
			glEnd();

			glColor3f(0.0, 0.0, 1.0);

			glBegin(GL_LINES);
			glVertex3i(0, 0, 0); glVertex3i(0 + Size, 0, 0);
			glVertex3i(0 + Size, 0, 0); glVertex3i(0 + Size, 0, Size);
			glVertex3i(0 + Size, 0, Size); glVertex3i(0, 0, Size);
			glVertex3i(0, 0, Size); glVertex3i(0, 0, 0);

			glVertex3i(0, 0, 0); glVertex3i(0, 0 - Size * 3, 0);
			glVertex3i(0 + Size, 0, 0); glVertex3i(0 + Size, 0 - Size * 3, 0);
			glVertex3i(0 + Size, 0, Size); glVertex3i(0 + Size, 0 - Size * 3, Size);
			glVertex3i(0, 0, Size); glVertex3i(0, 0 - Size * 3, Size);

			glVertex3i(0, 0 - Size * 3, Size); glVertex3i(0, 0 - Size * 3, 0);
			glVertex3i(0, 0 - Size * 3, 0); glVertex3i(0 + Size, 0 - Size * 3, 0);
			glVertex3i(0 + Size, 0 - Size * 3, 0); glVertex3i(0 + Size, 0 - Size * 3, Size);
			glVertex3i(0 + Size, 0 - Size * 3, Size); glVertex3i(0, 0 - Size * 3, Size);
			glEnd();
			glPopMatrix();
		}
		for (int i = 0; i < 4; ++i)
		{
			glPushMatrix();
			glTranslatef(point[i][0], point[i][1], 0);

			if(point[i][2]==1)
				glColor3f(0.0, 1.0, 0.0);
			else
				glColor3f(0.0, 0.0, 0.0);
			glBegin(GL_QUADS);
			glVertex3i(0, 0, 0);
			glVertex3i(0 + Size, 0, 0);
			glVertex3i(0 + Size, 0, Size);
			glVertex3i(0, 0, Size);

			glVertex3i(0, 0, 0);
			glVertex3i(0, 0 - Size, 0);
			glVertex3i(0 + Size, 0 - Size, 0);
			glVertex3i(0 + Size, 0, 0);

			glVertex3i(0 + Size, 0, 0);
			glVertex3i(0 + Size, 0 - Size , 0);
			glVertex3i(0 + Size, 0 - Size , Size);
			glVertex3i(0 + Size, 0, Size);

			glVertex3i(0 + Size, 0, Size);
			glVertex3i(0 + Size, 0 - Size , Size);
			glVertex3i(0, 0 - Size , Size);
			glVertex3i(0, 0, Size);

			glVertex3i(0, 0, Size);
			glVertex3i(0, 0 - Size, Size);
			glVertex3i(0, 0 - Size, 0);
			glVertex3i(0, 0, 0);

			glVertex3i(0, 0 - Size, Size);
			glVertex3i(0, 0 - Size, 0);
			glVertex3i(0 + Size, 0 - Size , 0);
			glVertex3i(0 + Size, 0 - Size , Size);
			glEnd();
			glPopMatrix();
		}
	}
	/****************************************************/
	glPopMatrix();
	glEnable(GL_DEPTH_TEST);
	glFlush();

}
GLvoid Reshape(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	glOrtho(-400.0, 400.0, -300.0, 300.0, -300.0, 300.0);
	glMatrixMode(GL_MODELVIEW);
}
