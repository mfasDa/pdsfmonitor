/***************************************************************************
 * Simple monitoring program for the PDSF cluster at NERSC using NEWT.     *
 * Copyright (C) 2015  Markus Fasel, Lawrence Berkeley National Laboratory *
 *                                                                         *
 * This program is free software: you can redistribute it and/or modify    *
 * it under the terms of the GNU General Public License as published by    *
 * the Free Software Foundation, either version 3 of the License, or       *
 * (at your option) any later version.                                     *
 *                                                                         *
 * This program is distributed in the hope that it will be useful,         *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
 * GNU General Public License for more details.                            *
 *                                                                         *
 * You should have received a copy of the GNU General Public License       *
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.   *
 ***************************************************************************/

#ifndef PDSFJOB_H
#define PDSFJOB_H

#include <string>
#include <ctime>

namespace NEWT{

class PDSFJob
{
public:
    PDSFJob();
    ~PDSFJob() {}

    std::string GetUser() const { return fUser; }
    std::string GetJobName() const { return fName; }
    std::string GetQueue() const { return fQueue; }
    std::string GetJobStatus() const { return fStatus; }
    float       GetPriority() const { return fPriority; }
    int         GetJobID() const { return fJobID; }
    struct tm   GetStartTime() const { return fStartTime; }
    void        GetSlots(int &min, int &max){
        min = fSlots[0];
        max = fSlots[1];
    }

    void SetJobStatus(const std::string &value) { fStatus = value; }
    void SetUser(const std::string &value) { fUser = value; }
    void SetJobName(const std::string &value) { fName = value; }
    void SetQueue(const std::string &value) { fQueue = value; }
    void SetPriority(float priority) { fPriority = priority; }
    void SetJobID(int jobid) { fJobID = jobid; }
    void SetSlots(int start, int end){
        fSlots[0] = start;
        fSlots[1] = end;
    }
    void SetStartTime(const struct tm &starttime) { fStartTime = starttime; }
    void SetStartTime(int year, int month, int day, int hours, int minutes, int seconds){
        fStartTime.tm_year = year - 1900;
        fStartTime.tm_mon = month - 1;
        fStartTime.tm_mday = day;
        fStartTime.tm_hour = hours;
        fStartTime.tm_min = minutes;
        fStartTime.tm_sec = seconds;
    }

private:
    int                         fJobID;
    std::string                 fUser;
    std::string                 fName;
    std::string                 fQueue;
    std::string                 fStatus;
    float                       fPriority;
    int                         fSlots[2];
    struct tm                   fStartTime;
};

}
#endif // PDSFJOB_H
