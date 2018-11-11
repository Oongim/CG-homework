#include <GL/freeglut.h>
#include<time.h>
#include<stdlib.h>

#define radius 5
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Mouse(int button, int state, int x, int y);
void TimerFunction(int value);

bool left_button;

struct Pos {
	int x, y;
	int stat;
	float col_randR;
	float col_randG;
	float col_randB;

};
Pos Rec[100];
Pos Eraser;
int Collision_R(int i)
{
	if ((Rec[i].x - radius <= Eraser.x+radius*2 ) &&
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
	for (int i = 0; i < 100; ++i)
	{
		Rec[i].stat = 1;
		Rec[i].x = rand() % 790+5;
		Rec[i].y = rand() % 590 + 5;
		Rec[i].col_randR = (rand() % 10 * 0.1);
		Rec[i].col_randG = (rand() % 10 * 0.1);
		Rec[i].col_randB = (rand() % 10 * 0.1);
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
		for (int i = 0; i < 100; ++i) {
			if (Rec[i].x != 0 && Rec[i].y != 0) {
				if (Rec[i].stat == 1) {
					glColor4f(0.0f + Rec[i].col_randR, 0.0f + Rec[i].col_randG, 0.0f + Rec[i].col_randB, 1.0f); // 그리기 색을 'green' 으로 지정
					glRectf(Rec[i].x - radius, Rec[i].y - radius, Rec[i].x + radius, Rec[i].y + radius);
					if (left_button == 1) {
						if (Collision_R(i))
							Rec[i].stat = 0;
					}
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
	
	glutPostRedisplay(); //drawscene 호출
	glutTimerFunc(100, TimerFunction, 1);
}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0);
}