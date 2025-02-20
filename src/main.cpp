#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <iostream>

const char* vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec2 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos, 0.0, 1.0);\n"
    "}\n";

const char* fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(0.0, 0.0, 0.0, 1.0);\n"
    "}\n";

std::vector<float> transformVertices(const float* originalVertices, size_t size, glm::mat4 transform) {
    std::vector<float> transformedVertices;
    for (size_t i = 0; i < size; i += 2) {
        glm::vec4 point(originalVertices[i], originalVertices[i + 1], 0.0f, 1.0f);
        glm::vec4 transformedPoint = transform * point;
        transformedVertices.push_back(transformedPoint.x);
        transformedVertices.push_back(transformedPoint.y);
    }
    return transformedVertices;
}

float baseVertices[] = {
    -0.9f,  0.9f,  -0.04737f, 0.9f, // G a I
    -0.04737f, 0.9f,  -0.04737f,0.42633f, // I J
    -0.04737f, 0.42633f, -0.42633f, 0.42633f, // J K
    -0.42633f, 0.61581f, -0.42633f, 0.04737f, // k z // luego cambio el k por w
    -0.42633f, 0.04737f, -0.61581f, 0.04737f, //z a'
    -0.61581f, 0.04737f, -0.61581f, 0.0f, // a1 i1
    -0.71055f, 0.0f, -0.71055f, 0.04737f,  // h1 f1
    -0.71055f, 0.04737f, -0.9, 0.04737f, //f1 g1
    -0.9, 0.04737f, -0.9f,  0.9f, //g1 G
    -0.71055f, 0.04737f, -0.71055f, 0.52107f, // f1 R
    -0.71055f, 0.52107f,  -0.52107f, 0.52107f,//r s
    -0.42633f, 0.52107f,  -0.14211f, 0.52107f,// l m 
    -0.14211f, 0.52107f, -0.14211f, 0.80529f, //m n
    -0.14211f, 0.80529f, -0.80529f, 0.80529f,//n o
    -0.80529f, 0.80529f, -0.80529f, 0.14211f, //o p
    -0.80529f, 0.14211f, -0.71055f, 0.14211f,// P G
    -0.61581f, 0.04737f, -0.61581f, 0.42633f,// A1 B1
    -0.61581f, 0.42633f, -0.52107f, 0.42633f, //b1 c1

    -0.14211f, 0.71055f, -0.52107,0.71055f,// u t
    -0.52107,0.71055f, -0.52107,0.14211f, //t d1
    -0.52107,0.14211f, -0.61581,0.14211f, //d1 e1

    -0.42633f, 0.61581f, -0.14211f, 0.61581f,//w v
    -0.04737f, 0.71055f, 0.0f, 0.71055f, // l1 j1
    -0.04737f, 0.61581f, 0.0f, 0.61581f, // m1 k1

    0.0f,0.23685f, -0.23685f, 0.23685f, //n1 o1
    -0.23685f, 0.23685f, -0.23685f, 0.0f, //o1 p1
    0.0f,0.33159f, -0.33159f,0.33159f,// s1 r1
    -0.33159f,0.33159f, -0.33159f,0.0f, //r1 q1
};

std::vector<float> mazeVertices(baseVertices, baseVertices + sizeof(baseVertices) / sizeof(float));

glm::mat4 identity = glm::mat4(1.0f);
glm::mat4 rotate90 = glm::rotate(identity, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
glm::mat4 rotate180 = glm::rotate(identity, glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
glm::mat4 rotate270 = glm::rotate(identity, glm::radians(270.0f), glm::vec3(0.0f, 0.0f, 1.0f));

std::vector<float> rotated90 = transformVertices(baseVertices, sizeof(baseVertices) / sizeof(float), rotate90);
std::vector<float> rotated180 = transformVertices(baseVertices, sizeof(baseVertices) / sizeof(float), rotate180);
std::vector<float> rotated270 = transformVertices(baseVertices, sizeof(baseVertices) / sizeof(float), rotate270);

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

int main() {
    if (!glfwInit()) {
        std::cerr << "Falló al inicializar GLFW" << std::endl;
        return -1;
    }
    
    GLFWwindow* window = glfwCreateWindow(1000, 1000, "Laberinto OpenGL Dibujo 2D 02", NULL, NULL);
    if (!window) {
        std::cerr << "No se pudo crear la ventana GLFW" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glViewport(0, 0, 1000, 1000);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    mazeVertices.insert(mazeVertices.end(), rotated90.begin(), rotated90.end());
    mazeVertices.insert(mazeVertices.end(), rotated180.begin(), rotated180.end());
    mazeVertices.insert(mazeVertices.end(), rotated270.begin(), rotated270.end());
    
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, mazeVertices.size() * sizeof(float), mazeVertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_LINES, 0, mazeVertices.size() / 2);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
    glfwTerminate();
    return 0;
}