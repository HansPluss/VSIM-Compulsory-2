#pragma once
#include "Draw.h"
#include "Entity.h"
#include "Resources/Shaders/shaderClass.h"
#include "Grid.h"
class Shader;
class RenderingSystem {
public:
    Draw draw;

    void initalize(Entity& entity)
    {
        if (entity.isMarkedForDeletion) return;
        auto* renderComponent = entity.GetComponent<RenderComponent>();
        auto* positionComponent = entity.GetComponent<PositionComponent>();
        if (positionComponent && renderComponent) {
            if (renderComponent->shape == "cube") {
                renderComponent->Draw.DrawCube(renderComponent->color, positionComponent->position, renderComponent->size);
    
                
            }
            else if (renderComponent->shape == "plane") {
                renderComponent->Draw.DrawPlane(renderComponent->color, positionComponent->position, renderComponent->size);
            }
            else if (renderComponent->shape == "sphere") {
                renderComponent->Draw.DrawSphere(renderComponent->color, positionComponent->position, renderComponent->size);
            }
            else if (renderComponent->shape == "boundingbox") {
                renderComponent->Draw.DrawBoundingBox(renderComponent->color, positionComponent->position, renderComponent->size);
			}
            else if (renderComponent->shape == "terrain") {
                renderComponent->Draw.DrawTerrain(renderComponent->color, positionComponent->position, renderComponent->size);
            }
            else if (renderComponent->shape == "bsplinesurface") {
                renderComponent->Draw.DrawBSplineSurface(renderComponent->color, positionComponent->position, renderComponent->size);
            }
            else if (renderComponent->shape == "pointcloud") {
                renderComponent->Draw.DrawPoints(renderComponent->color, positionComponent->position, renderComponent->size);
            }
            else 
			{
				std::cout << "Shape not found" << std::endl;
			}


        }
       
        SetVertecies(entity);
    }

    void Render(Entity& entity, const std::shared_ptr<Shader>& shader, glm::mat4 viewproj) {
        // Checking if the entity has a RenderComponent
        if (entity.isMarkedForDeletion) return;
        auto* renderComponent = entity.GetComponent<RenderComponent>();
        auto* positionComponent = entity.GetComponent<PositionComponent>();
        if (positionComponent && renderComponent) {

            // Calling the general render function
            renderComponent->Draw.Render(shader, viewproj, *positionComponent);
            if (renderComponent->shape == "cube") {
               // std::cout << "Marked" << std::endl;

            }
        }
          
        
    }
    void RenderPoints(Entity& entity, const std::shared_ptr<Shader>& shader, glm::mat4 viewproj) {
        if (entity.isMarkedForDeletion) return;
        auto* renderComponent = entity.GetComponent<RenderComponent>();
        auto* positionComponent = entity.GetComponent<PositionComponent>();
        if (positionComponent && renderComponent) {

            // Calling the general render function
            renderComponent->Draw.RenderPoints(shader, viewproj);
           
        }

    }
    void Rotate(Entity& entity, float deltaTime) {
        if (entity.isMarkedForDeletion) return;
        auto* renderComponent = entity.GetComponent<RenderComponent>();
        if (renderComponent) {

            renderComponent->Draw.RotateCube(deltaTime);
        }

    }
    void SetVertecies(Entity& entity) {
        if (entity.isMarkedForDeletion) return;
        auto* renderComponent = entity.GetComponent<RenderComponent>();
        if (renderComponent) {
            renderComponent->vertices = renderComponent->Draw.GetVertices();
            //std::cout << renderComponent->vertices.size() << "size of vert" << std::endl;

        }
        
        

    }

};