#include "DependencyAnalysis.h"

DependencyAnalysis::DependencyAnalysis(Toker* pToker, TypeTable<TypeTableRecord>* Ttable, std::string file) : _pToker(pToker),_typeTable(Ttable),_file(file)
{
	mapDep = new std::unordered_map<std::string, std::vector<std::string>>();
}

std::string DependencyAnalysis::getToke()
{
	if (_pToker == nullptr)
		throw(std::logic_error("No toker ref"));
	return _pToker->getTok();
}

void DependencyAnalysis::dependency()
{
	while (true)
	{	
		std::string token = getToke();
		if (token == "")
			break;
		else
			compare(token);

	}
}

void DependencyAnalysis::showDependency()
{
	for (auto record : *mapDep) {
		std::cout << record.first << " is dependent on ";
		for (auto vc : record.second)
			std::cout << vc << "  ";
		std::cout << "\n";
	}
}

void DependencyAnalysis::compare(std::string tok)
{
	for (auto type : *_typeTable) {
		if (tok.compare(type.name())==0 && tok.compare("main")!=0)
		{
			if (_file.compare(type.fileName()) != 0) {
				std::string fileName = type.fileName();
				std::vector<std::string> vec1;
				if (!mapDep->count(_file))
				{
					vec1.push_back(fileName);
					mapDep->insert(std::make_pair(_file, vec1));
				}
				else
				{
					vec1 = mapDep->at(_file);
					if (std::find(vec1.begin(), vec1.end(), fileName) != vec1.end())
						break;
					else
						mapDep->at(_file).push_back(fileName);
				}
			}
			else
				break;
		}
	
	}
}
