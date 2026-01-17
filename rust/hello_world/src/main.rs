use std::{thread::sleep, time::Duration};

struct LedController {
    led_on: bool,
    on_time_ms: u64,
    off_time_ms: u64,
    counter: u64,
}

impl LedController {
    pub fn new(period_ms: u64, duty_cycle: u64) -> Self {
        let on_time_ms = period_ms * duty_cycle / 100;
        let off_time_ms = period_ms - on_time_ms;
        LedController { led_on: false, on_time_ms, off_time_ms, counter: 0 }
    }

    fn tick(&mut self, tick_len_ms: u64) {
        self.counter += tick_len_ms;

        if (self.led_on && self.counter >= self.on_time_ms) || (!self.led_on && self.counter >= self.off_time_ms) {
            self.led_on = !self.led_on;
            self.counter = 0;
        }
    }

    fn state(&self) -> bool {
        self.led_on
    }
}

fn main() {
    let tick_len_ms = 1;
    let period_ms = 1000;
    let duty_cycle = 10; // percentage
    let mut num_cycles = 10;

    let mut led_controller = LedController::new(period_ms, duty_cycle);

    loop{
        let state = led_controller.state();
        sleep(Duration::from_millis(tick_len_ms));
        led_controller.tick(tick_len_ms);

        if state != led_controller.state() {
            println!("LED is now {}", if led_controller.state() { "ON" } else { "OFF" });
            
            if led_controller.state() == false {
                num_cycles -= 1;
                if num_cycles == 0 {
                    break;
                }
            }
        }
    }
}