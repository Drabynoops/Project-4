#include "BSTMenu.h"
#include <iostream>

/* Default constructor for BinarySearchTree
*
* Input: None
*
* Output: None
*
*/
BSTMenu::BSTMenu()
{
	this->_bst = BinarySearchTree();
}

/* Constructor for BinarySearchTree where you pass in a BinarySearchTree
*
* Input: bst = BinarySearchTree to be applied to the menu
*
* Output: None
*
*/
BSTMenu::BSTMenu(BinarySearchTree bst)
{
	this->_bst = bst;
}

BSTMenu::~BSTMenu()
{
}

/* Setter for the BinarySearchTree of the menu
*
* Input: BinarySearchTree to be applied to the menu
*
* Output: None
*
*/
void BSTMenu::SetBST(BinarySearchTree bst)
{
	this->_bst = bst;
}

/* Print the menu
*
* Input: None
*
* Output: None
*
*/
void BSTMenu::PrintMenu()
{
	system("CLS");
	std::cout << std::endl;
	std::cout << "************************************************" << std::endl;
	std::cout << "***  1.  Insert node into tree               ***" << std::endl;
	std::cout << "***  2.  Delete node from tree               ***" << std::endl;
	std::cout << "***  3.  Search tree for tree                ***" << std::endl;
	std::cout << "***  4.  Display current tree                ***" << std::endl;
	std::cout << "*** -999. Exit program                       ***" << std::endl;
	std::cout << "************************************************" << std::endl;
}
/* Call the other functions depending on user input
*
* Input: None
*
* Output: bool - whether or not to continue the loop
*
*/
bool BSTMenu::SelectMenuOption()
{
	int option = 0;
	while ( (option < 1 && option != -999) || (option > 5) )
	{
		std::cout << std::endl << "Please enter you desired option: ";
		std::cin >> option;
		std::cout << std::endl;
	}

	switch (option)
	{
	case 1:
		Insert();
		Display();
		return true;
		break;
	case 2:
		Delete();
		Display();
		return true;
		break;
	case 3:
		Search();
		Display();
		return true;
		break;
	case 4:
		Display();
		return true;
		break;
	case -999:
		return false;
		break;
	}
}

BinarySearchTree _bst;

/* Function for inserting a node into the BinarySearchTree
*
* Input: None
*
* Output: None
*
*/
void BSTMenu::Insert()
{
	std::cout << "Please enter the key of the new node to enter:  ";
	int key = 0;
	std::cin >> key;
	std::cout << std::endl;
	// Currently no entry of value
	std::string value = "NULL";
	Node* newNode = this->_bst.BalancedInsert(key, value);
}

/* Function for deleting a node from the BinarySearchTree
*
* Input: None
*
* Output: None
*
*/
void BSTMenu::Delete()
{
	std::cout << "Please enter the key of the new node to enter:  ";
	int key = 0;
	std::cin >> key;
	std::cout << std::endl;
	Node* nodeToDelete = this->_bst.Search(key, this->_bst.GetRoot());
	if (nodeToDelete != nullptr)
	{
		this->_bst.BalancedDelete(nodeToDelete);
	}
	else
	{
		std::cout << "No node with that key found." << std::endl;
	}
}

/* Function for searching a node in the BinarySearchTree
*
* Input: None
*
* Output: None
*
*/
void BSTMenu::Search()
{
	std::cout << "Please enter the key of the new node to enter:  ";
	int key = 0;
	std::cin >> key;
	std::cout << std::endl << std::endl;
	Node* nodeToDelete = this->_bst.Search(key, this->_bst.GetRoot());
	if (nodeToDelete != nullptr)
	{
		std::cout << "Node found!!" << std::endl;
	}
	else
	{
		std::cout << "No node with that key found." << std::endl;
	}
}

/* Function for calling the PrintTree function of BinarySearchTree
*
* Input: None
*
* Output: None
*
*/
void BSTMenu::Display()
{
	this->_bst.PrintTree();
	system("PAUSE");
}
