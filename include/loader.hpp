#ifndef LOADER_HPP
#define LOADER_HPP

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <GL/glew.h>
#include <vector>
#include "DataStructure.hpp"

void load_model(const char* path);

extern const aiScene* scene;



#endif