#ifndef METRICANALYSIS_H
#define METRICANALYSIS_H

/////////////////////////////////////////////////////////////////////
//  MetricAnalysis.h -  for evaluating and displaying the size     //
//                      and complexity of all functions            //
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
This module is for for evaluating and displaying the size and complexity of all functions


Public Interface:
=================

void display(element* elem);
void preOrderTraversal(element* elem);


Build Process:
==============
Required files
- AST.h

Build commands
- devenv Project2.sln

Maintenance History:
====================
ver 1.0 : 14 Mar 16
- first release

*/

#include "../AST/AST.h"

class Metric {

public:
	void display(element* elem);
	void preOrderTraversal(element* elem);

};

#endif // !METRICANALYSIS_H
