#include <iostream>
#include <string>

void print_job(const std::string &job_id,
               const std::string &job_name,
               int retry_count)
{
    std::cout << "Job " << job_id << ": " << job_name << "\n";
    std::cout << "Retries: " << retry_count << "\n";
}

int main()
{
    std::string job_id = "job-123";
    std::string job_name = "backup database";
    int retry_count = 0;
    print_job(job_id, job_name, retry_count);
    return 0;
}
