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

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <iostream>
#include <typeinfo>

void main()
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