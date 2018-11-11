#include <GL/freeglut.h>
#include<time.h>
#include<stdlib.h>
#include<math.h>

#define PI 3.14
#define RADIAN PI/180
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Mouse(int button, int state, int x, int y);
void TimerFunction(int value);

bool left_button;
struct Pos {
	int x, y;
	int rand;
	int T_cnt;
	int T_stat;
};
Pos Circle[10];
int count = 0;

void main(int argc, char *argv[])
{
	srand(time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정
	glutCreateWindow("Example2"); // 윈도우 생성 (윈도우 이름)
	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutMouseFunc(Mouse);
	glutTimerFunc(100, TimerFunction, 1);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}
// 윈도우 출력 함수
GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // 바탕색을 'blue' 로 지정
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기
	glPointSize(5);
	if (left_button == 1) {
		for (int i = 0; i < 10; ++i) {
			if (Circle[i].x != 0 && Circle[i].y != 0) {
				int rad = 0;
				glColor4f(0.0f + (rand() % 10 * 0.1), 0.0f + (rand() % 10 * 0.1), 0.0f + (rand() % 10 * 0.1), 1.0f);
				for (int j = 0; j < 40; ++j)
				{
					rad += 9;
					glBegin(GL_POINTS);
					glVertex2i(Circle[i].x+Circle[i].rand*cos(rad*RADIAN), Circle[i].y + Circle[i].rand*sin(rad*RADIAN));
					glEnd();
				}
			}
		}
	}// 사각형 그리기
	glFlush(); // 화면에 출력하기

}
void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		Circle[count].x = x;
		Circle[count].y = 600-y;
		Circle[count].rand = 1;
		Circle[count].T_cnt = 0;
		Circle[count].T_stat = rand() % 2;
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
		if (Circle[i].x != 0 && Circle[i].y != 0) {
			if (Circle[i].T_stat == 0)
			{
				Circle[i].rand += 3;
				Circle[i].T_cnt++;
				if (Circle[i].T_cnt == 30) {
					Circle[i].T_stat = 10;
					Circle[i].T_cnt = 0;
				}
			}
			else if (Circle[i].T_stat == 10)
			{
				Circle[i].rand -= 3;
				Circle[i].T_cnt++;
				if (Circle[i].T_cnt == 30) {
					Circle[i].T_stat = 0;
					Circle[i].T_cnt = 0;

				}
			}
			if (Circle[i].T_stat == 1)
			{
				Circle[i].rand += 3;
				Circle[i].T_cnt++;
				if (Circle[i].rand >= 800) {
					Circle[i].T_stat = 10;
					Circle[i].x = 0;
					Circle[i].y = 0;
				}
			}
		}
	}
	glutPostRedisplay(); 
	glutTimerFunc(100, TimerFunction, 1);
}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0);
}