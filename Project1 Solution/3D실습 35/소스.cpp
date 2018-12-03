#include <GL/freeglut.h>
#include<time.h>
#include<stdlib.h>
#include<iostream>
#include<math.h>
#include <windows.h>
#define PI 3.14
#define RADIAN PI/180

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
struct pos {
	float x, y, z;
	int dir;
	int mode;
	int speed;
};

pos camera;
GLdouble rotate[16]
= { 1,0,0,0,
0,1,0,0,
0,0,1,0,
0,0,0,1 };
void Init_array(GLdouble arr[])
{
	arr[0] = 1; arr[1] = 0; arr[2] = 0; arr[3] = 0;
	arr[4] = 0; arr[5] = 1; arr[6] = 0; arr[7] = 0;
	arr[8] = 0; arr[9] = 0; arr[10] = 1; arr[11] = 0;
	arr[12] = 0; arr[13] = 0; arr[14] = 0; arr[15] = 1;
}


GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO **info)
{
	FILE *fp;
	GLubyte *bits;
	int bitsize, infosize;
	BITMAPFILEHEADER header;
	// ���̳ʸ� �б� ���� ������ ����
	//if ((fp = fopen(filename, "rb")) == NULL)
	fopen_s(&fp, filename, "rb");
	if ( fp == NULL )
		return NULL;
	// ��Ʈ�� ���� ����� �д´�.
	if (fread(&header, sizeof(BITMAPFILEHEADER), 1, fp) < 1) {
		fclose(fp);
		return NULL;
	}
	// ������ BMP �������� Ȯ���Ѵ�.
	if (header.bfType != 'MB') {
		fclose(fp);
		return NULL;
	}
	// BITMAPINFOHEADER ��ġ�� ����.
	infosize = header.bfOffBits - sizeof(BITMAPFILEHEADER);
	// ��Ʈ�� �̹��� �����͸� ���� �޸� �Ҵ��� �Ѵ�.
	if ((*info = (BITMAPINFO *)malloc(infosize)) == NULL) {
		fclose(fp);
		exit(0);
		return NULL;
	}
	// ��Ʈ�� ���� ����� �д´�.
	if (fread(*info, 1, infosize, fp) < (unsigned int)infosize) {
		free(*info);
		fclose(fp);
		return NULL;
	}
	// ��Ʈ���� ũ�� ����
	if ((bitsize = (*info)->bmiHeader.biSizeImage) == 0)
		bitsize = ((*info)->bmiHeader.biWidth*(*info)->bmiHeader.biBitCount + 7) / 8.0 * abs((*info)->bmiHeader.biHeight);
	// ��Ʈ���� ũ�⸸ŭ �޸𸮸� �Ҵ��Ѵ�.
	if ((bits = (unsigned char *)malloc(bitsize)) == NULL) {
		free(*info);
		fclose(fp);
		return NULL;
	}
	// ��Ʈ�� �����͸� bit(GLubyte Ÿ��)�� �����Ѵ�.
	if (fread(bits, 1, bitsize, fp) < (unsigned int)bitsize) {
		free(*info); free(bits);
		fclose(fp);
		return NULL;
	}
	fclose(fp);
	return bits;
}

void Init()
{
	camera.x = 0;
	camera.y = 0;
	camera.z = 50;
	Init_array(rotate);


}
void Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'x':
		glPushMatrix();
		glRotatef(5, 1.0, 0.0, 0.0);
		glMultMatrixd(rotate);
		glGetDoublev(GL_MODELVIEW_MATRIX, rotate);
		glPopMatrix();
		break;
	case 'X':
		glPushMatrix();
		glRotatef(-5, 1.0, 0.0, 0.0);
		glMultMatrixd(rotate);
		glGetDoublev(GL_MODELVIEW_MATRIX, rotate);
		glPopMatrix();
		break;
	case 'y':
		glPushMatrix();
		glRotatef(5, 0.0, 1.0, 0.0);
		glMultMatrixd(rotate);
		glGetDoublev(GL_MODELVIEW_MATRIX, rotate);
		glPopMatrix();
		break;
	case 'Y':
		glPushMatrix();
		glRotatef(-5, 0.0, 1.0, 0.0);
		glMultMatrixd(rotate);
		glGetDoublev(GL_MODELVIEW_MATRIX, rotate);
		glPopMatrix();
		break;
	case 'z':
		glPushMatrix();
		glRotatef(5, 0.0, 0.0, 1.0);
		glMultMatrixd(rotate);
		glGetDoublev(GL_MODELVIEW_MATRIX, rotate);
		glPopMatrix();
		break;
	case 'Z':
		glPushMatrix();
		glRotatef(-5, 0.0, 0.0, 1.0);
		glMultMatrixd(rotate);
		glGetDoublev(GL_MODELVIEW_MATRIX, rotate);
		glPopMatrix();
		break;
	case '+':
		camera.x -= 2;
		break;
	case '-':
		camera.x += 2;
		break;
	default:
		break;
	}

}
void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{

		glutPostRedisplay();
	}
}

void TimerFunction(int value)
{
	
	glutPostRedisplay();
	glutTimerFunc(50, TimerFunction, 1);
}
GLubyte * TexBits;


void main(int argc, char *argv[])
{
	Init();
	srand(time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // ���÷��� ��� ����
	glutInitWindowPosition(100, 100); // �������� ��ġ����
	glutInitWindowSize(800, 600); // �������� ũ�� ����
	glutCreateWindow("�ǽ�1"); // ������ ���� (������ �̸�)
	glutDisplayFunc(drawScene); // ��� �Լ��� ����
	glutTimerFunc(50, TimerFunction, 1);
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}

void drawRect(float size, int i)
{
	glPushMatrix(); {
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_QUADS);
		if (i == 0) {
			//����
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(-size / 2, size / 2, -size / 2); //1
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(-size / 2, size / 2, size / 2);// 2
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(size / 2, size / 2, size / 2);// 3
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(size / 2, size / 2, -size / 2);//4
		}
		else if (i == 1) {
			//�ո�		 
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(-size / 2, size / 2, size / 2);//2
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(-size / 2, -size / 2, size / 2);//6
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(size / 2, -size / 2, size / 2);//7
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(size / 2, size / 2, size / 2);//3
		}
		else if (i == 2) {
		//�����ʿ���
			glTexCoord2f(0.0f, 1.0f);
		glVertex3f(size / 2, size / 2, size / 2);//3
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(size / 2, -size / 2, size / 2);//7
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(size / 2, -size / 2, -size / 2);//8
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(size / 2, size / 2, -size / 2);//4
		}
		else if (i == 3) {
		//���ʿ���
			glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-size / 2, size / 2, -size / 2);//1
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-size / 2, -size / 2, -size / 2);//5
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-size / 2, -size / 2, size / 2);//6
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-size / 2, size / 2, size / 2);//2
		}
		else if (i == 4) {
			//�޸�
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(size / 2, size / 2, -size / 2);//4
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(size / 2, -size / 2, -size / 2);//8
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(-size / 2, -size / 2, -size / 2);//5
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(-size / 2, size / 2, -size / 2);//1
		}
		else if (i == 5) {
			//�ٴڸ�
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(size / 2, -size / 2, -size / 2);//8
			
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(size / 2, -size / 2, size / 2);//7
			
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(-size / 2, -size / 2, size / 2);//6
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(-size / 2, -size / 2, -size / 2);//5
		}
		glEnd();
	}glPopMatrix();
}

GLvoid drawScene(GLvoid)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();

	gluLookAt(0, 100, 500, 0.0, 0.0, 0.0, 0.0, 1, 0.0);
	glMultMatrixd(rotate);
	glRotatef(30, 0.0, 1.0, 0.0);

	glRotatef(30, 1.0, 0.0, 0.0);
	/****************************************************/
	GLubyte *pBytes; // �����͸� ����ų ������
	BITMAPINFO *info; // ��Ʈ�� ��� ������ ����
					  // ���� ����
					  // n���� �̹��� �ؽ�ó ������ �Ѵ�.
	GLuint textures[6];
	
	glGenTextures(3, textures);
	//�ؽ�ó�� ��ü�� �����Ѵ�. --- (1)
	
	///////////////////////////////////////////////////////////////////////////////
	for (int i = 0; i < 6; ++i) {
		glBindTexture(GL_TEXTURE_2D, textures[i]);
		//�̹��� �ε��� �Ѵ�. --- (2)
		if (i == 0)
			pBytes = LoadDIBitmap("1.bmp", &info);
		else if(i==1)
			pBytes = LoadDIBitmap("2.bmp", &info);
		else if (i == 2)
			pBytes = LoadDIBitmap("3.bmp", &info);
		else if (i == 3)
			pBytes = LoadDIBitmap("4.bmp", &info);
		else if (i == 4)
			pBytes = LoadDIBitmap("5.bmp", &info);
		else if (i == 5)
			pBytes = LoadDIBitmap("6.bmp", &info);

		//�ؽ�ó ���� ���Ǹ� �Ѵ�. --- (3)
		glTexImage2D(GL_TEXTURE_2D, 0, 3, 82, 82, 0, GL_BGR_EXT,GL_UNSIGNED_BYTE, pBytes);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
		// �ؽ�ó ���� Ȱ��ȭ
		glEnable(GL_TEXTURE_2D);
		// �ؽ�ó�� ��ü�� ����
		drawRect(300,i);
	}
	///////////////////////////////////////////////////////////////////////////////


	


	/****************************************************/
	glPopMatrix();
	glEnable(GL_DEPTH_TEST);
	glFlush();
	glutSwapBuffers();
}
GLvoid Reshape(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(60.0f, w / h, 1.0, 2000.0);
	glTranslatef(0.0, 0.0, -500.0);
	glMatrixMode(GL_MODELVIEW);
}
