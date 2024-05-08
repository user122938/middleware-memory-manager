#pragma once

/**
   *
   * @brief Object Interface
   * @date 2024-05-02
   * @version 0.21
   *
   */
class IObject
{
public:
	virtual int getId() = 0;
	virtual char* getNameClass() = 0;
	virtual char* getNameObject() = 0;
};

