#include "MetricAnalysis.h"

/////////////////////////////////////////////////////////////////////
//  MetricAnalysis.cpp -  for evaluating and displaying the size   //
//                      and complexity of all functions            //
//  ver 1.0                                                        //
//  Language:      Visual C++ 2008, SP1                            //
//  Platform:      Dell XPS 15, Windows 7 Home Edition             //
//  Application:   Code Parser with AST for CSE687 Pr2, Sp16       //
//  Author:		   Sushant Garg, Syracuse University		       //
//  Source:        Jim Fawcett, CST 4-187, Syracuse University     //
//                 (315) 443-3948, jfawcett@twcny.rr.com           //
/////////////////////////////////////////////////////////////////////

//Indentation to show the AST
void Metric::display(element* elem)
{
	static size_t indentation = 0;
	std::cout << "\n  " << std::string(3 * indentation, '_') << "[" + elem->name + "," + elem->type + "]";
	auto iter = elem->childNode.begin();
	++indentation;
	while (iter != elem->childNode.end())
	{
		display(*iter);
		++iter;
	}
	--indentation;
}

//Traversing the tree 
void Metric::preOrderTraversal(element* root)
{
	if (root == NULL) { return; }

	else {
		if (root->type == "function") {
			std::cout << "\n" << "Metrics of : " << root->name << std::endl;
			std::cout << "-----------------------------------" << std::endl;
			std::cout << "\n" << "Name: " << root->name << std::endl;
			std::cout << "Type: " << root->type << std::endl;
			std::cout << "Start Line: " << root->startLine << std::endl;
			std::cout << "End Line: " << root->endLine << std::endl;
			std::cout << "Total Lines: " << root->lineCount << std::endl;
			std::cout << "Complexity: " << root->complexity << std::endl;
			std::cout << "\n" << "---------------------------" << std::endl;
		
		}
		for (int i = 0; i < root->childNode.size(); i++)
		{
			preOrderTraversal(root->childNode.at(i));
		}
		return;
	}

}
