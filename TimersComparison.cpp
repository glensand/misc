#include <chrono>
#include <intrin.h>
#include <iostream>

#include "Windows.h"

static double compute_seconds_per_cycle()
{
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);
	return 1.0 / frequency.QuadPart;
}

static const double SecPerCycle = compute_seconds_per_cycle();

static FORCEINLINE double seconds()
{
	LARGE_INTEGER Cycles;
	QueryPerformanceCounter(&Cycles);

	// add big number to make bugs apparent where return value is being passed to float
	return Cycles.QuadPart * SecPerCycle + 16777216.0;
}

int main()
{
	// measure time needed to measure time using std timer
	{
		auto start_win_timer = seconds();

        	auto&& begin = std::chrono::steady_clock::now();
		auto&& end = std::chrono::steady_clock::now();
		volatile auto delta = std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count();
		
		auto end_win_timer = seconds();

		std::cout << "Time difference(win) = " << 1000000.0 * (end_win_timer - start_win_timer) << "[mcs]" << std::endl;
	}

	// measure time needed to measure time using cpu-based timer :D
	{

		auto begin = seconds();

		auto start_win_timer = seconds();
		auto end_win_timer = seconds();
		volatile auto delta = end_win_timer - start_win_timer;

		auto end = seconds();

		std::cout << "Time difference(win) = " << 1000000.0 * (end - begin) << "[mcs]" << std::endl;
	}
	
	return 0;
}
