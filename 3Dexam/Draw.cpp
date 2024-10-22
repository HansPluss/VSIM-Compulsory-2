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

void Draw::DrawBSplineSurface(glm::vec3 Color, glm::vec3 pos, glm::vec3 size)
{
    // Set the object's position and size
    position = pos;
    objSize = size;

    // Initialize B-Spline parameters
    n_u = 4; // Number of control points in u direction
    n_v = 3; // Number of control points in v direction
    d_u = 2; // Degree in u direction
    d_v = 2; // Degree in v direction

    // Initialize knot vectors
    mu.clear();
    mu.push_back(0); mu.push_back(0); mu.push_back(0);
    mu.push_back(1);
    mu.push_back(2); mu.push_back(2); mu.push_back(2);

    mv.clear();
    mv.push_back(0); mv.push_back(0); mv.push_back(0);
    mv.push_back(1); mv.push_back(1); mv.push_back(1);

    // Initialize control points with enough points (Y and Z switched)
    mc.clear(); // Clear previous control points if necessary

    // Control points after switching Y and Z values
    mc.push_back(glm::vec3(0, 0, 0));  // (x, z, y) -> (x, y, z)
    mc.push_back(glm::vec3(1, 0, 0));
    mc.push_back(glm::vec3(2, 0, 0));
    mc.push_back(glm::vec3(3, 0, 0));

    mc.push_back(glm::vec3(0, 0, 1));  // Previously (0, 1, 0), now (0, 0, 1)
    mc.push_back(glm::vec3(1, 1, 1));  // Previously (1, 1, 1), remains same
    mc.push_back(glm::vec3(2, 1, 1));
    mc.push_back(glm::vec3(3, 0, 1));  // Previously (3, 1, 0), now (3, 0, 1)

    mc.push_back(glm::vec3(0, 0, 2));  // Previously (0, 2, 0), now (0, 0, 2)
    mc.push_back(glm::vec3(1, 1, 2));  // Previously (1, 2, 1), now (1, 1, 2)
    mc.push_back(glm::vec3(2, 1, 2));
    mc.push_back(glm::vec3(3, 0, 2));  // Previously (3, 2, 0), now (3, 0, 2)


    // Check if we have enough control points
    if (mc.size() < n_u * n_v) {
        std::cerr << "Error: Not enough control points initialized." << std::endl;
        return; // Early exit if there aren't enough control points
    }

    // Map the flat control point array mc to the 2D grid c without resizing
    for (int i = 0; i < n_u; ++i) {
        for (int j = 0; j < n_v; ++j) {
            c[i][j] = mc[j * n_u + i];  // Map mc to the static 2D grid c[i][j]
        }
    }

    // Call the function to make the Biquadratic surface
    MakeBiquadraticSurface();

    // Initialize any necessary OpenGL state
    this->Initalize();
}



void Draw::DrawPoints(glm::vec3 Color, glm::vec3 pos, glm::vec3 size)
{
	position = pos;
	objSize = size;
    const char* file = "32-2-516-156-31.txt";
	std::vector<glm::vec3> pointCloud = Readfile(file);
    for (const auto& point : pointCloud) {
        Vertex vertex;

        vertex.x = point.x;
        vertex.y = point.y;
        vertex.z = point.z;

        // Set UV coordinates based on some logic if needed
        vertex.u = point.x; // Set these based on your requirements
        vertex.v = point.y;

        // Set colors, normals, etc. if available in LAZ
        vertex.r = 1.0f; // Default or set based on your requirements
        vertex.g = 1.0f;
        vertex.b = 1.0f;
        
        vertices.push_back(vertex);
    }
    this->InitalizePoints();
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

void Draw::InitalizePoints()
{
    VAO.Bind(); // Binding the VAO
    VBO.Bind(); // Binding the VBO and upload vertex data

    // Upload vertex data to the GPU
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    // Setting vertex attributes pointers
    VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, x)); // Position
    VAO.LinkAttrib(VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, r)); // Color
    VAO.LinkAttrib(VBO, 2, 2, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, u)); // TexCoords

    // If using an EBO, you need to bind the EBO and upload index data
    if (!indices.empty()) // Check if you have index data
    {
        EBO1.Bind();
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
        EBO1.Unbind(); // Unbind EBO after uploading data
    }

    // Unbinding VAO and VBO after setup
    VAO.Unbind();
    VBO.Unbind();
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

void Draw::RenderPoints(const std::shared_ptr<Shader>& shader, glm::mat4 viewproj)
{
    glm::mat4 model2 = glm::mat4(1.0f);

    model2 = glm::translate(model2, position);
    model2 = glm::scale(model2, objSize);

    // Get the uniform location
    GLint camMatrixLocation = glGetUniformLocation(shader->ID, "camMatrix");
    if (camMatrixLocation != -1) {
        glUniformMatrix4fv(camMatrixLocation, 1, GL_FALSE, glm::value_ptr(viewproj * model2));
    }
    else {
        // Handle the error appropriately (e.g., log it)
        std::cerr << "Error: 'camMatrix' uniform not found in shader!" << std::endl;
    }

    VAO.Bind();
    VBO.Bind();

    // Adjust point size as needed
    glDrawArrays(GL_POINTS, 0, vertices.size()); // Use GL_POINTS instead of GL_POINT
   // glPointSize(1.0f);
    // Unbind
    VAO.Unbind();
    VBO.Unbind();
}


std::vector<glm::vec3> Draw::EvaluateBiquadratic(int my_u, int my_v, glm::vec3& bu,glm::vec3& bv)
{
    std::vector<glm::vec3> result;
    float w[3][3];
    glm::vec3 surfacePoint = glm::vec3(0.0f);
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            float weight = bu[i] * bv[j];
            glm::vec3 controlPoint = c[my_u - i][my_v - j];
            // Multiply the control point by the weight (scalar * vec3)
            surfacePoint += weight * controlPoint;
           /* std::cout << "Control Point [" << (my_u - i) << "][" << (my_v - j) << "]: ("
                << controlPoint.x << ", " << controlPoint.y << ", " << controlPoint.z << ")\n";*/
            
        }
    }
    result.push_back(surfacePoint);
    return result;
}
void Draw::MakeBiquadraticSurface()
{
    float h = 0.1f; // Spacing
    int nu = static_cast<int>((mu[n_u] - mu[d_u]) / h);  // Calculate the number of steps in u
    int nv = static_cast<int>((mv[n_v] - mv[d_v]) / h);  // Calculate the number of steps in v

    // Iterate through v and u to generate surface points
    for (int i = 0; i < nv; ++i)
    {
        for (int j = 0; j < nu; ++j)
        {
            float u = j * h;
            float v = i * h;

            // Find the corresponding knot intervals for u and v
            int my_u = FindKnotInterval(mu, d_u, n_u, u);
            int my_v = FindKnotInterval(mv, d_v, n_v, v);

            // Calculate the basis function coefficients for the current u and v
            auto koeff_par = B2(u, v, my_u, my_v);

            // Evaluate the biquadratic surface at the current u and v
            glm::vec3 surfacePoint = deBoorSurface(d_u, d_v, mu, mv, mc, u, v);

            Vertex vertex;

            // Assign the position values from the evaluated surface point
            vertex.x = surfacePoint.x;
            vertex.y = surfacePoint.y;
            vertex.z = surfacePoint.z;

            // Assign color and texture coordinates
            vertex.r = 1.0f;
            vertex.g = 1.0f;
            vertex.b = 1.0f;

            vertex.u = static_cast<float>(j) / (nu - 1); // Column index normalized
            vertex.v = static_cast<float>(i) / (nv - 1); // Row index normalized

            vertex.normalx = 0.0f;
            vertex.normaly = 1.0f;
            vertex.normalz = 0.0f;

            // Push the computed surface point into the vertices array
            vertices.push_back(vertex);
        }
    }

    // Generate indices for the triangle mesh
    for (int i = 0; i < nv - 1; ++i) {
        for (int j = 0; j < nu - 1; ++j) {
            int idx1 = i * nu + j;
            int idx2 = idx1 + 1;
            int idx3 = idx1 + nu;
            int idx4 = idx3 + 1;

            // First triangle (idx1, idx2, idx3)
            indices.push_back(idx1);
            indices.push_back(idx2);
            indices.push_back(idx3);

            // Second triangle (idx2, idx4, idx3)
            indices.push_back(idx2);
            indices.push_back(idx4);
            indices.push_back(idx3);
        }
    }
}

std::pair<glm::vec3, glm::vec3> Draw::B2(float tu, float tv, int my_u, int my_v)
{
    glm::vec3 Bu, Bv;

    // Assuming tu and tv are in the [0, 1] range for the basis functions:
    Bu.x = (1 - tu) * (1 - tu);
    Bu.y = 2 * tu * (1 - tu);
    Bu.z = tu * tu;

    Bv.x = (1 - tv) * (1 - tv);
    Bv.y = 2 * tv * (1 - tv);
    Bv.z = tv * tv;
    float sumBu = Bu.x + Bu.y + Bu.z;
    float sumBv = Bv.x + Bv.y + Bv.z;

    Bu /= sumBu;
    Bv /= sumBv;
   /* std::cout << "Bu: (" << Bu.x << ", " << Bu.y << ", " << Bu.z << ")\n";
    std::cout << "Bv: (" << Bv.x << ", " << Bv.y << ", " << Bv.z << ")\n";*/
    return std::make_pair(Bu, Bv);
}

int Draw::FindKnotInterval(const std::vector<float>& knots, int degree, int n, float t)
{
    for (int i = degree; i < n; ++i) {
        if (t >= knots[i] && t < knots[i + 1]) {
            return i;
        }
    }
    std::cout << "could not find knot" << std::endl;
    return -1;
}
glm::vec3 Draw::deBoorSurface(int du, int dv, const std::vector<float>& knotsU, const std::vector<float>& knotsV, std::vector<glm::vec3> controlPoints, float u, float v)
{
    // Step 1: Apply de Boor along the u-direction
    std::vector<glm::vec3> tempPoints;
    for (int i = 0; i < n_v; ++i) {
        // Extract the i-th row of control points (nu points per row)
        std::vector<glm::vec3> row;
        for (int j = 0; j < n_u; ++j) {
            row.push_back(controlPoints[i * n_u + j]);
        }

        // Apply de Boor along the u-direction for this row
        glm::vec3 t = deBoor(du, du, knotsU, row, u);
        tempPoints.push_back(t); // Store the result for v-direction interpolation
    }

    // Now apply de Boor along the v-direction on the result from the u-direction
    glm::vec3 f = deBoor(dv, dv, knotsV, tempPoints, v);
    return f; // Interpolate along v with the new points
}


glm::vec3 Draw::deBoor(int k, int degree, const std::vector<float>& knots, std::vector<glm::vec3> controlPoints, float t)
{
    // Find the knot span index
    int span = -1;
    for (int i = degree; i < knots.size() - 1; ++i) {
        if (t >= knots[i] && t < knots[i + 1]) {
            span = i;
            break;
        }
    }

    if (span == -1) {
        std::cout << "Could not find knot span" << std::endl;
        return glm::vec3(0.0f); // Return a default value if not found
    }

    // Initialize d as a copy of control points for the relevant knot span
    std::vector<glm::vec3> d(degree + 1);
    for (int i = 0; i <= degree; ++i) {
        d[i] = controlPoints[span - degree + i];
    }

    // Perform de Boor recursion
    for (int r = 1; r <= degree; ++r) {
        for (int j = degree; j >= r; --j) {
            float alpha = (t - knots[span - degree + j]) / (knots[span + 1 + j - r] - knots[span - degree + j]);
            d[j] = (1.0f - alpha) * d[j - 1] + alpha * d[j];
        }
    }

    // The evaluated point is now stored in d[degree]
    return d[degree];
}

std::vector<glm::vec3> Draw::ReadLazFile(const std::string& filePath)
{
    std::vector<glm::vec3> points;

   

    return points; // Return the vector of points
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

std::vector<glm::vec3> Draw::Readfile(const char* fileName)
{
    std::ifstream inputFile(fileName);
    std::vector<glm::vec3> pointCloud;
    if (inputFile.is_open()) {

        std::string line;
        std::getline(inputFile, line);
        Vertex vertex;
        char comma; // to capture the commas in the file
        glm::vec3 point;


        while (inputFile >> point.x >> comma >> point.z >> comma >> point.y) {

            pointCloud.push_back(point);
        }

        inputFile.close();
    }
    else {
        std::cerr << "Unable to open the input file for reading." << std::endl;
    }
    std::cout << "point Cloud " << pointCloud.size();
    return pointCloud;


}

