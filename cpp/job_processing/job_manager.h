#pragma once

#include "job.h"
#include "job_logger.h"
#include <string>
#include <unordered_map>
#include <memory>

struct JobExecutor
{
    void execute(Job &job);
};

struct JobManager
{
    explicit JobManager(JobLogger &logger, std::unique_ptr<JobExecutor> executor);

    bool add_job(Job job);
    Job *get_job(const std::string &job_id);
    const Job *get_job(const std::string &job_id) const;

    JobResult start_job(const std::string &job_id);
    JobResult complete_job(const std::string &job_id);
    JobResult fail_job(const std::string &job_id);
    JobResult retry_job(const std::string &job_id);

private:
    JobLogger &logger;
    std::unordered_map<std::string, Job> jobs;
    std::unique_ptr<JobExecutor> job_executor;
};