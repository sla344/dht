/*
* IMPLEMENTATION GOT FROM: 
* https://github.com/adafruit/Adafruit_Python_DHT/blob/master/source/Beaglebone_Black/
* AND IS PART OF ADAFRUIT's LIBRARY
* MINOR REVISIONS WERE MADE TO THE ORIGINAL IMPLEMENTATION 
* SO THAT IT CAN BE USED WITH OUR HARDWARE
*/
#include <errno.h>
#include <sched.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <stdint.h>

#include "common_dht_read.h"
// #include <linux/time.h>

// void busy_wait_milliseconds(uint32_t millis) {
//     // Calculate the number of loops needed to wait for the specified milliseconds
//     uint32_t loops = millis * 1000000 / 3; // Adjust this value according to your system's clock speed
    
//     // Perform a busy loop for the calculated number of loops
//     for (uint32_t i = 0; i < loops; i++) {
//         // This loop is optimized to waste time (and CPU)
//         // Without performing any meaningful operations
//         asm volatile ("nop");
//     }
// }
void delay_milliseconds(uint32_t millis) {
    usleep(millis * 1000); // Convert milliseconds to microseconds and delay
}

void sleep_milliseconds(uint32_t millis) {
  struct timespec sleep;
  sleep.tv_sec = millis / 1000;
  sleep.tv_nsec = (millis % 1000) * 1000000L;
  while (clock_nanosleep(CLOCK_MONOTONIC, 0, &sleep, &sleep) && errno == EINTR);
}

void set_max_priority(void) {
  struct sched_param sched;
  memset(&sched, 0, sizeof(sched));
  // Use FIFO scheduler with highest priority for the lowest chance of the kernel context switching.
  sched.sched_priority = sched_get_priority_max(SCHED_FIFO);
  sched_setscheduler(0, SCHED_FIFO, &sched);
}

void set_default_priority(void) {
  struct sched_param sched;
  memset(&sched, 0, sizeof(sched));
  // Go back to default scheduler with default 0 priority.
  sched.sched_priority = 0;
  sched_setscheduler(0, SCHED_OTHER, &sched);
}