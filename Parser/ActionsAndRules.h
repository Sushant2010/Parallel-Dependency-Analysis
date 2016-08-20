#ifndef ACTIONSANDRULES_H
#define ACTIONSANDRULES_H

/////////////////////////////////////////////////////////////////////
//  ActionsAndRules.h - declares new parsing rules and actions     //
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
This module defines several action classes.  Its classes provide
specialized services needed for specific applications.  The modules
Parser, SemiExpression, and Tokenizer, are intended to be reusable
without change.  This module provides a place to put extensions of
these facilities and is not expected to be reusable.

Public Interface:
=================
Toker t(someFile);              // create tokenizer instance
SemiExp se(&t);                 // create a SemiExp attached to tokenizer
Parser parser(se);              // now we have a parser
Rule1 r1;                       // create instance of a derived Rule class
Action1 a1;                     // create a derived action
r1.addAction(&a1);              // register action with the rule
parser.addRule(&r1);            // register rule with parser
while(se.getSemiExp())          // get semi-expression
parser.parse();               //   and parse it

Build Process:
==============
Required files
- Parser.h, Parser.cpp, ScopeStack.h, ScopeStack.cpp,
ActionsAndRules.h, ActionsAndRules.cpp, ConfigureParser.cpp,
ItokCollection.h, SemiExpression.h, SemiExpression.cpp, tokenizer.h, tokenizer.cpp
Build commands (either one)
- devenv Project2.sln
- cl /EHsc /DTEST_PARSER parser.cpp ActionsAndRules.cpp \
semiexpression.cpp tokenizer.cpp /link setargv.obj

Maintenance History:
====================

ver 1.0 : 14 Mar 16
- first release
*/

#include <queue>
#include <string>
#include <sstream>
#include "Parser.h"
#include "../SemiExp/itokcollection.h"
#include "../ScopeStack/ScopeStack.h"
#include "../Tokenizer/Tokenizer.h"
#include "../SemiExp/SemiExp.h"
#include "TypeTable.h"



///////////////////////////////////////////////////////////////
// Repository instance is used to share resources
// among all actions.

class Repository  
{
	ScopeStack<element> stack;
	Scanner::Toker* p_Toker;
	AST* tree = new AST(&stack);
	element root;

public:
	Repository(Scanner::Toker* pToker)
	{
		if (stack.size() == 0) {

			root.type = "root";
			root.name = "GlobalNameSpace";
			root.startLine = 0;
			stack.push(root);
			tree->setRoot(root);

		}

		p_Toker = pToker;
		table = new TypeTable<TypeTableRecord>();
	}
	
	AST* getTree() {
		return tree;
	}
	
	ScopeStack<element>& scopeStack()
	{
		return stack;
	}

	Scanner::Toker* Toker()
	{
		return p_Toker;
	}
	size_t lineCount()
	{
		return (size_t)(p_Toker->currentLineCount());
	}
	TypeTable<TypeTableRecord>* getTable() 
	{
		return table;
	}
	void setFileName(std::string f) 
	{
		file = f;
	}
	std::string getFileName() 
	{
		return file;
	}

private:
	TypeTable<TypeTableRecord>* table;
	std::string file;

};

///////////////////////////////////////////////////////////////
// rule to detect beginning of anonymous scope

class BeginningOfScope : public IRule
{
public:
	bool doTest(ITokCollection*& pTc)
	{
		if (pTc->find("{") < pTc->length())
		{
			doActions(pTc);
			return true;
		}
		return true;
	}
};

///////////////////////////////////////////////////////////////
// action to handle scope stack at end of scope

class HandlePush : public IAction
{
	Repository* p_Repos;
public:
	HandlePush(Repository* pRepos)
	{
		p_Repos = pRepos;
	}
	void doAction(ITokCollection*& pTc)
	{
		//std::cout << "\n--BeginningOfScope rule";
		element elem;
		elem.type = "scope";
		elem.name = "Beginning Scope";
		elem.lineCount = p_Repos->lineCount();
		p_Repos->scopeStack().push(elem);
	}
};

///////////////////////////////////////////////////////////////
// rule to detect end of scope

class EndOfScope : public IRule
{
public:
	bool doTest(ITokCollection*& pTc)
	{
		if (pTc->find("}") < pTc->length())
		{
			doActions(pTc);
			return true;
		}
		return true;
	}
};

///////////////////////////////////////////////////////////////
// action to handle scope stack at end of scope

class HandlePop : public IAction
{
	Repository* p_Repos;
public:
	HandlePop(Repository* pRepos)
	{
		p_Repos = pRepos;
	}
	void doAction(ITokCollection*& pTc)
	{
		//std::cout << "\n--EndOfScope rule";
		if (p_Repos->scopeStack().size() == 0)
			return;
		element elem = p_Repos->scopeStack().pop();
		if (elem.type == "function")
		{
			AST* tree = p_Repos->getTree();
			elem.endLine = p_Repos->lineCount();
			tree->setRecentElement(elem);
		}
		else if (elem.type == "class") {
			AST* tree = p_Repos->getTree();
			elem.endLine = p_Repos->lineCount();
			tree->setRecentElement(elem);
		}
		else if (elem.type == "struct") {
			AST* tree = p_Repos->getTree();
			elem.endLine = p_Repos->lineCount();
			tree->setRecentElement(elem);
		}
		else if (elem.type == "namespace") {
			AST* tree = p_Repos->getTree();
			elem.endLine = p_Repos->lineCount();
			tree->setRecentElement(elem);
		}
		else if (elem.type == "enum") {
			AST* tree = p_Repos->getTree();
			elem.endLine = p_Repos->lineCount();
			tree->setRecentElement(elem);
		}
		else if (elem.type == "loop") {
			AST* tree = p_Repos->getTree();
			elem.endLine = p_Repos->lineCount();
			tree->setRecentElement(elem);
		}

	}
};

///////////////////////////////////////////////////////////////
// rule to detect preprocessor statements

class PreprocStatement : public IRule
{
public:
	bool doTest(ITokCollection*& pTc)
	{
		if (pTc->find("#") < pTc->length())
		{
			doActions(pTc);
			return true;
		}
		return true;
	}
};



///////////////////////////////////////////////////////////////
// rule to detect function definitions

class FunctionDefinition : public IRule
{
public:
	bool isSpecialKeyWord(const std::string& tok)
	{
		const static std::string keys[]
			= { "for", "while", "switch", "if", "catch" };
		for (int i = 0; i<5; ++i)
			if (tok == keys[i])
				return true;
		return false;
	}
	bool doTest(ITokCollection*& pTc)
	{
		ITokCollection& tc = *pTc;
		if (tc[tc.length() - 1] == "{")
		{
			size_t len = tc.find("(");
			if (len < tc.length() && !isSpecialKeyWord(tc[len - 1]))
			{
				doActions(pTc);
				return true;
			}
		}
		return true;
	}
};

///////////////////////////////////////////////////////////////
// action to push function name onto ScopeStack

class PushFunction : public IAction
{
	Repository* p_Repos;
public:
	PushFunction(Repository* pRepos)
	{
		p_Repos = pRepos;
	}
	void doAction(ITokCollection*& pTc)
	{

		// pop anonymous scope
		p_Repos->scopeStack().pop();

		// push function scope
		std::string name = (*pTc)[pTc->find("(") - 1];
		element elem;
		elem.type = "function";
		elem.name = name;
		elem.lineCount = p_Repos->lineCount();
		AST* tree = p_Repos->getTree();
		tree->addChildNode(elem);
		p_Repos->scopeStack().push(elem);

		TypeTableRecord record;
		record.name() = (*pTc)[pTc->find("(") - 1];
		record.type() = "function";
		record.fileName() = p_Repos->getFileName();
		record.parent() = tree->searchParent(elem)->name;
		TypeTable<TypeTableRecord>* t = p_Repos->getTable();
		t->addRecord(record);
	}
};



//rule to detect "if,for,while,switch,catch"

class Loops : public IRule {
	size_t length;
public:
	bool isLoop(std::string& tok) {

		const static std::string keys[] = { "for","while","switch","if","catch" };
		for (int i = 0; i < 5; i++)
		{
			if (tok == keys[i]) { return true; }
		}

		return false;

	}
	bool doTest(ITokCollection*& pTc) {
		ITokCollection& tc = *pTc;

		if (tc[tc.length() - 1] == "{") {
			length = tc.find("(");
			if (length < tc.length() && isLoop(tc[length - 1])) {
				doActions(pTc);
				return true;
			}

		}
		return false;
	}

};

//action to push loop name onto scopestack
class PushLoops : public IAction {

	Repository* p_Repos;
	std::string name;


public:

	PushLoops(Repository* pRepos) {
		p_Repos = pRepos;
	}

	void doAction(ITokCollection*& pTc) {

		p_Repos->scopeStack().pop();
		name = (*pTc)[pTc->find("(") - 1];

		element elem;
		elem.type = "loop";
		elem.name = name;
		elem.lineCount = p_Repos->lineCount();
		p_Repos->scopeStack().push(elem);

		AST* tree = p_Repos->getTree();
		tree->addChildNode(elem);
		p_Repos->scopeStack().push(elem);

	}

};


//rule to detect class,struct,enum,namespace
class ClassDefinition :public IRule {

public:

	bool doTest(ITokCollection*& pTc) {
		ITokCollection& tc = *pTc;
		if (tc[tc.length() - 1] == "{") {
			if ((tc.find("class") < tc.length()) || tc.find("struct") < tc.length() || tc.find("enum") < tc.length() || tc.find("namespace") < tc.length()) {
				doActions(pTc);
				return true;

			}

		}

		return true;
	}

};

//action to push class,struct,enum,namespace onto scopestack

class PushClassDefinition :public IAction
{
	Repository* p_Repos;
	std::string name;
	element elem;
public:
	TypeTableRecord record;
	PushClassDefinition(Repository* pRepos)
	{
		p_Repos = pRepos;
	}

	void doAction(ITokCollection*& pTc)
	{
		p_Repos->scopeStack().pop();

		ITokCollection& tc = *pTc;
		if (tc[tc.length() - 1] == "{" && tc.find("class") < tc.length())
		{
			name = tc[tc.find("class") + 1];
			elem.type = "class";
			record.type() = "class";
		}
		if (tc[tc.length() - 1] == "{" && tc.find("struct") < tc.length())
		{
			name = tc[tc.find("struct") + 1];
			elem.type = "struct";
			record.type() = "struct";
		}
		if (tc[tc.length() - 1] == "{" && tc.find("enum") < tc.length())
		{
			name = tc[tc.find("enum") + 1];
			elem.type = "enum";
			record.type() = "enum";
		}
		if (tc[tc.length() - 1] == "{" && tc.find("namespace") < tc.length())
		{
			name = tc[tc.find("namespace") + 1];
			elem.type = "namespace";
			record.type() = "namespace";
		}
		elem.name = name;
		elem.lineCount = p_Repos->lineCount();
		AST* tree = p_Repos->getTree();
		tree->addChildNode(elem);
		p_Repos->scopeStack().push(elem);

		record.name() = name;
		record.fileName() = p_Repos->getFileName();
		record.parent() = tree->searchParent(elem)->name;
		TypeTable<TypeTableRecord>* t = p_Repos->getTable();
		t->addRecord(record);
	}

};


class Alias : IRule
{
	bool doTest(ITokCollection*& pTc)
	{
		ITokCollection& tc = *pTc;

		if (tc.find("using") < tc.length())
		{
			doActions(pTc);
			return true;
		}

		return true;
	}
};

class PushAlias : public IAction
{
	Repository* p_Repos;
public:
	PushAlias(Repository* pRepos)
	{
		p_Repos = pRepos;
	}

	void doAction(ITokCollection*& pTc)
	{
		p_Repos->scopeStack().pop();

		TypeTableRecord record;
		record.name() = (*pTc)[pTc->find("using") + 1];
		record.type() = "alias";
		record.fileName() = p_Repos->getFileName();
		TypeTable<TypeTableRecord>* t = p_Repos->getTable();
		t->addRecord(record);
	}
};

class TypeDef : public IRule
{
public:
	bool isSpecialKeyWord(const std::string& tok)
	{
		const static std::string keys[]
			= { "char", "int", "long", "unsigned", "std::string" };
		for (int i = 0; i<5; ++i)
			if (tok == keys[i])
				return true;
		return false;
	}

	bool doTest(ITokCollection*& pTc)
	{
		ITokCollection& tc = *pTc;
		if (tc[tc.length() - 1] == ";")
		{
			size_t len = tc.find("typedef");

			if (len < tc.length() && !isSpecialKeyWord(tc[len + 1]))
			{
				doActions(pTc);
				return true;
			}
		}
		return true;
	}
};



#endif
