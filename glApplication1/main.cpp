#include <Windows.h>
#include <gl/GL.h>
#include<gl/GLU.h>
#include<gl/glut.h>

#include<cstdlib>
#include<ctime>

#include <math.h>

static bool mouseLeftDown;
static int red;
static int green;
static int blue;
static float theta;
static bool rot;//true이면 반대로

void timer(int value)
{
	if(!rot)
	{
		theta += 2.0;
		if (theta >= 360.0)
			theta -= 360.0;
	}
	else
	{
		theta -= 2.0;
		if (theta <= 0.0)
			theta += 360.0;
	}
	

	glutTimerFunc(1000 / 30, timer, 1);
	glutPostRedisplay();
}
void mouseButton(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			if (!mouseLeftDown)
			{
				srand((unsigned int)time(NULL));
				red = rand()%2;
				srand((unsigned int)time(NULL)+1);
				green = rand() % 2;
				srand((unsigned int)time(NULL)+2);
				blue = rand() % 2;
				mouseLeftDown = true;
			}
		}
		else if (state == GLUT_UP)
		{
			if (mouseLeftDown)
				mouseLeftDown = false;
		}
	}
	else if (button == GLUT_RIGHT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{

		}
		else if (state == GLUT_UP)
		{

		}
	}
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'r' |'R':
		switch (rot)
		{
		case true:
			rot = false;
			break;
		case false:
			rot = true;
			break;
		}
		break;

	default:
		break;
	}
}

void init(void)
{
	mouseLeftDown = false;


	theta = 0;
	red = 1;
	green = 0;
	blue = 0;
	rot = false;
}

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	float cos_th = cos(theta *3.14159 / 180.0);
	float sin_th = sin(theta * 3.14159 / 180.0);

	//빨간 폴리곤
	glBegin(GL_POLYGON);
	{
		glColor3f(red, green, blue);
		glVertex2f(cos_th, sin_th);
		glVertex2f(-sin_th, cos_th);
		glVertex2f(-cos_th, -sin_th);
		glVertex2f(sin_th, -cos_th);
		
	}
	glEnd();
	//flush
	glutSwapBuffers();
}

void SetupRC(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);//Rendering Buffer를 지울 색 설정
}
void ChangeSize(int w, int h)
{
	if (h == 0)//0으로 나누기 예방
		h = 1;
	
	//뷰포인트 설정
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (w <= h)
	{
		gluOrtho2D(-2.0, 2.0, -2.0*(float)h / (float)w, 2.0 * (float)h / (float)w);
	}
	else
	{
		gluOrtho2D(-2.0*(float)w / (float)h,2.0*(float)w/(float)h,-2.0,2.0);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void main(int argc, char * argv[])
{
	glutInit(&argc, argv);//GLUT 라이브러리를 초기화 한 후 윈도우 시스템과 세션을 연다.
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); //생성될 윈도우의 디스플레이 모드를 설정
	glutInitWindowSize(600,600);//윈도우 크기 설정
	glutCreateWindow("Simple");//새로운 윈도우 생성
	glutDisplayFunc(RenderScene);//화면 디스플레이 이벤트가 발생 했을 시 실행될 콜백 등록 함수
	glutReshapeFunc(ChangeSize);//윈도우 크기가 변경되었을 시 발생 했을 시 실행될 콜백 등록 함수

	glutMouseFunc(mouseButton);
	glutTimerFunc(1000 / 30, timer, 1);
	glutKeyboardFunc(keyboard);

	init();
	SetupRC();//void SetupRC() / void Init() -초기화 함수로서 관습적으로 사용(개발자 임의)

	glutMainLoop();//GLUT, GL 루틴
}