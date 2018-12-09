#include "Node.h"

Node::Node()
{
	_parent = nullptr;
	_left = nullptr;
	_right = nullptr;
	_key = 0;
	_value = "";
}


void Node::SetKey(int key)
{
	_key = key;
}

void Node::SetValue(std::string value)
{
	_value = value;
}

void Node::SetParent(Node* parent)
{
	_parent = parent;
}

void Node::SetLeft(Node* left)
{
	_left = left;
}

void Node::SetRight(Node* right)
{
	_right = right;
}

int Node::GetKey()
{
	return _key;
}

std::string Node::GetValue()
{
	return _value;
}

Node* Node::GetParent()
{
	return _parent;
}

Node* Node::GetLeft()
{
	return _left;
}

Node* Node::GetRight()
{
	return _right;
}

bool Node::IsExternal()
{
	return (_left == nullptr && _right == nullptr);
}

bool Node::IsInternal()
{
	return (!IsExternal());
}

bool Node::IsRoot()
{
	return (_parent == nullptr);
}

bool Node::operator<(Node* other)
{
	return (this->_key < other->GetKey());
}

bool Node::operator==(Node* other)
{
	return !((this) < other) && !(other < (this));
}

bool Node::operator>(Node* other)
{
	return !((this) < other) && !((this) == other);
}

bool Node::operator<=(Node* other)
{
	return ((this) < other) || ((this) == other);
}

bool Node::operator>=(Node* other)
{
	return ((this) > other) || ((this) == other);
}

bool Node::operator!=(Node* other)
{
	return !((this) == other);
}

int _key;
std::string value;
Node* parent;
Node* left;
Node* right;