#include "TimedTask.h"

namespace seneca {

    TimedTask::TimedTask() : numRecords(0) {}

    void TimedTask::startClock() {
        startTime = std::chrono::steady_clock::now();
    }

    void TimedTask::stopClock() {
        endTime = std::chrono::steady_clock::now();
    }

    void TimedTask::addTask(const char* taskName) {
        if (numRecords < MAX_TASKS) {
            tasks[numRecords].name = taskName;
            tasks[numRecords].units = "nanoseconds";
            tasks[numRecords].duration = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);
            ++numRecords;
        }
    }

    std::ostream& operator<<(std::ostream& os, const TimedTask& tt) {
        os<< "--------------------------\n";
        os << "Execution Times:\n";
        os << "--------------------------\n";
        for (int i = 0; i < tt.numRecords; ++i) {
            os << std::left << std::setw(21) << tt.tasks[i].name
                << std::right << std::setw(13) << tt.tasks[i].duration.count()
                << " " << tt.tasks[i].units << "\n";
        }
        os << "--------------------------\n";
        return os;
    }
}
