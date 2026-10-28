package main

import (
	"errors"
	"fmt"
)

type JobManager struct {
	Jobs map[string]*Job
}

var ErrJobNotFound = errors.New("job not found")
var ErrJobCannotStart = errors.New("job cannot start")

func NewJobManager() *JobManager {
	return &JobManager{
		Jobs: make(map[string]*Job),
	}
}

func (jm *JobManager) AddJob(j *Job) bool {
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
			return nil
		}

		return ErrJobCannotStart
	}

	return ErrJobNotFound
}
