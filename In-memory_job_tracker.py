from dataclasses import dataclass 

@dataclass
class Job:
    job_id: int
    status: str
    retry_count: int
    error_message: str