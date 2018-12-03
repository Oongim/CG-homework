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
	// 바이너리 읽기 모드로 파일을 연다
	//if ((fp = fopen(filename, "rb")) == NULL)
	fopen_s(&fp, filename, "rb");
	if ( fp == NULL )
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

void drawRect(float size, int i)
{
	glPushMatrix(); {
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_QUADS);
		if (i == 0) {
			//윗면
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
			//앞면		 
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
		//오른쪽옆면
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
		//왼쪽옆면
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
			//뒷면
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
			//바닥면
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
	GLubyte *pBytes; // 데이터를 가리킬 포인터
	BITMAPINFO *info; // 비트맵 헤더 저장할 변수
					  // 조명 설정
					  // n개의 이미지 텍스처 매핑을 한다.
	GLuint textures[6];
	
	glGenTextures(3, textures);
	//텍스처와 객체를 결합한다. --- (1)
	
	///////////////////////////////////////////////////////////////////////////////
	for (int i = 0; i < 6; ++i) {
		glBindTexture(GL_TEXTURE_2D, textures[i]);
		//이미지 로딩을 한다. --- (2)
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

		//텍스처 설정 정의를 한다. --- (3)
		glTexImage2D(GL_TEXTURE_2D, 0, 3, 82, 82, 0, GL_BGR_EXT,GL_UNSIGNED_BYTE, pBytes);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
		// 텍스처 매핑 활성화
		glEnable(GL_TEXTURE_2D);
		// 텍스처를 객체에 맵핑
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
