#include <GL/freeglut.h>
#include<time.h>
#include<stdlib.h>
#include<math.h>

#define PI 3.141592653589793238462643383279f
#define RADIAN 180/PI
#define radius 10
#define Circle_num 30

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Mouse(int button, int state, int x, int y);
void TimerFunction(int value);

bool left_button;

struct Pos {
	int x, y;
	float col_randR;
	float col_randG;
	float col_randB;
	int T_cnt;
	int T_stat;
	int radian;
	int xspeed, yspeed;
	int r;
};
Pos Rec[Circle_num];
Pos Eraser;
int Collision_R(int i)
{
	if ((Rec[i].x - radius <= Eraser.x + radius * 2) &&
		(Rec[i].x + radius >= Eraser.x - radius * 2) &&
		(Rec[i].y - radius <= Eraser.y + radius * 2) &&
		(Rec[i].y + radius >= Eraser.y - radius * 2))
		return 1;
	else
		return 0;
}
void Motion(int x, int y)
{
	if (left_button == true)
	{
		Eraser.x = x;
		Eraser.y = 600 - y;
		glutPostRedisplay();
	}
}

void main(int argc, char *argv[])
{
	srand(time(NULL));
	for (int i = 0; i < Circle_num; ++i)
	{
		Rec[i].x = rand() % 790 + 5;
		Rec[i].y = rand() % 590 + 5;
		Rec[i].col_randR = (rand() % 10 * 0.1);
		Rec[i].col_randG = (rand() % 10 * 0.1);
		Rec[i].col_randB = (rand() % 10 * 0.1);
		Rec[i].T_cnt = 0;
		Rec[i].radian = (rand() % 30 + 30)*RADIAN;
		Rec[i].xspeed = rand() % 10 + 5;
		Rec[i].yspeed = Rec[i].xspeed;
		Rec[i].r = 0;
	}

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정
	glutCreateWindow("Example2"); // 윈도우 생성 (윈도우 이름)
	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glutTimerFunc(100, TimerFunction, 1);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}
// 윈도우 출력 함수
GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // 바탕색을 'blue' 로 지정
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기
	for (int i = 0; i < Circle_num; ++i) {
		if (Rec[i].x != 0 && Rec[i].y != 0) {

			if(Rec[i].T_stat > 0)
				glColor4f(0.0f + (rand() % 10 * 0.1), 0.0f + (rand() % 10 * 0.1), 0.0f + (rand() % 10 * 0.1), 1.0f);
			else
				glColor4f(0.0f + Rec[i].col_randR, 0.0f + Rec[i].col_randG, 0.0f + Rec[i].col_randB, 1.0f); // 그리기 색을 'green' 으로 지정

				glBegin(GL_POLYGON);

					glVertex2i(Rec[i].x - radius-Rec[i].r, Rec[i].y - radius);
					glVertex2i(Rec[i].x - radius+ Rec[i].r, Rec[i].y + radius+ Rec[i].r);
					
					glVertex2i(Rec[i].x + radius- Rec[i].r, Rec[i].y + radius+ Rec[i].r);
					glVertex2i(Rec[i].x + radius+ Rec[i].r, Rec[i].y - radius);

				glEnd();
				if (left_button == 1&& Rec[i].T_stat==0) {
					if (Collision_R(i))
						Rec[i].T_stat = 1;

			}
		}
	}
	if (left_button == 1)
	{
		glColor4f(1, 1, 1, 1.0f); // 그리기 색을 'green' 으로 지정
		glRectf(Eraser.x - radius * 2, Eraser.y - radius * 2, Eraser.x + radius * 2, Eraser.y + radius * 2);
	}
	glFlush(); // 화면에 출력하기

}
void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		Eraser.x = x;
		Eraser.y = 600 - y;
		glutPostRedisplay();
		left_button = 1;

	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		left_button = 0;
	}


}
void TimerFunction(int value)
{
	for (int i = 0; i < Circle_num; ++i)
	{
		if (Rec[i].x != 0 && Rec[i].y != 0) {
			if (Rec[i].T_stat == 1)
			{
				Rec[i].r++;
				Rec[i].T_cnt++;
				if (Rec[i].T_cnt == 10) {
					Rec[i].T_stat = 2;
				}
			}
			else if (Rec[i].T_stat == 2)
			{
				Rec[i].r--;
				Rec[i].T_cnt--;
				if (Rec[i].T_cnt == 0) {
					Rec[i].T_stat = 0;
				}
			}
			Rec[i].x += Rec[i].xspeed*cos(Rec[i].radian);
			Rec[i].y += Rec[i].yspeed*sin(Rec[i].radian);
			if ((Rec[i].x - radius <= 0) || (Rec[i].x + radius >= 800))
			{
				Rec[i].xspeed *= -1;
				if ((Rec[i].x - radius <= 0))
					Rec[i].x = radius;
				else
					Rec[i].x = 800 - radius;
			}
			else if ((600 - (Rec[i].y + radius)) <= 0 || (600 - (Rec[i].y - radius)) >= 600)
			{
				Rec[i].yspeed *= -1;
				if ((600 - (Rec[i].y + radius)) <= 0)
					Rec[i].y = 600 - radius;
				else
					Rec[i].y = radius;
			}
		}
	}
	glutPostRedisplay(); //drawscene 호출
	glutTimerFunc(100, TimerFunction, 1);
}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0);
}