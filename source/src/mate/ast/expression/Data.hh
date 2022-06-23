#pragma once

#include <string>
#include <iostream>

namespace mate::ast::expression {

enum class Type{ 
	INT,
	BOOL,
	STRING,
	DOUBLE,
	_NULL
};

union Value {
	long double doubleVal;
	long long intVal;
	bool boolVal;
};

class Data {

private:
	Value _value;
    Type _type;
	std::string stringVal;

public:
	static Data* _NULL;
	Data();
	Data(long double val);
	Data(long long val);
	Data(bool val);
	Data(std::string val);

	~Data();

	long double getDouble();
	long long getInt();
	bool getBool();
	std::string getString();

	void setVal(long double val);
	void setVal(long long val);
	void setVal(bool val);
	void setVal(std::string s);

	Type type();
	std::string typeAsString();
	std::string valueAsString();

	static Data* ofDouble(long double val){
		return new Data(val);
	}

	static Data* ofInt(long long val){
		return new Data(val);
	}

	static Data* ofBool(bool val){
		return new Data(val);
	}

	static Data* ofString(std::string val){
		return new Data(val);
	}

};

} /* end namespace mate::ast::expression */
