/**
 * @file benchmark.cpp
 *
 * @date Apr 3 2012
 * @author stefan
 * @brief Micro benchmarks
 */

#include <raykernel.h>
#include <video/VideoStream.h>
#include <video/KernelVideo.h>

#include "benchmark.h"
#include "sha1.h"

using namespace Kernel;


inline UINT64 ReadTSC() {
	UINT32 eax, edx;
	UINT64 result;
	
	__asm__ __volatile__("rdtsc":"=a"(eax), "=d"(edx));
	result = edx;
	result <<= 32;
	return result + eax;
}

#define BENCHBODY(x...) UINT64 totalTime = 0; \
	for(UINT32 test = 0; test < 100; test++) \
	{ \
		UINT64 startTime = ReadTSC(); \
		x \
		;\
		totalTime += ReadTSC() - startTime; \
	} \
	return totalTime / 100;	

static UINT64 BenchmarkEmptyBody()
{
	BENCHBODY( );
}

static UINT64 BenchmarkDepBody()
{
	BENCHBODY(int a = 0, b = 0, c = 0;
	a = b + c;
	b = a + c;
	c = b + a;
	a++;
	b++;
	c++);
}

void SomeFunction()
{
	
}

static UINT64 BenchmarkCallBody()
{
	BENCHBODY(SomeFunction(););
}

static UINT64 BenchmarkLoopBody()
{
	BENCHBODY(for(int i = 0; i < 100; i++); );
}

static UINT64 BenchmarkBubble()
{
	unsigned char* a = new unsigned char[1024];
	// Bubble sort
	
	BENCHBODY(
	int n = 1024;
	do
	{
	int newn = 0;
		
	for(int i = 0; i < n-1; i++)
	{
		if(a[i] > a[i+1])
		{
			// swap
			unsigned char temp = a[i];
			a[i] = a[i+1];
			a[i+1] = temp;
			newn = i + 1;
		}
	}
	n = newn;
	} while ( n > 1);
	);
	
	delete[] a;
}
	

static UINT64 BenchmarkSHA1()
{
	UINT32 bufferSize = 1024; // 1 KB
	unsigned char* buffer = new unsigned char[bufferSize]; 
	
	BENCHBODY(SHA1Context con;
	SHA1Reset(&con);
	SHA1Input(&con, buffer, bufferSize);
	);
	
	delete[] buffer;
}

void Benchmark()
{
	UINT64 emptyBody = BenchmarkEmptyBody();
	UINT64 depBody = BenchmarkDepBody();
	UINT64 callBody = BenchmarkCallBody();
	UINT64 loopBody = BenchmarkLoopBody();
	UINT64 sha1 = BenchmarkSHA1();
	UINT64 bubble = BenchmarkBubble();
	
	kout << "loop for 9999 iterations took:(cycles)" << VideoStream::endl;	
	kout << "Empty body     : " << (UINT32)(emptyBody & 0xFFFFFFFF) << VideoStream::endl;
	kout << "Dependecy body : " << (UINT32)(depBody & 0xFFFFFFFF) << VideoStream::endl;
	kout << "Func. call body: " << (UINT32)(callBody & 0xFFFFFFFF) << VideoStream::endl;
	kout << "loop body      : " << (UINT32)(loopBody & 0xFFFFFFFF) << VideoStream::endl;
	kout << "SHA-1          : " << (UINT32)(sha1 & 0xFFFFFFFF) << VideoStream::endl;
	kout << "Bubble Sort    : " << (UINT32)(bubble & 0xFFFFFFFF) << VideoStream::endl;
}

