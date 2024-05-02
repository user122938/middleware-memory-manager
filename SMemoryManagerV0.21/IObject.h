#pragma once
class IObject
{
public:
	virtual int getId() = 0;
	virtual char* getNameClass() = 0;
	virtual char* getNameObject() = 0;
};

