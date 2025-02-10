#include "SimpleTimer.h"

SimpleTimer timer;

#define LED_1_PIN    (13)
#define TIMER_INTERVAL   1000

void my_func() {
    static int val= 1;
    Serial.print("Uptime(s): ");
    Serial.println(millis() / 1000);
    digitalWrite(LED_1_PIN, val);
    val ^= 0x01;
}

void setup() {
    Serial.begin(9600);
    pinMode(LED_1_PIN, OUTPUT);
    timer.setInterval(TIMER_INTERVAL, my_func);
}

void loop() {
    //timer.update();
    timer.run();
}
