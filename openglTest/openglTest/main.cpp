#include "glut.h"
#include "stdio.h"
#include "iostream"

int point1[]{ 15,50 };
int point2[]{ 25,30 };
int point3[]{ 60,50 };
int point4[]{ 42,38 };
int point5[]{ 30,45 };
int point6[]{ 90,60 };

GLint points[8][3] = { {0,0,0},{0,1,0},{1,0,0},{1,1,0},{0,0,1},{0,1,1},{1,0,1},{1,1,1} };



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
quad(GLint n1,GLint n2,GLint n3,GLint n4)
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
    glClearColor(1.0f, 1.0f, 1.0f,0.0f);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 200.0, 0.0, 150.0);
}

int
main(int argc,char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowPosition(100, 200);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Simple");
    SetupRC();
    glutDisplayFunc(RenderScene);
    glutMainLoop();
    return 0;
}
