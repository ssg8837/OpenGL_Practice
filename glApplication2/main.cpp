#include <Windows.h>
#include <gl/GL.h>
#include<gl/GLU.h>
#include<gl/glut.h>

static bool mouseLeftDown;
static float point[3][2];
static int howclick;

void mouseButton(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			if (!mouseLeftDown)
			{
				if (howclick < 3)
				{
					double viewport[4];
					glGetDoublev(GL_VIEWPORT, viewport);

					point[howclick][0] = x / (float)viewport[2] * 500;
					point[howclick][1] = (viewport[3] - y) / (float)viewport[3] * 500;
					howclick++;
				}

				mouseLeftDown = true;
			}
		}
		else if (state == GLUT_UP)
		{
			glutPostRedisplay();
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
		glutPostRedisplay();
	}
}

void mouseMotion(int x, int y)
{
	if (mouseLeftDown)
	{
		double viewport[4];
		glGetDoublev(GL_VIEWPORT, viewport);

	}
	glutPostRedisplay();
}

void init(void)
{
	mouseLeftDown = false;

	point[0][0] = -10;
	point[0][1] = -10;
	point[1][0] = -10;
	point[1][1] = -10;
	point[2][0] = -10;
	point[2][1] = -10;
	howclick = 0;
}

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glPointSize(10);
	glBegin(GL_POINTS);
	{
		glColor3f(0, 0, 1);
		glVertex2fv(point[0]);
		glVertex2fv(point[1]);
		glVertex2fv(point[2]);
	}
	glEnd();

	//���� ������
	if (howclick > 2) {

		glBegin(GL_TRIANGLES);
		{

			glColor3f(1, 0, 0);
			glVertex2fv(point[0]);
			glVertex2fv(point[1]);
			glVertex2fv(point[2]);

		}
		glEnd();
	}
	//flush
	glFlush();
}



void SetupRC(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);//Rendering Buffer�� ���� �� ����
}
void ChangeSize(int w, int h)
{
	GLfloat aspectRatio;

	if (h == 0)//0���� ������ ����
		h = 1;

	//������Ʈ ����
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	aspectRatio = (GLfloat)w / (GLfloat)h;
	if (w <= h)
	{
		gluOrtho2D(0, 500, 0, 500 * (float)h / (float)w);
	}
	else
	{
		gluOrtho2D(0, 500 * (float)w / (float)h, 0, 500);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void main(int argc, char * argv[])
{
	glutInit(&argc, argv);//GLUT ���̺귯���� �ʱ�ȭ �� �� ������ �ý��۰� ������ ����.
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); //������ �������� ���÷��� ��带 ����
	glutInitWindowSize(600, 600);//������ ũ�� ����
	glutCreateWindow("Simple");//���ο� ������ ����
	glutDisplayFunc(RenderScene);//ȭ�� ���÷��� �̺�Ʈ�� �߻� ���� �� ����� �ݹ� ��� �Լ�
	glutReshapeFunc(ChangeSize);//������ ũ�Ⱑ ����Ǿ��� �� �߻� ���� �� ����� �ݹ� ��� �Լ�

	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMotion);

	init();
	SetupRC();//void SetupRC() / void Init() -�ʱ�ȭ �Լ��μ� ���������� ���(������ ����)

	glutMainLoop();//GLUT, GL ��ƾ
}

