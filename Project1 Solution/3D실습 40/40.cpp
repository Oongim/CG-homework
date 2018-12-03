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
};
pos camera;
int num=3;
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
void Init()
{
	camera.x = 0;
	camera.y = 100;
	camera.z = 100;
	Init_array(rotate);
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
	if (fp == NULL)
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
bool isLight1 = true;
bool isLight2 = true;
bool isrotate = false;
bool isVector = true;
float diffuse_num = 1;
float Specular_num = 1;
float ambient_num = 0;
float rotate1;
float rotate2;
float rotatemoon;
float move_x = 0;
GLfloat ambientLight[] = { 0.0f, ambient_num, 0.0f, 1.0f };
GLfloat DiffuseLightr[] = { diffuse_num + 1, diffuse_num,diffuse_num, 1.0f };
GLfloat DiffuseLightb[] = { diffuse_num , diffuse_num,diffuse_num + 1, 1.0f };
GLfloat SpecularLight[] = { Specular_num, Specular_num, Specular_num, 1.0 }; // �������
GLfloat lightPos1[] = { 500.0, 0.0, 0.0, 1.0 };
GLfloat lightPos2[] = { -500.0, 0.0, 0.0, 1.0 };

GLfloat gray[] = { 0.75f, 0.75f, 0.75f, 1.0f };
GLfloat specref[] = { Specular_num, Specular_num, Specular_num, 1.0f };

GLuint filter;                        // ����� ����
GLuint fogMode[] = { GL_EXP, GL_EXP2, GL_LINEAR };    // ������ �Ȱ�����
GLuint fogfilter = 1;                    // ����� �Ȱ�����
GLfloat fogColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };        // �Ȱ�����
GLfloat density = 0.002f;
GLfloat start = 100.0f;
GLfloat end = 100.0f;

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
	case 'w':
		if (ambient_num > 0)
			ambient_num -= 0.1;
		break;
	case 'W':
		if (ambient_num < 1)
			ambient_num += 0.1;
		break;
	case 's':
		if (Specular_num > 0)
			Specular_num -= 0.1;
		break;
	case 'S':
		if (Specular_num < 2)
			Specular_num += 0.1;
		break;
	case 'a':
		if (isrotate)
			isrotate = false;
		else
			isrotate = true;
		break;
	case 'd':
		if (diffuse_num > 0)
			diffuse_num -= 0.1;
		break;
	case 'D':
		if (diffuse_num < 1)
			diffuse_num += 0.1;
		break;
	case '+':
		num++;
		break;
	case '-':
		num--;
		break;
	case '1':
		if (isLight1)
			isLight1 = false;
		else
			isLight1 = true;
		break;
	case '2':
		if (isLight2)
			isLight2 = false;
		else
			isLight2 = true;
		break;
	case 'o':
		if (isVector)
			isVector = false;
		else
			isVector = true;
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
	if (isrotate) {
		rotate1++;
		rotate2++;
	}
	rotatemoon -= 3;
	move_x += 0.02;
	glutPostRedisplay();
	glutTimerFunc(50, TimerFunction, 1);
}
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
// ������ ��� �Լ�
GLubyte *pBytes; // �����͸� ����ų ������
BITMAPINFO *info; // ��Ʈ�� ��� ������ ����
				  // ���� ����
				  // n���� �̹��� �ؽ�ó ������ �Ѵ�.
GLuint textures[5];
void practal(float p1[], float p2[], float p3[], int n)
{
	
	if (n<=0)
	{
		glBegin(GL_TRIANGLES);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3fv(p1);//6
		glTexCoord2f(1.0f, 0.0f);
		glVertex3fv(p2);//7
		glTexCoord2f(0.5f, 1.0f);
		glVertex3fv(p3);//2
 		glEnd();
		return;
	}

	
	float p1_p3[3] = { (p3[0] + p1[0]) / 2,(p3[1] + p1[1]) / 2,(p3[2] + p1[2]) / 2 };
	float p1_p2[3] = { (p2[0] + p1[0]) / 2,(p2[1] + p1[1]) / 2,(p2[2] + p1[2]) / 2 };
	float p2_p3[3] = { (p3[0] + p2[0]) / 2,(p3[1] + p2[1]) / 2,(p3[2] + p2[2]) / 2 };

	practal(p1, p1_p2, p1_p3, n-1);
	practal(p1_p2, p2, p2_p3, n-1);
	practal(p1_p3, p2_p3, p3, n-1);

	
}
void pyramid(float size)
{


	glGenTextures(3, textures);
	//�ؽ�ó�� ��ü�� �����Ѵ�. --- (1)

	///////////////////////////////////////////////////////////////////////////////
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	//�̹��� �ε��� �Ѵ�. --- (2)
	pBytes = LoadDIBitmap("1.bmp", &info);
	//�ؽ�ó ���� ���Ǹ� �Ѵ�. --- (3)
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 217, 185, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
	// �ؽ�ó ���� Ȱ��ȭ
	glEnable(GL_TEXTURE_2D);

	float P11[3]{ -size / 2, -size / 2, size / 2 };
	float P21[3]{ size / 2, -size / 2, size / 2 };
	float P31[3]{ 0, size / 2, 0 };
	if (isVector)
		glNormal3f(0, 1, 1);
	practal(P11, P21, P31, num);

	float P12[3]{ size / 2, -size / 2, size / 2 };
	float P22[3]{ size / 2, -size / 2, -size / 2 };
	float P32[3]{ 0, size / 2, 0 };
	if (isVector)
		glNormal3f(1, 1, 0);
	practal(P12, P22, P32, num);
	glBegin(GL_TRIANGLES);
	
	float P13[3]{ -size / 2, -size / 2, -size / 2 };
	float P23[3]{ -size / 2, -size / 2, size / 2 };
	float P33[3]{ 0, size / 2, 0 };
	if (isVector)
		glNormal3f(-1, 1, 0);
	practal(P13, P23, P33, num);
	
	float P14[3]{ size / 2, -size / 2, -size / 2 };
	float P24[3]{ -size / 2, -size / 2, -size / 2 };
	float P34[3]{ 0, size / 2, 0 };
	if (isVector)
		glNormal3f(0, 1, -1);
	practal(P14, P24, P34, num);

	glDisable(GL_TEXTURE_2D);
}

void draw_bottom(float size)
{
	
	glGenTextures(3, textures);
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	//�̹��� �ε��� �Ѵ�. --- (2)
	pBytes = LoadDIBitmap("clock.bmp", &info);
	//�ؽ�ó ���� ���Ǹ� �Ѵ�. --- (3)
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 640, 480, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
	// �ؽ�ó ���� Ȱ��ȭ
	glEnable(GL_TEXTURE_2D);

	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	for (int i = 0; i < 50; ++i)
	{
		for (int j = 0; j < 50; ++j)
		{
			glColor3f(0.5, 0.5, 0.5);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(-size / 2 + size / 50 * i, -250, -size / 2 + size / 50 * j);//5
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(-size / 2 + size / 50 * i, -250, -size / 2 + size / 50 * (j + 1));//6
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(-size / 2 + size / 50 * (i + 1), -250, -size / 2 + size / 50 * (j + 1));//7
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(-size / 2 + size / 50 * (i + 1), -250, -size / 2 + size / 50 * j);//8
		}
	}

	glBegin(GL_QUADS);
	
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-size / 2, -size / 2, -size / 2);//5
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-size / 2, -size / 2, size / 2);//6
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(size / 2, -size / 2, size / 2);//7
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(size / 2, -size / 2, -size / 2);//8




	glEnd();
}
void drawRec(float size)
{
	glGenTextures(5, textures);
	//�ؽ�ó�� ��ü�� �����Ѵ�. --- (1)

	///////////////////////////////////////////////////////////////////////////////
	glBindTexture(GL_TEXTURE_2D, textures[2]);
	//�̹��� �ε��� �Ѵ�. --- (2)
	pBytes = LoadDIBitmap("image.bmp", &info);
	//�ؽ�ó ���� ���Ǹ� �Ѵ�. --- (3)
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 276, 183, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);

	//�ո�	
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-size / 2, size / 2, -size / 2);//2
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-size / 2, -size / 2, -size / 2);//6
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(size / 2, -size / 2, -size / 2);//7
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(size / 2, size / 2, -size / 2);//3

	glEnd();
}
void drawRect(float size)
{


	glGenTextures(3, textures);
	//�ؽ�ó�� ��ü�� �����Ѵ�. --- (1)

	///////////////////////////////////////////////////////////////////////////////
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	//�̹��� �ε��� �Ѵ�. --- (2)
	pBytes = LoadDIBitmap("garo.bmp", &info);
	//�ؽ�ó ���� ���Ǹ� �Ѵ�. --- (3)
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 217, 77, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
	// �ؽ�ó ���� Ȱ��ȭ
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	//����
	glNormal3f(0, 1, 0);
	glVertex3f(-size / 2, size / 2, -size / 2); //1
	glVertex3f(-size / 2, size / 2, size / 2);// 2
	glVertex3f(size / 2, size / 2, size / 2);// 3
	glVertex3f(size / 2, size / 2, -size / 2);//4
	//�ո�
	glNormal3f(-0.5, 0, 1);
	glTexCoord2f(move_x, 1.0f);
	glVertex3f(-size / 2, size / 2, size / 2);//2
	glTexCoord2f(move_x, 0.0f);
	glVertex3f(-size / 2, -size / 2, size / 2);//6
	glTexCoord2f(move_x + 0.25f, 0.0f);
	glVertex3f(size / 2, -size / 2, size / 2);//7
	glTexCoord2f(move_x + 0.25f, 1.0f);
	glVertex3f(size / 2, size / 2, size / 2);//3
											 //�����ʿ���
	glNormal3f(1, 0, -0.5);
	glTexCoord2f(move_x + 0.25f, 1.0f);
	glVertex3f(size / 2, size / 2, size / 2);//3
	glTexCoord2f(move_x + 0.25f, 0.0f);
	glVertex3f(size / 2, -size / 2, size / 2);//7
	glTexCoord2f(move_x + 0.5f, 0.0f);
	glVertex3f(size / 2, -size / 2, -size / 2);//8
	glTexCoord2f(move_x + 0.5f, 1.0f);
	glVertex3f(size / 2, size / 2, -size / 2);//4

											  //�޸�
	glNormal3f(-0.5, 0, -1);
	glTexCoord2f(move_x + 0.5f, 1.0f);
	glVertex3f(size / 2, size / 2, -size / 2);//4
	glTexCoord2f(move_x + 0.5f, 0.0f);
	glVertex3f(size / 2, -size / 2, -size / 2);//8
	glTexCoord2f(move_x + 0.75f, 0.0f);
	glVertex3f(-size / 2, -size / 2, -size / 2);//5
	glTexCoord2f(move_x + 0.75f, 1.0f);
	glVertex3f(-size / 2, size / 2, -size / 2);//1
											   //���ʿ���
	glNormal3f(-1, 0, -0.5);
	glTexCoord2f(move_x + 0.75f, 1.0f);
	glVertex3f(-size / 2, size / 2, -size / 2);//1
	glTexCoord2f(move_x + 0.75f, 0.0f);
	glVertex3f(-size / 2, -size / 2, -size / 2);//5
	glTexCoord2f(move_x + 1.0f, 0.0f);
	glVertex3f(-size / 2, -size / 2, size / 2);//6
	glTexCoord2f(move_x + 1.0f, 1.0f);
	glVertex3f(-size / 2, size / 2, size / 2);//2
											   //�ٴڸ�
	glVertex3f(-size / 2, -size / 2, size / 2);//6
	glVertex3f(-size / 2, -size / 2, -size / 2);//5
	glVertex3f(size / 2, -size / 2, -size / 2);//8
	glVertex3f(size / 2, -size / 2, size / 2);//7

	glEnd();
}
GLvoid drawScene(GLvoid)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
	drawRec(2000);
	gluLookAt(0 + camera.x, 25 + camera.y, 200, 0.0 + camera.x, 0.0 + camera.y, 0.0 + camera.z, 0.0, 1, 0.0);
	glMultMatrixd(rotate);
	/****************************************************/




	

	glFogi(GL_FOG_MODE, fogMode[fogfilter]);        // �Ȱ����
	glFogfv(GL_FOG_COLOR, fogColor);            // �Ȱ� ���� ����
	glFogf(GL_FOG_DENSITY, density);                // �Ȱ��� ������
	glHint(GL_FOG_HINT, GL_NICEST);           // �Ȱ� ��Ʈ ��
	glFogf(GL_FOG_START, start);                // �Ȱ� ���� ����
	glFogf(GL_FOG_END, end);                // �Ȱ� �� ����
	glEnable(GL_FOG);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, gray);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
	glMateriali(GL_FRONT, GL_SHININESS, 128);
	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glPushMatrix(); {
		glTranslated(-150, -200, 150);
		glScaled(1, 2, 1);
		drawRect(100);
	}glPopMatrix();
	draw_bottom(500);

	GLfloat lightPos3[] = { 0, 100, 0 };
	GLfloat DiffuseLight[] = { 1, 1,1, 1.0f };
	GLfloat lightVector[] = { 0,-1,0 };

	GLfloat radian[] = { 90 };
	GLfloat exponent[] = { 30 };
	glPushMatrix(); {
		glEnable(GL_LIGHT2);
		glLightfv(GL_LIGHT2, GL_POSITION, lightPos3);
		glLightfv(GL_LIGHT2, GL_AMBIENT, ambientLight);
		glLightfv(GL_LIGHT2, GL_DIFFUSE, DiffuseLight);
		glLightfv(GL_LIGHT2, GL_SPECULAR, SpecularLight);

		glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, lightVector);
		glLightfv(GL_LIGHT2, GL_SPOT_CUTOFF, radian);
		glLightfv(GL_LIGHT2, GL_SPOT_EXPONENT, exponent);
		glTranslated(0, -200, 0);
		pyramid(100);

	}glPopMatrix();
	glPushMatrix(); {
		glRotated(rotatemoon, 0, 1, 0);
		glTranslated(100, 0, 0);
		glGenTextures(5, textures);
		//�ؽ�ó�� ��ü�� �����Ѵ�. --- (1)

		///////////////////////////////////////////////////////////////////////////////
		glBindTexture(GL_TEXTURE_2D, textures[4]);
		//�̹��� �ε��� �Ѵ�. --- (2)
		pBytes = LoadDIBitmap("moon.bmp", &info);
		//�ؽ�ó ���� ���Ǹ� �Ѵ�. --- (3)
		glTexImage2D(GL_TEXTURE_2D, 0, 3, 224, 225, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
		glEnable(GL_TEXTURE_GEN_S);
		glEnable(GL_TEXTURE_GEN_T);
		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
		glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
		glBindTexture(GL_TEXTURE_2D, textures[4]);
		glEnable(GL_TEXTURE_2D);

		glutSolidSphere(50, 40, 40);
		glDisable(GL_TEXTURE_GEN_S);
		glDisable(GL_TEXTURE_GEN_T);
	}glPopMatrix();
	glPushMatrix(); {
		glRotated(rotate1, 0, 1, 0);
		glEnable(GL_LIGHT0);

		glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLightr);
		glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularLight);
		glLightfv(GL_LIGHT0, GL_POSITION, lightPos1);
		if (!isLight1) {
			glDisable(GL_LIGHT0);
		}
		glColor3f(1.0f, 0.0f, 0.0f);
		glTranslated(500, 0, 0);
		glRotated(270, 0, 1, 0);
		glutSolidCone(20, 20, 20, 20);
	}glPopMatrix();

	glPushMatrix(); {
		glRotated(rotate2, 0, 1, 0);
		glEnable(GL_LIGHT1);

		glLightfv(GL_LIGHT1, GL_AMBIENT, ambientLight);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, DiffuseLightb);
		glLightfv(GL_LIGHT1, GL_SPECULAR, SpecularLight);
		glLightfv(GL_LIGHT1, GL_POSITION, lightPos2);
		if (!isLight2) {
			glDisable(GL_LIGHT1);
		}
		glColor3f(1.0f, 0.0f, 0.0f);
		glTranslated(-500, 0, 0);
		glRotated(-270, 0, 1, 0);
		glutSolidCone(20, 20, 20, 20);
	}glPopMatrix();

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
