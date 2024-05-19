#include "Main.h"
#include "MemoryManager.h"
#include "ExceptionManager.h"
#include "Exception.h"

#define SIZE_MEMORY 1024
#define SIZE_PAGE 64

	/**
 	*
 	* @brief Main 함수
	* @details 메모리 크기 1024, 한 페이지 64로 메모리를 할당하고, Main객체를 생성하여 초기화, 실행, 종료를 수행한다.
 	* @date 2024-05-19
 	* @version 0.21
 	*
 	*/
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