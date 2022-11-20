#include <YAWN/Node.hpp>

using namespace YAWN;

void Node::Update(float timeStep) {
}

void Node::FixedUpdate(float timeStep) {
}

void Node::LateUpdate(float timeStep) {
}

void Node::SetName(const String& name) {
    _name = name;
}

const String& Node::Name() const {
    return _name;
}

void Node::AddChild(Node* node) {
    CheckReturn(!node->_parent, "Node is already attached to parent.");

    node->_parent = this;
    _children.PushBack(node);
}

Node* Node::Parent() const {
    return _parent;
}

ArrayView<const Managed<Node>> Node::Children() const {
    return _children;
}

int32 Node::Index() const {
    // TODO: Index should be cached for performance reason.

    if (!_parent) {
        return 0;
    }

    for (usize i = 0; i < _parent->_children.Size(); ++i) {
        if (_parent->_children[i] == this) {
            return int32(i);
        }
    }

    return 0;
}

int32 Node::GlobalIndex() const {
    if (_parent) {
        return Index() + _parent->GlobalIndex();
    }

    return Index();
}
