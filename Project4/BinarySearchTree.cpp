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

/* Return the depth of the node provided
*
*  Input: nodeToFindDepthOf
*
*  Output: int - depth of nodeToFindDepthOf
*
*/
int BinarySearchTree::GetNodeDepth(Node* nodeToFindDepthOf)
{
	// Root has a depth of 0
	// All other nodes have a depth 1 greater than their parent
	if (nodeToFindDepthOf->IsRoot())
	{
		return 0;
	}
	else
	{
		return GetNodeDepth(nodeToFindDepthOf->GetParent()) + 1;
	}
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
		return Search(keyToSearch, nodeToSearchAt->GetLeftChild());
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
		return Search(keyToSearch, nodeToSearchAt->GetRightChild());
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
			return Insert(keyToInsert, valueToInsert, newNode->GetLeftChild());
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
	if (_size != 0)
	{
		Node* nodeToCheck = newlyInsertedNode;
		// Make sure that nodeToBalance isn't root
		// Root's parent is nullptr, this is bad
		while (!nodeToCheck->IsRoot())
		{
			// Current node is assumed balanced as it starts with
			// a newly inserted node. So grab the parent instead.
			nodeToCheck = nodeToCheck->GetParent();
			// If node is not balanced, grabs the "tallest" grandchild
			if (!this->IsBalanced(nodeToCheck))
			{
				Node* grandchildOfUnbalanced = TallGrandchild(nodeToCheck);
				if (grandchildOfUnbalanced != nullptr)
				{
					this->Restructure(grandchildOfUnbalanced);
				}
			}
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

/* Delete a non-external node
*
* Input: nodeToDelete - point to node to be deleted
*
* Output: Node* - sibling of the deleted node
*
*/
Node* BinarySearchTree::Delete(Node* nodeToDelete)
{
	if (nodeToDelete->IsExternal())
	{
		delete nodeToDelete;
		_size--;
		return nullptr;
	}
	else if (nodeToDelete->IsRoot())
	{
		Node* leftChild = nodeToDelete->GetLeftChild();
		Node* rightChild = nodeToDelete->GetRightChild();

		if (leftChild == nullptr)
		{
			rightChild->SetParent(nullptr);
			_root = rightChild;
		}
		else if (rightChild == nullptr)
		{
			leftChild->SetParent(nullptr);
			_root - leftChild;
		}
		else
		{
			leftChild->SetParent(nullptr);
			_root = leftChild;
			Node* newParent = leftChild;
			while (newParent->GetRightChild() != nullptr && newParent->GetRightChild()->GetKey() != 0)
			{
				newParent = newParent->GetRightChild();
				std::cout << "new parent is " << newParent->GetKey() << std::endl;
			}
			newParent->SetRightChild(rightChild);
			rightChild->SetParent(newParent);
		}
		delete nodeToDelete;
		_size--;
	}
	else
	{
		Node* parent = nodeToDelete->GetParent();
		Node* leftChild = nodeToDelete->GetLeftChild();
		Node* rightChild = nodeToDelete->GetRightChild();
		
		if (leftChild == nullptr || leftChild->GetKey() == 0)
		{
			if (parent->GetLeftChild() == nodeToDelete)
			{
				parent->SetLeftChild(rightChild);
			}
			else
			{
				parent->SetRightChild(rightChild);
			}
			rightChild->SetParent(parent);
		}
		else
		{
			if (parent->GetLeftChild() == nodeToDelete)
			{
				parent->SetLeftChild(leftChild);
			}
			else
			{
				parent->SetRightChild(leftChild);
			}
			leftChild->SetParent(nodeToDelete);
		}

		delete nodeToDelete;
		this->_size--;
		return parent;
	}
}

/* Delete, but ReBalance is called after
*
*  Input: nodeToDelete - node to be removed from the tree
*
*  Output: Node* - sibling of the node that was deleted
*
*/
Node* BinarySearchTree::BalancedDelete(Node* nodeToDelete)
{
	Node* siblingOfDeleted = Delete(nodeToDelete);
	if (siblingOfDeleted != nullptr)
	{
		Rebalance(siblingOfDeleted);
	}
	return siblingOfDeleted;
}

/* Print out a graphical representation of the tree using InOrder traversal
*
* Input: none
*
* Output: none
*
*/
void BinarySearchTree::PrintTree()
{
	if (_size != 0)
	{
		// Create vector large enough for drawing the tree
		int col = this->GetSize();
		int row = GetNodeHeight(this->GetRoot()) + 1;

		std::vector<std::vector<std::string>> grid(row, std::vector<std::string>(col, "NULL"));

		// In order traversal of the tree and assign coordinates
		int counter = 0;
		AssignCoordinates(this->GetRoot(), grid, counter);

		for (int o = 0; o < row; o++)
		{
			for (int i = 0; i < col; i++)
			{
				if (grid[o][i] == "NULL")
				{
					std::cout << " ";
				}
				else
				{
					std::cout << grid[o][i];
				}
			}
			std::cout << std::endl;
		}
	}
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
		externalNode->SetLeftChild(left);
		externalNode->SetRightChild(right);
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
int BinarySearchTree::GetNodeHeight(Node* nodeToReturnHeight)
{	
	// Height of an external node is always 0
	if (nodeToReturnHeight->IsExternal()) 
	{
		return 0;
	}
	// Return the hightest height of children of node
	else 
	{
		int leftHeight = GetNodeHeight(nodeToReturnHeight->GetLeftChild());
		int rightHeight = GetNodeHeight(nodeToReturnHeight->GetRightChild());
		if (leftHeight > rightHeight) 
		{
			return leftHeight + 1;
		}
		else 
		{
			return rightHeight + 1;
		}
	}
}

/* Returns difference between height of children is greate than 1
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
	else 
	{
		int diffInHeight = GetNodeHeight(nodeToCheck->GetLeftChild()) - GetNodeHeight(nodeToCheck->GetRightChild());
		return ((-1 <= diffInHeight) && (diffInHeight <= 1));
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
	if (!unbalancedNode->IsExternal())
	{
		Node* left = unbalancedNode->GetLeftChild();
		Node* right = unbalancedNode->GetRightChild();
		// Left child is the tallest child
		if (GetNodeHeight(left) >= GetNodeHeight(right))
		{
			Node* tallestChild = left;
			// Left grandchild is the tallest grandchild
			if (GetNodeHeight(tallestChild->GetLeftChild()) >= GetNodeHeight(tallestChild->GetRightChild()))
			{
				return tallestChild->GetLeftChild();
			}
			// Right grandchild is the tallest grandchild
			else
			{
				return tallestChild->GetRightChild();
			}
		}
		// Right child is the tallest child
		else
		{
			Node* tallestChild = right;
			// Left grandchild is the tallest grandchild
			if (GetNodeHeight(tallestChild->GetLeftChild()) >= GetNodeHeight(tallestChild->GetRightChild()))
			{
				return tallestChild->GetLeftChild();
			}
			// Right grandchild is the tallest grandchild
			else
			{
				return tallestChild->GetRightChild();
			}
		}
	}
	else
	{
		return unbalancedNode;
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
	if (parent->GetRightChild() == child && child->GetRightChild() == grandchild)
	{
		a = parent;
		b = child;
		c = grandchild;
	}
	else if (parent->GetLeftChild() == child && child->GetLeftChild() == grandchild)
	{
		a = grandchild;
		b = child;
		c = parent;
	}
	else if (parent->GetRightChild() == child && child->GetLeftChild() == grandchild)
	{
		a = parent;
		b = grandchild;
		c = child;
	}
	else if (parent->GetLeftChild() == child && child->GetRightChild() == grandchild)
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
		T0 = a->GetLeftChild();
		T1 = b->GetLeftChild();
		T2 = c->GetLeftChild();
		T3 = c->GetRightChild();
	}
	else if (a == grandchild && b == child && c == parent)
	{
		T0 = a->GetLeftChild();
		T1 = a->GetRightChild();
		T2 = b->GetRightChild();
		T3 = c->GetRightChild();
	}
	else if (a == parent && b == grandchild && c == child)
	{
		T0 = a->GetLeftChild();
		T1 = b->GetLeftChild();
		T2 = b->GetRightChild();
		T3 = c->GetRightChild();
	}
	else if (a == child && b == grandchild && c == parent)
	{
		T0 = a->GetLeftChild();
		T1 = b->GetLeftChild();
		T2 = b->GetRightChild();
		T3 = c->GetRightChild();
	}

	// Replace the subtree rooted at the parent with a new subtree rooted at b
	// If parent is not root
	if (!parent->IsRoot())
	{
		if (parent->GetParent()->GetLeftChild() == parent)
		{
			parent->GetParent()->SetLeftChild(b);
		}
		else
		{
			parent->GetParent()->SetRightChild(b);
		}
		b->SetParent(parent->GetParent());
	}
	// If parent is root
	else
	{
		b->SetParent(nullptr);
		this->SetRoot(b);
	}

	// Set a be left child of b
	b->SetLeftChild(a);
	a->SetParent(b);
	a->SetLeftChild(nullptr);
	a->SetRightChild(nullptr);

	// Set c be right child of b
	b->SetRightChild(c);
	c->SetParent(b);
	c->SetLeftChild(nullptr);
	c->SetRightChild(nullptr);

	// Let T0, T1 be left and right subtrees of a, respectively
	a->SetLeftChild(T0);
	if (T0 != nullptr)
	{
		T0->SetParent(a);
	}
	a->SetRightChild(T1);
	if (T1 != nullptr)
	{
		T1->SetParent(a);
	}

	// Let T2, T3 be left and right subtrees of c, respectively
	c->SetLeftChild(T2);
	if (T2 != nullptr)
	{
		T2->SetParent(c);
	}
	c->SetRightChild(T3);
	if (T3 != nullptr)
	{
		T3->SetParent(c);
	}
}

/* Puts a node into a grid based on it's depth and order it came in traversal
*
*  Input: nodeToStartAt - the node that will be recursed through
*		  grid - A two-dimensional vector containing the information for the graph
*		  counter - the order in which the nodes have been visited
*
*  Output: None
*
*/
void BinarySearchTree::AssignCoordinates(Node* nodeToStartAt, std::vector<std::vector<std::string>>& grid, int& counter)
{
	// Follows in order algorithm
	if (nodeToStartAt != nullptr )
	{
		/*This is a fix for a bug*/
		if (nodeToStartAt->GetKey() != 0 && nodeToStartAt->GetLeftChild() != nullptr && nodeToStartAt->GetRightChild() != nullptr)
		{
			AssignCoordinates(nodeToStartAt->GetLeftChild(), grid, counter);
			int col = counter;
			int row = this->GetNodeDepth(nodeToStartAt);
			grid[row][col] = std::to_string(nodeToStartAt->GetKey());  // We are showing that the keys are ordered correctly
			counter++;
			AssignCoordinates(nodeToStartAt->GetRightChild(), grid, counter);
		}
	}
}
