package main

import "fmt"

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
	Status     Status
}

func (j *Job) Start() {
	if j.Status != Pending {
		fmt.Println("Can't Start a non pending job.", j.JobID)
	}
	j.Status = Running
	fmt.Println("Starting", j.JobID)
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
