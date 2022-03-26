#include <GL/gl3w.h> // 最先被引用
#include <GLFW/glfw3.h>
#include <cstdio>

typedef struct _shaderInfo
{
    GLenum type;
    const char *filename;
    GLuint shader;
}ShaderInfo;

GLFWwindow *m_pWindow;

enum VAO_IDS { triangles, NumVAOs };
enum Buffer_IDs { ArrayBuffer, NumBuffers };
enum Attrib_IDs { vPosition = 0 };

GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];

const GLuint NumVertices = 6;

static const GLchar* ReadShader(const char *filename)
{
    FILE *infile;
    fopen_s(&infile, filename, "rb");
    if (!infile) {
        return nullptr;
    }

    fseek(infile, 0, SEEK_END);
    int len = ftell(infile);
    fseek(infile, 0, SEEK_SET);

    GLchar *source = new GLchar[len + 1];
    fread(source, 1, len, infile);
    fclose(infile);

    source[len] = 0;
    return const_cast<const GLchar*>(source);
}

void window_size_callback(GLFWwindow *window, int width, int height)
{
    auto p_window = glfwGetWindowUserPointer(window);
    glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    glfwGetWindowUserPointer(window);
}

void char_callback(GLFWwindow *window, unsigned int codepoint)
{
    glfwGetWindowUserPointer(window);
}

GLuint LoadShader(ShaderInfo *shader_info)
{
    if (shader_info == nullptr) return 0;

    GLuint program = glCreateProgram();

    ShaderInfo *entry = shader_info;

    while (entry->type != GL_NONE) {
        GLuint shader = glCreateShader(entry->type);

        entry->shader = shader;
        const GLchar *source = ReadShader(entry->filename);
        if (!source) {
            for (entry = shader_info; entry->type != GL_NONE; ++entry) {
                glDeleteShader(entry->shader);
                entry->shader = 0;
            }
            return 0;
        }

        glShaderSource(shader, 1, &source, nullptr);
        delete[]source;

        glCompileShader(shader);

        GLint compiled;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
        if (!compiled) {
            return 0;
        }

        glAttachShader(program, shader);

        ++entry;
    }

    glLinkProgram(program);

    GLint linked;
    glGetProgramiv(program, GL_LINK_STATUS, &linked);
    if (!linked) {
        for (entry = shader_info; entry->type != GL_NONE; ++entry) {
            glDeleteShader(entry->shader);
            entry->shader = 0;
        }
        return 0;
    }
    return program;

}

void Display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBindVertexArray(VAOs[triangles]);
    glDrawArrays(GL_TRIANGLES, 0, NumVertices);
}

void init()
{
    //glCreateVertexArrays(NumVAOs, VAOs);
    glGenVertexArrays(NumVAOs, VAOs);
    glBindVertexArray(VAOs[triangles]);

    GLfloat vertices[NumVertices][2] = {
        { -0.90f, -0.90f }, { 0.85f, -0.90f }, { -0.90f, 0.85f }, //triangle 1
        { 0.90f, -0.85f }, { 0.90f, 0.90f },{ -0.85f, 0.90f }  // triangle 2
    };

    glGenBuffers(NumBuffers, Buffers);
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    ShaderInfo shader_info[] = {
        {GL_VERTEX_SHADER ,"media/shaders/keypress/keypress.vert"},
        {GL_FRAGMENT_SHADER,"media/shaders/keypress/keypress.frag"},
        {GL_NONE,nullptr}
    };

    GLuint program = LoadShader(shader_info);

    glUseProgram(program);
    glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, (void *)0);
    glEnableVertexAttribArray(vPosition);

}

void main1()
{
    glfwInit();

    m_pWindow = glfwCreateWindow(800, 600, "opengl application", nullptr, nullptr);
    glfwSetWindowUserPointer(m_pWindow, nullptr);
    glfwSetWindowSizeCallback(m_pWindow, window_size_callback);
    glfwSetKeyCallback(m_pWindow, key_callback);
    glfwSetCharCallback(m_pWindow, char_callback);

    glfwMakeContextCurrent(m_pWindow);
    if (gl3wInit()) {
        return;
    }
    if (!gl3wIsSupported(3, 2)) {
        return;
    }

    init();

    while (!glfwWindowShouldClose(m_pWindow)) {
        Display();
        glfwSwapBuffers(m_pWindow);
        glfwPollEvents();
    }

    glfwTerminate();
    return;
}

#include <iostream>
#include <filesystem>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void processInput(GLFWwindow *window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

enum GL_VAOs { VA1, VAO };
enum GL_BUFFER_IDs { VB1, VBO };
enum GL_EBUFFER_IDs { EB1, EBO };

GLuint NVAOs[VAO];
GLuint NBuffers[VBO];
GLuint EBuffers[EBO];

const GLuint NVertices = 6;

// 加载shader和png 图片
void main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // 主版本号
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // 次版本号
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_pWindow = glfwCreateWindow(800, 600, "Learn OPENGL", nullptr, nullptr);
    if (m_pWindow == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(m_pWindow);

    if (gl3wInit()) {
        return;
    }
    if (!gl3wIsSupported(3, 2)) {
        return;
    }

    // 设置窗口大小改变函数
    glfwSetFramebufferSizeCallback(m_pWindow, window_size_callback);

    float vertices[] = {
        //     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
             0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
             0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
            -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
    };

    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    glGenVertexArrays(VAO, NVAOs);
    // 绑定顶点数组对象
    glBindVertexArray(NVAOs[VA1]);

    glGenBuffers(VBO, NBuffers);
    // 把我们的顶点数组复制到有个顶点缓冲中，供OpenGL使用
    glBindBuffer(GL_ARRAY_BUFFER, NBuffers[VB1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenBuffers(EBO, EBuffers);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBuffers[EB1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // 位置属性
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // 颜色属性
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // 纹理坐标属性
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    unsigned int texture1;
    glGenTextures(1, &texture1);

    glBindTexture(GL_TEXTURE_2D, texture1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    ShaderInfo shader_info[] = {
        {GL_VERTEX_SHADER ,"./vertex.vert"},
        {GL_FRAGMENT_SHADER,"./fragment.frag"},
        {GL_NONE,nullptr}
    };

    GLuint Id = LoadShader(shader_info);

    int width, height, nrChannels;
    unsigned char *data = stbi_load("./container.jpg", &width, &height, &nrChannels, 0);

    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "Failed to load texture" << std::endl;
    }

    stbi_image_free(data);

    while (!glfwWindowShouldClose(m_pWindow)) {
        processInput(m_pWindow);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        // 绑定材质
        glBindTexture(GL_TEXTURE_2D, texture1);
        // 渲染箱子
        glUseProgram(Id);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        // 交换缓冲区
        glfwSwapBuffers(m_pWindow);
        // 事件回传
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, NVAOs);
    glDeleteBuffers(1, NBuffers);
    glDeleteBuffers(1, EBuffers);

    glfwTerminate();
    return;
}

void processInput(GLFWwindow* window)
{
    // 返回这个按键是否正在被按下
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)//是否按下了返回键
        glfwSetWindowShouldClose(window, true);
}