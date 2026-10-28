package main

import (
	"errors"
	"fmt"
)

type Status string

const (
	Pending   Status = "pending"
	Running   Status = "running"
	Failed    Status = "failed"
	Completed Status = "completed"
)

type Job struct {
	JobID      string
	JobName    string
	RetryCount int
	RetryLimit int
	Status     Status
}

type JobManager struct {
	Jobs map[string]*Job
}

func NewJobManager() *JobManager {
	return &JobManager{
		Jobs: make(map[string]*Job),
	}
}

func (jm *JobManager) AddJob(j *Job) bool {
	if _, ok := jm.Jobs[j.JobID]; ok {
		fmt.Println("Job exists, existing...")
		return false
	}

	jm.Jobs[j.JobID] = j
	return true
}

func (jm *JobManager) GetJob(jobID string) (*Job, bool) {
	if job, ok := jm.Jobs[jobID]; ok {
		return job, true
	}

	return nil, false
}

func (jm *JobManager) StartJob(jobID string) error {
	if job, ok := jm.GetJob(jobID); ok {
		if job.Start() {
			return nil
		}

		return errors.New("job will not start")
	}

	return errors.New("job not found")
}

func (j *Job) Start() bool {
	if j.Status != Pending {
		fmt.Println("Can't Start a non pending job.", j.JobID)
		return false
	}
	j.Status = Running
	fmt.Println("Starting", j.JobID)
	return true
}

func (j *Job) Fail() bool {
	if j.Status != Running {
		fmt.Println("Only running jobs can fail")
		return false
	}
	j.Status = Failed
	return true
}

func (j *Job) Retry() bool {
	if j.Status != Failed {
		fmt.Println("Only failed jobs can be retried")
		return false
	}
	if j.RetryCount >= j.RetryLimit {
		fmt.Println("Retry limit reached, can't rerun the job")
		return false
	}
	j.Status = Running
	j.RetryCount++
	return true
}

func (j *Job) Complete() bool {
	if j.Status != Running {
		fmt.Println("Only running jobs can be completed")
		return false
	}
	j.Status = Completed
	return true
}

func main() {
	job := Job{
		JobID:      "job-123",
		JobName:    "backup db",
		RetryCount: 0,
		Status:     Pending,
	}
	fmt.Println(job.Status)
	job.Start()
	fmt.Println(job.Status)
}
