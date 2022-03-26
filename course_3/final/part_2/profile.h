#pragma once
/*-------------------------DESCRIPTION-------------------
Here is a code block, which allow you to get a time of work your program.
-------------------------------------------------------*/
#include <chrono>
#include <iostream>
#include <string>

using namespace std;
using namespace std::chrono;

class LogDuration {
public:
	LogDuration(const string& msg) : message(msg + ": "), start(steady_clock::now()) {
	}

	~LogDuration() {
		steady_clock::time_point end = steady_clock::now();
		auto duration = end - start;
		cerr << message << duration_cast<milliseconds>(duration).count() << " ms " << endl;
	}
private:
	string message;
	steady_clock::time_point start;
};

#define UNIQ_ID_1(line) a_local_var_name_##line
#define UNIQ_ID(line) UNIQ_ID_1(line)

#define LOG_DURATION(message) LogDuration UNIQ_ID(__LINE__){message};
