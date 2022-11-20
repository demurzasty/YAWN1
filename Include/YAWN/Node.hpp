#pragma once 

#include "Managed.hpp"
#include "Array.hpp"
#include "ArrayView.hpp"
#include "String.hpp"

namespace YAWN {
    class Node : public Reference {
    public:
        virtual ~Node() = default;

        virtual void Update(float timeStep);

        virtual void FixedUpdate(float timeStep);

        virtual void LateUpdate(float timeStep);

        void SetName(const String& name);

        const String& Name() const;

        void AddChild(Node* node);

        Node* Parent() const;

        ArrayView<const Managed<Node>> Children() const;

        int32 Index() const;
        
        int32 GlobalIndex() const;

    private:
        String _name;
        Node* _parent = nullptr;
        Array<Managed<Node>> _children;
    };
}
