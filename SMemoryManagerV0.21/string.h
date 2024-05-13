#pragma once
namespace o2system
{
	#define NOT_DEFINED -1
	#define SIZE_NAME 20
	#define EOS '\0'

	char* to_pchar(int number);
	size_t strlen(const char* pString);
	char* strcpy(const char* pNameSource);
};

