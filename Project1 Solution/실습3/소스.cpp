#include <GL/freeglut.h>
#include<time.h>
#include<stdlib.h>


GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

void main(int argc, char *argv[])
{
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
	srand(time(NULL));

	glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // �������� 'blue' �� ����
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�
	int count = rand() % 4;

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			glBegin(GL_LINES);
			glVertex2f(-400 + 800 / 3 + 800 / 3 * j, 300);
			glVertex2f(-400 + 800 / 3 + 800 / 3 * j, -300);
			glEnd();

			if (count == 0) {
				glBegin(GL_LINES);
				glVertex2f(-400 + 800 / 3 * j + 800 / 3 / 3, 300 - (600 / 3 * i + 600 / 3 / 3));
				glVertex2f(-400 + 800 / 3 * j + (800 / 3 / 3) * 2, 300 - (600 / 3 * i + (600 / 3 / 3) * 2));
				glEnd();
			}
			if (count == 1) {
				glBegin(GL_TRIANGLES);
				glVertex2f(-400 + 800 / 3 * j + 800 / 3 / 2, 300 - (600 / 3 * i + 600 / 3 / 3));
				glVertex2f(-400 + 800 / 3 * j + (800 / 3 / 3), 300 - (600 / 3 * i + (600 / 3 / 3) * 2));
				glVertex2f(-400 + 800 / 3 * j + (800 / 3 / 3) * 2, 300 - (600 / 3 * i + (600 / 3 / 3) * 2));
				glEnd();
			}
			if (count == 2) {
				glBegin(GL_POLYGON);
				glVertex2f(-400 + 800 / 3 * j + 800 / 3 / 3, 300 - (600 / 3 * i + 600 / 3 / 3));
				glVertex2f(-400 + 800 / 3 * j + (800 / 3 / 3) * 2, 300 - (600 / 3 * i + 600 / 3 / 3));
				glVertex2f(-400 + 800 / 3 * j + (800 / 3 / 3) * 2, 300 - (600 / 3 * i + (600 / 3 / 3) * 2));
				glVertex2f(-400 + 800 / 3 * j + (800 / 3 / 3), 300 - (600 / 3 * i + (600 / 3 / 3) * 2));
				glEnd();
			}
			if (count == 3) {
				glBegin(GL_POLYGON);
				glVertex2f(-400 + 800 / 3 * j + 800 / 3 / 3 - 20, 300 - (600 / 3 * i + 600 / 3 / 3 + 10));
				glVertex2f(-400 + 800 / 3 * j + 800 / 3 / 2, 300 - (600 / 3 * i + 600 / 3 / 3 - 20));
				glVertex2f(-400 + 800 / 3 * j + (800 / 3 / 3) * 2 + 20, 300 - (600 / 3 * i + 600 / 3 / 3 + 10));
				glVertex2f(-400 + 800 / 3 * j + (800 / 3 / 3) * 2, 300 - (600 / 3 * i + (600 / 3 / 3) * 2 + 10));
				glVertex2f(-400 + 800 / 3 * j + (800 / 3 / 3), 300 - (600 / 3 * i + (600 / 3 / 3) * 2 + 10));
				glEnd();
			}
			if (count == 3)
				count = 0;
			else
				count++;

		}
		glBegin(GL_LINES);
		glVertex2f(-400, -300 + 600 / 3 + 600 / 3 * i);
		glVertex2f(400, -300 + 600 / 3 + 600 / 3 * i);
		glEnd();
	}



	glFlush(); // ȭ�鿡 ����ϱ�
}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(-400.0, 400.0, -300.0, 300.0, -1.0, 1.0);

}
