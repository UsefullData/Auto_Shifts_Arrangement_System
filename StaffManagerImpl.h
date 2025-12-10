#ifndef STAFF_MANAGER_IMPL_H
#define STAFF_MANAGER_IMPL_H
#include "IStaffManager.h"
#include <vector>
class StaffManagerImpl : public IStaffManager {
private:
 int staffCount=0;
 int dayCount=0;
 int minOffDays=0;

 std::vector<int> workDays;
 std::vector<int> offDays;


public:
    StaffManagerImpl() = default;
    ~StaffManagerImpl() override = default;

    void initialize(int staffCount, int dayCount, int minOffDays) override;

    void addWorkDay(int staffID) override;
    void addOffDay(int staffID) override;
    int getWorkDays(int staffID) const override;
    int getOffDays(int staffID) const override;
    bool canWork(int staffID, int remainingDays) const override; 
}; 

#endif

