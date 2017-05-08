#ifndef __config__h
#define __config__h

#include "stddef.h"
#include "stdint.h"
#include <stdbool.h>

#ifndef MOTOR_COUNT
#define MOTOR_COUNT 4
#endif

struct motor {
  int pin;
};

struct fraction {
  uint8_t n;
  uint8_t d;
};

struct timer {
  struct motor motor;
  struct fraction fraction;
};

struct timer timers[MOTOR_COUNT];

inline
void
setMotorTimer(size_t motor, uint8_t n, uint8_t d)
{
  timers[motor].fraction.n = n;
  timers[motor].fraction.d = d;
}

#endif
