from dataclasses import dataclass 

@dataclass
class Job:
    job_id: str
    error_message: None | str = None
    status: str = "pending"
    retry_count: int = 0
    status_transitions = {
        "pending": {"running"},
        "running": {"completed", "failed"},
        "failed": {"pending"},
        "completed": set()
    }

    def update_status(self, new_status: str):
        if new_status in self.status_transitions[self.status]:
            self.status = new_status
        else:
            raise ValueError("Only pending, running, completed, and failed are accepted")

    def retry(self):
        if self.status != "failed":
            raise ValueError("Only failed jobs can be retried")

        self.status = self.status_transitions[self.status]
        self.retry_count += 1
        self.error_message = None