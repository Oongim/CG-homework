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
	if (left_button == 1) {
		for (int i = 0; i < 10; ++i) {
			if (Rec[i].x != 0 && Rec[i].y != 0) {

				glColor4f(0.0f + (rand() % 10 * 0.1), 0.0f + (rand() % 10 * 0.1), 0.0f + (rand() % 10 * 0.1), 1.0f); // �׸��� ���� 'green' ���� ����
				glRectf(Rec[i].x - Rec[i].rand, 600 - (Rec[i].y + Rec[i].rand), Rec[i].x + Rec[i].rand, 600 - (Rec[i].y - Rec[i].rand));
			}
		}
	}// �簢�� �׸���
	glFlush(); // ȭ�鿡 ����ϱ�

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
	glutPostRedisplay(); //drawscene ȣ��
	glutTimerFunc(100, TimerFunction, 1);
}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0);
}