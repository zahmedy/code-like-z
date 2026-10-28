package main

import "testing"

func TestJob(t *testing.T) {
	j := Job{JobID: "job-123", JobName: "Clean logs",
		RetryCount: 3, RetryLimit: 5, Status: Pending}

	if j.JobID != "job-123" {
		t.Errorf("name should be job-123")
	}
}
