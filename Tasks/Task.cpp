#include "Task.h"


Task::Task(std::string path, std::vector<std::string> patterns)
{
	_patterns = patterns;
	_path = path;
	_blkQ = new BlockingQueue<std::string>();
	getwork();
}

void Task::getwork()
{
	std::string file;
	ProcessWorkItem<std::string> _ThreadPool(4);
	_ThreadPool.start();

	WorkItem<std::string> fileSearch = [&]()
	{
		std::cout << "thread ID : " << std::this_thread::get_id() << "\t" << "File Manager" << "\n";
		FileMgr fm(_path, _blkQ);
		for (auto pat : _patterns)
			fm.addPattern(pat);
		fm.search();
		end();
		return "";
	};

	WorkItem<std::string> parseFile = [&]()
	{
		ConfigParseToConsole configure(trimPath(file));
		Parser* pParser = configure.Build();

		if (pParser)
		{
			if (!configure.Attach(file))
				std::cout << "\n  could not open file " << file << std::endl;
		}
		else
			std::cout << "\n\n  Parser not built\n\n";

		// now that parser is built, use it

		while (pParser->next())
			pParser->parse();

		TypeTables.push_back(configure.getTypeTable());
		std::cout << "thread ID : " << std::this_thread::get_id() << "\t" << file << "\n";
		return "";
	};

	WorkItem<std::string> mergeTables = [&]()
	{
		for (auto tbl : TypeTables)
			MergedTypeTbl = MergedTypeTbl.Merge(MergedTypeTbl, *tbl);

		std::cout << "\n" << "Merged Type Table" << "\t" << "thread ID : " << std::this_thread::get_id() << "\n";
		std::cout << "====================";
		MergedTypeTbl.showTypeTable(MergedTypeTbl);
		return "";
	};

	_ThreadPool.doWork(&fileSearch);

	while (true)
	{
		if (_blkQ != NULL && _blkQ->size() > 0)
		{
			std::string top = _blkQ->deQ();
			if (top.compare("EndofFM") == 0)
			{
				_ThreadPool.doWork(&mergeTables);
				_ThreadPool.doWork(nullptr);
				std::this_thread::sleep_for(std::chrono::seconds(1));
				break;
			}
			else
			{
				file = top;
				_ThreadPool.doWork(&parseFile);
				std::this_thread::sleep_for(std::chrono::seconds(1));
			}
		}
	}
	_ThreadPool.wait();
}

//TypeTable<TypeTableRecord> Task::MergeTables()
//{
//	for (auto tbl : TypeTables)
//		MergedTypeTbl.Merge(MergedTypeTbl, *tbl);
//	return MergedTypeTbl;
//}

std::string Task::trimPath(std::string fullpath)
{
	const size_t last_slash_idx = fullpath.find_last_of("\\/");
	if (std::string::npos != last_slash_idx)
	{
		fullpath.erase(0, last_slash_idx + 1);
	}
	return fullpath;
}