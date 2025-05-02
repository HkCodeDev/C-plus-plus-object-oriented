#ifndef TIMEDTASK_H
#define TIMEDTASK_H

#include <chrono>
#include <string>
#include <iostream>
#include <iomanip>

namespace seneca {
    const int MAX_TASKS = 10;

    struct Task {
        std::string name;
        std::string units;
        std::chrono::nanoseconds duration;

        Task() : name(""), units("nanoseconds"), duration(0) {}
    };

    class TimedTask {
        int numRecords;
        Task tasks[MAX_TASKS];
        std::chrono::steady_clock::time_point startTime;
        std::chrono::steady_clock::time_point endTime;

    public:
        TimedTask();
        void startClock();
        void stopClock();
        void addTask(const char* taskName);
        friend std::ostream& operator<<(std::ostream& os, const TimedTask& tt);
    };
}
#endif // TIMEDTASK_H
