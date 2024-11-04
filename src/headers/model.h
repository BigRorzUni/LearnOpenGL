#include <glad/glad.h> 

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stb_image.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <mesh.h>
#include <shader.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

using namespace std;

class Model
{
    public:
        Model(const char *path)
        {
            cout << "Loading model from path: " << path << endl;
            loadModel(path);
        }

        void Draw(Shader &shader)
        {
            cout << "Drawing model with " << meshes.size() << " meshes." << endl;
            for(unsigned int i = 0; i < meshes.size(); i++)
            {
                cout << "Drawing mesh " << i << endl;
                meshes[i].Draw(shader);
            }
        }

    private:
        // model data
        vector<Mesh> meshes;
        string directory;
        vector<Texture> textures_loaded;

        void loadModel(string path)
        {
            cout << "Loading model: " << path << endl;
            Assimp::Importer importer;
            const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

            if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
            {
                cout << "ERROR::ASSIMP::" << importer.GetErrorString() << endl;
                return;
            }

            directory = path.substr(0, path.find_last_of('/'));

            //prints directory
            cout << "Directory: " << directory << endl;

            // begin processing through the scene graph
            processNode(scene->mRootNode, scene);

            cout << "Model loaded successfully." << endl;
        }

        void processNode(aiNode *node, const aiScene *scene)
        {
            cout << "Processing node with " << node->mNumMeshes << " meshes and " << node->mNumChildren << " children." << endl;
            // process all the node's meshes (if any)
            for(unsigned int i = 0; i < node->mNumMeshes; i++)
            {
                aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
                cout << "Processing mesh " << i << endl;
                meshes.push_back(processMesh(mesh, scene));
            }

            // then do the same for each of its children nodes
            for(unsigned int i = 0; i < node->mNumChildren; i++)
            {
                cout << "Processing child node " << i << endl;
                processNode(node->mChildren[i], scene);
            }
        }

        Mesh processMesh(aiMesh *mesh, const aiScene *scene)
        {
            cout << "Processing mesh with " << mesh->mNumVertices << " vertices and " << mesh->mNumFaces << " faces." << endl;
            vector<Vertex> vertices;
            vector<unsigned int> indices;
            vector<Texture> textures;

            // process vertices
            for(unsigned int i = 0; i < mesh->mNumVertices; i++)
            {
                Vertex vertex; 

                // vertex position
                glm::vec3 vector(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
                vertex.Position = vector;

                // vertex normal
                glm::vec3 normal(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
                vertex.Normal = normal;

                // vertex texture coordinates
                if(mesh->mTextureCoords[0]) // check if there are any
                {
                    glm::vec2 texCoord(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
                    vertex.TexCoords = texCoord;
                }
                else
                    vertex.TexCoords = glm::vec2(0.0f, 0.0f);

                vertices.push_back(vertex);
            }

            // process indices
            for(unsigned int i = 0; i < mesh->mNumFaces; i++)
            {
                aiFace face = mesh->mFaces[i];

                for(unsigned int j = 0; j < face.mNumIndices; j++)
                    indices.push_back(face.mIndices[j]);
            }

            // process textures/materials
            if(mesh->mMaterialIndex >= 0)
            {
                aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];

                vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
                textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

                vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
                textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
            }

            return Mesh(vertices, indices, textures);
        }

        unsigned int TextureFromFile(string path, string dir)
        {
            string fname = string(dir + '/' + path);
            cout << "Loading texture from file: " << fname << endl;

            unsigned int textureID;
            glGenTextures(1, &textureID);

            int width, height, nrComponents;
            unsigned char *data = stbi_load(fname.c_str(), &width, &height, &nrComponents, 0);
            if(data)
            {
                GLenum format;
                if(nrComponents == 1)
                    format = GL_RED;
                else if(nrComponents == 3)
                    format = GL_RGB;
                else if(nrComponents == 4)
                    format = GL_RGBA;

                glBindTexture(GL_TEXTURE_2D, textureID);
                glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(GL_TEXTURE_2D);

                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

                stbi_image_free(data);
            }
            else
            {
                cout << "Texture failed to load at path: " << path << endl;
                stbi_image_free(data);
            }

            return textureID;
        }

        vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName)
        {
            cout << "Loading material textures of type: " << typeName << endl;
            vector<Texture> textures;
            for(unsigned int i = 0; i < mat->GetTextureCount(type); i++)
            {
                aiString str;
                mat->GetTexture(type, i, &str);

                // check if texture has already been loaded
                bool skip = false;
                for(unsigned int j = 0; j < textures_loaded.size(); j++)
                {
                    if(std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
                    {
                        textures.push_back(textures_loaded[j]);
                        skip = true;
                        break;
                    }
                }

                if(skip)
                    continue;
                // if texture hasn't already been loaded then load it
                Texture texture;
                texture.id = TextureFromFile(str.C_Str(), directory);
                texture.type = typeName;
                texture.path = str.C_Str();
                textures.push_back(texture);
                textures_loaded.push_back(texture);
            }

            return textures;
        }

};