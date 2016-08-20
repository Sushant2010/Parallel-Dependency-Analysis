#ifndef TASK_H
#define TASK_H

#include "../Threadpool/BlockingQueue.h"
#include "../ThreadPool/ThreadPool.h"
#include "../Parser/ConfigureParser.h"
#include "../Parser/TypeTable.h"
#include "../FileMngr/FileMgr.h"
#include <vector>

class Task
{
public:
	Task(std::string, std::vector<std::string>);
	void getwork();
	void end() { _blkQ->enQ("EndofFM"); }
	//TypeTable<TypeTableRecord> MergeTables();
private:
	BlockingQueue<std::string>* _blkQ;
	std::vector<std::string> _patterns;
	std::string _path;
	std::vector<TypeTable<TypeTableRecord>*> TypeTables;
	TypeTable<TypeTableRecord> MergedTypeTbl;
	std::string trimPath(std::string fullpath);
};

#endif // !TASK_H