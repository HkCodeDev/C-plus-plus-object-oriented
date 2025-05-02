/*****************************************************************************
                  Workshop - #2 (Part - 2)>
Full Name : Hoda Karimi
Student ID# : 138611223
 Email : hkarimi9@myseneca.ca
 Section : NAA
 File: TimedTask.cpp
 Date:
    Authenticity Declaration :
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider.This submitted
piece of work is entirely of my own creation.
* ****************************************************************************/
#include "TimedTask.h"

namespace seneca {
    // Constructor initializes the number of records to 0
    TimedTask::TimedTask() : numRecords(0) {}
    // Starts the timer by recording the current time
    void TimedTask::startClock() {
        startTime = std::chrono::steady_clock::now();
    }
    // Stops the timer by recording the current time
    void TimedTask::stopClock() {
        endTime = std::chrono::steady_clock::now();
    }
    // Adds a new task to the record array after stopping the timer
    void TimedTask::addTask(const char* taskName) {
        // Check if there is space to add a new task
        if (numRecords < MAX_TASKS) {
            // Set task name
            tasks[numRecords].name = taskName;
            // Set units to nanoseconds
            tasks[numRecords].units = "nanoseconds";
            // Calculate and store the duration in nanoseconds
            tasks[numRecords].duration = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);
            ++numRecords;// Increment the count of recorded tasks
        }
    }
    // Overloads the output stream operator to print all tasks
    std::ostream& operator<<(std::ostream& os, const TimedTask& tt) {
        os << "--------------------------\n";
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
