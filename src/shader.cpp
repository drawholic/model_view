#include "shader.hpp"
#include <iostream>

/// @brief Reads file, creates and compiles shaders
/// @param path path to file
/// @param shader_type type of the shader. i.e. vertex or fragment
/// @return shaderID
GLuint create_shader(const char *path, GLenum shader_type)
{

    std::ifstream in(path);
    char *body;
    int file_length;

    // Condition to read file
    if (in.is_open())
    {
        in.seekg(0, in.end);
        file_length = in.tellg();
        in.seekg(0, in.beg);
        body = new char[file_length];
        in.read(body, file_length);
    }
    else
    {
        std::cout << "Failure opening : " << path << '\n';
        exit(-1);
    };
    body[file_length] = '\0';
    GLint status = GL_FALSE;
    int infoLogLength;
    GLuint shaderID = glCreateShader(shader_type);
    glShaderSource(shaderID, 1, &body, 0);
    glCompileShader(shaderID);

    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &status);
    glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);

    if (infoLogLength > 0)
    {
        char log[infoLogLength + 1];
        glGetShaderInfoLog(shaderID, infoLogLength, NULL, log);
        std::cout << path << ":\n";
        std::cout << log << '\n';
    }
    // else
    // {
    //     std::cout << "Failure compiling: " << path << '\n';
    // }

    delete[] body;
    return shaderID;
};
GLuint load_program(const char *vertex_path, const char *fragment_path)
{
    GLuint programID = glCreateProgram();
    GLuint vertex = create_shader(vertex_path, GL_VERTEX_SHADER);
    GLuint fragment = create_shader(fragment_path, GL_FRAGMENT_SHADER);

    glAttachShader(programID, vertex);
    glAttachShader(programID, fragment);

    GLint status = GL_FALSE;
    int infoLogLength;
    glLinkProgram(programID);
    glGetProgramiv(programID, GL_LINK_STATUS, &status);
    glGetProgramiv(programID, GL_LINK_STATUS, &infoLogLength);

    if (!status)
    {
        printf("infolog call\n");
        char log[infoLogLength];
        glGetProgramInfoLog(programID, infoLogLength, 0, log);
        std::cout << log << '\n';
    }

    glDetachShader(programID, vertex);
    glDetachShader(programID, fragment);

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return programID;
}
