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
    Start,
    complete,
    fail,
    retry
};

struct Job
{
    Job(std::string job_id, std::string job_name,
        int retry_count, int threashold);

    JobResult start();
    JobResult complete();
    JobResult fail();
    JobResult retry();

private:
    Status status = Status::Pending;

    JobResult transition_to(Status new_status);
};