#pragma once
#include "SQLType.h"

class Real : public SQLType
{
private:
	double field = 0.;

public:
	Real() = default;

	Real(double value);

	SQLType* clone() const override;

	char getType() const override;

	void getValue(const char* field);

	void setField(double value);

	double getField() const;
};


