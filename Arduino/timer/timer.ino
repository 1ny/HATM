#include "SimpleTimer.h"

SimpleTimer timer;

#define TASK_1 2000
#define TASK_2 3000
#define TASK_3 5000
#define TIMER_INTERVAL   1000

int num = 0;

void task_1() {
  Serial.print(" #1");
}

void task_2() {
  Serial.print(" #2");
}

void task_3() {
  Serial.print(" #3");
}

void my_func() {
  Serial.print("[" + String(++num) + "]");
  if(num % (TASK_1 / 1000) == 0) {
    task_1();
  }

  if(num % (TASK_2 / 1000) == 0) {
    task_2();
  }

  if(num % (TASK_3 / 1000) == 0) {
    task_3();
  }

  Serial.println();
}

// void my_func2() {
//   Serial.println();
// }

void setup() {
  Serial.begin(9600);
  timer.setInterval(TIMER_INTERVAL, my_func);
  // timer.setInterval(TASK_1, task_1);
  // timer.setInterval(TASK_2, task_2);
  // timer.setInterval(TASK_3, task_3);
  // timer.setInterval(TIMER_INTERVAL, my_func2);
}

void loop() {
  timer.run();
}
