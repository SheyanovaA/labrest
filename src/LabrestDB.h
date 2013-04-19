#ifndef __LabrestDB_H__
#define __LabrestDB_H__

#include <iostream>
#include <sqlite3.h>

namespace LabrestAPI 
{

class LabrestDB 
{

	sqlite3 *db;

	char * szErrMsg;

public:

	LabrestDB();

	~LabrestDB();

	int connect();

	int disconnect();

	int exec(::std::string SQL);

};

};

extern LabrestAPI::LabrestDB * dbPtr;


#endif /* __LabrestDB_H__ */

