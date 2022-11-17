#include <YAWN/Scene.hpp>

using namespace YAWN;

Node* Scene::_root = nullptr;

void Scene::Initialize() {
    _root = new Node();
}

void Scene::Release() {
    delete _root;
}

void Scene::Update(float32 timeStep) {
    Update(Root(), timeStep);
}

void Scene::FixedUpdate(float32 timeStep) {
    FixedUpdate(Root(), timeStep);
}

void Scene::LateUpdate(float32 timeStep) {
    LateUpdate(Root(), timeStep);
}

Node* Scene::Root() {
    return _root;
}

void Scene::Update(Node* node, float32 timeStep) {
    node->Update(timeStep);

    for (const Managed<Node>& node : node->Children()) {
        Update(node, timeStep);
    }
}

void Scene::FixedUpdate(Node* node, float32 timeStep) {
    node->FixedUpdate(timeStep);

    for (const Managed<Node>& node : node->Children()) {
        FixedUpdate(node, timeStep);
    }
}

void Scene::LateUpdate(Node* node, float32 timeStep) {
    node->LateUpdate(timeStep);

    for (const Managed<Node>& node : node->Children()) {
        LateUpdate(node, timeStep);
    }
}