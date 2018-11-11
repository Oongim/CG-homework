#include <GL/freeglut.h>
#include<time.h>
#include<stdlib.h>


GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

void main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정
	glutCreateWindow("실습1"); // 윈도우 생성 (윈도우 이름)
	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutReshapeFunc(Reshape);
	glutMainLoop();
}
// 윈도우 출력 함수
GLvoid drawScene(GLvoid)
{
	srand(time(NULL));

	glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // 바탕색을 'blue' 로 지정
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기
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



	glFlush(); // 화면에 출력하기
}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(-400.0, 400.0, -300.0, 300.0, -1.0, 1.0);

}
