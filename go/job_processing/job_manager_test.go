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

func TestJobStart(t *testing.T) {
	jm := NewJobManager()
	job := Job{JobID: "job-123", JobName: "Clean logs", Status: Pending}
	jm.AddJob(&job)

	err := jm.StartJob("job-123")

	if err != nil {
		t.Errorf("job did not start")
	}

	err = jm.StartJob("job-999")

	if err == nil {
		t.Errorf("non existing job started")
	}
}
