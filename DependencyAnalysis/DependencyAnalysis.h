#ifndef DEPENDENCYANALYSIS_H
#define DEPENDENCYANALYSIS_H

#include <unordered_map>
#include <vector>
#include "../Tokenizer/Tokenizer.h"
#include "../Parser/TypeTable.h"

using namespace Scanner;

class DependencyAnalysis {
public:
	DependencyAnalysis(Toker* pToker, TypeTable<TypeTableRecord>* Ttable, std::string file);
	std::string getToke();
	DependencyAnalysis(const DependencyAnalysis&) = delete;
	DependencyAnalysis& operator=(const DependencyAnalysis&) = delete;
	void dependency();
	void showDependency();
	void compare(std::string tok);

private:	
	Toker* _pToker;
	TypeTable<TypeTableRecord>* _typeTable;
	std::vector<std::string> _tokens;
	std::unordered_map<std::string, std::vector<std::string>>* mapDep;
	std::string _file;
};



#endif // !DEPENDENCYANALYSIS_H

