package main

func busyWork() {
	total := 0

	for i := 0; i < 100_000_000; i++ {
		total += i
	}

	_ = total
}
