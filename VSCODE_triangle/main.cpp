#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <streambuf>
#include <string>

int main(int argc, char **argv)
{
    std::ifstream vertexFile("./vertex_shader.vert",std::ios::in);
    if(!vertexFile.is_open()){
        std::cout << "vertex file error " << std::endl;
        return false;
    }
    std::string stringVertexTmp(std::istreambuf_iterator<char>(vertexFile),
                                std::istreambuf_iterator<char>());
    vertexFile.close();

    std::ifstream fragFile("./fragment_shader.frag",std::ios::in);
    if(!fragFile.is_open()){
        std::cout << "frag file error " << std::endl;
        return false;
    }
    std::string stringFragTmp(std::istreambuf_iterator<char>(fragFile),
                              std::istreambuf_iterator<char>());


    //init openGL
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(800,600,"learnOPENGL",NULL,NULL);
    if(window == nullptr)
    {
        
    }

    return 0;
}