#define VR_PIN A0

#define SW_PIN_1 3
#define SW_PIN_2 2

#define LED_PIN_1 13
#define LED_PIN_2 12

#define RGB_RED 9
#define RGB_GREEN 10
#define RGB_BLUE 11

#define DHT_SSN 4
#define LHT_SSN 1
void setup() {
    Serial.begin(9600);
}

int tmp_cnt= 0;
int adc_val= 0;
int dht_val = 0;
int light_val = 0;

void loop() {
    while(1) {
        adc_val= analogRead(VR_PIN);
        dht_val = analogRead(DHT_SSN);
        light_val = analogRead(LHT_SSN);
        light_val = map(light_val, 0, 1023, 0 , 50);
        // adc_val = adc_val/1023*255;
        adc_val = map(adc_val, 0, 1023, 0, 255);
        Serial.println("["+String(++tmp_cnt)+"] dht = "+String(dht_val));
        // delay(10);
        Serial.println("["+String(++tmp_cnt)+"] light = "+String(light_val));
        // Serial.println(adc_val);
        delay(100);
        analogWrite(RGB_BLUE, light_val);
    }
}