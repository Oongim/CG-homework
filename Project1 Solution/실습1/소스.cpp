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
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // 바탕색을 'blue' 로 지정
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기

	glBegin(GL_LINES);
	glVertex2f(-1.0f, 0.0f); // v1
	glVertex2f(1.0f, 0.0f); // v3
	glVertex2f(0.0f, -1.0f); // v1
	glVertex2f(0.0f, 1.0f); // v3
	glEnd();

	glColor4f(0.0f, 1.0f, 0.0f, 1.0f); // 그리기 색을 'green' 으로 지정
	glRectf(-1.0f, -1.0f, -0.65f, -0.6f); // 사각형 그리기

	glColor4f(1.0f, 0.0f, 0.0f, 1.0f); // 그리기 색을 'green' 으로 지정
	glRectf(-1.0f, 1.0f, -0.65f, 0.6f); // 사각형 그리기

	glColor4f(0.5f, 0.5f, 0.5f, 1.0f); // 그리기 색을 'green' 으로 지정
	glRectf(1.0f, 1.0f, 0.65f, 0.6f); // 사각형 그리기

	glColor4f(0.0f, 1.0f, 1.0f, 1.0f); // 그리기 색을 'green' 으로 지정
	glRectf(1.0f, -1.0f, 0.65f, -0.6f); // 사각형 그리기

	glColor4f(0.8f, 0.2f, 0.8f, 1.0f); // 그리기 색을 'green' 으로 지정
	glBegin(GL_POLYGON);
	glVertex2f(-0.1f, -0.1f); // v1
	glVertex2f(0.1f, -0.1f); // v3
	glVertex2f(0.0f, 0.1f); // v2
	glEnd();

	glFlush(); // 화면에 출력하기
}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}
