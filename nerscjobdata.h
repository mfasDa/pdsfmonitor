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

#ifndef NERSCJOBDATA_H
#define NERSCJOBDATA_H

#include <vector>

namespace NEWT{

class PDSFJob;

class NERSCJobData
{
public:
    enum JobClass{
        kRunning = 0,
        kPending = 1,
        kAll = 3
    };

    NERSCJobData();

    std::vector<PDSFJob> GetJobsForUser(std::string username, JobClass jobclass);

    void InsertPDSFJob(PDSFJob &job);
    void Reset();

protected:
    std::vector<PDSFJob>                  fPDSFJobs;
};

}

#endif // NERSCJOBDATA_H
