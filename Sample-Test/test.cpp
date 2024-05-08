#include "pch.h"
#include "../SMemoryManagerV0.21/MemoryManager.h"
#include "../SMemoryManagerV0.21/Object.h"

#include "./TestObject.h"

#define SIZE_MEMORY 1024
#define SIZE_PAGE 64
#define SIZE_SLOT 16
#define SIZE_INSTANCE 64UL

static size_t normalizeSize(size_t size) {
	size_t size1 = size >> 4;
	size_t size2 = size1 << 4;
	size = ((size == size2) ? size1 : ++size1) << 4;
	return size;
}
TEST(MemoryManagerTest, PageSizeEqualsAllocatedMemory1) {
	//memory = page = slot = object
	char* pBuffer = new char[SIZE_MEMORY];
	Object::s_pMemoryManager = new MemoryManager(pBuffer, sizeof(char) * SIZE_MEMORY, SIZE_MEMORY);
	TestObject* object = new(SIZE_MEMORY, "1") TestObject();
	EXPECT_EQ(object->getSizeSlot(), SIZE_MEMORY);
}
TEST(MemoryManagerTest, PageSizeEqualsAllocatedMemory2) {
	//memory = page = slot > object
	char* pBuffer = new char[SIZE_MEMORY];
	Object::s_pMemoryManager = new MemoryManager(pBuffer, sizeof(char) * SIZE_MEMORY, SIZE_MEMORY);
	TestObject* object = new(SIZE_MEMORY - 1, "1") TestObject();
	EXPECT_EQ(object->getSizeSlot(), normalizeSize(SIZE_MEMORY - 1));
}
TEST(MemoryManagerTest, PageSizeEqualsAllocatedMemory3) {
	//memory = page = slot < object
	char* pBuffer = new char[SIZE_MEMORY];
	Object::s_pMemoryManager = new MemoryManager(pBuffer, sizeof(char) * SIZE_MEMORY, SIZE_MEMORY);
	EXPECT_THROW(new(SIZE_MEMORY + 1, "1") TestObject(); , Exception);
}
TEST(MemoryManagerTest, PageSizeSmallerThenAllocatedMemory1) {
	//memory > page = slot = object
	char* pBuffer = new char[SIZE_MEMORY];
	Object::s_pMemoryManager = new MemoryManager(pBuffer, sizeof(char) * SIZE_MEMORY, SIZE_PAGE);
	TestObject* object = new(SIZE_PAGE, "1") TestObject();
	EXPECT_EQ(object->getSizeSlot(), SIZE_PAGE);
}
TEST(MemoryManagerTest, PageSizeSmallerThenAllocatedMemory2) {
	//memory > page = slot > object
	char* pBuffer = new char[SIZE_MEMORY];
	Object::s_pMemoryManager = new MemoryManager(pBuffer, sizeof(char) * SIZE_MEMORY, SIZE_PAGE);
	TestObject* object = new(SIZE_PAGE-1, "1") TestObject();
	EXPECT_EQ(object->getSizeSlot(), normalizeSize(SIZE_PAGE - 1));
}
TEST(MemoryManagerTest, PageSizeSmallerThenAllocatedMemory3) {
	//memory > page = slot < object
	char* pBuffer = new char[SIZE_MEMORY];
	Object::s_pMemoryManager = new MemoryManager(pBuffer, sizeof(char) * SIZE_MEMORY, SIZE_PAGE);
	TestObject* object = new(SIZE_PAGE + 1, "1") TestObject();
	EXPECT_EQ(object->getSizeSlot(), normalizeSize(SIZE_PAGE + 1));
}
TEST(MemoryManagerTest, PageSizeLargerThenAllocatedMemory1) {
	//memory < page = slot = object
	//exception
	char* pBuffer = new char[SIZE_MEMORY];
	Object::s_pMemoryManager = new MemoryManager(pBuffer, sizeof(char) * SIZE_MEMORY, 2*SIZE_MEMORY);
	EXPECT_THROW(new(2 * SIZE_MEMORY, "1") TestObject();, Exception);
}
TEST(MemoryManagerTest, PageSizeLargerThenAllocatedMemory2) {
	//memory < page = slot < object
	//exception
	char* pBuffer = new char[SIZE_MEMORY];
	Object::s_pMemoryManager = new MemoryManager(pBuffer, sizeof(char) * SIZE_MEMORY, 2 * SIZE_MEMORY);
	EXPECT_THROW(new(2 * SIZE_MEMORY + 1, "1") TestObject(); , Exception);
}
TEST(MemoryManagerTest, PageSizeLargerThenAllocatedMemory3) {
	//memory < page = slot > object
	//exception
	char* pBuffer = new char[SIZE_MEMORY];
	Object::s_pMemoryManager = new MemoryManager(pBuffer, sizeof(char) * SIZE_MEMORY, SIZE_MEMORY);
	EXPECT_THROW(new(2 * SIZE_MEMORY - 1, "1") TestObject(); , Exception);
}
