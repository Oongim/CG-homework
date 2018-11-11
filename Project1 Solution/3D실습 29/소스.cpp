#include <GL/freeglut.h>
#include<iostream>
#include<time.h>
#include<stdlib.h>
#include<math.h>
#define PI 3.14
#define RADIAN PI/180
using namespace std;

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
/////////////////////////////////////  'c'  ȸ�� �̵� ��ȯ ,    'r'  �簢�� �ﰢ�� ��ȯ

bool right_button = 0;
double mouse_x = 0, mouse_y = 0;
GLfloat mouse_arr[3][16][3] = { { { 0 } } };
GLfloat mouse_select[3][16] = { { 0 } };
int mouse_count = 0;
int pivot = 0;
int mouse_move = false;

int sel_p = 0, sel_c = 0;
void delLine()
{
	for (int i = 0; i < pivot; i++)
		for (int j = 0; j < 16; ++j) {
			mouse_arr[i][j][0] = 0;
			mouse_arr[i][j][1] = 0;
			mouse_arr[i][j][2] = 0;
			mouse_select[i][j] = 0;
		}
	mouse_count = 0;
	pivot = 0;
}
void Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case'r':
		delLine();
		break;

	default:
		break;
	}

}

void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (pivot < 3) {
			mouse_select[pivot][mouse_count] = 1;
			mouse_arr[pivot][mouse_count][0] = x;
			mouse_arr[pivot][mouse_count++][2] = 600 - y;
			if (mouse_count == 1)
			{
				mouse_select[pivot][mouse_count] = 1;
				mouse_arr[pivot][mouse_count][0] = (mouse_arr[pivot][0][0]- x)/3;
				mouse_arr[pivot][mouse_count++][2] = (mouse_arr[pivot][0][2] - 600 - y)/3;
				mouse_select[pivot][mouse_count] = 1;
				mouse_arr[pivot][mouse_count][0] = (mouse_arr[pivot][0][0] - x) / 3*2;
				mouse_arr[pivot][mouse_count++][2] = (mouse_arr[pivot][0][2] - 600 - y) / 3*2;
				mouse_select[pivot][mouse_count] = 1;
				mouse_arr[pivot][mouse_count][0] = x;
				mouse_arr[pivot][mouse_count][2] = 600 - y;
				mouse_count = 8;
			}
			if (mouse_count == 13)
			{
				mouse_select[pivot][mouse_count] = 1;
				mouse_arr[pivot][mouse_count][0] = (mouse_arr[pivot][8][0] - x) / 3;
				mouse_arr[pivot][mouse_count++][2] = (mouse_arr[pivot][8][2] - 600 - y) / 3;
				mouse_select[pivot][mouse_count] = 1;
				mouse_arr[pivot][mouse_count][0] = (mouse_arr[pivot][8][0] - x) / 3 * 2;
				mouse_arr[pivot][mouse_count++][2] = (mouse_arr[pivot][8][2] - 600 - y) / 3 * 2;
				mouse_select[pivot][mouse_count] = 1;
				mouse_arr[pivot][mouse_count][0] = x;
				mouse_arr[pivot][mouse_count][2] = 600 - y;
			}
			for (int i=4; i < 8;++i) {
				mouse_select[pivot][i] = 1;
				mouse_arr[pivot][i][0] = (mouse_arr[pivot][i+8][0] - mouse_arr[pivot][i - 4][0]) / 3;
				mouse_arr[pivot][i][2] = (mouse_arr[pivot][i + 8][2] - mouse_arr[pivot][i - 4][2]) / 3;
			}
			for (int i = 8; i < 12; ++i) {
				mouse_select[pivot][i] = 1;
				mouse_arr[pivot][i][0] = (mouse_arr[pivot][i + 4][0] - mouse_arr[pivot][i - 8][0]) / 3;
				mouse_arr[pivot][i][2] = (mouse_arr[pivot][i + 4][2] - mouse_arr[pivot][i - 8][2]) / 3;
			}
			pivot++;
			if (pivot < 5) {
				mouse_count = 0;
				mouse_select[pivot][mouse_count] = 1;
				mouse_arr[pivot][mouse_count][0] = x;
				mouse_arr[pivot][mouse_count++][1] = 600 - y;
			}
			
				
			
		}
		
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		right_button = true;
		for (int i = 0; i < pivot; i++)
			for (int j = 0; j < 4; ++j) {
				if (mouse_arr[i][j][0] - 10 < x&&mouse_arr[i][j][0] + 10 > x&&
					mouse_arr[i][j][1] - 10 <(600 - y) && mouse_arr[i][j][1] + 10 >(600 - y))
				{
					sel_p = i;
					sel_c = j;
				}
			}
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP)
	{
		right_button = false;
		sel_p = -1;
		sel_c = -1;
	}
	glutPostRedisplay();

}
void Motion(int x, int y) {
	if (right_button == true && sel_p >= 0)
	{
		mouse_arr[sel_p][sel_c][0] = x;
		mouse_arr[sel_p][sel_c][1] = 600 - y;

		if (sel_p > 0 && sel_c == 0) {
			mouse_arr[sel_p - 1][3][0] = x;
			mouse_arr[sel_p - 1][3][1] = 600 - y;
		}
		glutPostRedisplay();
	}
}
void TimerFunction(int value)
{

	glutPostRedisplay();
	glutTimerFunc(50, TimerFunction, 1);
}
void main(int argc, char *argv[])
{
	srand(time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // ���÷��� ��� ����
	glutInitWindowPosition(0, 0); // �������� ��ġ����
	glutInitWindowSize(800, 600); // �������� ũ�� ����
	glutCreateWindow("�ǽ�28"); // ������ ���� (������ �̸�)

	glutDisplayFunc(drawScene); // ��� �Լ��� ����

	glutTimerFunc(50, TimerFunction, 1);
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);

	glutReshapeFunc(Reshape);
	glutMainLoop();
}

GLvoid drawScene(GLvoid)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	///////////////////////////////  ��ǥ��
	GLfloat ctrlpoints[3][3][3] = { { { 200.0, 400.0, 0.0 },{400.0, 400.0, 0.0 },{ 600.0, 400.0, .0 } },
	{ { 200.0, 300.0, 0.0 },{ 400.0, 300.0, 0.0 },{ 600.0, 300.0, 0.0 } },
	{ { 200.0, 200.0, 0.0 },{ 400.0, 200.0, 0.0 },{ 600.0, 200.0, 0.0 } } };
	// ��� ������ ���� 
	glMap2f (GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 3, 0.0, 1.0, 9, 3, &ctrlpoints[0][0][0]); 
	glEnable (GL_MAP2_VERTEX_3);
	// �׸��带 �̿��� ��� ����� 
	glMapGrid2f (10, 0.0, 1.0, 10, 0.0, 1.0);
	// ���� �̿��Ͽ� �׸��� ���� 
	glEvalMesh2 (GL_LINE, 0, 10, 0, 10);
	glPointSize(2.0); 
	glColor3f(0.0, 0.0, 1.0); 
	glBegin(GL_POINTS); 
	for (int i = 0; i < 16; i++)
		for (int j = 0; j < 16; j++)
			if (mouse_select[i][j] == 1)
				glVertex3fv(mouse_arr[i][j]);
	glEnd();

	glPopMatrix();
	glFlush();

}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(0, 800, 0, 600.0, 0, 600.0);
}
