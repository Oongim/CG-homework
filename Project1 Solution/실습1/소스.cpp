#include <GL/freeglut.h>
#include<time.h>
#include<stdlib.h>


GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
int x_rand, y_rand, col_rand;

void main(int argc, char *argv[])
{
	srand(time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // ���÷��� ��� ����
	glutInitWindowPosition(100, 100); // �������� ��ġ����
	glutInitWindowSize(800, 600); // �������� ũ�� ����
	glutCreateWindow("�ǽ�1"); // ������ ���� (������ �̸�)
	glutDisplayFunc(drawScene); // ��� �Լ��� ����

	glutReshapeFunc(Reshape);
	glutMainLoop();
}
// ������ ��� �Լ�

GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // �������� 'blue' �� ����
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�

	glBegin(GL_LINES);
	glVertex2f(-1.0f, 0.0f); // v1
	glVertex2f(1.0f, 0.0f); // v3
	glVertex2f(0.0f, -1.0f); // v1
	glVertex2f(0.0f, 1.0f); // v3
	glEnd();

	glColor4f(0.0f, 1.0f, 0.0f, 1.0f); // �׸��� ���� 'green' ���� ����
	glRectf(-1.0f, -1.0f, -0.65f, -0.6f); // �簢�� �׸���

	glColor4f(1.0f, 0.0f, 0.0f, 1.0f); // �׸��� ���� 'green' ���� ����
	glRectf(-1.0f, 1.0f, -0.65f, 0.6f); // �簢�� �׸���

	glColor4f(0.5f, 0.5f, 0.5f, 1.0f); // �׸��� ���� 'green' ���� ����
	glRectf(1.0f, 1.0f, 0.65f, 0.6f); // �簢�� �׸���

	glColor4f(0.0f, 1.0f, 1.0f, 1.0f); // �׸��� ���� 'green' ���� ����
	glRectf(1.0f, -1.0f, 0.65f, -0.6f); // �簢�� �׸���

	glColor4f(0.8f, 0.2f, 0.8f, 1.0f); // �׸��� ���� 'green' ���� ����
	glBegin(GL_POLYGON);
	glVertex2f(-0.1f, -0.1f); // v1
	glVertex2f(0.1f, -0.1f); // v3
	glVertex2f(0.0f, 0.1f); // v2
	glEnd();

	glFlush(); // ȭ�鿡 ����ϱ�
}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}
