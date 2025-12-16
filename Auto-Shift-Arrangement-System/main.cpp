#include <iostream>
#include "VectorScheduleTable.h"
#include "GreedyShiftScheduler.h"

using namespace std;

int main() {
    int staffCount, dayCount, minOffDays;

    cout << "Enter number of staff: ";
    cin >> staffCount;

    cout << "Enter number of days: ";
    cin >> dayCount;

    cout << "Enter minimum days off per staff: ";
    cin >> minOffDays;

    if (staffCount <= 0 || dayCount <= 0) {
        cout << "Error: staffCount and dayCount must be positive.\n";
        return 0;
    }
    if (minOffDays < 0 || minOffDays > dayCount) {
        cout << "Error: minOffDays must be between 0 and dayCount.\n";
        return 0;
    }

    VectorScheduleTable schedule;
    GreedyShiftScheduler scheduler;

    scheduler.setStaffCount(staffCount);
    scheduler.setDayCount(dayCount);
    scheduler.setMinimumDaysOff(minOffDays);

    // Optional: scheduler.setDailyRequirements(x);
    // If you don't set it, it auto-calculates.

    scheduler.generateSchedule(schedule);

    if (!scheduler.validate(schedule)) {
        cout << "\nGenerated schedule is INVALID.\n";
        return 0;
    }

    cout << "\nAutomatically generated schedule:\n";
    schedule.print();

    // Emergency query loop
    while (true) {
        int day;
        cout << "\nCheck extra staff for which day? (1.." << dayCount << ", 0=exit): ";
        cin >> day;

        if (!cin) break;
        if (day == 0) break;

        if (day < 1 || day > dayCount) {
            cout << "Invalid day.\n";
            continue;
        }

        auto extras = scheduler.extraStaff(day - 1); // convert to 0-based dayID

        if (extras.empty()) {
            cout << "No extra staff available for day " << day << ".\n";
        } else {
            cout << "Extra staff candidates for day " << day << " (staff IDs): ";
            for (int id : extras) cout << (id + 1) << " "; // print 1-based
            cout << "\n";
        }

        char ch;
        cout<<"Do you want assign extra staff:(y/n):";
        cin>>ch;

        if (ch == 'y' || ch == 'Y') {
            if (!extras.empty()) schedule.assign(extras[0], day - 1);    
        }
    }

    schedule.print();


    return 0;
}
