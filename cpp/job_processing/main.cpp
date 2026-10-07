#include <iostream>
#include <string>

struct Job
{
    std::string job_id;
    std::string job_name;
    int retry_count;
};

void print_job(Job job)
{
    std::cout << "Job " << job.job_id << ": " << job.job_name << "\n";
    std::cout << "Retries: " << job.retry_count << "\n";
}

int main()
{
    Job job;
    job.job_id = "job-123";
    job.job_name = "backup database";
    job.retry_count = 0;
    print_job(job);
    return 0;
}
