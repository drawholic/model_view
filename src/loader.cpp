#include "loader.hpp"

#include <assimp/Importer.hpp>
#include <assimp/mesh.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <assimp/vector3.h>
#include <iostream>
#include <string>

#include <GL/glew.h>

#include "DataStructure.hpp"

const aiScene* scene;

void render_mesh( unsigned int meshID)
{
    // global data is used from file DataStructure.hpp

    data.verticesNum = mesh->mNumFaces * 3;
    data.vertices = new GLfloat[data.verticesNum * 3];
    data.normals = new GLfloat[data->verticesNum * 3];
    
    aiMesh* mesh = scene->mMeshes[meshID];

    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
    {  
        const aiFace& face = mesh->mFaces[i];

        for(int j = 0; j < 3; j++)
        {
            int vertexIndex = face.mIndices[j];
            aiVector3D vec3 = mesh->mVertices[vertexIndex];
            aiVector3D norm3 = mesh->mNormals[vertexIndex];

            data->vertices[vertexIndex * 3] = vec3.x;
            data->vertices[vertexIndex * 3 + 1] = vec3.y;
            data->vertices[vertexIndex * 3 + 2] = vec3.z;

            data->normals[vertexIndex * 3] = norm3.x;
            data->normals[vertexIndex * 3 + 1] = norm3.y;
            data->normals[vertexIndex * 3 + 2] = norm3.z;


        };
    };

    glGenBuffers(1, &buffer.verticesID);
    glBindBuffer(GL_ARRAY_BUFFER, buffer.verticesID);
    glBufferData(GL_ARRAY_BUFFER, data.verticesNum * 3 * sizeof(GLfloat), data.vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &buffer.normalsID);
    glBindBuffer(GL_ARRAY_BUFFER, buffer.normalsID);
    glBufferData(GL_ARRAY_BUFFER, data.verticesNum * 3 * sizeof(GLfloat), data.vertices, GL_STATIC_DRAW);


    // glDrawArrays(GL_TRIANGLES, 0, data.verticesNum * 3);
    delete [] data.vertices; 
};

void render_node(aiNode* node)
{
    for(unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        unsigned int meshID = node->mMeshes[i];
        render_mesh(meshID);
    }

    if(node->mNumChildren > 0)
    {
        for(unsigned int i = 0; i < node->mNumChildren; i++)
        {
            render_node(node->mChildren[i]);
        };
    }
};

void render_model()
{
    aiNode* rootNode = scene->mRootNode;

    if(rootNode->mNumChildren < 1)
        return;

    for(unsigned int i = 0; i < rootNode->mNumChildren; i++)
    {
        aiNode* child = rootNode->mChildren[i];
        
        render_node(child);

    };
}

void load_model(const char* path, Data* data)
{
    Assimp::Importer importer;

    scene = importer.ReadFile(path, 
        aiProcess_CalcTangentSpace |
        aiProcess_Triangulate |
        aiProcess_JoinIdenticalVertices |
        aiProcess_SortByPType
    ); 

    if (scene == nullptr) {
        std::cerr << importer.GetErrorString();
        exit(-1);
    };
    return scene;

}

 