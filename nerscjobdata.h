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
