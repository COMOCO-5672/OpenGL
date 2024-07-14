#include <GL/freeglut.h>
#include <string>

#define M_PI 3.1415926

void DrawRoundedRect(float x, float y, float width, float height, float radius);

void DrawText(const std::string &text, float x, float y);

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

void Display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.0, 0.0, 0.0, 0.3);
    DrawRoundedRect(50.0 + 5.0, 50.0 - 5.0, 150.0, 100.0, 20.0);
    glDisable(GL_BLEND);

    glColor4f(1.0, 0.0, 0.0, 0.6);
    DrawRoundedRect(50.0, 50.0, 150.0, 100.0, 20.0);

    glColor4f(0.0, 0.0, 0.0, 1.0);
    DrawText("hello", 110.0, 90.0);

    glFlush();
}

void DrawRoundedRect(float x, float y, float width, float height, float radius)
{
    float x1 = x;
    float y1 = y;
    float x2 = x + width;
    float y2 = y + height;

    glBegin(GL_QUADS);
    glVertex2f(x1 + radius, y1);
    glVertex2f(x2 - radius, y1);

    glVertex2f(x2 - radius, y2);
    glVertex2f(x1 + radius, y2);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(x1, y1 + radius);
    glVertex2f(x1 + radius, y1 + radius);

    glVertex2f(x1 + radius, y2 - radius);
    glVertex2f(x1, y2 - radius);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(x2, y1 + radius);
    glVertex2f(x2 - radius, y1 + radius);

    glVertex2f(x2 - radius, y2 - radius);
    glVertex2f(x2, y2 - radius);
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x1 + radius, y1 + radius);
    for (int i = 0; i <= 100; ++i) {
        glVertex2f(
            x1 + radius + radius * cos(i * 2.0f * M_PI / 100),
            y1 + radius + radius * sin(i * 2.0f * M_PI / 100)
        );
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x2 - radius, y1 + radius);
    for (int i = 0; i <= 100; ++i) {
        glVertex2f(
            x2 - radius + radius * cos(i * 2.0f * M_PI / 100),
            y1 + radius + radius * sin(i * 2.0f * M_PI / 100)
        );
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x1 + radius, y2 - radius);
    for (int i = 0; i <= 100; ++i) {
        glVertex2f(
            x1 + radius + radius * cos(i * 2.0f * M_PI / 100),
            y2 - radius + radius * sin(i * 2.0f * M_PI / 100)
        );
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x2 - radius, y2 - radius);
    for (int i = 0; i <= 100; ++i) {
        glVertex2f(
            x2 - radius + radius * cos(i * 2.0f * M_PI / 100),
            y2 - radius + radius * sin(i * 2.0f * M_PI / 100)
        );
    }
    glEnd();
}

void DrawText(const std::string& text, float x, float y)
{
    glRasterPos2f(x, y);
    for (char c : text)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
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
    glutDisplayFunc(Display);
    glutMainLoop();

    return 0;
}