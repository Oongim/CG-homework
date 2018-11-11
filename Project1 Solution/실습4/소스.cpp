#include <GL/freeglut.h>
#include<time.h>
#include<stdlib.h>
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
Pos Rec[10];
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
	if (left_button == 1) {
		for (int i = 0; i < 10; ++i) {
			if (Rec[i].x != 0 && Rec[i].y != 0) {

				glColor4f(0.0f + (rand() % 10 * 0.1), 0.0f + (rand() % 10 * 0.1), 0.0f + (rand() % 10 * 0.1), 1.0f); // 그리기 색을 'green' 으로 지정
				glRectf(Rec[i].x - Rec[i].rand, 600 - (Rec[i].y + Rec[i].rand), Rec[i].x + Rec[i].rand, 600 - (Rec[i].y - Rec[i].rand));
			}
		}
	}// 사각형 그리기
	glFlush(); // 화면에 출력하기

}
void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		Rec[count].x = x;
		Rec[count].y = y;
		Rec[count].rand = rand() % 50 + 10;
		Rec[count].T_cnt = rand() % 3;
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
	}
	glutPostRedisplay(); //drawscene 호출
	glutTimerFunc(100, TimerFunction, 1);
}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0);
}