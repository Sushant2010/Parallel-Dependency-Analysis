#include "TypeTable.h"

using namespace Utilities;
using Utils = StringHelper;



#ifdef TEST_TYPETABLE

void main()
{
	Utils::Title("MT4Q1 - TypeTable");
	putline();

	TypeTable<TypeTableRecord> table;

	TypeTableRecord record;
	record.name() = "X";
	record.type() = "class";
	record.fileName() = "X.h";
	record.addNameSpace("TypeAnalysis");
	record.addNameSpace("MT4");

	table.addRecord(record);

	record.name() = "fun";
	record.type() = "method";
	record.fileName() = "X.h";
	record.addNameSpace("TypeAnalysis");
	record.addNameSpace("MT4");

	table.addRecord(record);

	showTypeTable(table);
	std::cout << "\n\n";
}

#endif // TEST_TYPETABLE