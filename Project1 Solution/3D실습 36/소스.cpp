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
	// 바이너리 읽기 모드로 파일을 연다
	//if ((fp = fopen(filename, "rb")) == NULL)
	fopen_s(&fp, filename, "rb");
	if (fp == NULL)
		return NULL;
	// 비트맵 파일 헤더를 읽는다.
	if (fread(&header, sizeof(BITMAPFILEHEADER), 1, fp) < 1) {
		fclose(fp);
		return NULL;
	}
	// 파일이 BMP 파일인지 확인한다.
	if (header.bfType != 'MB') {
		fclose(fp);
		return NULL;
	}
	// BITMAPINFOHEADER 위치로 간다.
	infosize = header.bfOffBits - sizeof(BITMAPFILEHEADER);
	// 비트맵 이미지 데이터를 넣을 메모리 할당을 한다.
	if ((*info = (BITMAPINFO *)malloc(infosize)) == NULL) {
		fclose(fp);
		exit(0);
		return NULL;
	}
	// 비트맵 인포 헤더를 읽는다.
	if (fread(*info, 1, infosize, fp) < (unsigned int)infosize) {
		free(*info);
		fclose(fp);
		return NULL;
	}
	// 비트맵의 크기 설정
	if ((bitsize = (*info)->bmiHeader.biSizeImage) == 0)
		bitsize = ((*info)->bmiHeader.biWidth*(*info)->bmiHeader.biBitCount + 7) / 8.0 * abs((*info)->bmiHeader.biHeight);
	// 비트맵의 크기만큼 메모리를 할당한다.
	if ((bits = (unsigned char *)malloc(bitsize)) == NULL) {
		free(*info);
		fclose(fp);
		return NULL;
	}
	// 비트맵 데이터를 bit(GLubyte 타입)에 저장한다.
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
		camera.z -= 2;
		break;
	case '-':
		camera.z += 2;
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
	glutPostRedisplay();
	glutTimerFunc(50, TimerFunction, 1);
}
void main(int argc, char *argv[])
{
	Init();
	srand(time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정
	glutCreateWindow("실습1"); // 윈도우 생성 (윈도우 이름)
	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutTimerFunc(50, TimerFunction, 1);
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}
// 윈도우 출력 함수
GLubyte *pBytes; // 데이터를 가리킬 포인터
BITMAPINFO *info; // 비트맵 헤더 저장할 변수
				  // 조명 설정
				  // n개의 이미지 텍스처 매핑을 한다.
GLuint textures[3];
void pyramid(float size)
{
	

	glGenTextures(3, textures);
	//텍스처와 객체를 결합한다. --- (1)

	///////////////////////////////////////////////////////////////////////////////
		glBindTexture(GL_TEXTURE_2D, textures[0]);
		//이미지 로딩을 한다. --- (2)
			pBytes = LoadDIBitmap("1.bmp", &info);
		//텍스처 설정 정의를 한다. --- (3)
		glTexImage2D(GL_TEXTURE_2D, 0, 3, 217, 185, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
		// 텍스처 매핑 활성화
		glEnable(GL_TEXTURE_2D);
	glBegin(GL_TRIANGLES);
	if (isVector)
		glNormal3f(0, 0, 1);
	
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-size / 2, -size / 2, size / 2);//6
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(size / 2, -size / 2, size / 2);//7
	glTexCoord2f(0.5f, 1.0f);
	glVertex3f(0, size / 2, 0);//2
	if (isVector)
		glNormal3f(1, 0, 0);
	glTexCoord2f(0.5f, 1.0f);
	
	glVertex3f(0, size / 2, 0);//2
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(size / 2, -size / 2, size / 2);//7
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(size / 2, -size / 2, -size / 2);//8
	if (isVector)
		glNormal3f(-1, 0, 0);
	glTexCoord2f(0.5f, 1.0f);
	glVertex3f(0, size / 2, 0);//2
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-size / 2, -size / 2, -size / 2);//5
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-size / 2, -size / 2, size / 2);//6
	if (isVector)
		glNormal3f(0, 0, -1);
	glTexCoord2f(0.5f, 1.0f);
	glVertex3f(0, size / 2, 0);//2
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(size / 2, -size / 2, -size / 2);//8
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-size / 2, -size / 2, -size / 2);//5
	glEnd();
	glBegin(GL_QUADS);
	glNormal3f(0, -1, 0);
	glVertex3f(-size / 2, -size / 2, size / 2);//6
	glVertex3f(-size / 2, -size / 2, -size / 2);//5
	glVertex3f(size / 2, -size / 2, -size / 2);//8
	glVertex3f(size / 2, -size / 2, size / 2);//7
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void draw_bottom(float size)
{
	glGenTextures(3, textures);
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	//이미지 로딩을 한다. --- (2)
	pBytes = LoadDIBitmap("clock.bmp", &info);
	//텍스처 설정 정의를 한다. --- (3)
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 640, 480, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
	// 텍스처 매핑 활성화
	glEnable(GL_TEXTURE_2D);

	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
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
GLvoid drawScene(GLvoid)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();

	gluLookAt(0 + camera.x, 200 + camera.y, 500, 0.0 + camera.x, 0.0 + camera.y, 0.0 + camera.z, 0.0, 1, 0.0);
	glMultMatrixd(rotate);
	/****************************************************/




	GLfloat ambientLight[] = { 0.0f, ambient_num, 0.0f, 1.0f };
	GLfloat DiffuseLightr[] = { diffuse_num + 1, diffuse_num,diffuse_num, 1.0f };
	GLfloat DiffuseLightb[] = { diffuse_num , diffuse_num,diffuse_num + 1, 1.0f };
	GLfloat SpecularLight[] = { Specular_num, Specular_num, Specular_num, 1.0 }; // 백색조명
	GLfloat lightPos1[] = { 500.0, 0.0, 0.0, 1.0 };
	GLfloat lightPos2[] = { -500.0, 0.0, 0.0, 1.0 };

	GLfloat gray[] = { 0.75f, 0.75f, 0.75f, 1.0f };
	GLfloat specref[] = { Specular_num, Specular_num, Specular_num, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, gray);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
	glMateriali(GL_FRONT, GL_SHININESS, 128);
	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	draw_bottom(500);
	glPushMatrix(); {
		glTranslated(0, -200, 0);
		pyramid(100);
		glPushMatrix(); {
			glTranslated(200, 0, 200);
			pyramid(100);
		}glPopMatrix();
		glPushMatrix(); {
			glTranslated(-200, 0, 200);
			pyramid(100);
		}glPopMatrix();
		glPushMatrix(); {
			glTranslated(-200, 0, -200);
			pyramid(100);
		}glPopMatrix();
		glPushMatrix(); {
			glTranslated(200, 0, -200);
			pyramid(100);
		}glPopMatrix();
	}glPopMatrix();
	glPushMatrix(); {
		glRotated(rotatemoon, 0, 1, 0);
		glTranslated(100, 0, 0);
		glutSolidSphere(50, 40, 40);
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
