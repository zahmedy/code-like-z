#include <iostream>
#include <string>
#include <vector>

enum class Status
{
    Pending,
    Running,
    Failed,
    Completed
};

struct Job
{
    std::string job_id;
    std::string job_name;
    int retry_count;
    Status status = Status::Pending;

    std::string status_text() const
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

    bool start()
    {
        if (status == Status::Pending)
        {
            status = Status::Running;
            return true;
        }
        else
        {
            return false;
        }
    }
};

void print_job(const Job &job)
{
    std::cout << "Job " << job.job_id << ": " << job.job_name << "\n";
    std::cout << "Retries: " << job.retry_count << "\n";
    std::cout << "Status: " << job.status_text() << "\n";
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
