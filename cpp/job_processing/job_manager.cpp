#include "job_manager.h"
#include <utility>

bool JobManager::add_job(Job job)
{
    auto [it, added] = jobs.try_emplace(job.job_id, std::move(job));
    return added;
}

Job *JobManager::get_job(const std::string &job_id)
{
    const auto it = jobs.find(job_id);

    if (it != jobs.end())
    {
        return &it->second;
    }
    else
    {
        return nullptr;
    }
}

const Job *JobManager::get_job(const std::string &job_id) const
{
    const auto it = jobs.find(job_id);

    if (it != jobs.end())
    {
        return &it->second;
    }
    else
    {
        return nullptr;
    }
}

JobResult JobManager::start_job(const std::string &job_id)
{
    Job *job_ptr = get_job(job_id);

    if (job_ptr != nullptr)
    {
        return job_ptr->start();
    }

    return JobResult::JobNotFound;
}
JobResult JobManager::complete_job(const std::string &job_id)
{
    Job *job_ptr = get_job(job_id);

    if (job_ptr != nullptr)
    {
        return job_ptr->complete();
    }

    return JobResult::JobNotFound;
}
JobResult JobManager::fail_job(const std::string &job_id)
{
    Job *job_ptr = get_job(job_id);

    if (job_ptr != nullptr)
    {
        return job_ptr->fail();
    }

    return JobResult::JobNotFound;
}
JobResult JobManager::retry_job(const std::string &job_id)
{
    Job *job_ptr = get_job(job_id);

    if (job_ptr != nullptr)
    {
        return job_ptr->retry();
    }

    return JobResult::JobNotFound;
}