package main

import "fmt"

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
