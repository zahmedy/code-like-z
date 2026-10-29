package main

import (
	"errors"
	"fmt"
	"sync"
	"testing"
)

func TestGetJob(t *testing.T) {
	logger := &TestLogger{}
	jm := NewJobManager(logger)
	job := NewJob("job-123", "Clean database", 5)
	jm.AddJob(job)
	j, ok := jm.GetJob("job-123")

	if ok != true {
		t.Errorf("expected job to exist")
	}
	if j.JobID != "job-123" {
		t.Errorf("expected job-123 to exist")
	}

	_, ok = jm.GetJob("job-999")

	if ok {
		t.Errorf("expected job-99 to not exist")
	}
}

func TestJobStart(t *testing.T) {
	logger := &TestLogger{}
	jm := NewJobManager(logger)
	job := NewJob("job-123", "Clean database", 5)
	jm.AddJob(job)

	err := jm.StartJob("job-123")

	if err != nil {
		t.Errorf("job did not start")
	}

	queueJob := <-jm.Queue

	if queueJob.JobID != "job-123" {
		t.Errorf("job ID should be job-123")
	}

	err = jm.StartJob("job-999")

	if !errors.Is(err, ErrJobNotFound) {
		t.Errorf("expected ErrJobNotFound, got %v", err)
	}

	err = jm.StartJob("job-123")

	if !errors.Is(err, ErrJobCannotStart) {
		t.Errorf("expected ErrJobCannotStart, got %v", err)
	}
}

type TestLogger struct {
	Messages []string
}

func (t *TestLogger) Log(message string) {
	t.Messages = append(t.Messages, message)
}

func TestStartJobWithMissingJob(t *testing.T) {
	logger := &TestLogger{}
	jm := NewJobManager(logger)
	err := jm.StartJob("job-999")

	if !errors.Is(err, ErrJobNotFound) {
		t.Fatalf("expected ErrJobNotFound, got %v", err)
	}

	if len(logger.Messages) != 1 {
		t.Fatalf("expected 1 log message, got %d", len(logger.Messages))
	}

	if logger.Messages[0] != "job not found" {
		t.Errorf("expected log message %q, got %q",
			"job not found",
			logger.Messages[0],
		)
	}
}

func TestJobManagerRace(t *testing.T) {
	logger := &TestLogger{}
	jm := NewJobManager(logger)

	var wg sync.WaitGroup

	for i := 1; i < 100; i++ {
		wg.Add(2)

		go func(i int) {
			defer wg.Done()

			job := NewJob(
				fmt.Sprintf("job-%d", i),
				"test job",
				3,
			)

			jm.AddJob(job)
		}(i)

		go func(i int) {
			defer wg.Done()

			jm.GetJob(fmt.Sprintf("job-%d", i))
		}(i)
	}

	wg.Wait()
}
