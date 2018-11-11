#include <GL/freeglut.h>
#include<time.h>
#include<stdlib.h>
#include<math.h>
#define PI 3.14
#define RADIAN PI/180

int All_x=0;
int All_y=0;
int move_x = 0;
int move_x_T[2] = { 0 };
int move_x_R[2] = { 0 };
double size = 0;
int setTimer = 0;
int TimerStat = 0;
int statRT[2] = { 0 };
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'x':
		All_x += 10;
		break;
	case 'X':
		All_x -= 10;
		break;
	case 'y':
		All_y += 10;
		break;
	case 'Y':
		All_y -= 10;
		break;
	case 's':
		size+= 0.1;
		break;
	case 'S':
		size += -0.1;
		break;
	case 'r':
		move_x += 10;
		if (move_x >= 1200)
			move_x = 0;
		if (statRT[0] == 0)
		{
			move_x_T[0] += 5;
			move_x_T[1] -= 1;
			if (move_x_T[0] >= 500)
			{
				statRT[0] = 1;
				move_x_T[0] = 500;
				move_x_T[1] = -100;
			}
		}
		else if (statRT[0] == 1)
		{
			move_x_T[1] += 2;
			if (move_x_T[1] >= 0)
			{
				statRT[0] = 2;
				move_x_T[0] = 500;
				move_x_T[1] = 0;
			}
		}
		else if (statRT[0] == 2)
		{
			move_x_T[0] -= 5;
			move_x_T[1] -= 1;
			if (move_x_T[0] <= 0)
			{
				statRT[0] = 3;
				move_x_T[0] = 0;
				move_x_T[1] = -100;
			}
		}
		else if (statRT[0] == 3)
		{
			move_x_T[1] += 2;
			if (move_x_T[1] >= 0)
			{
				statRT[0] = 0;
				move_x_T[0] = 0;
				move_x_T[1] = 0;
			}
		}
		
		if (statRT[1] == 0)
		{
			move_x_R[0] += 10;
			if (move_x_R[0] >= 500)
			{
				statRT[1] = 1;
				move_x_R[0] = 500;
			}
		}
		else if (statRT[1] == 1)
		{
			move_x_R[1] -= 4;
			if (move_x_R[1] <= -100)
			{
				statRT[1] = 2;
				move_x_R[1] = -100;
			}
		}
		else if (statRT[1] == 2)
		{
			move_x_R[0] -= 10;
			if (move_x_R[0] <= 0)
			{
				statRT[1] = 3;
				move_x_R[0] = 0;
			}
		}
		else if (statRT[1] == 3)
		{
			move_x_R[1] += 4;
			if (move_x_R[1] >= 0)
			{
				statRT[1] = 0;
				move_x_R[1] = 0;
			}
		}
		break;
	case 'R':
		move_x -= 10;
		if (move_x <= 0)
			move_x = 1200;
		if (statRT[0] == 0)
		{
			move_x_T[0] -= 10;
			move_x_T[1] += 2;
			if (move_x_T[0] <= 0)
			{
				statRT[0] = 3;
				move_x_T[0] = 0;
				move_x_T[1] = 0;
			}
		}
		else if (statRT[0] == 3)
		{
			move_x_T[1] -= 4;
			if (move_x_T[1] <= -100)
			{
				statRT[0] = 2;
				move_x_T[0] = 0;
				move_x_T[1] = -100;
			}
		}
		else if (statRT[0] == 2)
		{
			move_x_T[0] += 10;
			move_x_T[1] += 2;
			if (move_x_T[0] >= 500)
			{
				statRT[0] = 1;
				move_x_T[0] = 500;
				move_x_T[1] = 0;
			}
		}
		else if (statRT[0] == 1)
		{
			move_x_T[1] -= 4;
			if (move_x_T[1] <= -100)
			{
				statRT[0] = 0;
				move_x_T[0] = 500;
				move_x_T[1] = -100;
			}
		}
		
		if (statRT[1] == 0)
		{
			move_x_R[0] -= 10;
			if (move_x_R[0] <= 0)
			{
				statRT[1] = 3;
				move_x_R[0] = 0;
			}
		}
		else if (statRT[1] == 3)
		{
			move_x_R[1] -= 4;
			if (move_x_T[1] <= -100)
			{
				statRT[1] = 2;
				move_x_R[1] = -100;
			}
		}
		else if (statRT[1] == 2)
		{
			move_x_R[0] += 10;
			if (move_x_R[0] >= 500)
			{
				statRT[1] = 1;
				move_x_R[0] = 500;
			}
		}
		else if (statRT[1] == 1)
		{
			move_x_R[1] += 4;
			if (move_x_R[1] >= 0)
			{
				statRT[1] = 0;
				move_x_R[1] = 0;
			}
		}
		break;
	case 'a':
		setTimer = 1;
		TimerStat = 0;
		break;
	case 'A':
		setTimer = 1;
		TimerStat = 1;
		break;
	case 't':
		setTimer = 0;
		break;
	case 'q':
		exit(0);
		break;
	default:
		break;
	}
	glutPostRedisplay();
}
void TimerFunction(int value)
{
	if (setTimer == 1)
	{
		if (TimerStat == 0)
		{
			move_x += 5;
			if (move_x >= 1200)
				move_x = 0;

			if (statRT[0] == 0)
			{
				move_x_T[0] += 5;
				move_x_T[1] -= 1;
				if (move_x_T[0] >= 500)
				{
					statRT[0] = 1;
					move_x_T[0] = 500;
					move_x_T[1] = -100;
				}
			}
			else if (statRT[0] == 1)
			{
				move_x_T[1] += 2;
				if (move_x_T[1] >= 0)
				{
					statRT[0] = 2;
					move_x_T[0] = 500;
					move_x_T[1] = 0;
				}
			}
			else if (statRT[0] == 2)
			{
				move_x_T[0] -= 5;
				move_x_T[1] -= 1;
				if (move_x_T[0] <= 0)
				{
					statRT[0] = 3;
					move_x_T[0] = 0;
					move_x_T[1] = -100;
				}
			}
			else if (statRT[0] == 3)
			{
				move_x_T[1] += 2;
				if (move_x_T[1] >= 0)
				{
					statRT[0] = 0;
					move_x_T[0] = 0;
					move_x_T[1] = 0;
				}
			}

			if (statRT[1] == 0)
			{
				move_x_R[0] += 5;
				if (move_x_R[0] >= 500)
				{
					statRT[1] = 1;
					move_x_R[0] = 500;
				}
			}
			else if (statRT[1] == 1)
			{
				move_x_R[1] -= 2;
				if (move_x_R[1] <= -100)
				{
					statRT[1] = 2;
					move_x_R[1] = -100;
				}
			}
			else if (statRT[1] == 2)
			{
				move_x_R[0] -= 5;
				if (move_x_R[0] <= 0)
				{
					statRT[1] = 3;
					move_x_R[0] = 0;
				}
			}
			else if (statRT[1] == 3)
			{
				move_x_R[1] += 2;
				if (move_x_R[1] >= 0)
				{
					statRT[1] = 0;
					move_x_R[1] = 0;
				}
			}
		}
		if (TimerStat == 1)
		{
			move_x -= 5;
			if (move_x <= 0)
				move_x = 1200;
			if (statRT[0] == 0)
			{
				move_x_T[0] -= 5;
				move_x_T[1] += 1;
				if (move_x_T[0] <= 0)
				{
					statRT[0] = 3;
					move_x_T[0] = 0;
					move_x_T[1] = 0;
				}
			}
			else if (statRT[0] == 3)
			{
				move_x_T[1] -= 2;
				if (move_x_T[1] <= -100)
				{
					statRT[0] = 2;
					move_x_T[0] = 0;
					move_x_T[1] = -100;
				}
			}
			else if (statRT[0] == 2)
			{
				move_x_T[0] += 5;
				move_x_T[1] += 1;
				if (move_x_T[0] >= 500)
				{
					statRT[0] = 1;
					move_x_T[0] = 500;
					move_x_T[1] = 0;
				}
			}
			else if (statRT[0] == 1)
			{
				move_x_T[1] -= 2;
				if (move_x_T[1] <= -100)
				{
					statRT[0] = 0;
					move_x_T[0] = 500;
					move_x_T[1] = -100;
				}
			}

			if (statRT[1] == 0)
			{
				move_x_R[0] -= 5;
				if (move_x_R[0] <= 0)
				{
					statRT[1] = 3;
					move_x_R[0] = 0;
				}
			}
			else if (statRT[1] == 3)
			{
				move_x_R[1] -= 2;
				if (move_x_T[1] <= -100)
				{
					statRT[1] = 2;
					move_x_R[1] = -100;
				}
			}
			else if (statRT[1] == 2)
			{
				move_x_R[0] += 5;
				if (move_x_R[0] >= 500)
				{
					statRT[1] = 1;
					move_x_R[0] = 500;
				}
			}
			else if (statRT[1] == 1)
			{
				move_x_R[1] += 2;
				if (move_x_R[1] >= 0)
				{
					statRT[1] = 0;
					move_x_R[1] = 0;
				}
			}
		}
	}
	glutPostRedisplay(); //drawscene 호출
	if (setTimer == 1)
		glutTimerFunc(50, TimerFunction, 1);
	else if (setTimer == 0)
		glutTimerFunc(50, TimerFunction, 0);
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
	glutReshapeFunc(Reshape);
	glutMainLoop();
}
// 윈도우 출력 함수

GLvoid drawScene(GLvoid)
{
	int x = 0, y = 0;
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINES);
	glVertex2f(-400.0, 0.0);
	glVertex2f(400.0, 0.0);
	glVertex2f(0.0, -300.0);
	glVertex2f(0.0, 300.0);
	glEnd();
	

	glScalef(1.0f + size, 1.0f, 1.0f);
	glTranslatef(All_x, All_y, 0.0);

	glColor3f(1.0, 1.0, 1.0);
	for (int i = 0; i < 1200; ++i)
	{
		glBegin(GL_POINTS);
		glVertex2i((i-600)*0.5, 50*sin(RADIAN*(i-600))+225);
		glEnd();
	}
	glColor3f(1.0, 0.0, 0.0);
	glRectf((move_x - 600)*0.5 -5, 50 * sin(RADIAN*(move_x - 600)) + 225-5, (move_x - 600)*0.5 + 5, 50 * sin(RADIAN*(move_x - 600)) + 225+5);
	glColor3f(1.0, 1.0, 1.0);
	for (int i = 0; i < 1200; ++i)
	{
		x = 50 * sin(RADIAN*(90-i + 600)*2);
		y= 50 * cos(RADIAN*(90-i + 600)*2);

		glBegin(GL_LINES);
		glVertex2i(x+ (i - 600)*0.5, y+75);
		glVertex2i(50 * sin(RADIAN*(90 - (i+1) + 600) * 2) + ((i+1) - 600)*0.5, 50 * cos(RADIAN*(90 - (i+1) + 600) * 2)+75);
		glEnd();
	}
	

	glColor3f(1.0, 0.0, 0.0);
	glRectf(50 * sin(RADIAN*(90 - (move_x + 1) + 600) * 2) + (move_x - 600)*0.5-5,50 * cos(RADIAN*(90 - move_x + 600) * 2) + 75-5, 
		50 * sin(RADIAN*(90 - (move_x + 1) + 600) * 2) + (move_x - 600)*0.5+5, 50 * cos(RADIAN*(90 - move_x + 600) * 2) + 75+5);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_TRIANGLES);
	glVertex2i(0 ,0-80 );
	glVertex2i(-250 , 50-80 );
	glVertex2i(-250, -50-80 );
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex2i(0 , 0-80);
	glVertex2i(250 , 50-80 );
	glVertex2i(250 , -50-80);
	glEnd();

	glColor3f(1.0, 0.0, 0.0);
	glRectf(-250+move_x_T[0]-5,50-80-5 + move_x_T[1], -250 + move_x_T[0]+5, 50 - 80+5 + move_x_T[1]);

	glColor3f(1.0, 1.0, 1.0);
	//glRectf(-250 ,-175, 250 , -275 );
	glBegin(GL_LINES);
	glVertex2i(-250,-175);
	glVertex2i(-250,-275);
	
	glVertex2i(-250, -275);
	glVertex2i(250, -275);

	glVertex2i(250, -275);
	glVertex2i(250, -175);

	glVertex2i(250, -175);
	glVertex2i(-250, -175);
	glEnd();
	glColor3f(1.0, 0.0, 0.0);
	glRectf(-250 + move_x_R[0] - 5,-175 - 5 + move_x_R[1], -250 + move_x_R[0] + 5,-175 + 5 + move_x_R[1]);

	glLoadIdentity();
	glPopMatrix();
	glFlush();
	
}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(-400.0,400.0, -300.0, 300.0, -300.0, 300.0);
}
