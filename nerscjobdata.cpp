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

#include <string>

#include "nerscjobdata.h"
#include "pdsfjob.h"

namespace NEWT {

NERSCJobData::NERSCJobData()
{
}

void NERSCJobData::Reset(){
    fPDSFJobs.clear();
}

void NERSCJobData::InsertPDSFJob(PDSFJob &job){
    fPDSFJobs.push_back(job);
}

std::vector<PDSFJob> NERSCJobData::GetJobsForUser(std::string username, JobClass jobclass){
    std::string runtags[] = {"dr", "r"},
            pendtags[] = {"qw", "hqw"};
    std::vector<PDSFJob> outjobs;
    for(std::vector<PDSFJob>::iterator jobiter = fPDSFJobs.begin(); jobiter != fPDSFJobs.end(); ++jobiter){
        if(jobiter->GetUser().compare(username)) continue;          // not same user
        bool found = false;
        std::string jobstatus = jobiter->GetJobStatus();
        switch(jobclass){
        case kRunning:
            for(unsigned int itag = 0; itag < sizeof(runtags)/sizeof(std::string); itag++){
                if(!runtags[itag].compare(jobstatus)){
                    found = true;
                    break;
                }
            }
            break;
        case kPending:
            for(unsigned int itag = 0; itag < sizeof(pendtags)/sizeof(std::string); itag++){
                if(!pendtags[itag].compare(jobstatus)){
                    found = true;
                    break;
                }
            }
            break;
        case kAll:
            found = true;
            break;
        }
        if(!found) continue;
        outjobs.push_back(*jobiter);
    }
    return outjobs;
}

}
