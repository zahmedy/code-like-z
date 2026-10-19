package main

import "fmt"

type Job struct {
	JobID      string
	JobName    string
	RetryCount int
}

func main() {
	jobID := "job-123"
	jobName := "backup db"
	retryCount := 0

	fmt.Println("Job:", jobID)
	fmt.Println("Name:", jobName)
	fmt.Println("Retries:", retryCount)
}
