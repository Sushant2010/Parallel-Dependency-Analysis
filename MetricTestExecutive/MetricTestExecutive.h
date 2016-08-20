#ifndef METRICTESTEXECUTIVE_H
#define METRICTESTEXECUTIVE_H

/////////////////////////////////////////////////////////////////////
//  MetricTestExecutive.h -  Test suite that exercises all of      //
//                           the packages                          //
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
This module is a Test suite that exercises all of the packages  


Public Interface:
=================

void fileManagerTest(std::string path, std::vector<std::string> patterns);
void parserTest(std::string file);


Build Process:
==============
Required files
- ConfigureParser.h
- FileMgr.h
- MetricAnalysis.h

Build commands
- devenv Project2.sln

Maintenance History:
====================
ver 1.0 : 14 Mar 16
- first release

*/

#include <string>
#include <vector>
#include <iostream>
#include "../Parser/ConfigureParser.h"
#include "../FileMngr/FileMgr.h"
#include "../MetricAnalysis/MetricAnalysis.h"


class MetricTestExecutive {

public:
	
	void fileManagerTest(std::string path, std::vector<std::string> patterns);
	void parserTest(std::string file);
};


#endif // !METRICTESTEXECUTIVE_H
