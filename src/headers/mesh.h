#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <shader.h>

using namespace std;

struct Vertex
{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

struct Texture
{
    unsigned int id;
    string type;
    string path;
};

class Mesh 
{
    public:
        vector<Vertex> vertices;
        vector<unsigned int> indices;
        vector<Texture> textures;

        Mesh(vector<Vertex> _vertices, vector<unsigned int> _indices, vector<Texture> _textures)
        {
            cout << "Initializing Mesh" << endl;
            this->vertices = _vertices;
            this->indices = _indices;
            this->textures = _textures;

            setupMesh();
        }

        void Draw(Shader &shader)
        {
            unsigned int diffuseNum = 1;
            unsigned int specularNum = 1;

            // bind appropriate textures and set their sampler number for the shader
            for (int i = 0; i < textures.size(); i++)
            {
                cout << "Processing texture " << i << endl;

                GLint activeTexture;
                glGetIntegerv(GL_ACTIVE_TEXTURE, &activeTexture);
                activeTexture -= GL_TEXTURE0;
                std::cout << "Currently active texture unit: " << activeTexture << std::endl;

                GLenum error;
                if(activeTexture != 0 || i != 0)
                {
                    cout << "Activating texture unit " << i << endl;
                    glActiveTexture(GL_TEXTURE0 + i);
                    error = glGetError();
                    if (error != GL_NO_ERROR)
                    {
                        cout << "Error activating texture unit " << i << ": " << error << endl;
                        continue;
                    }
                }

                string number;
                string name = textures[i].type;

                if (name == "texture_diffuse")
                    number = to_string(diffuseNum++);
                else if (name == "texture_specular")
                    number = to_string(specularNum++);

                // set the sampler to the correct texture unit
                glUniform1i(glGetUniformLocation(shader.ID, (name + number).c_str()), i);

                // bind the texture
                glBindTexture(GL_TEXTURE_2D, textures[i].id);
                error = glGetError();
                if (error != GL_NO_ERROR)
                {
                    cout << "Error binding texture " << name << " to unit " << i << ": " << error << endl;
                    continue;
                }

                cout << "Bound texture " << name << " to unit " << i << endl;
            }

            glActiveTexture(GL_TEXTURE0);

            // draw mesh
            glBindVertexArray(VAO);
            cout << "Drawing elements with " << indices.size() << " indices" << endl;
            glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);
        }

    private:
        // render data
        unsigned int VAO, VBO, EBO;

        void setupMesh()
        {
            cout << "Setting up Mesh" << endl;
            // generate VAO, VBO and EBO
            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBO);
            glGenBuffers(1, &EBO);

            // bind VBO and fill with data
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

            // bind EBO and fill with data
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
            
            // set VAO attributes
            glBindVertexArray(VAO);

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

            cout << "Mesh setup complete" << endl;
        }
};