
#include <assimp/Importer.hpp>
#include <assimp/mesh.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <assimp/vector3.h>
#include <iostream>
#include <string>

#include <GL/glew.h>

#include "DataStructure.hpp"
#include "loader.hpp"

const aiScene* scene;

int bufferSize;
Data data;
Buffer buffer;
Buffer* buffers;


int count_indices(aiMesh* mesh)
{
    int count = 0;
    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        for(unsigned int j = 0; j < mesh->mFaces[i].mNumIndices; j++)
        {
            count++;
        }
    }
    return count;
};

void render_mesh( unsigned int meshID)
{
    aiMesh* mesh = scene->mMeshes[meshID]; 

    buffer.verticesNum = mesh->mNumFaces * 3;
    buffer.indicesNum = count_indices(mesh);

    data.verticesNum = mesh->mNumVertices;

    data.indices = new GLuint[buffer.indicesNum];
    data.vertices = new GLfloat[data.verticesNum * 3];
    data.normals = new GLfloat[data.verticesNum * 3];
        
    for(unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        aiVector3D vec3 = mesh->mVertices[i];
        aiVector3D norm3 = mesh->mNormals[i];

        data.vertices[i * 3] = vec3.x;    
        data.vertices[i * 3 + 1] = vec3.y;
        data.vertices[i * 3 + 2] = vec3.z;

        data.normals[i * 3] = norm3.x;
        data.normals[i * 3 + 1] = norm3.y;
        data.normals[i * 3 + 2] = norm3.z;
    };
    int count = 0;
    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        const aiFace& face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++ )
        {
            data.indices[count] = face.mIndices[j];
            count++;
        }
    }
 

    glGenBuffers(1, &buffer.verticesID);
    glBindBuffer(GL_ARRAY_BUFFER, buffer.verticesID);
    glBufferData(GL_ARRAY_BUFFER, data.verticesNum  * 3* sizeof(GLfloat), data.vertices, GL_STATIC_DRAW);
    
    glGenBuffers(1, &buffer.normalsID);
    glBindBuffer(GL_ARRAY_BUFFER, buffer.normalsID);
    glBufferData(GL_ARRAY_BUFFER, data.verticesNum  * 3 * sizeof(GLfloat), data.normals, GL_STATIC_DRAW);

    glGenBuffers(1, &buffer.indicesID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer.indicesID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, buffer.indicesNum * sizeof(GLuint), data.indices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, buffer.verticesID); // test
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, buffer.normalsID);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer.indicesID);

    buffers[bufferIndex] = std::move(buffer);
  
    delete [] data.vertices; 
    delete [] data.normals; 

};

/**
 * @brief Iterates and renders node's meshes 
 * 
 * Iterates over it's meshes indices and calls render_mesh(unsigned int) with the respective mesh index.
 * Increments a bufferIndex after each render_mesh(unsigned int) call for the next buffer to use.
 * Recursively calls itself for it's children
 * 
*/
void render_node(aiNode* node)
{
    std::cout << node->mName.C_Str() << '\n';
    for(unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        unsigned int meshID = node->mMeshes[i];
        render_mesh(meshID);
    }
    bufferIndex++;

    if(node->mNumChildren > 0)
    {
        for(unsigned int i = 0; i < node->mNumChildren; i++)
        {
            render_node(node->mChildren[i]);
        };
    }
};

/** 
 * @brief Calls render_node for rootNode children
 * 
 * Instantiates a static integer variable bufferIndex used to access 
 * a buffer in buffer array.
 * Instatiates a rootNode for scene's mRootNode to recurse over it's children.
 * If rootNode has no children - return.
 * Instatiates a bufferSize as a number of scene's number of meshes.
 * Instatiates a buffer with a size of number of meshes in the scene.
 *  
*/
void render_model()
{
    aiNode* rootNode = scene->mRootNode;

    bufferSize = scene->mNumMeshes;
    buffers = new Buffer[bufferSize];

    if(rootNode->mNumChildren < 1)
        return;

    for(unsigned int i = 0; i < rootNode->mNumChildren; i++)
    {
        aiNode* child = rootNode->mChildren[i];
        
        render_node(child);

    };
}

void load_model(const char* path)
{
    std::cout << "load model call\n";
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
    render_model();
    // return scene;

}

 