#pragma once

#include "job.h"
#include <string>
#include <unordered_map>

struct JobManager
{
    bool add_job(Job job);
    Job *get_job(const std::string &job_id);
    const Job *get_job(const std::string &job_id) const;
    JobResult start_job(const std::string &job_id);
    JobResult complete_job(const std::string &job_id);
    JobResult fail_job(const std::string &job_id);
    JobResult retry_job(const std::string &job_id);

private:
    std::unordered_map<std::string, Job> jobs;
};