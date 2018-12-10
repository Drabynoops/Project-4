#pragma once
#include <string>

class Node
{
public:
	Node();
	void SetKey(int key);
	void SetValue(std::string value);
	void SetParent(Node* parent);
	void SetLeftChild(Node* left);
	void SetRightChild(Node* right);
	int GetKey();
	std::string GetValue();
	Node* GetParent();
	Node* GetLeftChild();
	Node* GetRightChild();
	bool IsExternal();
	bool IsInternal();
	bool IsRoot();
	bool operator<(Node* other);
	bool operator==(Node* other);
	bool operator>(Node* other);
	bool operator<=(Node* other);
	bool operator>=(Node* other);
	bool operator!=(Node* other);
private:
	Node* _parent;
	Node* _left;
	Node* _right;
	int _key;
	std::string _value;
};