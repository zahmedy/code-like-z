#include "job_manager.h"
#include "job_logger.h"
#include "job.h"
#include <utility>

JobManager::JobManager(JobLogger &logger)
    : logger(logger)
{
}

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
        JobResult started = job_ptr->start();
        logger.log(job_id + " start: " + job_result_text(started));
        return started;
    }

    logger.log(job_id + ": Job not found");
    return JobResult::JobNotFound;
}
JobResult JobManager::complete_job(const std::string &job_id)
{
    Job *job_ptr = get_job(job_id);

    if (job_ptr != nullptr)
    {
        JobResult completed = job_ptr->complete();
        logger.log(job_id + " complete: " + job_result_text(completed));
        return completed;
    }

    logger.log(job_id + ": Job not found");
    return JobResult::JobNotFound;
}
JobResult JobManager::fail_job(const std::string &job_id)
{
    Job *job_ptr = get_job(job_id);

    if (job_ptr != nullptr)
    {
        JobResult failed = job_ptr->fail();
        logger.log(job_id + " fail: " + job_result_text(failed));
        return failed;
    }

    logger.log(job_id + ": Job not found");
    return JobResult::JobNotFound;
}
JobResult JobManager::retry_job(const std::string &job_id)
{
    Job *job_ptr = get_job(job_id);

    if (job_ptr != nullptr)
    {
        JobResult retried = job_ptr->retry();
        logger.log(job_id + " retry: " + job_result_text(retried));
        return retried;
    }

    logger.log(job_id + ": Job not found");
    return JobResult::JobNotFound;
}