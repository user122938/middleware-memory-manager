#include "Main.h"
#include "MemoryManager.h"
#include "ExceptionManager.h"
#include "Exception.h"

#define SIZE_MEMORY 1024
#define SIZE_PAGE 64

int main() {
	try {
		char* pBuffer = new char[SIZE_MEMORY];
		Object::s_pMemoryManager = new MemoryManager(pBuffer, sizeof(char) * SIZE_MEMORY, SIZE_PAGE);
		printf("sizeof(MemoryManager)=%zu\n", sizeof(MemoryManager));

		Main* pMain;
		pMain = new("main") Main();
		pMain->initialize();
		pMain->run();
		pMain->finalize();
		delete pMain;
	}
	catch (Exception& exception) {
		exception.println();
		Object::s_pMemoryManager->showStatus();
		ExceptionManager::printAllExceptions();
	}
}