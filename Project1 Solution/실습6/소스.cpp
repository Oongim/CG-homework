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
	int move_stat;
	int move_x, move_y;
	int move_speed;
};
Pos Rec[9];

int count = 0;
int Shape_stat = 0;
int time_count = 100;
int setTimer = 1;
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
/*

9개 사각형
키보드로 그린순서 클릭 1~9
튕기던 사각형이 현재 위치에서 화면을 시계 또는 반시계방향으로 한바퀴 이동
0번을 누르면 모든 사각형이 시계/반시계방향으로 이동하고 제자리 오면 다시 튕기기
s 이동 애니메이션 멈춤
키보드 p를 누르면 모든 사각형 튕기기 시작

*/
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
	
	glutMainLoop();
}
// 윈도우 출력 함수
GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // 바탕색을 'blue' 로 지정
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기
	if (left_button == 1) {
		for (int i = 0; i < 9; ++i) {
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
	case 's':
		setTimer = 0;
		break;
	case 'p':
		if (setTimer == 0)
			setTimer = 1;
		else
		{
			for (int i = 0; i < 9; ++i)
			{
				Rec[i].radian = (rand() % 30 + 30)*RADIAN;
				Rec[i].move_stat = 0;
			}
		}
		break;
	case '0':
		for (int i = 0; i < 9; ++i)
		{
			Rec[i].move_x = Rec[i].x;
			Rec[i].move_y = Rec[i].y;
			Rec[i].move_stat = rand() % 2 + 1;
			if (Rec[i].xspeed > 0)
				Rec[i].move_speed = Rec[i].xspeed;
			else
				Rec[i].move_speed = Rec[i].xspeed*-1;
		}
		break;
	case '1':
		Rec[0].move_x = Rec[0].x;
		Rec[0].move_y = Rec[0].y;
		Rec[0].move_stat = rand() % 2 + 1;
		if (Rec[0].xspeed>0)
			Rec[0].move_speed = Rec[0].xspeed;
		else
			Rec[0].move_speed = Rec[0].xspeed*-1;
		break;
	case '2':
		Rec[1].move_x = Rec[1].x;
		Rec[1].move_y = Rec[1].y;
		Rec[1].move_stat = rand() % 2 + 1;
		if (Rec[1].xspeed > 0)
			Rec[1].move_speed = Rec[1].xspeed;
		else
			Rec[1].move_speed = Rec[1].xspeed*-1;
		break;
	case '3':
		Rec[2].move_x = Rec[2].x;
		Rec[2].move_y = Rec[2].y;
		Rec[2].move_stat = rand() % 2 + 1;
		if (Rec[2].xspeed > 0)
			Rec[2].move_speed = Rec[2].xspeed;
		else
			Rec[2].move_speed = Rec[2].xspeed*-1;
		break;
	case '4':
		Rec[3].move_x = Rec[3].x;
		Rec[3].move_y = Rec[3].y;
		Rec[3].move_stat = rand() % 2 + 1;
		if (Rec[3].xspeed > 0)
			Rec[3].move_speed = Rec[3].xspeed;
		else
			Rec[3].move_speed = Rec[3].xspeed*-1;
		break;
	case '5':
		Rec[4].move_x = Rec[4].x;
		Rec[4].move_y = Rec[4].y;
		Rec[4].move_stat = rand() % 2 + 1;
		if (Rec[4].xspeed > 0)
			Rec[4].move_speed = Rec[4].xspeed;
		else
			Rec[4].move_speed = Rec[4].xspeed*-1;
		break;
	case '6':
		Rec[5].move_x = Rec[5].x;
		Rec[5].move_y = Rec[5].y;
		Rec[5].move_stat = rand() % 2 + 1;
		if (Rec[5].xspeed > 0)
			Rec[5].move_speed = Rec[5].xspeed;
		else
			Rec[5].move_speed = Rec[5].xspeed*-1;
		break;
	case '7':
		Rec[6].move_x = Rec[6].x;
		Rec[6].move_y = Rec[6].y;
		Rec[6].move_stat = rand() % 2 + 1;
		if (Rec[6].xspeed > 0)
			Rec[6].move_speed = Rec[6].xspeed;
		else
			Rec[6].move_speed = Rec[6].xspeed*-1;
		break;
	case '8':
		Rec[7].move_x = Rec[7].x;
		Rec[7].move_y = Rec[7].y;
		Rec[7].move_stat = rand() % 2 + 1;
		if (Rec[7].xspeed > 0)
			Rec[7].move_speed = Rec[7].xspeed;
		else
			Rec[7].move_speed = Rec[7].xspeed*-1;
		break;
	case '9':
		Rec[8].move_x = Rec[8].x;
		Rec[8].move_y = Rec[8].y;
		Rec[8].move_stat = rand() % 2 + 1;
		if (Rec[8].xspeed > 0)
			Rec[8].move_speed = Rec[8].xspeed;
		else
			Rec[8].move_speed = Rec[8].xspeed*-1;
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
		if (count == 9)
			count = 0;
		left_button = 1;
	}
	glutPostRedisplay();

}

void TimerFunction(int value)
{
	if (value == 1) {
		for (int i = 0; i < 9; ++i)
		{/******************************************************************************************************/
			if (Rec[i].x != 0 && Rec[i].y != 0) {
				if (Rec[i].T_stat == 0)//커지고 작아지는 애니메이션 
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
				}/*************************************************************/
				if (Rec[i].move_stat == 0)
				{
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
				}/************************************************************************************/
				else if (Rec[i].move_stat == 1 || (Rec[i].move_stat >= 11 && Rec[i].move_stat <= 14))
				{
					if (Rec[i].move_stat == 1)
					{
						Rec[i].x -= Rec[i].move_speed;

						if (Rec[i].x - Rec[i].rand <= 0)
						{
							Rec[i].x = Rec[i].rand;
							Rec[i].move_stat = 11;
						}
					}
					else if (Rec[i].move_stat == 11)
					{
						Rec[i].y += Rec[i].move_speed;
						if ((600 - (Rec[i].y + Rec[i].rand)) <= 0)
						{
							Rec[i].y = 600 - Rec[i].rand;
							Rec[i].move_stat = 12;
						}
					}
					else if (Rec[i].move_stat == 12)
					{
						Rec[i].x += Rec[i].move_speed;
						if ((Rec[i].x + Rec[i].rand) >= 800)
						{
							Rec[i].x = 800 - Rec[i].rand;
							Rec[i].move_stat = 13;
						}
					}
					else if (Rec[i].move_stat == 13)
					{
						Rec[i].y -= Rec[i].move_speed;
						if ((Rec[i].y) <= Rec[i].move_y)
						{
							Rec[i].y = Rec[i].move_y;
							Rec[i].move_stat = 14;
						}
					}
					else if (Rec[i].move_stat == 14)
					{
						Rec[i].x -= Rec[i].move_speed;
						if (Rec[i].x <= Rec[i].move_x)
						{
							Rec[i].x = Rec[i].move_x;
							Rec[i].move_stat = 0;
						}
					}
				}
				else if (Rec[i].move_stat == 2 || (Rec[i].move_stat >= 21 && Rec[i].move_stat <= 24))
				{
					if (Rec[i].move_stat == 2)
					{
						Rec[i].x += Rec[i].move_speed;
						if ((Rec[i].x + Rec[i].rand) >= 800)
						{
							Rec[i].x = 800 - Rec[i].rand;
							Rec[i].move_stat = 21;
						}
					}
					else if (Rec[i].move_stat == 21)
					{
						Rec[i].y += Rec[i].move_speed;
						if ((600 - (Rec[i].y + Rec[i].rand)) <= 0)
						{
							Rec[i].y = 600 - Rec[i].rand;
							Rec[i].move_stat = 22;
						}
					}
					if (Rec[i].move_stat == 22)
					{
						Rec[i].x -= Rec[i].move_speed;

						if (Rec[i].x - Rec[i].rand <= 0)
						{
							Rec[i].x = Rec[i].rand;
							Rec[i].move_stat = 23;
						}
					}
					else if (Rec[i].move_stat == 23)
					{
						Rec[i].y -= Rec[i].move_speed;
						if ((Rec[i].y) <= Rec[i].move_y)
						{
							Rec[i].y = Rec[i].move_y;
							Rec[i].move_stat = 24;
						}
					}
					else if (Rec[i].move_stat == 24)
					{
						Rec[i].x += Rec[i].move_speed;
						if (Rec[i].x >= Rec[i].move_x)
						{
							Rec[i].x = Rec[i].move_x;
							Rec[i].move_stat = 0;
						}
					}
				}
			}/***************************************************************************************************/

		}
		glutPostRedisplay(); //drawscene 호출
	}
	if (setTimer == 1)
		glutTimerFunc(time_count, TimerFunction, 1);
	else if (setTimer == 0)
		glutTimerFunc(time_count, TimerFunction, 0);
}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0);
}
