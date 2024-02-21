#include <GL/freeglut.h>
#include <string>

void
init(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);

    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 250.0, 0.0, 250.0);
}

void
RenderTimer(int value)
{
    glutSetWindowTitle(("FPS:" + std::to_string(value)).c_str());
}

void
lineSegment(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor4f(1.0, 0.0, 0.0, 0.6);
    //glBegin(GL_POLYGON);
    glRectf(0.0, 200.0, 200.0, 0.0);
    /* glVertex2i(180, -10);
     glVertex2i(10, 180);*/
    //glEnd();

    glFlush();

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
    glutDisplayFunc(lineSegment);
    glutMainLoop();

    return 0;
}