#ifndef ELEMENT_H
#define ELEMENT_H

/////////////////////////////////////////////////////////////////////
//  element.h - Builds an Abstract Syntax Tree                     //
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
std::string type;
std::string name;
element* parent;
std::vector<element*> childNode;
size_t startLine;
size_t endLine;
size_t lineCount;
size_t complexity;


Build Process:
==============
Required files
- ScopeStack.h

Build commands 
- devenv Project2.sln

Maintenance History:
====================
ver 1.0 : 14 Mar 16
- first release

*/

#include <string>
#include <sstream>
#include <queue>
#include <vector>
#include "../ScopeStack/ScopeStack.h"



class element {
	
public:
	std::string type;
	std::string name;
	element* parent;
	std::vector<element*> childNode;
	size_t startLine;
	size_t endLine;
	size_t lineCount;
	size_t complexity;
	
	element() {
		parent = NULL; startLine = 0; endLine = 0; lineCount = 0; complexity = 1;
	}


};




#endif // !ELEMENT_H
