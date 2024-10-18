#include "Draw.h"
#include "Resources/Shaders/shaderClass.h"
#include "glm/gtc/type_ptr.hpp"
#include <cmath>
#include <iostream>
#include <glm/glm.hpp>
#include "Resources/Shaders/shaderClass.h"
#include "Grid.h"
#include "Component.h"
#include <random> // For random seeds

Draw::Draw() : rotation(glm::quat(0.0, 0.0, 0.0, 0.0))
{
}

void Draw::DrawCube(glm::vec3 Color, glm::vec3 pos, glm::vec3 size)
{

    position = pos;
    objSize = size;

    vertices.resize(8);
    glm::vec3 sizeXYZ = glm::vec3(1.f, 1.f, 1.f);

    // Front face vertices
    Vertex v0{ -sizeXYZ.x, -sizeXYZ.y,  sizeXYZ.z , Color.x, Color.y, Color.z, 0.0f, 1.0f };
    Vertex v1{ sizeXYZ.x, -sizeXYZ.y,  sizeXYZ.z , Color.x, Color.y, Color.z, 1.0f, 1.0f };
    Vertex v2{ sizeXYZ.x,  sizeXYZ.y,  sizeXYZ.z , Color.x, Color.y, Color.z, 1.0f, 0.0f };
    Vertex v3{ -sizeXYZ.x,  sizeXYZ.y,  sizeXYZ.z , Color.x, Color.y, Color.z, 0.0f, 0.0f };

    Vertex v4{ -sizeXYZ.x, -sizeXYZ.y, -sizeXYZ.z , Color.x, Color.y, Color.z, 0.0f, 1.0f };
    Vertex v5{ sizeXYZ.x, -sizeXYZ.y, -sizeXYZ.z , Color.x, Color.y, Color.z, 1.0f, 1.0f };
    Vertex v6{ sizeXYZ.x,  sizeXYZ.y, -sizeXYZ.z , Color.x, Color.y, Color.z, 1.0f, 0.0f };
    Vertex v7{ -sizeXYZ.x,  sizeXYZ.y, -sizeXYZ.z , Color.x, Color.y, Color.z, 0.0f, 0.0f };


    vertices = {
   v0, // Front bottom left
   v1, // Front bottom right
   v2, // Front top right
   v3, // Front top left
   v4, // Back bottom left
   v5, // Back bottom right
   v6, // Back top right
   v7  // Back top left
    };



    // Indices
    indices = {
        // Front face
        0, 1, 2, 2, 3, 0,
        // Back face
        4, 5, 6, 6, 7, 4,
        // Left face
        4, 0, 3, 3, 7, 4,
        // Right face
        1, 5, 6, 6, 2, 1,
        // Top face
        3, 2, 6, 6, 7, 3,
        // Bottom face
        4, 5, 1, 1, 0, 4
    };

    this->Initalize();
}

void Draw::DrawPlane(glm::vec3 Color, glm::vec3 pos, glm::vec3 size)
{

    position = pos;
    objSize = size;

    vertices.resize(4);
    glm::vec3 sizeXYZ = glm::vec3(1.f, 1.f, 1.f);

    // face vertices
    //Vertex v1{ sizeXYZ.x,  -sizeXYZ.y,  sizeXYZ.z , Color.x, Color.y, Color.z, 1.0f, 0.0f };
    //Vertex v2{ -sizeXYZ.x,  -sizeXYZ.y,  sizeXYZ.z , Color.x, Color.y, Color.z, 0.0f, 0.0f };
    //Vertex v3{ sizeXYZ.x,  -sizeXYZ.y, -sizeXYZ.z , Color.x, Color.y, Color.z, 1.0f, 1.0f };
    //Vertex v0{ -sizeXYZ.x,  -sizeXYZ.y, -sizeXYZ.z , Color.x, Color.y, Color.z, 0.0f, 1.0f };

    Vertex v1{ sizeXYZ.x,  -sizeXYZ.y,  sizeXYZ.z , Color.x, Color.y, Color.z, 1.0f, 0.0f };
    Vertex v2{ -sizeXYZ.x,  sizeXYZ.y,  sizeXYZ.z , Color.x, Color.y, Color.z, 0.0f, 0.0f };
    Vertex v3{ sizeXYZ.x,  sizeXYZ.y, -sizeXYZ.z , Color.x, Color.y, Color.z, 1.0f, 1.0f };
    Vertex v0{ -sizeXYZ.x,  -sizeXYZ.y, -sizeXYZ.z , Color.x, Color.y, Color.z, 0.0f, 1.0f };


    vertices = {
   v1, // Front top right
   v2, // Front top left
   v3, // Back top right
   v0  // Back top left
    };



    // Indices
    indices = {
    0,1,2,1,2,3
    };
    // Calculating the normal
    glm::vec3 A = glm::vec3(v1.x, v1.y, v1.z);
    glm::vec3 B = glm::vec3(v2.x, v2.y, v2.z);
    glm::vec3 C = glm::vec3(v0.x, v0.y, v0.z);

    // Creating vectors AB and AC
    glm::vec3 AB = B - A;
    glm::vec3 AC = C - A;

    // Calculating the normal using the cross product
    glm::vec3 normal = glm::normalize(glm::cross(AB, AC));
    normalvector = normal;
    this->Initalize();
}

void Draw::DrawBoundingBox(glm::vec3 Color, glm::vec3 pos, glm::vec3 size)
{
    position = pos;
    objSize = size;

    vertices.resize(8);
    glm::vec3 sizeXYZ = glm::vec3(1.f, 1.f, 1.f);

    // Front face vertices
    Vertex v0{ -sizeXYZ.x, -sizeXYZ.y,  sizeXYZ.z , Color.x, Color.y, Color.z, 0.0f, 1.0f };
    Vertex v1{ sizeXYZ.x, -sizeXYZ.y,  sizeXYZ.z , Color.x, Color.y, Color.z, 1.0f, 1.0f };
    Vertex v2{ sizeXYZ.x,  sizeXYZ.y,  sizeXYZ.z , Color.x, Color.y, Color.z, 1.0f, 0.0f };
    Vertex v3{ -sizeXYZ.x,  sizeXYZ.y,  sizeXYZ.z , Color.x, Color.y, Color.z, 0.0f, 0.0f };

    Vertex v4{ -sizeXYZ.x, -sizeXYZ.y, -sizeXYZ.z , Color.x, Color.y, Color.z, 0.0f, 1.0f };
    Vertex v5{ sizeXYZ.x, -sizeXYZ.y, -sizeXYZ.z , Color.x, Color.y, Color.z, 1.0f, 1.0f };
    Vertex v6{ sizeXYZ.x,  sizeXYZ.y, -sizeXYZ.z , Color.x, Color.y, Color.z, 1.0f, 0.0f };
    Vertex v7{ -sizeXYZ.x,  sizeXYZ.y, -sizeXYZ.z , Color.x, Color.y, Color.z, 0.0f, 0.0f };


    vertices = {
   v0, // Front bottom left
   v1, // Front bottom right
   v2, // Front top right
   v3, // Front top left
   v4, // Back bottom left
   v5, // Back bottom right
   v6, // Back top right
   v7  // Back top left
    };



    // Indices
    indices = {
        // Front face
        0, 1, 2, 2, 3, 0,
        // Back face
        4, 5, 6, 6, 7, 4,
        // Left face
        4, 0, 3, 3, 7, 4,
        // Right face
        1, 5, 6, 6, 2, 1
    };

    this->Initalize();
}

void Draw::DrawSphere(glm::vec3 Color, glm::vec3 pos, glm::vec3 size)
{
    // Part of the source code is from this website
    // https://stackoverflow.com/questions/45482988/generating-spheres-vertices-indices-and-normals


    position = pos;
    objSize = size;
    int radius = 1.0f;
    int circumferenceTile = 18;
    int layerTile = 18;
    int slices = (int)(circumferenceTile + 0.5f);
    if (slices < 4) {
        slices = 4;
    }

    int half_slices = slices / 2;
    int layerCount = (int)(layerTile + 0.5f);
    if (layerCount < 2)
    {
        layerCount = 2;
    }
    float pi = 3.1415f;
    for (int layerIndex = 0; layerIndex <= layerCount; layerIndex++)
    {
        float v = (1.0 - (float)layerIndex / layerCount);
        float heightOffset = std::sin((1.0 - 2.0 * layerIndex / layerCount) * pi / 2.0);
        float cosUp = sqrt(1.0 - heightOffset * heightOffset);
        float z = heightOffset;
        for (int i = 0; i <= half_slices; i++)
        {
            float u = (float)i / (float)half_slices;
            float angle = 2 * pi * u; // pi * 2 to get full sphere
            float x = std::cos(angle) * cosUp;
            float y = std::sin(angle) * cosUp;
            Vertex V1 = Vertex{ x * radius, y * radius, z * radius, x, y, z, u, v };
            vertices.push_back(V1);
        }

    }
    for (int layer = 0; layer < layerCount; layer++)
    {
        for (int i = 0; i < half_slices; i++)
        {
            // Index for the current layer and the next layer
            int currentRow = layer * (half_slices + 1) * 2;
            int nextRow = (layer + 1) * (half_slices + 1) * 2;

            // Creating two triangles (quad) between each pair of vertices in adjacent layers
            indices.push_back(currentRow + i);        // 1st triangle: curRow, nextRow, nextRow+1
            indices.push_back(nextRow + i);
            indices.push_back(nextRow + i + 1);

            indices.push_back(currentRow + i);        // 2nd triangle: curRow, nextRow+1, curRow+1
            indices.push_back(nextRow + i + 1);
            indices.push_back(currentRow + i + 1);
        }
    }

    this->Initalize();
}

void Draw::DrawTerrain(glm::vec3 Color, glm::vec3 pos, glm::vec3 size)
{
    position = pos;
    objSize = size;
    float waveAmplitude = 10.0f; // Adjust for more extreme or subtle "bumps"
    float waveFrequency = 1.0f;
    float terrainScale = 1.0f;
    int terrainDepth = 10;
    int terrainWidth = 10;

    // Generating vertices
    for (int z = 0; z <= terrainDepth; ++z) {
        for (int x = 0; x <= terrainWidth; ++x) {
            // Calculating vertex positions
            double xPos = static_cast<float>(x) * terrainScale;  // Scale based on x index
            double zPos = static_cast<float>(z) * terrainScale;  // Scale based on z index
            double yPos = sin(xPos * waveFrequency) * waveAmplitude + cos(zPos * waveFrequency) * waveAmplitude; // Height variation

            // Texture coordinates
            float u = static_cast<float>(x) / terrainWidth;
            float v = static_cast<float>(z) / terrainDepth;

            // Creating the vertex
            Vertex vertex;
            vertex.x = xPos - size.x / 2;
            vertex.y = yPos;
            vertex.z = zPos - size.z / 2;
            vertex.u = u;
            vertex.v = v;

            // Normal (placeholder for now)
            vertex.normalx = 0.0f;
            vertex.normaly = 1.0f;
            vertex.normalz = 0.0f;

            vertices.push_back(vertex);
        }
    }

    // Generating indices
    for (int z = 0; z < terrainDepth; ++z) {
        for (int x = 0; x < terrainWidth; ++x) {
            // Calculating indices
            int topLeftIndex = z * (terrainWidth + 1) + x;
            int topRightIndex = topLeftIndex + 1;
            int bottomLeftIndex = (z + 1) * (terrainWidth + 1) + x;
            int bottomRightIndex = bottomLeftIndex + 1;

            // First triangle (top-left, top-right, bottom-left)
            indices.push_back(topLeftIndex);
            indices.push_back(topRightIndex);
            indices.push_back(bottomLeftIndex);

            // Second triangle (top-right, bottom-right, bottom-left)
            indices.push_back(topRightIndex);
            indices.push_back(bottomRightIndex);
            indices.push_back(bottomLeftIndex);
        }
    }
    this->Initalize();
}



void Draw::Initalize()
{
    VAO.Bind(); // Binding the VAO
    VBO.Bind(); // Binding the VBO and upload vertex data

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    // Setting vertex attributes pointers
    VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, x)); // Position
    VAO.LinkAttrib(VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, r)); // Color
    VAO.LinkAttrib(VBO, 2, 2, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, u)); // TexCoords

    // Binding the EBO and upload index data
    EBO1.Bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    // Unbinding VAO, VBO, EBO
    VAO.Unbind();
    VBO.Unbind();
    EBO1.Unbind();
}

void Draw::Render(const std::shared_ptr<Shader>& Shader, glm::mat4 viewproj, PositionComponent& pos)
{
    glm::mat4 model2 = glm::mat4(1.0f);

    //glm::quat quaterninon = glm::quat(0.0, 0.0, 0.0, 0.0);
    //glm::mat4 rotationMatrix = glm::mat4_cast(quaterninon);
    rotation = glm::mat4_cast(Quaternion);
    model2 = glm::translate(model2, pos.position);
    model2 = glm::scale(model2, objSize);
    model2 *= rotation;
    glUniformMatrix4fv(glGetUniformLocation(Shader->ID, "camMatrix"), 1, GL_FALSE, glm::value_ptr(viewproj * model2));
    VAO.Bind();
    VBO.Bind();
    EBO1.Bind();

    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    // glDrawArrays(GL_POINT, 0, vertices.size());
     //unbind
    VAO.Unbind();
    VBO.Unbind();
    EBO1.Unbind();


}



glm::vec3 Draw::GetPosition()
{
    return position;
}

glm::vec3 Draw::GetSize()
{
    return objSize;
}

void Draw::SetPosition(glm::vec3 newPos)
{
    position = newPos;
}

float Draw::GetMass()
{
    return mass;
}

void Draw::SetMass(float newMass)
{
    mass = newMass;
}

void Draw::SetVelocity(glm::vec3 newVelocity)
{
    velocity = newVelocity;
}

glm::vec3 Draw::GetVelocity()
{
    return velocity;
}

void Draw::ApplyForce(glm::vec3 force)
{
    Acceleration += force / mass;
}

void Draw::Update(float deltaTime, Grid* grid)
{
    velocity += Acceleration * deltaTime;
    position += velocity * deltaTime;
    Acceleration = glm::vec3(0.0f, gravity, 0.0f);
}

void Draw::MoveXdir()
{
   // position.x += speed;
}




void Draw::Delete()
{
    VAO.Delete();
    VBO.Delete();
    EBO1.Delete();
}

void Draw::SetNormalVector(glm::vec3 normal)
{
    normalvector = normal;
}

void Draw::SetAngularVelocity(glm::vec3 angularVelocity)
{
    AngularVelocity = angularVelocity;
}

glm::vec3 Draw::GetAngularVelocity()
{
    return AngularVelocity;
}

void Draw::RotateCube(float deltaTime)
{
    glm::vec3 velocityDirection;
    if (AngularVelocity.x != 0 || AngularVelocity.z != 0) {
        glm::vec3 velocityDirection = glm::normalize(AngularVelocity);
        // std::cout << "V Dir " << velocityDirection.x << ", " << velocityDirection.z << std::endl;
    }

    float speed = glm::length(AngularVelocity);

    glm::quat AngularRotation = glm::angleAxis(glm::radians(1.0f), glm::vec3(-AngularVelocity.z, 0.0f, -AngularVelocity.x));
    Quaternion = Quaternion * AngularRotation * deltaTime;  // Updating rotation (quaternion math)
    Quaternion = glm::normalize(Quaternion);

    glm::mat4 newRotationMatrix = glm::mat4_cast(Quaternion);
    rotation = newRotationMatrix;
    //position += AngularVelocity * deltaTime;
}

glm::vec3 Draw::GetNormal()
{
    return normalvector;
}

void Draw::CalculateGravity(float inclineAngle, glm::vec3 slopeVector, glm::vec3 normal) {
    float gravity = 9.81f;
    
    
    // Downward gravity force
    glm::vec3 gravityForce(0.0f, -gravity, 0.0f);

    // Calculating normal force (perpendicular to the slope)
    float normalForceMagnitude = glm::dot(gravityForce, normal); // Gravity along the normal
    glm::vec3 normalForce = normal * normalForceMagnitude;

    // Calculating gravitational force acting parallel to the slope (slope vector)
    glm::vec3 gravityParallel = gravityForce - normalForce; // Parallel force along the slope

    // Projecting this parallel gravity onto the slope's horizontal direction (slopeVector)
    glm::vec3 gravityAlongSlope = glm::dot(gravityParallel, slopeVector) * slopeVector;

    // Applying the force along the slope
    ApplyForce(gravityAlongSlope);
}

void Draw::FollowPlayer(Draw& ball, float speed)
{
    glm::vec3 direction = (ball.GetPosition() - GetPosition());

    // Computing the distance between the balls
    float distance = glm::length(direction);

    // Normalizing the direction vector (prevent zero-length vector)
    if (distance > 0.0001f) {
        glm::vec3 dirvec = glm::normalize(direction);

        // Applying force to move the follower ball towards the player ball
        // With speed controls for how fast the follower moves
        glm::vec3 force = dirvec * speed;

        ApplyForce(force); // Applying the calculated force to move the follower
    }
}

void Draw::UpdateTick(float deltatime)
{
    
}

