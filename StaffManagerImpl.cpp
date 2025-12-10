#include "StaffManagerImpl.h"

void StaffManagerImpl::initialize(int staffCount, int dayCount, int minOffDays) {
    this->staffCount = staffCount;
    this->dayCount = dayCount;
    this->minOffDays = minOffDays;

    // Initialize workDays and offDays for each staff member to 0
    workDays.assign(staffCount, 0);
    offDays.assign(staffCount, 0);

}
void StaffManagerImpl::addWorkDay(int staffID) {
    if (staffID >= 0 && staffID < staffCount) {
        workDays[staffID]++;
    }
}
void StaffManagerImpl::addOffDay(int staffID) {
    if (staffID >= 0 && staffID < staffCount) {
        offDays[staffID]++;
    }
}

