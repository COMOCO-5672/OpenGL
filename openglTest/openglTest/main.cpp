
#if 0

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

class screenPt {
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
winReshapeFcn(int newWidth, int newHeight)
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

int
main(int argc, char** argv)
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


#endif 

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

// 窗口大小改变回调
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

float vertices[] = {
    -0.5f,-0.5f,0.0f,
    0.5f, -0.5f,0.0f,
    0.0f, 0.5f, 0.0f
};

// 顶点着色器
const char *vertexShaderSource = "#version 330 core \n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\n";

const char *fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n";


unsigned int VBO, VAO;

int
main(int argc, char** argv)
{
    // 初始化窗口
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
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  // 每当窗口变化时调用

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // 编译着色器
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // 片段着色器
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // 链接着色器程序
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // glViewport(0, 0, 800, 600);  // create view
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    // 复制顶点数组到缓冲中供OpenGL使用
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // 设置顶点属性指针
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); // 告诉渲染器如何解析顶点数据
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // 循环渲染
    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        //清除
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // 当我们渲染一个物体是要用到的着色器程序
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapInterval(1);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}
