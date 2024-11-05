#ifndef MESH_H
#define MESH_H

#include <glad/glad.h> 

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <shader.h>

#include <string>
#include <vector>

using namespace std;

struct Vertex {
    // position
    glm::vec3 Position;
    // normal
    glm::vec3 Normal;
    // texCoords
    glm::vec2 TexCoords;
};

struct Texture {
    unsigned int id;
    string type;
    string path;
};

class Mesh {
public:
    // mesh Data
    vector<Vertex>       vertices;
    vector<unsigned int> indices;
    vector<Texture>      textures;

    // constructor
    Mesh(vector<Vertex> _vertices, vector<unsigned int> _indices, vector<Texture> _textures)
    {
        this->vertices = _vertices;
        this->indices = _indices;
        this->textures = _textures;

        // now that we have all the required data, set the vertex buffers and its attribute pointers.
        setupMesh();
    }

    // render the mesh
    void Draw(Shader &shader)
        {
            unsigned int diffuseNum = 1;
            unsigned int specularNum = 1;

            // bind appropriate textures and set their sampler number for the shader
            for (int i = 0; i < textures.size(); i++)
            {
                glActiveTexture(GL_TEXTURE0 + i);
                GLenum error = glGetError();
                if (error != GL_NO_ERROR)
                {
                    cout << "Error activating texture unit " << i << ": " << error << endl;
                    continue;
                }

                string number;
                string name = textures[i].type;

                if (name == "texture_diffuse")
                    number = to_string(diffuseNum++);
                else if (name == "texture_specular")
                    number = to_string(specularNum++);

                // set the sampler to the correct texture unit
                shader.setInt("material." + name + number, i);

                // bind the texture
                glBindTexture(GL_TEXTURE_2D, textures[i].id);
                error = glGetError();
                if (error != GL_NO_ERROR)
                {
                    cout << "Error binding texture " << name << " to unit " << i << ": " << error << endl;
                    continue;
                }
            }

            // draw mesh
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

            // always good practice to set everything back to defaults once configured.
            glBindVertexArray(0);
            glActiveTexture(GL_TEXTURE0);
        }

private:
    // render data 
    unsigned int VAO, VBO, EBO;

    // initializes all the buffer objects/arrays
    void setupMesh()
    {
        // create buffers/arrays
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        // bind VAO, VBO and EBO
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

        // fill VBO with vertex data
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

        // fill EBO with indice data
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

        // set the vertex attribute pointers
        // vertex positions
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

        // vertex normals
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
        
        // vertex texture coordinates
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
        
        // unbind VAO to prevent accidental changes (not unbinding EBO because it is bound to VAO)
        glBindVertexArray(0);
    }
};
#endif