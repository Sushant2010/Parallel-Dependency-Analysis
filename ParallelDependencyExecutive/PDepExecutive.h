#ifndef PDEPEXECUTIVE_H
#define PDEPEXECUTIVE_H

#include <vector>
#include "../Tasks/Task.h"

class Dependency {
public:
	void testFile(std::string path, std::vector<std::string> patterns);

};


#endif // !PDEPEXECUTIVE_H
