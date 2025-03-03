// utilities :D
package util

import "github.com/hellory4n/stellarthing/modules/platform"

// timer. useful for when you want to wait for something
type Timer struct {
	// how long the timer lasts, in seconds
	Duration float64
	// how much time is left, in seconds
	TimeLeft float64
	// if true, the timer repeats when it's over
	Loop bool
	// if true, the timer is currently timing
	Playing bool
	// called when the timer ends
	Timeout func()
}

var timers []*Timer

// makes a new timer. note you have to manually start it and give it a timeout function
func NewTimer(duration float64, loop bool) *Timer {
	timer := &Timer{Duration: duration, Loop: loop, TimeLeft: duration}
	timers = append(timers, timer)
	return timer
}

// starts the timer :)
func (t *Timer) Start() {
	t.Playing = true
	t.TimeLeft = t.Duration
}

// stops the timer :)
func (t *Timer) Stop() {
	t.Playing = false
	t.TimeLeft = t.Duration
}

// as the name implies, it updates all timers
func UpdateAllTimers() {
	for _, timer := range timers {
		if !timer.Playing {
			continue
		}

		timer.TimeLeft -= platform.DeltaTime()
		
		if timer.TimeLeft < 0.01 {
			timer.Timeout()

			if timer.Loop {
				timer.TimeLeft = timer.Duration
			}
		}
	}
}