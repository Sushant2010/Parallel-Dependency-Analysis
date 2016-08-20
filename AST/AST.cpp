/////////////////////////////////////////////////////////////////////
//  AST.cpp - Builds an Abstract Syntax Tree                       //
//  ver 1.0                                                        //
//  Language:      Visual C++ 2008, SP1                            //
//  Platform:      Dell XPS 15, Windows 7 Home Edition             //
//  Application:   Code Parser with AST for CSE687 Pr2, Sp16       //
//  Author:		   Sushant Garg, Syracuse University		       //
//  Source:        Jim Fawcett, CST 4-187, Syracuse University     //
//                 (315) 443-3948, jfawcett@twcny.rr.com           //
/////////////////////////////////////////////////////////////////////


#include "AST.h"
#include "element.h"

AST::AST(ScopeStack<element>* scopeStack1)
{
	scopeStack = scopeStack1;
	rootNode = NULL;
	recentElement = NULL;
}

//Gives the root of AST
element* AST::Root() {
	return rootNode;
}


//For searching top most element of Scopestack 
element* AST::searchParent(element elem)
{
	if (recentElement != NULL) {
		
		std::string name = elem.name;
		std::string type = elem.type;

		while (true) {
			if (recentElement == NULL)
				return rootNode;
			else if (name == recentElement->name && type == recentElement->type) {
				return recentElement;
			}
			else {
				recentElement = recentElement->parent;
			}

		}
		return NULL;
	}
	return NULL;
}

//Adds root to AST
void AST::setRoot(element first_node)
{
	element* node = new element();
	node->name = first_node.name;
	node->type = first_node.type;
	node->lineCount = first_node.lineCount;
	node->startLine = first_node.lineCount;
	rootNode = node;
	recentElement = rootNode;
	return;
}

//To add a child node to AST where parent is taken as the top element of scopestack  
void AST::addChildNode(element first_node) {
	element* node = new element();
	node->name = first_node.name;
	node->type = first_node.type;
	node->lineCount = first_node.lineCount;
	node->startLine = first_node.lineCount;

	if (rootNode == NULL) {
		rootNode = node;
		recentElement = node;
		return;
	}

	element* first_parent = recentElement;
	
	if (first_parent != NULL) {
		if (node->type == "loop") {
			node->complexity = 1;
		}
		first_parent->childNode.push_back(node);
		node->parent = first_parent;
		recentElement = node;
	}
	return;
}

//For setting a last encountered node as current node
void AST::setRecentElement(element node)
{
	if (recentElement != NULL && recentElement->parent != NULL) {
		recentElement->endLine = node.endLine;
		recentElement->lineCount = recentElement->endLine - recentElement->startLine + 1;
		(recentElement->parent)->complexity = (recentElement->parent)->complexity + recentElement->complexity;
		recentElement = recentElement->parent;
	}
}