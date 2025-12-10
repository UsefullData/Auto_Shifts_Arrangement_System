#include "GreedyShiftScheduler.h"
#include <iostream>

void GreedyShiftScheduler::setStaffCount(int m) {
    staffCount = m;
}

void GreedyShiftScheduler::setDayCount(int n) {
    dayCount = n;
}

void GreedyShiftScheduler::setMinimumDaysOff(int k) {
    minDaysOff = k;
}

void GreedyShiftScheduler::setDailyRequirements(const std::vector<int>& requirements) {
    dailyReq = requirements;
}

void GreedyShiftScheduler::generateSchedule(IScheduleTable& schedule) {
    // Loop through each day
    for (int d = 0; d < dayCount; d++) {

        int required = dailyReq[d];

        // Assign the first available staff
        for (int s = 0; s < staffCount && required > 0; s++) {

            // assign(staffID, dayID)
            schedule.assign(s, d);

            required--;
        }
    }
}

bool GreedyShiftScheduler::validate(const IScheduleTable& schedule) const {
    for (int d = 0; d < dayCount; d++) {
        int workers = schedule.countWorkersOnDay(d);
        if (workers < dailyReq[d]) return false;
    }
    return true;
}
