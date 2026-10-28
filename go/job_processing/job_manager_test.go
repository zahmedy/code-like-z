package main

import "testing"

func TestGetJob(t *testing.T) {
	jm := NewJobManager()
	job := Job{JobID: "job-123", JobName: "Clean database"}
	jm.AddJob(&job)
	j, ok := jm.GetJob("job-123")

	if ok != true {
		t.Fail()
	}
	if j.JobID != "job-123" {
		t.Fail()
	}
}
