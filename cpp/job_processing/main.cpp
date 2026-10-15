#include <iostream>
#include <string>
#include <array>
#include <utility>
#include "job.h"
#include "job_manager.h"

void print_job(const Job &job)
{
    std::cout << "Job " << job.job_id << ": " << job.job_name << "\n";
    std::cout << "Retries: " << job.retry_count << "\n";
    std::cout << "Status: " << job.status_text() << "\n";
}

int main()
{
    JobManager manager;
    std::array<Job, 3> jobs_array = {Job("job-123", "backup database", 0, 10),
                                     Job("job-124", "clean logs", 0, 10),
                                     Job("job-125", "run worker", 0, 10)};

    for (auto &job : jobs_array)
    {
        manager.add_job(std::move(job));
    }

    std::array<std::string, 3> start_jobs = {"job-123", {"job-124"}, "job-125"};

    for (const std::string &job_id : start_jobs)
    {
        JobResult started = manager.start_job(job_id);
        if (started == JobResult::Success)
        {
            std::cout << "Job: " << job_id << " Started " << job_result_text(started) << "\n";
        }
    }

    std::array<std::string, 1> fail_jobs = {"job-124"};

    for (std::string &job_id : fail_jobs)
    {
        JobResult failed = manager.fail_job(job_id);
        if (failed == JobResult::Success)
        {
            std::cout << "Job: " << job_id << " failed " << job_result_text(failed) << "\n";
        }
    }

    std::array<std::string, 3> jobs = {"job-123", "job-124", "job-125"};

    for (std::string &job_id : jobs)
    {
        const Job *job = manager.get_job(job_id);
        if (job != nullptr)
        {
            print_job(*job);
        }
        else
        {
            std::cout << "Job not found\n";
        }
    }

    std::cout << "######################################\n";

    std::array<std::string, 1> retry_jobs = {"job-124"};

    for (const std::string &job_id : retry_jobs)
    {
        JobResult retry = manager.retry_job(job_id);
        if (retry == JobResult::Success)
        {
            std::cout << "Job: " << job_id << " retry started " << job_result_text(retry) << "\n";
        }
    }

    std::array<std::string, 3> jobs1 = {"job-123", "job-124", "job-125"};

    for (const std::string &job_id : jobs1)
    {
        const Job *job = manager.get_job(job_id);
        if (job != nullptr)
        {
            print_job(*job);
        }
        else
        {
            std::cout << "Job not found\n";
        }
    }

    return 0;
}
