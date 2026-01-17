// core/main.cpp
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib> // for atoi, atof

#include "VectorScheduleTable.h"
#include "GreedyShiftScheduler.h"
#include "StaffManagerImpl.h"

using namespace std;

// A helper to manually print JSON so Python can read it easily
void printJSON(const VectorScheduleTable& schedule, const StaffManagerImpl& mgr, int staffCount, int dayCount, double rate) {
    cout << "---JSON_START---" << endl;
    cout << "{" << endl;
    
    // Print Schedule Matrix
    cout << "  \"schedule\": [" << endl;
    for (int s = 0; s < staffCount; ++s) {
        cout << "    [";
        for (int d = 0; d < dayCount; ++d) {
            cout << (schedule.isAssigned(s, d) ? 1 : 0);
            if (d < dayCount - 1) cout << ", ";
        }
        cout << "]";
        if (s < staffCount - 1) cout << ",";
        cout << endl;
    }
    cout << "  ]," << endl;

    // Print Salaries and Stats
    cout << "  \"staff_stats\": [" << endl;
    for (int s = 0; s < staffCount; ++s) {
        cout << "    {" << endl;
        cout << "      \"id\": " << s + 1 << "," << endl;
        cout << "      \"work_days\": " << mgr.getWorkDays(s) << "," << endl;
        cout << "      \"off_days\": " << mgr.getOffDays(s) << "," << endl;
        cout << "      \"salary\": " << mgr.staffSalary(s, rate) << endl;
        cout << "    }";
        if (s < staffCount - 1) cout << ",";
        cout << endl;
    }
    cout << "  ]" << endl;

    cout << "}" << endl;
    cout << "---JSON_END---" << endl;
}

int main(int argc, char* argv[]) {
    // We expect 4 arguments: ./prog <staff> <days> <minOff> <rate>
    if (argc < 5) {
        cerr << "Error: Not enough arguments provided." << endl;
        return 1;
    }

    int staffCount = atoi(argv[1]);
    int dayCount = atoi(argv[2]);
    int minOffDays = atoi(argv[3]);
    double rate = atof(argv[4]);

    // Initialize System
    VectorScheduleTable schedule;
    StaffManagerImpl staffMgr;
    staffMgr.initialize(staffCount, dayCount, minOffDays);

    GreedyShiftScheduler scheduler;
    scheduler.setStaffCount(staffCount);
    scheduler.setDayCount(dayCount);
    scheduler.setMinimumDaysOff(minOffDays);

    // Run Logic
    scheduler.generateSchedule(schedule, staffMgr);

    // Output Data for Python
    printJSON(schedule, staffMgr, staffCount, dayCount, rate);

    return 0;
}