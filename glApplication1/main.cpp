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
static bool rot;//true�̸� �ݴ��

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

	//���� ������
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
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);//Rendering Buffer�� ���� �� ����
}
void ChangeSize(int w, int h)
{
	if (h == 0)//0���� ������ ����
		h = 1;
	
	//������Ʈ ����
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
	glutInit(&argc, argv);//GLUT ���̺귯���� �ʱ�ȭ �� �� ������ �ý��۰� ������ ����.
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); //������ �������� ���÷��� ��带 ����
	glutInitWindowSize(600,600);//������ ũ�� ����
	glutCreateWindow("Simple");//���ο� ������ ����
	glutDisplayFunc(RenderScene);//ȭ�� ���÷��� �̺�Ʈ�� �߻� ���� �� ����� �ݹ� ��� �Լ�
	glutReshapeFunc(ChangeSize);//������ ũ�Ⱑ ����Ǿ��� �� �߻� ���� �� ����� �ݹ� ��� �Լ�

	glutMouseFunc(mouseButton);
	glutTimerFunc(1000 / 30, timer, 1);
	glutKeyboardFunc(keyboard);

	init();
	SetupRC();//void SetupRC() / void Init() -�ʱ�ȭ �Լ��μ� ���������� ���(������ ����)

	glutMainLoop();//GLUT, GL ��ƾ
}