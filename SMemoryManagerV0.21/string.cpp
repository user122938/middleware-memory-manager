#include "string.h"

char* o2system::to_pchar(int number) {
	int numDigit = 0;
	if (number == 0) {
		numDigit = 1;
	}
	else {
		for (int digit = number; digit > 0; digit = digit / 10) {
			numDigit++;
		}
	}
	char* pNumber = new char[numDigit + 1];
	for (int i = numDigit - 1; i >= 0; i--) {
		pNumber[i] = (number % 10) + '0';
		number = number / 10;
	}
	pNumber[numDigit] = EOS;
	return pNumber;
}
size_t o2system::strlen(const char* pString) {
	size_t length = 0;
	for (const char* pElement = pString; *pElement != EOS; pElement++) {
		length++;
	}
	return length;
}
char* o2system::strcpy(const char* pNameSource) {
	size_t lengthName = (strlen(pNameSource) > SIZE_NAME ? SIZE_NAME : strlen(pNameSource));
	char* pNameDest = new char[lengthName + 1];
	for (int i = 0; i < lengthName; i++) {
		pNameDest[i] = pNameSource[i];
	}
	pNameDest[lengthName] = EOS;
	return pNameDest;
}