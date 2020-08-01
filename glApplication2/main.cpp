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

	//빨간 폴리곤
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
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);//Rendering Buffer를 지울 색 설정
}
void ChangeSize(int w, int h)
{
	GLfloat aspectRatio;

	if (h == 0)//0으로 나누기 예방
		h = 1;

	//뷰포인트 설정
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
	glutInit(&argc, argv);//GLUT 라이브러리를 초기화 한 후 윈도우 시스템과 세션을 연다.
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); //생성될 윈도우의 디스플레이 모드를 설정
	glutInitWindowSize(600, 600);//윈도우 크기 설정
	glutCreateWindow("Simple");//새로운 윈도우 생성
	glutDisplayFunc(RenderScene);//화면 디스플레이 이벤트가 발생 했을 시 실행될 콜백 등록 함수
	glutReshapeFunc(ChangeSize);//윈도우 크기가 변경되었을 시 발생 했을 시 실행될 콜백 등록 함수

	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMotion);

	init();
	SetupRC();//void SetupRC() / void Init() -초기화 함수로서 관습적으로 사용(개발자 임의)

	glutMainLoop();//GLUT, GL 루틴
}

