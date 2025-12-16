#ifndef GREEDYSHIFTSCHEDULER_H
#define GREEDYSHIFTSCHEDULER_H

#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>

#include "IScheduleTable.h"
#include "IShiftScheduler.h"
#include "StaffManagerImpl.h"

using namespace std;

class GreedyShiftScheduler : public IShiftScheduler {
private:
    // Core parameters
    int staffCount = 0;
    int dayCount = 0;
    int minOffDays = 0;
    int dailyRequirements = 0; // <=0 means "auto-calculate"

    // Keep the last generated schedule so main() can query extras later
    const IScheduleTable* schedulePtr = nullptr;

    // Track work/off counts for the last generated schedule
    StaffManagerImpl staffMgr;

    // Heap helper structures
    struct StaffNode {
        int id;
        int worked;
        int remaining;
    };

    struct StaffCompare {
        bool operator()(const StaffNode& a, const StaffNode& b) const {
            if (a.worked != b.worked)
                return a.worked > b.worked;        // fewer worked first
            if (a.remaining != b.remaining)
                return a.remaining < b.remaining;  // more remaining first
            return a.id > b.id;                    // smaller id first (tie-break)
        }
    };


    void calculateDailyRequirements();

public:
    GreedyShiftScheduler() = default;
    virtual ~GreedyShiftScheduler() = default;

    void setStaffCount(int m) override;
    void setDayCount(int n) override;
    void setMinimumDaysOff(int k) override;
    void setDailyRequirements(const int& requirements) override;

    void generateSchedule(IScheduleTable& schedule) override;

    // ✅ one-parameter emergency query (valid only AFTER generateSchedule)
    vector<int> extraStaff(int dayID) const;
    bool hasExtraStaff(int dayID) const;

    bool validate(const IScheduleTable& schedule) const override;
};

#endif // GREEDYSHIFTSCHEDULER_H
