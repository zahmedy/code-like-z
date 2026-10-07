#include <iostream>
#include <string>
#include <vector>

enum status
{
    pending,
    running,
    failed,
    completed
};

struct Job
{
    std::string job_id;
    std::string job_name;
    int retry_count;
};

void print_job(const Job &job)
{
    std::cout << "Job " << job.job_id << ": " << job.job_name << "\n";
    std::cout << "Retries: " << job.retry_count << "\n";
}

int main()
{
    std::vector<Job> jobs;
    Job job1{"job-123", "backup database", 0};
    Job job2{"job-124", "clean logs", 0};
    Job job3{"job-125", "run worker", 0};
    jobs.push_back(job1);
    jobs.push_back(job2);
    jobs.push_back(job3);
    for (const Job &job : jobs)
    {
        print_job(job);
    }
    return 0;
}
