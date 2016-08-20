#ifndef AST_H
#define AST_H

/////////////////////////////////////////////////////////////////////
//  AST.h - Provides functions for AST                             //
//  ver 1.0                                                        //
//  Language:      Visual C++ 2008, SP1                            //
//  Platform:      Dell XPS 15, Windows 7 Home Edition             //
//  Application:   Code Parser with AST for CSE687 Pr2, Sp16       //
//  Author:		   Sushant Garg, Syracuse University		       //
//  Source:        Jim Fawcett, CST 4-187, Syracuse University     //
//                 (315) 443-3948, jfawcett@twcny.rr.com           //
/////////////////////////////////////////////////////////////////////
/*

Module Operations:
==================
This module is for building an Abstract Syntax Tree (AST)


Public Interface:
=================

element* Root();
element* searchParent(element);
void addChildNode(element node); 
void setRoot(element);
void setRecentElement(element node);
			

Build Process:
==============
Required files
- element.h

Build commands 
- devenv Project2.sln

Maintenance History:
====================
ver 1.0 : 14 Mar 16
- first release

*/

#include <iostream>
#include "element.h"
#include "ASTInterface.h"

class AST :public ASTInterface {
		
	element* rootNode;
	element* recentElement;

public:
	
	ScopeStack<element>* scopeStack;
	AST(ScopeStack<element>* scopeStack);

	element* Root();
	element* searchParent(element);

	void setRoot(element);
	void addChildNode(element node);
	void setRecentElement(element node);

};



#endif 

