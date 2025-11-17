//
// Created by sw_306 on 2025-11-12.
//

#ifndef PROJECT_MESHCOMPONENT_H
#define PROJECT_MESHCOMPONENT_H
#include "NodeComponent.h"

class Shader;
class Material;
template<class VertexType>
class Mesh;

template<class VertexType>
class MeshComponent : public NodeComponent {
    Mesh<VertexType>* _mesh;
    Material* material;
public:
    MeshComponent(Mesh<VertexType>* _mesh, Material* material) : NodeComponent() {

        this->_mesh = _mesh;
        this->material = material;
    }
    ~MeshComponent()
    {
        delete _mesh;
    }

    void render(Shader* shader, CameraComponent* camera);
};


#endif //PROJECT_MESHCOMPONENT_H