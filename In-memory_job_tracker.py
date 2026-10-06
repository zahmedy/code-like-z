from dataclasses import dataclass 

@dataclass
class Job:
    job_id: str
    error_message: None | str = None
    status: str = "pending"
    retry_count: int = 0
    