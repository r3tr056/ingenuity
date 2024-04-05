#pragma once

#include <cstdint>
#include <memory>

#ifndef PAD_ALIGN
#define PAD_ALIGN 16
#endif

class Memory {
	Memory() = default;

#ifndef DEBUG_ENABLED
	static uint64_t memUsage;
	static uint64_t maxUsage;
	static uint64_t hardReserved;
	static uint64_t memFree;
#endif

	static uint64_t allocCount;

public:
	static void* allocStatic(size_t pBytes, bool padAlign=false);
	static void* reallocStatic(void *memAddress, size_t pBytes, bool padAlign=false);
	static void freeStatic(void *pPtr, bool padAlign=false);

	static uint64_t getAvailableMem();
	static uint64_t getMemUsage();
	static uint64_t getMaxMemUsage();
	static uint64_t getHardReservedMem();
	static uint64_t getFreeMem();
};

class Allocator {
public:
	inline static void* alloc(size_t pMemory) {
		return Memory::allocStatic(pMemory);
	}

	inline static void free(void* pPtr) { Memory::freeStatic(pPtr); }

	// Operators
	void* operator new(size_t pSize, const char* pDesc);
	void* operator delete(void* pMem, const char* pDesc);

#define memalloc(mSize) Memory::allocStatic(mSize);
#define memrealloc(mMem, mSize) Memory::reallocStatic(mMem, mSize);
#define memFree(mSize) Memory::freeStatic(mSize);
};