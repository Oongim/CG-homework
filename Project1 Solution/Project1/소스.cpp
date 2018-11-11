#include <GL/freeglut.h>
#include<time.h>
#include<stdlib.h>
#include<math.h>

#define PI 3.141592653589793238462643383279f
#define RADIAN 180/PI
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Mouse(int button, int state, int x, int y);
void TimerFunction(int value);
void Keyboard(unsigned char key, int x, int y);

bool left_button;
struct Pos {
	int x, y;
	int rand, rand_static;
	int T_cnt;
	int T_stat;
	int radian;
	int xspeed, yspeed;
};
Pos Rec[10];

int count = 0;
int Shape_stat = 0;
int time_count = 100;
/*void MenuFunc(int button)
{
switch (button) {
case 1:
count++;
break;
case 2:
count++;
break;
}
glutPostRedisplay();
}*/

void main(int argc, char *argv[])
{
	srand(time(NULL));
	//int MainMenu;


	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정
	glutCreateWindow("Example2"); // 윈도우 생성 (윈도우 이름)
	glutDisplayFunc(drawScene); // 출력 함수의 지정

	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);

	glutTimerFunc(time_count, TimerFunction, 1);
	glutReshapeFunc(Reshape);
	/*
	MainMenu = glutCreateMenu(MenuFunc);
	glutAddSubMenu("사각형", 1);
	glutAddSubMenu("삼각형", 2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	*/
	glutMainLoop();
}
// 윈도우 출력 함수
GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // 바탕색을 'blue' 로 지정
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기
	if (left_button == 1) {
		for (int i = 0; i < 10; ++i) {
			if (Rec[i].x != 0 && Rec[i].y != 0) {
				if (Shape_stat == 0) {
					glColor4f(0.0f + (rand() % 10 * 0.1), 0.0f + (rand() % 10 * 0.1), 0.0f + (rand() % 10 * 0.1), 1.0f);
					glRectf(Rec[i].x - Rec[i].rand, 600 - (Rec[i].y + Rec[i].rand), Rec[i].x + Rec[i].rand, 600 - (Rec[i].y - Rec[i].rand));
				}
				else
				{
					glColor4f(0.0f + (rand() % 10 * 0.1), 0.0f + (rand() % 10 * 0.1), 0.0f + (rand() % 10 * 0.1), 1.0f);
					glBegin(GL_TRIANGLES);
					glVertex2f(Rec[i].x - Rec[i].rand, 600 - (Rec[i].y + Rec[i].rand / 2));
					glVertex2f(Rec[i].x + Rec[i].rand, 600 - (Rec[i].y + Rec[i].rand / 2));
					glVertex2f(Rec[i].x, 600 - (Rec[i].y - Rec[i].rand));
					glEnd();
				}
			}
		}
	}// 사각형 그리기
	glFlush(); // 화면에 출력하기

}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 't':
		Shape_stat = 1;
		break;
	case 'r':
		Shape_stat = 0;
		break;
	case '+':
		if (time_count != 0)
			time_count -= 10;
		break;
	case '-':
		time_count += 10;
		break;
	}
}

void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		Rec[count].x = x;
		Rec[count].y = y;
		Rec[count].rand = rand() % 50 + 10;
		Rec[count].rand_static += Rec[count].rand + 5;
		Rec[count].T_cnt = rand() % 3;
		Rec[count].radian = (rand() % 30 + 30)*RADIAN;
		Rec[count].xspeed = rand() % 10 + 5;
		Rec[count].yspeed = Rec[count].xspeed;
		count++;
		if (count == 10)
			count = 0;
		left_button = 1;
	}
	glutPostRedisplay();

}

void TimerFunction(int value)
{
	for (int i = 0; i < 10; ++i)
	{
		if (Rec[i].x != 0 && Rec[i].y != 0) {
			if (Rec[i].T_stat == 0)
			{
				Rec[i].rand += 5;
				Rec[i].T_cnt++;
				if (Rec[i].T_cnt == 3) {
					Rec[i].T_stat = 1;
					Rec[i].T_cnt = 0;
				}
			}
			else if (Rec[i].T_stat == 1)
			{
				Rec[i].rand -= 5;
				Rec[i].T_cnt++;
				if (Rec[i].T_cnt == 3) {
					Rec[i].T_stat = 0;
					Rec[i].T_cnt = 0;
				}
			}
			Rec[i].x += Rec[i].xspeed*cos(Rec[i].radian);
			Rec[i].y += Rec[i].yspeed*sin(Rec[i].radian);
			if ((Rec[i].x - Rec[i].rand <= 0) || (Rec[i].x + Rec[i].rand >= 800))
			{
				Rec[i].xspeed *= -1;
				if ((Rec[i].x - Rec[i].rand <= 0))
					Rec[i].x = Rec[i].rand;
				else
					Rec[i].x = 800 - Rec[i].rand;
			}
			else if ((600 - (Rec[i].y + Rec[i].rand)) <= 0 || (600 - (Rec[i].y - Rec[i].rand)) >= 600)
			{
				Rec[i].yspeed *= -1;
				if ((600 - (Rec[i].y + Rec[i].rand)) <= 0)
					Rec[i].y = 600 - Rec[i].rand;
				else
					Rec[i].y = Rec[i].rand;
			}
		}
	}
	glutPostRedisplay(); //drawscene 호출
	glutTimerFunc(time_count, TimerFunction, 1);
}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0);
}