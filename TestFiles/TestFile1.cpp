#include <queue>
#include <string>
#include <iostream>

int main(int argc, char* argv[])
{
	std::cout << "\n  Testing ConfigureParser module\n "
		<< std::string(32, '=') << std::endl;


	for (int i = 1; i < argc; ++i)
	{
		std::cout << "\n  Processing file " << argv[i];
		std::cout << "\n  " << std::string(16 + strlen(argv[i]), '-');
	}
	
	
	

	const static size_t i;
	while (i>0)
	{
		std::cout << "\n  could not open file " << argv[i] << std::endl;

		continue;
	}

	int j = 0;
	switch (j) {
	case 0:
		std::cout << "\n case 0" << std::endl;
		break;
	default:
		break;
	}

}


