#define GLM_ENABLE_EXPERIMENTAL
// Libraries
#include <iostream>
#include "glm/mat4x3.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cstdlib> 
#include <stb/stb_image.h>
#include <chrono>


// Classes
#include "Resources/Shaders/shaderClass.h"
#include "Texture.h"
#include "Camera.h"
#include "Grid.h"
#include "Entity.h"
#include "Player.h"
#include "Component.h"
#include "ImGuiManager.h"
#include "Item.h"

// Can be removed if unused 
#include "Tick.h"
#include "memory" // for smart pointers

// Systems
#include "EntityManager.h"
#include "RenderingSystem.h"
#include "PhysicsSystem.h"
#include "CollisionSystem.h"
#include "InputSystem.h"
#include "Resources/Systems/CombatSystem.h"


#include <fstream>  // std::ifstream





// Some of the code for the spotlight is from the following repo
// https://github.com/VictorGordan/opengl-tutorials.git
// 

void framebuffer_size_callback(GLFWwindow* window, int width, int height);  // Dynamic window size
void processInput(GLFWwindow* window);
bool del = false;
bool spawnObj = false;
bool isEKeyPressed = false;
// Window dimensions
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

double scrollY = 0.0;  // Store scroll amount

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    // Get the InputSystem from user pointer
    InputSystem* inputSystem = static_cast<InputSystem*>(glfwGetWindowUserPointer(window));

    scrollY += yoffset;
   
    if (scrollY > 8.0) {
        scrollY = 1.0;
    }
    else if (scrollY < 0.0) {
        scrollY = 8.0;
    }
    inputSystem->SetMouseInput(scrollY);
}

int main()
{
    // glfw: initialize and configure
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Basic RPG Game", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    gladLoadGL();

    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

    std::shared_ptr<ImGuiManager> imgui = std::make_shared<ImGuiManager>(window);

    // Shader setup
    std::shared_ptr<Shader> shaderProgram = std::make_shared<Shader>("default.vert", "default.frag");
    shaderProgram->Activate();

    std::shared_ptr<Shader> lightShader = std::make_shared<Shader>("light.vert", "light.frag");
    lightShader->Activate();


    // Entities setup
    std::shared_ptr<EntityManager> manager = std::make_shared<EntityManager>();
   
    // Enemy Entity


    // Player Entity
    Player player;
    std::shared_ptr<InputSystem> inputSystem = std::make_shared<InputSystem>();
    glfwSetWindowUserPointer(window, &inputSystem);
    glfwSetScrollCallback(window, scroll_callback);

    // Terrain Entity
    Entity planeObject;
    planeObject.AddComponent<PositionComponent>(0.0f, 0.0f, 0.0f);
    planeObject.AddComponent<RenderComponent>(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), "sphere");

    Entity splinesurface;
    splinesurface.AddComponent<PositionComponent>(0.0f, 0.0f, 0.0f);
    splinesurface.AddComponent<RenderComponent>(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(10.0f, 1.0f, 10.0f), "bsplinesurface");

    Entity pointCloud;
    pointCloud.AddComponent<PositionComponent>(-607435.0f, -400.0f, -6750600.0f);
    pointCloud.AddComponent<RenderComponent>(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), "pointcloud");


    // Intializing Systems
    std::shared_ptr <RenderingSystem> renderSystem = std::make_shared<RenderingSystem>();
    std::shared_ptr <PhysicsSystem> physicsSystem = std::make_shared<PhysicsSystem>();
    std::shared_ptr <CollisionSystem> collisionSystem = std::make_shared<CollisionSystem>();

    //renderSystem->initalize(pointCloud);
    renderSystem->initalize(splinesurface);
    


  

    // Intializing entity vector
    std::vector<Entity*> myEntities;
    //myEntities.push_back(&player);
    //myEntities.push_back(&planeObject);
   

    //Add all components to storage for batch proccesing
    for (auto& entity : myEntities) {


        renderSystem->initalize(*entity);


    }
    
 
    std::vector<Texture> textures;

    char basePath[] = "Resources/Textures/";
    char filetype[] = ".png";

    for (int i = 1; i <= 15; ++i) {
        std::string tempPath = std::string(basePath) + std::to_string(i) + filetype;    // Use std::string to build the file path
        char filePath[31];
        strcpy_s(filePath, tempPath.c_str());                                           // Copy std::string into C-style string (char array)

        Texture tt(filePath, shaderProgram);                                            // Pass the C-style string to the constructor
        textures.push_back(tt);
    }

    // Camera FOV & starting position
    std::shared_ptr<Camera> camera = std::make_shared<Camera>(SCR_WIDTH, SCR_HEIGHT, glm::vec3(0.0f, 0.0f, 0.0f));

    // Initalizing textures
    Texture wood("Resources/Textures/wood.png", shaderProgram);
    Texture green("Resources/Textures/green.jpg", shaderProgram);
    Texture queball("Resources/Textures/queball.png", shaderProgram);

    // Light setup
    glm::vec4 lightColor = glm::vec4(1.0f, 0.9f, 1.0f, 1.0f);
    glm::vec3 lightPos = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::mat4 lightModel = glm::mat4(1.0f);
    glUniformMatrix4fv(glGetUniformLocation(lightShader->ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
    glUniform4f(glGetUniformLocation(lightShader->ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    glm::vec3 objectPos = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::mat4 objectModel = glm::mat4(1.0f);
    objectModel = glm::translate(objectModel, objectPos);

    glUniformMatrix4fv(glGetUniformLocation(shaderProgram->ID, "model"), 1, GL_FALSE, glm::value_ptr(objectModel));
    glUniform4f(glGetUniformLocation(shaderProgram->ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    glUniform3f(glGetUniformLocation(shaderProgram->ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
    

    glUniformMatrix4fv(glGetUniformLocation(shaderProgram->ID, "model"), 1, GL_FALSE, glm::value_ptr(objectModel));
    glUniform4f(glGetUniformLocation(shaderProgram->ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    glUniform3f(glGetUniformLocation(shaderProgram->ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);



    glfwSwapInterval(1);
    glEnable(GL_DEPTH_TEST);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    int timeSinceStart = 0;

    //For deltatime
    auto previousTime = std::chrono::high_resolution_clock::now();
    
 

    std::shared_ptr<Collision> collision = std::make_shared<Collision>();


    // ---------------------------------------------------------------------------------------------------------------------------
    //                                                        Main Loop
    // ---------------------------------------------------------------------------------------------------------------------------
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
       glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  // Wireframe mode

        auto currentTime = std::chrono::high_resolution_clock::now();

        // Calculate delta time (in seconds)
        std::chrono::duration<float> deltaTime = currentTime - previousTime;
        previousTime = currentTime;
        float dt = deltaTime.count();

        // Updates Tick
    
        // Setup camera settings and inputs
        camera->Inputs(window);
        glm::mat4 viewproj = camera->Matrix(45.0f, 0.1f, 1000.0f, shaderProgram, "camMatrix");
        //camera->Position = glm::vec3(player.GetComponent<PositionComponent>()->position.x, camera->Position.y, player.GetComponent<PositionComponent>()->position.z + 25);

      
        //poitcloud 
        glBindTexture(GL_TEXTURE_2D, green.texture);
		renderSystem->RenderPoints(pointCloud, shaderProgram, viewproj);

        glBindTexture(GL_TEXTURE_2D, green.texture);
        renderSystem->Render(splinesurface, shaderProgram, viewproj);
        for (int i = 0; i < myEntities.size(); ++i) {

            if (myEntities[i]->GetComponent<RenderComponent>()->shape == "terrain") {
                glBindTexture(GL_TEXTURE_2D, green.texture);

            }
            else if(myEntities[i]->GetComponent<RenderComponent>()->shape == "sphere"){
                glBindTexture(GL_TEXTURE_2D, textures[1].texture);

            }
            else if (myEntities[i]->GetComponent<RenderComponent>()->shape == "cube") {
                glBindTexture(GL_TEXTURE_2D, textures[4].texture);
            }
           

            //Gives movement/physics to entities
            //physicsSystem->Update(*myEntities[i], dt);
            //Calculates the collisions
            //collisionSystem->BarycentricCoordinates(*myEntities[i], planeObject, physicsSystem);
            //Renders the entities
            renderSystem->Render(*myEntities[i], shaderProgram, viewproj);
            
            
            
         
        }
       

        //Deletes the entities
        manager->DeleteEntities(myEntities);
        //UI display
        //imgui->BasicText("Inventory", player);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    imgui->shutdown();
    // Clearing GLFW resources
    glfwTerminate();
    return 0;
}

// Process all input
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
        del = true;
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
       //Use to spawn objects into scene
        if (!isEKeyPressed) {
            spawnObj = true;
        }
        isEKeyPressed = true;
    }
    else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_RELEASE) {   
        isEKeyPressed = false;
    }

}

// Dynamic window size
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
