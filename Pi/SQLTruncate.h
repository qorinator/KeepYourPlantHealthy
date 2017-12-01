#ifndef SQLTRUNCATE_H
#define SQLTRUNCATE_H

#include "SQLInterface.h"

class SQLTruncate : public SQLInterface
{
public:
	SQLTruncate();
	void GetAction() final;
private: 
	void TruncateDailyMeasurementQuery();
};

#endif // SQLTRUNCATE_H