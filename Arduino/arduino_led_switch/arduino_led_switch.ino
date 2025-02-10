const int LED = 9;

int i = 0;
float volt = 0.0;

void setup() {
    Serial.begin(9600);
    pinMode(LED,OUTPUT);
}

void loop() {
    for(i=0; i<100; i++)   {
        analogWrite(LED,i);
        volt = i / 255 * 5;
        Serial.println(String(volt));
        delay(10);
    }

    for(i=100; i>0; i--) {
        analogWrite(LED,i);
        volt = i / 255 * 5;
        Serial.println(String(volt));
        delay(10);
    }
} 