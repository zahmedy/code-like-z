#include "job.h"
#include <utility>

Job::Job(std::string job_id, std::string job_name, int retry_count, int threshold) : job_id(std::move(job_id)),
                                                                                     job_name(std::move(job_name)),
                                                                                     retry_count(retry_count),
                                                                                     threshold(threshold)
{
}

std::string Job::status_text() const
{
    switch (status)
    {
    case Status::Pending:
        return "Pending";
    case Status::Running:
        return "Running";
    case Status::Failed:
        return "Failed";
    case Status::Completed:
        return "Completed";
    }
    return "Unknown";
}

Status Job::get_status() const
{
    return status;
}

JobResult Job::start()
{
    return transition_to(Status::Running);
}
JobResult Job::complete()
{
    return transition_to(Status::Completed);
}
JobResult Job::fail()
{
    return transition_to(Status::Failed);
}
JobResult Job::retry()
{
    return transition_to(Status::Running);
}

JobResult Job::transition_to(Status new_status)
{
    switch (status)
    {
    case Status::Running:
        if (new_status == Status::Completed || new_status == Status::Failed)
        {
            status = new_status;
            return JobResult::Success;
        }
        return JobResult::InvalidTransition;
    case Status::Pending:
        if (new_status == Status::Running)
        {
            status = new_status;
            return JobResult::Success;
        }
        return JobResult::InvalidTransition;
    case Status::Completed:
        return JobResult::InvalidTransition;
    case Status::Failed:
        if (new_status != Status::Running)
        {
            return JobResult::InvalidTransition;
        }

        if (retry_count >= threshold)
        {
            return JobResult::RetryLimitReached;
        }

        status = Status::Running;
        retry_count++;
        return JobResult::Success;
    }
    return JobResult::InvalidTransition;
}
