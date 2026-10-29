package main

import (
	"context"
	"sync"
	"time"
)

func main() {
	job1 := NewJob("job-123", "clean db", 5)
	job2 := NewJob("job-124", "backup db", 5)
	job3 := NewJob("job-125", "rotate logs", 5)
	logger := &ConsoleLogger{}
	jm := NewJobManager(logger)
	var wg sync.WaitGroup

	jm.AddJob(job1)
	jm.AddJob(job2)
	jm.AddJob(job3)

	ctx, cancel := context.WithTimeout(context.Background(), 1*time.Second)
	defer cancel()
	for i := 1; i <= 3; i++ {
		wg.Add(1)
		go func(workerID int) {
			defer wg.Done()
			jm.Worker(ctx, workerID)
		}(i)
	}

	jm.StartJob(job1.JobID)
	jm.StartJob(job2.JobID)
	jm.StartJob(job3.JobID)

	close(jm.Queue)
	wg.Wait()
}
