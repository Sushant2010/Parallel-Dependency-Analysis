#include "MetricTestExecutive.h"

/////////////////////////////////////////////////////////////////////
//  MetricTestExecutive.cpp -  Test suite that exercises all of      //
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
void MetricTestExecutive::fileManagerTest(std::string path, std::vector<std::string> patterns)
{
	DataStore ds;
	FileMgr fm(path, ds);
	std::vector<std::string> files;
	for (std::string str : patterns) {
		fm.addPattern(str);
	}
	fm.search();
	
	files = fm.getFiles();
	for (std::string str:files){
		parserTest(str);
	}

}

void MetricTestExecutive::parserTest(std::string file)
{
	std::string fileSpec;
	fileSpec = FileSystem::Path::getFullFileSpec(file);
	ConfigParseToConsole configure;
	Parser* pParser = configure.Build();
	AST* tree = configure.tree;

	std::cout << "Path provided:" << fileSpec << std::endl;

	try
	{
		if (pParser) {
			if (!configure.Attach(file)) {
				std::cout << "\n Couldn't open file : " << fileSpec << std::endl;
			}
		}
		else

			std::cout << "\n Parser not built yet" << std::endl;
		
		while (pParser->next())
			pParser->parse();
		Metric metanalysis;
        std::string filename = fileSpec.substr(fileSpec.find_last_of("/\\") + 1);

		std::cout << "\n" << "For File : " << filename << std::endl;
		std::cout << "\n" << "ABSTRACT SYNTAX TREE" << std::endl;
		std::cout << "--------------------" << std::endl;
		metanalysis.display(tree->Root());
		std::cout << "\n" << std::endl;
		std::cout << "\n" << "METRIC ANALYSIS" << std::endl;
		std::cout << "---------------" << std::endl;
		

		metanalysis.preOrderTraversal(tree->Root());
		std::cout << "\n";
	}
	catch (std::exception& ex)
	{
		std::cout << "\n\n    " << ex.what() << "\n\n";
	}
}
*/
int main(int argc, char* argv[]) {
		
	std::vector<std::string> patterns;
	MetricTestExecutive m;
	for (int i = 2; i < argc; i++)
	{
		patterns.push_back(argv[i]);
	}
	m.fileManagerTest(argv[1], patterns);
	return 0;
	
}
