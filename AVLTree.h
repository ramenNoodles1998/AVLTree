#pragma once
#include <string>
#include "Node.h"
/********************************************************************************************
**	Project: AVLTree
**  Programmer: Roman Meredith
**  Course:		cs2420
**	Section:	602
**	Assignment: 8
**	Data:		November 11, 2018
**
**	I certify that I wrote all code in this project except that which was
**	provided by the instructor.
**
***********************************************************************************************/

class AVLTree
{
public:
	AVLTree();
	~AVLTree();

	void Insert(int data);
	void Print();
	Node* Search(int target);
	void Remove(int target);
	void PreOrderTraversal();

private:
	Node* root;
	Node* RotRight(Node* cursor);
	Node* RotLeft(Node* cursor);
	int BalanceFactor(Node* cursor);
	void UpdatHeight(Node* cursor);
	void DestructorHelper(Node* cursor);
	Node* InsertHelper(Node *cursor, int data);
	void PrintHelper(Node *cursor, std::string indent);
	Node* SearchHelper(Node *cursor, int target);
	Node* RemoveHelper(Node *cursor, int target);
	bool IsLeaf(Node *cursor);
	Node* FindSuccessor(Node *cursor);
	void TraversalHelper(Node *cursor);


};