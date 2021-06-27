#include "glut.h"
#include "stdio.h"
#include "iostream"

int point1[]{ 15,50 };
int point2[]{ 25,30 };
int point3[]{ 60,50 };
int point4[]{ 42,38 };

void
RenderScene(void)
{
    // Clear the window with current clearing color
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.0, 0.4, 0.2);
    glBegin(GL_LINE_LOOP);
    glVertex2iv(point1);
    glVertex2iv(point2);
    glVertex2iv(point3);
    glVertex2iv(point4);
    glEnd();
    // Flush drawing commands
    glFlush();
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
