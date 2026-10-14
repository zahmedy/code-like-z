#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <array>
#include <unordered_map>

enum class Status
{
    Pending,
    Running,
    Failed,
    Completed
};

// Job class/struct starts
struct Job
{
    std::string job_id;
    std::string job_name;
    int retry_count;

    Job(std::string job_id, std::string job_name, int retry_count)
        : job_id(std::move(job_id)),
          job_name(std::move(job_name)),
          retry_count(retry_count)
    {
    }

    Status get_status() const
    {
        return status;
    }

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
        return transition_to(Status::Running);
    }
    bool complete()
    {
        return transition_to(Status::Completed);
    }
    bool fail()
    {
        return transition_to(Status::Failed);
    }

private:
    Status status = Status::Pending;

    bool transition_to(Status new_status)
    {
        switch (status)
        {
        case Status::Running:
            if (new_status == Status::Completed || new_status == Status::Failed)
            {
                status = new_status;
                return true;
            }
            return false;
        case Status::Pending:
            if (new_status == Status::Running)
            {
                status = new_status;
                return true;
            }
            return false;
        case Status::Completed:
            return false;
        case Status::Failed:
            return false;
        }
        return false;
    }
};
// Job class/struct end

// JobManager class/struct start

struct JobManager
{
    bool add_job(Job job)
    {
        auto [it, added] = jobs.try_emplace(job.job_id, std::move(job));
        return added;
    }

    Job *get_job(const std::string &job_id)
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

    const Job *get_job(const std::string &job_id) const
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

    bool start_job(const std::string &job_id)
    {
        Job *job_ptr = get_job(job_id);

        if (job_ptr != nullptr)
        {
            return job_ptr->start();
        }

        return false;
    }
    bool complete_job(const std::string &job_id)
    {
        Job *job_ptr = get_job(job_id);

        if (job_ptr != nullptr)
        {
            return job_ptr->complete();
        }

        return false;
    }
    bool fail_job(const std::string &job_id)
    {
        Job *job_ptr = get_job(job_id);

        if (job_ptr != nullptr)
        {
            return job_ptr->fail();
        }

        return false;
    }

private:
    std::unordered_map<std::string, Job> jobs;
};

// JobManager class/struct end

void print_job(const Job &job)
{
    std::cout << "Job " << job.job_id << ": " << job.job_name << "\n";
    std::cout << "Retries: " << job.retry_count << "\n";
    std::cout << "Status: " << job.status_text() << "\n";
}

int main()
{
    JobManager manager;
    std::array<Job, 3> jobs_array = {Job("job-123", "backup database", 0),
                                     Job("job-124", "clean logs", 0),
                                     Job("job-125", "run worker", 0)};

    for (const auto &job : jobs_array)
    {
        manager.add_job(job);
    }

    std::array<std::string, 3> start_jobs = {"job-123", "job-125"};

    for (const std::string &job_id : start_jobs)
    {
        bool started = manager.start_job(job_id);
        if (started == true)
        {
            std::cout << "Job: " << job_id << " Started\n";
        }
    }

    std::array<std::string, 3> jobs = {"job-123", "job-124", "job-125"};

    for (const std::string &job_id : jobs)
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
