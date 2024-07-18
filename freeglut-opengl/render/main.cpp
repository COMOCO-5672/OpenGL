#include <GL/freeglut.h>
#include <string>

void reshape(int width, int height);
void keyboard(unsigned char key, int x, int y);
void mouse(int button, int state, int x, int y);
void motion(int x, int y);

float angleX = 0.0f;
float angleY = 0.0f;
float angleZ = 0.0f;

int lastMouseX;
int lastMouseY;
bool isDragging = false;

void
init(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void
RenderTimer(int value)
{
    glutSetWindowTitle(("FPS:" + std::to_string(value)).c_str());
}

void Display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // 设置相机
    gluLookAt(0.0, 0.0, 5.0,  // 相机位置
        0.0, 0.0, 0.0,  // 观察点
        0.0, 1.0, 0.0); // 上向量

    // 旋转立方体
    glRotatef(angleX, 1.0, 0.0, 0.0);
    glRotatef(angleY, 0.0, 1.0, 0.0);
    glRotatef(angleZ, 0.0, 0.0, 1.0);
    // 绘制立方体
    //glColor4f(1.0, 0.0, 0.0, 0.6);
    //glutSolidCube(1.0);

    glBegin(GL_QUADS);
    // 前面
    glColor4f(1.0, 0.0, 0.0, 0.6); // 红色
    glVertex3f(-0.5, -0.5, 0.5);
    glVertex3f(0.5, -0.5, 0.5);
    glVertex3f(0.5, 0.5, 0.5);
    glVertex3f(-0.5, 0.5, 0.5);

    // 背面
    glColor4f(0.0, 1.0, 0.0, 0.6); // 绿色
    glVertex3f(-0.5, -0.5, -0.5);
    glVertex3f(0.5, -0.5, -0.5);
    glVertex3f(0.5, 0.5, -0.5);
    glVertex3f(-0.5, 0.5, -0.5);

    // 左面
    glColor4f(0.0, 0.0, 1.0, 0.6); // 蓝色
    glVertex3f(-0.5, -0.5, -0.5);
    glVertex3f(-0.5, -0.5, 0.5);
    glVertex3f(-0.5, 0.5, 0.5);
    glVertex3f(-0.5, 0.5, -0.5);

    // 右面
    glColor4f(1.0, 1.0, 0.0, 0.6); // 黄色
    glVertex3f(0.5, -0.5, -0.5);
    glVertex3f(0.5, -0.5, 0.5);
    glVertex3f(0.5, 0.5, 0.5);
    glVertex3f(0.5, 0.5, -0.5);

    // 顶面
    glColor4f(1.0, 0.0, 1.0, 0.6); // 洋红色
    glVertex3f(-0.5, 0.5, 0.5);
    glVertex3f(0.5, 0.5, 0.5);
    glVertex3f(0.5, 0.5, -0.5);
    glVertex3f(-0.5, 0.5, -0.5);

    // 底面
    glColor4f(0.0, 1.0, 1.0, 0.6); // 青色
    glVertex3f(-0.5, -0.5, 0.5);
    glVertex3f(0.5, -0.5, 0.5);
    glVertex3f(0.5, -0.5, -0.5);
    glVertex3f(-0.5, -0.5, -0.5);
    glEnd();

    glFlush();
    glutSwapBuffers();
}


void reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (GLfloat)width / (GLfloat)height, 1.0, 100.0);
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 27:
        exit(0);
        break;
    }
}

void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            isDragging = true;
            lastMouseX = x;
            lastMouseY = y;
        }
        else if (state == GLUT_UP) {
            isDragging = false;
        }
    }
}

void motion(int x, int y)
{
    if (isDragging)
    {
        int dx = x - lastMouseX;
        int dy = y - lastMouseY;

        angleX += dy * 0.5f;
        angleY += dx * 0.5f;

        lastMouseX = x;
        lastMouseY = y;

        glutPostRedisplay();
    }
}


int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(50, 100);
    glutInitWindowSize(400, 300);
    glutCreateWindow("example opengl");

    init();
    glutTimerFunc(1000, &RenderTimer, 60);
    glutDisplayFunc(Display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);

    glutMainLoop();

    return 0;
}