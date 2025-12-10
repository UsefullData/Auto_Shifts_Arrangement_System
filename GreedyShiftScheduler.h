#ifndef GREEDY_SHIFT_SCHEDULER_H
#define GREEDY_SHIFT_SCHEDULER_H

#include "IShiftScheduler.h"

class GreedyShiftScheduler : public IShiftScheduler {
public:
    GreedyShiftScheduler() = default;
    ~GreedyShiftScheduler() override = default;

    void setStaffCount(int m) override;
    void setDayCount(int n) override;
    void setMinimumDaysOff(int k) override;
    void setDailyRequirements(const std::vector<int>& requirements) override;

    void generateSchedule(IScheduleTable& schedule) override;

    bool validate(const IScheduleTable& schedule) const override;

private:
    int staffCount = 0;
    int dayCount = 0;
    int minDaysOff = 0;
    std::vector<int> dailyReq;
};

#endif
