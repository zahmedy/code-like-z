package main

import "fmt"

func main() {
	job := NewJob("job-123", "clean db", 5)
	logger := &ConsoleLogger{}
	jm := NewJobManager(logger)
	fmt.Println(job.Status)
	jm.StartJob(job.JobID)
	fmt.Println(job.Status)
}
