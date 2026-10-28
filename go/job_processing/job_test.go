package main

import "testing"

func TestJob(t *testing.T) {
	job := NewJob("job-123", "Clean database", 5)

	if job.JobID != "job-123" {
		t.Errorf("name should be job-123")
	}
}
