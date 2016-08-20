#include "PDepExecutive.h"

void Dependency::testFile(std::string path, std::vector<std::string> patterns)
{
	Task tasks(path, patterns);
}

int main(int argc,char* argv[]) {
	std::vector<std::string> patterns;
	Dependency d;
	std::string path;

	if (argc > 1) {
		path = argv[1];
		for (int i = 2; i < argc; i++)
		{
			patterns.push_back(argv[i]);
		}
		d.testFile(argv[1], patterns);
	
	}
	else

	std::cout << "Wrong path or patterns";
	return 0;
	
}
