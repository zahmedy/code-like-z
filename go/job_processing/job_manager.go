package main

import (
	"context"
	"errors"
	"fmt"
	"sync"
	"time"
)

var ErrJobNotFound = errors.New("job not found")
var ErrJobCannotStart = errors.New("job cannot start")

type JobManager struct {
	Jobs   map[string]*Job
	Logger Logger
	Queue  chan *Job
	mu     sync.RWMutex
}

func NewJobManager(logger Logger) *JobManager {
	return &JobManager{
		Jobs:   make(map[string]*Job),
		Logger: logger,
		Queue:  make(chan *Job, 10),
	}
}

func (jm *JobManager) AddJob(j *Job) bool {
	jm.mu.Lock()
	defer jm.mu.Unlock()

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
			jm.Queue <- job
			return nil
		}

		jm.Logger.Log("job cannot start")
		return ErrJobCannotStart
	}

	jm.Logger.Log("job not found")
	return ErrJobNotFound
}

func (jm *JobManager) Worker(ctx context.Context, workerID int) {
	for {
		select {
		case job, ok := <-jm.Queue:
			if !ok {
				return
			}
			select {
			case <-time.After(1 * time.Second):
				jm.Logger.Log("finished " + job.JobID)

			case <-ctx.Done():
				fmt.Println(ctx.Err())
				jm.Logger.Log("cancelled " + job.JobID)
				return
			}
		case <-ctx.Done():
			fmt.Println(ctx.Err())
			jm.Logger.Log("worker stopping")
			return
		}
	}
}
