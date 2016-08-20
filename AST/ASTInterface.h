/////////////////////////////////////////////////////////////////////
//  ASTInterface.h - Interface for Abstract Syntax Tree            //
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

struct ASTInterface
{
	element *rootNode;
	element* recentElement;

public:
	virtual element* Root() = 0;
	virtual element* searchParent(element) = 0;
	virtual void setRoot(element) = 0;
	virtual void addChildNode(element node) = 0;
	virtual void setRecentElement(element node) = 0;

};