#ifndef SHADER_HPP
#define SHADER_HPP

#include <fstream>
#include <GL/glew.h>

GLuint load_program(const char *vertex_path, const char *fragment_path);

GLuint create_shader(const char *path, GLenum shader_type);

#endif