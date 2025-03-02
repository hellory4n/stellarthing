package core

import (
	"fmt"
	"time"
)

// simple utility to measure how much time part of some code takes to run
type Benchmark struct {
	startms int64
	// how much time it took, in milliseconds
	Result int64
}

// simple utility to measure how much time part of some code takes to run
func StartBenchmark() *Benchmark {
	var itstimetoleave int64 = time.Now().UnixMilli()
	return &Benchmark{startms: itstimetoleave, Result: -1}
}

// stops the benchmark and prints it to the screen
func (b *Benchmark) Stop() {
	var itstimetoleave int64 = time.Now().UnixMilli()
	b.Result = itstimetoleave - b.startms
	fmt.Printf("Benchmark ended; took %v ms\n", b.Result)
}