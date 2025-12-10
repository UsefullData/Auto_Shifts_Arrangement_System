#include "GreedyShiftScheduler.h"

void GreedyShiftScheduler::setStaffCount(int m) {
    staffCount = m;
}

void GreedyShiftScheduler::setDayCount(int n) {
    dayCount = n;
}

void GreedyShiftScheduler::setMinimumDaysOff(int k) {
    minOffDays = k;
}

void GreedyShiftScheduler::setDailyRequirements(const vector<int>& requirements) {
    dailyRequirements = requirements;
}

// Greedy algorithm to assign shifts automatically
void GreedyShiftScheduler::generateSchedule(VectorScheduleTable& schedule) {
    vector<int> workDays(staffCount, 0); // tracks how many days each staff member is assigned

    for (int day = 0; day < dayCount; ++day) {
        int workersAssigned = 0;

        // Assign staff to meet daily requirements
        for (int staff = 0; staff < staffCount && workersAssigned < dailyRequirements[day]; ++staff) {
            if (!schedule.isAssigned(staff, day) && workDays[staff] < (dayCount - minOffDays)) {
                schedule.assign(staff, day);
                workDays[staff]++;
                workersAssigned++;
            }
        }

        // Optional: assign extra staff if available
        for (int staff = 0; staff < staffCount && workersAssigned < staffCount; ++staff) {
            if (!schedule.isAssigned(staff, day) && workDays[staff] < (dayCount - minOffDays)) {
                schedule.assign(staff, day);
                workDays[staff]++;
                workersAssigned++;
            }
        }
    }
}
