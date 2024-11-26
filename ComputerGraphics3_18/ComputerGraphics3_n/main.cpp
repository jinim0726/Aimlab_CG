#define _CRT_SECURE_NO_WARNINGS //--- ���α׷� �� �տ� ������ ��
#include <iostream>
#include <vector>
#include "random.h"
#include "shaderSourceCode.h"

#define SCREENWIDTH 720
#define SCREENHEIGHT 480

// ����� ���� �Լ�
GLvoid Reshape(int w, int h); //--- �ݹ� �Լ�: �ٽ� �׸��� �ݹ� �Լ�
GLvoid drawScene(GLvoid);
void Keyboard(unsigned char, int, int); // Ű �Է� �޴� �Լ�
void SpecialKeyboard(int key, int x, int y);
void TimerFunction(int); // Ÿ�̸� �Լ�
void Mouse(int, int, int, int);
void Motion(int x, int y);

// ����� ���� ���� ( �ʼ� )
GLuint shaderProgramID; // ���̴� ���α׷� �̸�
GLuint vertexShader; // ���ؽ� ���̴� ��ü
GLuint fragmentShader; // �����׸�Ʈ ���̴� ��ü
bool setTimer = true;
bool isLeftButtonClick;
bool isRightButtonClick;
GLuint vao, vbo[2], ebo;

// ����� ���� ���� ( �ʼ��ƴ� )
shape::DefaultShape line_x{};
shape::DefaultShape line_y{};
shape::DefaultShape line_z{};
bool isDepth = true;
bool isOrtho{};
bool isSolid{};

void main(int argc, char** argv) //--- ������ ����ϰ� �ݹ��Լ� ����
{
	//--- ������ �����ϱ�
	glutInit(&argc, argv); // glut �ʱ�ȭ
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // ���÷��� ��� ����
	glutInitWindowPosition(100, 100); // �������� ��ġ ����
	glutInitWindowSize(SCREENWIDTH, SCREENHEIGHT); // �������� ũ�� ����
	glutCreateWindow("Example1"); // ������ ���� (������ �̸�)

	//--- GLEW �ʱ�ȭ�ϱ�
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) // glew �ʱ�ȭ
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized\n";

	// ���� ����
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);

	// ���̴� �о�ͼ� ���̴� ���α׷� �����
	make_shaderProgram(vertexShader, fragmentShader, shaderProgramID);
	glPointSize(1.f);
	glLineWidth(1.f);

	line_x.SetVertex(glm::vec3(1.0f, 0.0f, 0.0f), 0);
	line_x.SetVertex(glm::vec3(-1.0f, 0.0f, 0.0f), 1);
	line_y.SetVertex(glm::vec3(0.0f, 1.0f, 0.0f), 0);
	line_y.SetVertex(glm::vec3(0.0f, -1.0f, 0.0f), 1);
	line_z.SetVertex(glm::vec3(0.0f, 0.0f, 1.0f), 0);
	line_z.SetVertex(glm::vec3(0.0f, 0.0f, -1.0f), 1);
	line_x.SetColor(glm::vec4(1.0f, 0.0f, 0.0f, 0.5f), 0);
	line_x.SetColor(glm::vec4(1.0f, 0.0f, 0.0f, 0.5f), 1);
	line_y.SetColor(glm::vec4(0.0f, 1.0f, 0.0f, 0.5f), 0);
	line_y.SetColor(glm::vec4(0.0f, 1.0f, 0.0f, 0.5f), 1);
	line_z.SetColor(glm::vec4(0.0f, 0.0f, 1.0f, 0.5f), 0);
	line_z.SetColor(glm::vec4(0.0f, 0.0f, 1.0f, 0.5f), 1);
	line_x.cnt = 2;
	line_y.cnt = 2;
	line_z.cnt = 2;

	glutTimerFunc(60, TimerFunction, 1); // Ÿ�̸��Լ� �� ����

	glutDisplayFunc(drawScene); // ��� �Լ��� ����
	glutReshapeFunc(Reshape); // �ٽ� �׸��� �Լ� ����
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SpecialKeyboard);
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glClearColor(1.f, 1.f, 1.f, 1.f); // �������� ��backGround���� ����
	glutMainLoop(); // �̺�Ʈ ó�� ����
}

GLvoid Reshape(int w, int h) //--- �ݹ� �Լ�: �ٽ� �׸��� �ݹ� �Լ�
{
	glViewport(0, 0, w, h);
}

GLvoid drawScene() //--- �ݹ� �Լ�: �׸��� �ݹ� �Լ�
{
	glClearColor(1.f, 1.f, 1.f, 1.f); // �������� ��backGround���� ����
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�
	// �׸��� �κ� ����: �׸��� ���� �κ��� ���⿡ ���Եȴ�.

	// ������ ���������ο� ���̴� �ҷ�����
	glUseProgram(shaderProgramID);

	// �������------------------------------------------------

	// x y z ��
	DrawShape(shaderProgramID, vao, vbo, line_x, isOrtho);
	DrawShape(shaderProgramID, vao, vbo, line_y, isOrtho);
	DrawShape(shaderProgramID, vao, vbo, line_z, isOrtho);


	// �������-----------------------------------------------

	glutSwapBuffers(); // ȭ�鿡 ����ϱ�
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	}

	glutPostRedisplay();
}

void SpecialKeyboard(int key, int x, int y) {
	switch (key) {
	}
	glutPostRedisplay();
}


void Mouse(int button, int state, int x, int y) // ���콺 ��ǥ�� ���� ���� 0,0 ������ �Ʒ��� 800,800 (â ũ��)
{
	GLfloat xPos = (2.0f * x) / SCREENWIDTH - 1.0f;
	GLfloat yPos = 1.0f - (2.0f * y) / SCREENHEIGHT;

	if (state == GLUT_DOWN)
	{
		if (button == GLUT_LEFT_BUTTON)
		{
			isLeftButtonClick = true;
		}
		else if (button == GLUT_RIGHT_BUTTON)
		{
			isRightButtonClick = true;
		}
	}
	else if (state == GLUT_UP)
	{
		if (button == GLUT_LEFT_BUTTON)
		{
			isLeftButtonClick = false;
		}
		else if (button == GLUT_RIGHT_BUTTON)
		{
			isRightButtonClick = false;
		}
	}

	glutPostRedisplay();
}

void Motion(int x, int y)
{
	GLfloat xPos = (2.0f * x) / SCREENWIDTH - 1.0f;
	GLfloat yPos = 1.0f - (2.0f * y) / SCREENHEIGHT;

	if (isLeftButtonClick == true)
	{
	}
	else if (isRightButtonClick == true)
	{
	}

	glutPostRedisplay();
}

void TimerFunction(int value)
{
	if (setTimer)
	{
		glutPostRedisplay(); // ȭ�� �� ���
		glutTimerFunc(60, TimerFunction, 1); // Ÿ�̸��Լ� �� ����
	}
}