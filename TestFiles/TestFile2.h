#include <iostream>
#include "../AST/element.h"

struct ASTInterface
{
	element *rootNode;
	element* recentElement;

public:
	virtual element* Root() = 0;
	virtual element* searchParent(element) = 0;
	virtual void setRoot(element) = 0;
	virtual void addChildNode(element node) = 0;
	virtual void setRecentElement(element node) = 0;

};