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
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // ���÷��� ��� ����
	glutInitWindowPosition(100, 100); // �������� ��ġ����
	glutInitWindowSize(800, 600); // �������� ũ�� ����
	glutCreateWindow("Example2"); // ������ ���� (������ �̸�)
	glutDisplayFunc(drawScene); // ��� �Լ��� ����
	glutMouseFunc(Mouse);
	glutTimerFunc(100, TimerFunction, 1);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}
// ������ ��� �Լ�
GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // �������� 'blue' �� ����
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�
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
	}// �簢�� �׸���
	glFlush(); // ȭ�鿡 ����ϱ�

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