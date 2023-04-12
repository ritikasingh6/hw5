
#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#endif

// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;




// Add prototypes for any helper functions here
bool backtrack(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched, 
		map<size_t, size_t>& workerShifts, 
		int scheduling,
    const size_t day
);


// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below
		sched.resize(avail.size(), vector<Worker_T>(dailyNeed, INVALID_ID));

		for (unsigned int i = 0; i < avail.size(); i++){
			sched[i].resize(dailyNeed, -1);
		}

		map<size_t, size_t> workerShifts;
		for (size_t w = 0; w < avail[0].size(); ++w){
			workerShifts.insert(make_pair(w, 0));
		}


		return backtrack(avail, dailyNeed, maxShifts, sched, workerShifts, 0, 0);

}

bool backtrack(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched, 
		map<size_t, size_t>& workerShifts, 
		int scheduling,
    const size_t day
){
    if (day == avail.size()){
        return true;
    }

    if (scheduling == static_cast<int>(dailyNeed)){
			return backtrack(avail, dailyNeed, maxShifts, sched, workerShifts, 0, day + 1);
		}
		else{
			for (Worker_T w = 0; w < avail[day].size(); ++w){
				if (avail[day][w] == 1 && find(sched[day].begin(), sched[day].end(), w) == sched[day].end() && 
				workerShifts.find(w) -> second < maxShifts){
					sched[day][scheduling] = w;
					workerShifts.find(w) -> second++;
					if (backtrack(avail, dailyNeed, maxShifts, sched, workerShifts, scheduling + 1, day)){
						return true;
					}
					else{
						sched[day][scheduling] = -1;
						workerShifts.find(w) -> second--;
					}
				}
			}
		}
    return false;
}



