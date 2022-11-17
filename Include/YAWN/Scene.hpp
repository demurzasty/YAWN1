#pragma once 

#include "Node.hpp"

namespace YAWN {
    class Scene : public NonInstantiable {
    public:
        static void Initialize();

        static void Release();

        static void Update(float32 timeStep);

        static void FixedUpdate(float32 timeStep);

        static void LateUpdate(float32 timeStep);

        static Node* Root();

    private:
        static void Update(Node* node, float32 timeStep);

        static void FixedUpdate(Node* node, float32 timeStep);

        static void LateUpdate(Node* node, float32 timeStep);

    private:
        static Node* _root;
    };
}