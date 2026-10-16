#include "job_logger.h"

JobLogger::JobLogger(const std::string &filename)
    : file(filename) {
      };

void JobLogger::log(const std::string &message)
{
    file << message << "\n";
}