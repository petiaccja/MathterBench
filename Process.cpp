#include "Process.hpp"

#include <iostream>

using std::cout;
using std::endl;

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>

void SetAffinity() {
	BOOL success;
	success = SetThreadAffinityMask(GetCurrentThread(), 1) != 0;
	cout << (success ? "Thread is limited to 1st CPU core." : "Failed to set thread affinity - cycle count may be incorrect.");
	cout << endl;
}

void SetPriority() {
	BOOL success;
	success = SetPriorityClass(GetCurrentProcess(), REALTIME_PRIORITY_CLASS);
	cout << (success ? "Process set to highest priority." : "Failed to set process priority class - times may have jitter.");
	cout << endl;
	success = SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL);
	cout << (success ? "Thread set to highest priority." : "Failed to set thread priority class - times may have jitter.");
	cout << endl;
}

#elif __unix__
#include <pthread.h>
#include <sched.h>

void SetAffinity() {}

void SetPriority() {
	pthread_t this_thread = pthread_self();
	sched_param params;
	params.sched_priority = sched_get_priority_max(SCHED_FIFO);
	int ret = pthread_setschedparam(this_thread, SCHED_FIFO, &params);
	cout << (ret == 0 ? "Thread set to highest priority." : "Failed to set thread priority class - times may have jitter.");
	cout << endl
		 << endl;
}


#else

void SetAffinity() {}
void SetPriority() {}

#endif