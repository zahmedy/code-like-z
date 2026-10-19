package main

import "fmt"

type Job struct {
	JobID      string
	JobName    string
	RetryCount int
}

func (j *Job) Start() {
	fmt.Println("Starting", j.JobID)
}

func main() {
	job := Job{
		JobID:      "job-123",
		JobName:    "backup db",
		RetryCount: 0,
	}

	job.Start()
}
