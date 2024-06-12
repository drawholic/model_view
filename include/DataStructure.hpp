#ifndef DATA_HPP
#define DATA_HPP

#include <GL/glew.h>

struct Data
{
	GLfloat *vertices;
	GLfloat *normals;

	unsigned int verticesNum;

} data;


struct Buffer
{
	GLuint verticesID;
	GLfloat *verticesData;

	GLuint normalsID;
	GLfloat* normalsData;
} buffer;

#endif