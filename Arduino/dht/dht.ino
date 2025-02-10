#include <DHT11.h>
#define BUZ_PIN 5

int pin=4;
DHT11 dht11(pin);

void setup() {
    Serial.begin(9600);
    // while (!Serial) {
    //     ; // wait for serial port to connect. Needed for Leonardo only
    // }
}

int tmp_cnt= 0;
int err_code= 0;
float temp= 0.0f;
float humi= 0.0f;

void dht11_read() {
    err_code=dht11.read(humi, temp);    
    delay(DHT11_RETRY_DELAY); //delay for reread    
}

void dht11_display() {
    if(err_code==0) {
        // Serial.println("["+String(++tmp_cnt)+"] dht11(temp,humi)=("+String(temp)+","+String(humi)+")");
        Serial.print(temp);
        Serial.print(',');
        Serial.println(humi);
    }
    else {
        Serial.println("\nError No :"+String(err_code));
    }    
}

void loop() {
    dht11_read();
    dht11_display();
}