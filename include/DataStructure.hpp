#ifndef DATA_HPP
#define DATA_HPP

#include <GL/glew.h>

struct Data
{
	GLfloat *vertices;
	GLfloat *normals;
	GLuint *indices;

	int verticesNum;

};


struct Buffer
{
	GLuint verticesID;
	GLuint normalsID;
	GLuint indicesID;

	int indicesNum; 
	int verticesNum;

	// GLfloat* normalsData;
	// GLfloat *verticesData;

};

static int bufferIndex = 0;

extern int bufferSize;

extern Data data;
extern Buffer buffer;
extern Buffer* buffers;



#endif