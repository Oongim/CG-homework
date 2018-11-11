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

	x_rand = rand() % 15 + 5;
	y_rand = rand() % 5 + 3;
	col_rand = rand() % 5;
	for (int j = 0; j < y_rand; ++j)
	{
		for (int i = 0; i < x_rand; ++i)
		{
			if (col_rand == 0)
				glColor4f(1.0f - (100 / x_rand * 0.01)*i, 0.0f + (100 / y_rand * 0.01)*j, 0.0f, 1.0f);
			else if (col_rand == 1)
				glColor4f(0.0f + (100 / x_rand * 0.01)*i, 0.0f + (100 / y_rand * 0.01)*j, 0.0f, 1.0f);
			else if (col_rand == 2)
				glColor4f(0.0f, 0.0f + (100 / y_rand * 0.01)*j, 1.0f - (100 / x_rand * 0.01)*i, 1.0f);
			else if (col_rand == 3)
				glColor4f(1.0f - (100 / y_rand * 0.01)*j, 0.0f, 1.0f - (100 / x_rand * 0.01)*i, 1.0f);
			else if (col_rand == 4)
				glColor4f(1.0f - (100 / x_rand * 0.01)*i, 0.0f + (100 / y_rand * 0.01)*j, 1.0f - (100 / x_rand * 0.01)*i, 1.0f);
			glRectf(800 - ((800 / y_rand)*j + 1), 600 - ((600 / (x_rand))*i + 1), 0, 0);
		}
	}


	glFlush(); // 화면에 출력하기
}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0);

}
