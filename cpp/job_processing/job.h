#pragma once

#include <string>

enum class Status
{
    Pending,
    Running,
    Failed,
    Completed
};

enum class JobResult
{
    Success,
    JobNotFound,
    InvalidTransition,
    RetryLimitReached
};

struct Job
{
    std::string job_id;
    std::string job_name;
    int retry_count;
    int threshold;

    Job(std::string job_id, std::string job_name,
        int retry_count, int threshold);

    JobResult start();
    JobResult complete();
    JobResult fail();
    JobResult retry();

    Status get_status() const;
    std::string status_text() const;

private:
    Status status = Status::Pending;

    JobResult transition_to(Status new_status);
};
