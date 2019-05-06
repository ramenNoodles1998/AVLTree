#include <iostream>
#include <stdexcept>
#include <algorithm>
#include "AVLTree.h"

using namespace std;



AVLTree::AVLTree()
{
	root = nullptr;
}


AVLTree::~AVLTree()
{
	DestructorHelper(root);
}
void AVLTree::DestructorHelper(Node * cursor)
{
	// base case
	if (cursor == nullptr)
		return;

	// delete left
	DestructorHelper(cursor->left);
	// delete right
	DestructorHelper(cursor->right);
	// delete me
	delete cursor;
}

void AVLTree::Insert(int data)
{
	root = InsertHelper(root, data);
}
Node * AVLTree::InsertHelper(Node * cursor, int data)
{
	// base case
	
	if (cursor == nullptr) {
		return new Node(data);
	}
	if (data <= cursor->data) {
		cursor->left = InsertHelper(cursor->left, data);
	}
	else {
		cursor->right = InsertHelper(cursor->right, data);
	}
	if (cursor != nullptr) {
		UpdatHeight(cursor);
		int cursorBalance = BalanceFactor(cursor);
		int rightBalance = BalanceFactor(cursor->right);
		int leftBalance = BalanceFactor(cursor->left);
		if (cursorBalance == 2 && leftBalance >= 0) {
			cursor = RotRight(cursor);
		}
		if (cursorBalance == -2 && rightBalance <= 0) {
			cursor = RotLeft(cursor);
		}
		if (cursorBalance == 2 && leftBalance < 0) {
			cursor->left = RotLeft(cursor->left);
			cursor = RotRight(cursor);
		}
		if (cursorBalance == -2 && rightBalance > 0) {
			cursor->right = RotRight(cursor->right);
			cursor = RotLeft(cursor);
		}
		return cursor;
	}
	else {
		UpdatHeight(cursor);
		return cursor;
	}

}
Node * AVLTree::RotRight(Node * cursor)
{
	
	Node* tmp = cursor->left;
	cursor->left = tmp->right;
	tmp->right = cursor;
	UpdatHeight(cursor);
	UpdatHeight(tmp);
	return tmp;
}
Node * AVLTree::RotLeft(Node * cursor)
{
	
	Node* tmp = cursor->right;
	cursor->right = tmp->left;
	tmp->left = cursor;
	UpdatHeight(cursor);
	UpdatHeight(tmp);
	
	return tmp;
}
int AVLTree::BalanceFactor(Node * cursor) {
	int rightHeight;
	int leftHeight;
	if (cursor == nullptr) {
		return -1;
	}
	if (cursor->right == nullptr) {
		rightHeight = -1;
	}
	else {
		rightHeight = cursor->right->height;
	}
	if (cursor->left == nullptr) {
		leftHeight = -1;
	}
	else {
		leftHeight = cursor->left->height;
	}
	return leftHeight - rightHeight;

}

void AVLTree::UpdatHeight(Node * cursor)
{
	if (cursor == nullptr)
		return;
	int leftHeight = -1;
	int RightHeight = -1;
	if (cursor->left != nullptr) {
		leftHeight = cursor->left->height;
	}
	if (cursor->right != nullptr) {
		RightHeight = cursor->right->height;
	}
	cursor->height = max(leftHeight, RightHeight) + 1;
}
void AVLTree::Print()
{
	PrintHelper(root, "");
	cout << endl;
}
void AVLTree::PrintHelper(Node * cursor, std::string indent)
{
	if (cursor == nullptr)
		cout << indent << "[Empty]" << endl;
	else
	{
		if (cursor->right == nullptr && cursor->left == nullptr) {
			cout << indent << cursor->data << "(" << cursor->height << ")" << "[leaf]" << endl;
		}
		else {
			cout << indent << cursor->data << "(" << cursor->height << ")" << endl;
			PrintHelper(cursor->left, indent + "   ");
			PrintHelper(cursor->right, indent + "   ");
		}
	}
}

Node* AVLTree::Search(int target)
{
	return SearchHelper(root, target);
}
Node* AVLTree::SearchHelper(Node *cursor, int target)
{
	// base cases
	if (cursor == nullptr)
		return nullptr;
	if (cursor->data == target)
		return cursor;

	else if (target < cursor->data)
		return SearchHelper(cursor->left, target);
	else
		return SearchHelper(cursor->right, target);
}

bool AVLTree::IsLeaf(Node * cursor)
{
	if (cursor == nullptr)
		throw invalid_argument("nullptr passed to IsLeaf()");
	if (cursor->left == nullptr && cursor->right == nullptr)
		return true;
	else
		return false;
}

Node * AVLTree::FindSuccessor(Node * cursor)
{
	Node *successor = cursor->right;

	while (successor->left != nullptr)
		successor = successor->left;

	return successor;
}
void AVLTree::PreOrderTraversal()
{
	cout << endl;
	TraversalHelper(root);
}
void AVLTree::TraversalHelper(Node * cursor)
{
	if (cursor == nullptr) {
		return;
	}
	else {
		cout << cursor->data << ", ";
		TraversalHelper(cursor->left);
		TraversalHelper(cursor->right);
	}
}

void AVLTree::Remove(int target)
{
	RemoveHelper(root, target);
}

Node * AVLTree::RemoveHelper(Node * cursor, int target)
{
	// base cases
	if (cursor == nullptr)
		return nullptr;
	if (cursor->data == target)
	{
		// case 2: cursor is a leaf
		if (IsLeaf(cursor))
		{
			delete cursor;
			return nullptr;
		}
		// case 3: cursor has only one child
		else if (cursor->right != nullptr && cursor->left == nullptr)
		{
			Node *tmp = cursor->right;
			delete cursor;
			return tmp;
		}
		else if (cursor->left != nullptr && cursor->right == nullptr)
		{
			Node *tmp = cursor->left;
			delete cursor;
			return tmp;
		}
		else
		{
			// case 4: cursor has both children
			Node *successor = FindSuccessor(cursor);
			cursor->data = successor->data;
			cursor->right = RemoveHelper(cursor->right, successor->data);
			return cursor;
		}
	}
	else
	{
		if (target < cursor->data)
			cursor->left = RemoveHelper(cursor->left, target);
		else
			cursor->right = RemoveHelper(cursor->right, target);

		return cursor;
	}
}
