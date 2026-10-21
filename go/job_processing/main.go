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

func (j *Job) Start() bool {
	if j.Status != Pending {
		fmt.Println("Can't Start a non pending job.", j.JobID)
		return false
	}
	j.Status = Running
	fmt.Println("Starting", j.JobID)
	return true
}

func (j *Job) Complete() bool {
	if j.Status != Running {
		fmt.Println("Only running process can be completed")
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
