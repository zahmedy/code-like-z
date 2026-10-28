package main

import (
	"fmt"
	"sync"
)

func main() {
	job := NewJob("job-123", "clean db", 5)
	logger := &ConsoleLogger{}
	jm := NewJobManager(logger)
	var wg sync.WaitGroup

	fmt.Println(job.Status)

	jm.AddJob(job)

	fmt.Println(job.Status)

	wg.Add(1)
	go func() {
		defer wg.Done()
		jm.Worker()
	}()

	jm.StartJob(job.JobID)

	close(jm.Queue)

	wg.Wait()

	fmt.Println(job.Status)

}
