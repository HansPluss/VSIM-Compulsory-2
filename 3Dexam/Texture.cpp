#include "Texture.h"
#include <iostream>
#include <GLFW/glfw3.h>
//texture class is from the following github repo
//https://github.com/tordelias/Compulsory-3.git




Texture::Texture(const char* texture1, const std::shared_ptr<Shader>& shaderProgram)
{
    ID = 1;

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // Setting the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Flipping the texture vertically on load
    stbi_set_flip_vertically_on_load(true);

    // Loading and generating the texture
    int nwidth, nheight, nrChannels;
    unsigned char* data = stbi_load(texture1, &nwidth, &nheight, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, nwidth, nheight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    shaderProgram->Activate();
    // shaderProgram.setInt("tex0", num);
}



