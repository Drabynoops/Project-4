#include "BinarySearchTree.h"
#include <iostream>

/* Default constructor for BinarySearchTree
*
* Input: None
*
* Output: None
*
*/
BinarySearchTree::BinarySearchTree()
{
	_root = nullptr;
	_size = 0;
}

/* Set _size, the number of the nodes in the tree
*
* Input: int - number of nodes in the tree
*
* Output: None
*
*/
void BinarySearchTree::SetSize(int size)
{
	_size = size;
}

/* Set _root, the pointer to the root node of the tree
*
* Input: Node* - pointer to the node to be set as root
*
* Output: None
*
*/
void BinarySearchTree::SetRoot(Node* root)
{
	_root = root;
}

/* Return the number of nodes in the tree
*
* Input: None
*
* Output: int - number of nodes in the tree
*
*/
int BinarySearchTree::GetSize()
{
	return _size;
}

/* Return the pointer to the root node of the tree
*
* Input: None
*
* Output: Node* - the pointer to the root node of the tree
*
*/
Node* BinarySearchTree::GetRoot()
{
	return _root;
}

/* Return whether or not the binary tree is empty
*
* Input: None
*
* Output: bool - true if _size is 0, false otherwise
*
*/
bool BinarySearchTree::IsEmpty()
{
	return (_size == 0);
}

/* Search for a node in the tree based on it's key
*
* Input: keyToSearch - the key of the node to be searched for
*		 nodeToSearchAt - the starting point of the search (starts at root)
*
* Output: Node* - A node that matches the key given 
*			      If not found, an external node.
*
*/
Node* BinarySearchTree::Search(int keyToSearch, Node* nodeToSearchAt)
{
	// No node with the same key was found
	if (nodeToSearchAt->IsExternal())
	{
		return nodeToSearchAt;
	}
	// key is less than nodeToSearchAt
	// children that are smaller go to the left
	else if (keyToSearch < nodeToSearchAt->GetKey())
	{
		return Search(keyToSearch, nodeToSearchAt->GetLeft());
	}
	// key matches and node was found
	else if (keyToSearch == nodeToSearchAt->GetKey())
	{
		return nodeToSearchAt;
	}
	// Remainder condition - keyToSearch > nodeToSearchAt->GetKey()
	// children that are larger go to the right
	else
	{
		return Search(keyToSearch, nodeToSearchAt->GetRight());
	}
}

/* Insert a new node into the binary search tree
*
* Input: keyToInsert - key of the new node being inserted
*        valueToInsert - value of the new node being inserted
*        nodeToInsertAt - node to insert the new node at (starts at root node)
*
* Output: Node* - pointer to the new node
*
*/
Node* BinarySearchTree::Insert(int keyToInsert, std::string valueToInsert, Node* nodeToInsertAt)
{
	Node* newNode;
	// BinarySearchTree is empty and newNode will be the root
	if (IsEmpty()) 
	{
		Node* root = new Node;
		this->_root = root;
		newNode = root;
		InsertAtExternal(this->_root, keyToInsert, valueToInsert);
	}
	else {
		//search for appropriate node
		newNode = Search(keyToInsert, nodeToInsertAt);
		//if such node already exists in the tree
		if (newNode->IsInternal()) 
		{
			return Insert(keyToInsert, valueToInsert, newNode->GetLeft());
		}
		//insert the new node at an external node on the tree
		this->InsertAtExternal(newNode, keyToInsert, valueToInsert);
	}
	//return the new node
	this->_size++;
	return newNode;
}

/* Reblance tree after insert
*
* Input: newlyInsertedNode - node that was recently added to the BinarySearchTree
*
* Output: None
*
*/
void BinarySearchTree::Rebalance(Node* newlyInsertedNode)
{
	Node* nodeToCheck = newlyInsertedNode;
	// Make sure that nodeToBalance isn't root
	// Root's parent is nullptr, this is bad
	while (!nodeToCheck->IsRoot()) 
	{
		// Current node is assumed balanced as it starts with
		// a newly inserted node. So grab the parent instead.
		nodeToCheck= nodeToCheck->GetParent();
		// If node is not balanced, grabs the "tallest" grandchild
		if (!this->IsBalanced(nodeToCheck)) 
		{
			Node* grandchildOfUnbalanced = TallGrandchild(nodeToCheck);
			this->Restructure(grandchildOfUnbalanced);
		}
	}
}

/* Insert a node and immediately reblance the tree
*
* Input: keyToInsert - key of new node to be inserted
*        valueToInsert - value of new node to be inserted
*  
* Output: Node* - pointer to newly inserted node
*
*/
Node* BinarySearchTree::BalancedInsert(int keyToInsert, std::string valueToInsert)
{
	Node* insertedNode = Insert(keyToInsert, valueToInsert, this->GetRoot());
	Rebalance(insertedNode);
	return insertedNode;
}

Node* _root;
int _size;

/* Auxillary function for Insert.
*
* Input: externalNode - node to insert new node at, becomes internal
*        keyToInsert - key for node being inserted
*        valueToInsert - value for node being inserted
*
* Output: None
*
*/
void BinarySearchTree::InsertAtExternal(Node* externalNode, int keyToInsert, std::string valueToInsert)
{
	if (externalNode->IsExternal()) 
	{
		//assign key and value to the node
		externalNode->SetKey(keyToInsert);
		externalNode->SetValue(valueToInsert);
		//create children of v, so it becomes internal node
		Node* left = new Node;
		Node* right = new Node;
		externalNode->SetLeft(left);
		externalNode->SetRight(right);
		left->SetParent(externalNode);
		right->SetParent(externalNode);
	}
	// Display error message if not external
	else 
	{
		std::cout << "this function should insert new node on an external node" << std::endl;
	}
}

/* Return height of node
*  Auxillary function needed for rebalancing
*
* Input: nodeToReturnHeight - pointer to node that needs height returned
*
* Output: int - height of the specificed node
*
*/
int BinarySearchTree::Height(Node* nodeToReturnHeight)
{	
	// Make sure pointer isn't to a null memory space
	if (nodeToReturnHeight != nullptr) 
	{
		// Height of an external node is always 0
		if (nodeToReturnHeight->IsExternal()) 
		{

			return 0;
		}
		// Return the hightest height of children of node
		else 
		{
			int leftHeight = Height(nodeToReturnHeight->GetLeft());
			int rightHeight = Height(nodeToReturnHeight->GetRight());
			if (leftHeight >= rightHeight) 
			{
				return leftHeight + 1;
			}
			else 
			{
				return rightHeight + 1;
			}
		}
	}
	// Display error message if the pointer is to nullptr
	else 
	{
		std::cout << "node this null" << std::endl;
	}
}

/* Return is difference between height of children is greate than 1
*
*  Input: nodeToCheck - pointer to node to see if balanced
*
*  Output: bool - true is balanced, false if unbalanced
*
*/
bool BinarySearchTree::IsBalanced(Node* nodeToCheck)
{
	if (nodeToCheck->IsExternal()) {
		return true;
	}
	else {
		int diffInHeight = Height(nodeToCheck->GetLeft()) - Height(nodeToCheck->GetRight());
		return (std::abs(diffInHeight) > 1);
	}
}

/* Return grandchild of unbalancedNode with greatest height
*
* Input: unbalancedNode - node that is being rebalanced
*
* Output: Node* - pointer to the grandchild with greatest height
*
*/
Node* BinarySearchTree::TallGrandchild(Node* unbalancedNode)
{
	Node* left = unbalancedNode->GetLeft();
	Node* right = unbalancedNode->GetRight();
	// Left child is the tallest child
	if (Height(left) >= Height(right)) 
	{
		Node* tallestChild = left;
		// Left grandchild is the tallest grandchild
		if (Height(tallestChild->GetLeft()) >= Height(tallestChild->GetRight())) 
		{
			return tallestChild->GetLeft();
		}
		// Right grandchild is the tallest grandchild
		else 
		{
			return tallestChild->GetRight();
		}
	}
	// Right child is the tallest child
	else 
	{
		Node* tallestChild = right;
		// Left grandchild is the tallest grandchild
		if (Height(tallestChild->GetLeft()) >= Height(tallestChild->GetRight())) 
		{
			return tallestChild->GetLeft();
		}
		// Right grandchild is the tallest grandchild
		else 
		{
			return tallestChild->GetRight();
		}
	}
}

/* Using the grandchild as a point of reference, balance the tree around it, the child, and the parent
*
* Input: grandchild - the tallest grandchild of the unbalanced node
*
* Output: None
*/
void BinarySearchTree::Restructure(Node* grandchild)
{
	// Get the parent and child relative to the grandchild
	Node* child = grandchild->GetParent();
	Node* parent = child->GetParent();

	// 2. Get the inorder progression of parent, child, and grandchild
	Node* a = nullptr; 
	Node* b = nullptr; 
	Node* c = nullptr;
	if (parent->GetRight() == child && child->GetRight() == grandchild) 
	{
		a = parent;
		b = child; 
		c = grandchild;
	}
	else if (parent->GetLeft() == child && child->GetLeft() == grandchild)
	{
		a = grandchild;
		b = child;
		c = parent;
	}
	else if (parent->GetRight() == child && child->GetLeft() == grandchild) 
	{
		a = parent; 
		b = grandchild;
		c = child;
	}
	else if (parent->GetLeft() == child && child->GetRight() == grandchild) 
	{
		a = child; 
		b = grandchild;
		c = parent;
	}

	//3. Find the subtrees that aren't from the parent, child, and grandchild 
	Node* T0 = nullptr; 
	Node* T1 = nullptr;
	Node* T2 = nullptr; 
	Node* T3 = nullptr;
	if (a == parent && b == child && c == grandchild) 
	{
		T0 = a->GetLeft(); 
		T1 = b->GetLeft(); 
		T2 = c->GetLeft(); 
		T3 = c->GetRight();
	}
	else if (a == grandchild && b == child && c == parent) 
	{
		T0 = a->GetLeft(); 
		T1 = a->GetRight(); 
		T2 = b->GetRight(); 
		T3 = c->GetRight();
	}
	else if (a == parent && b == grandchild && c == child) 
	{
		T0 = a->GetLeft(); 
		T1 = b->GetLeft(); 
		T2 = b->GetRight(); 
		T3 = c->GetRight();
	}
	else if (a == child && b == grandchild && c == parent) 
	{
		T0 = a->GetLeft(); 
		T1 = b->GetLeft(); 
		T2 = b->GetRight(); 
		T3 = c->GetRight();
	}

	// Replace the subtree rooted at the parent with a new subtree rooted at b
	// If parent is not root
	if (!parent->IsRoot()) 
	{
		if (parent->GetParent()->GetLeft() == parent) 
		{
			parent->GetParent()->SetLeft(b);
		}
		else 
		{
			parent->GetParent()->SetRight(b);
		}
		b->SetParent(parent->GetParent());
	}
	// If parent is root
	else 
	{
		b->SetParent(nullptr);
		this->_root = b;
	}

	// Set a be left child of b
	b->SetLeft(a);
	a->SetParent(b);
	a->SetLeft(nullptr);
	a->SetRight(nullptr);

	// Set c be right child of b
	b->SetRight(c);
	c->SetParent(b);
	c->SetLeft(nullptr);
	c->SetRight(nullptr);

	// Let T0, T1 be left and right subtrees of a, respectively
	a->SetLeft(T0);
	if (T0 != nullptr) 
	{
		T0->SetParent(a);
	}
	a->SetRight(T1);
	if (T1 != nullptr) 
	{
		T1->SetParent(a);
	}

	// Let T2, T3 be left and right subtrees of c, respectively
	c->SetLeft(T2);
	if (T2 != nullptr) 
	{
		T2->SetParent(c);
	}
	c->SetRight(T3);
	if (T3 != nullptr) 
	{
		T3->SetParent(c);
	}
}