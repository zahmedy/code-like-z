package main

import "testing"

func TestGetJob(t *testing.T) {
	jm := NewJobManager()
	job := Job{JobID: "job-123", JobName: "Clean database"}
	jm.AddJob(&job)
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
