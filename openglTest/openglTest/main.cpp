#include "glut.h"
#include "stdio.h"
#include "iostream"
#include <stdlib.h>
#include <math.h>

int point1[]{ 15,50 };
int point2[]{ 25,30 };
int point3[]{ 60,50 };
int point4[]{ 42,38 };
int point5[]{ 30,45 };
int point6[]{ 90,60 };

GLint points[8][3] = { {0,0,0},{0,1,0},{1,0,0},{1,1,0},{0,0,1},{0,1,1},{1,0,1},{1,1,1} };

GLsizei winWidth = 400, winHeight = 400;
GLuint regHex;
const double TWO_PI = 6.2831853;

class screenPt
{
private:
    GLint x, y;
public:
    screenPt()
    {
        x = y = 0;
    }

    void setCoords(GLint xCoord, GLint yCoord)
    {
        x = xCoord;
        y = yCoord;
    }

    GLint getx() const
    {
        return x;
    }
    GLint gety() const
    {
        return y;
    }
};

static void
init(void)
{
    screenPt hexVertex, circCtr;
    GLdouble theta;
    GLint k;
    circCtr.setCoords(winWidth / 2, winHeight / 2);

    glClearColor(1.0, 1.0, 1.0, 0.0);
    regHex = glGenLists(1);
    glNewList(regHex, GL_COMPILE);
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    for (k = 0; k < 6; k++) {
        theta = TWO_PI * k / 6.0;
        hexVertex.setCoords(circCtr.getx() + 150 * cos(theta),
            circCtr.gety() + 150 * sin(theta));
        glVertex2i(hexVertex.getx(), hexVertex.gety());
    }
    glEnd();
    glEndList();
}

void
regHexgon(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glCallList(regHex);
    glFlush();
}

void
winReshapeFcn(int newWidth,int newHeight)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, (GLdouble)newWidth, 0.0, (GLdouble)newHeight);

    glClear(GL_COLOR_BUFFER_BIT);
}

void
RenderScene(void)
{
    // Clear the window with current clearing color
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.2, 0.2, 0.2);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2iv(point1);
    glVertex2iv(point2);
    glVertex2iv(point3);
    glVertex2iv(point4);
    glVertex2iv(point5);
    glVertex2iv(point6);
    //glRecti(200, 100, 50, 250);
    glEnd();
    // Flush drawing commands
    glFlush();
}

void
quad(GLint n1, GLint n2, GLint n3, GLint n4)
{
    glBegin(GL_QUADS);

    glVertex3iv(points[n1]);
    glVertex3iv(points[n2]);
    glVertex3iv(points[n3]);
    glVertex3iv(points[n4]);

    glEnd();
}

///
// Set up the rendering state
void
SetupRC(void)
{
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 200.0, 0.0, 150.0);
}

#include <GLFW/glfw3.h>
#include <glad/glad.h>

int
main(int argc, char** argv)
{
    /* glutInit(&argc, argv);
     glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
     glutInitWindowPosition(100, 200);
     glutInitWindowSize(500, 500);
     glutCreateWindow("Simple");
     SetupRC();
     glutDisplayFunc(RenderScene);
     glutMainLoop();*/

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(800, 600, "learnOpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
}
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    glViewport(0, 0, 800, 600);  // create view



    return 0;
}
