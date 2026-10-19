package main

import "fmt"

type Job struct {
	JobID      string
	JobName    string
	RetryCount int
}

func main() {
	job := Job{
		JobID:      "job-123",
		JobName:    "backup db",
		RetryCount: 0,
	}

	fmt.Println("Job:", job.JobID)
	fmt.Println("Name:", job.JobName)
	fmt.Println("Retries:", job.RetryCount)
}
