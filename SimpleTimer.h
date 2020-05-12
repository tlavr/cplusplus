#pragma once
#include <chrono>
#include <iostream>

class SimpleTimer {
public:
	SimpleTimer();

	~SimpleTimer();

private:
	std::chrono::time_point<std::chrono::steady_clock> start, end;
	std::chrono::duration<float> duration;
};
