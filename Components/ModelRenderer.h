//
// Created by user on 2026-03-19.
//

#ifndef MODELRENDERER_H
#define MODELRENDERER_H
#include "Model.h"
#include "NodeComponent.h"

class Shader;
class CameraComponent;

class ModelRenderer : public NodeComponent{
    Model* model;
public:
    ModelRenderer(Model* model) : model(model) {}
    ~ModelRenderer() {
        if (model) delete model;
    }

    void render(Shader* shader, CameraComponent* camera) override;
    const std::string getType() override { return "ModelRenderer"; }

};



#endif //MODELRENDERER_H
