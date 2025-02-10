#include <DHT11.h>
// #include <LiquidCrystal.h>

#define HDT_PIN 4
#define BUZ_PIN 5
#define RGB_RED 9
#define RGB_GREEN 10
#define RGB_BLUE 11

DHT11 dht11(HDT_PIN);
// LiquidCrystal lcd(8, 9, 4, 5, 6, 7); // select the pins used on the LCD panel

void setup() {
  Serial.begin(9600);

  // lcd.begin(16, 2); // start the library
  // lcd.setCursor(0,0); // set the LCD cursor position
  // lcd.print("LCD TEST"); // print a simple message on the LCD
}

int tmp_cnt = 0;

void loop() {
  float temp = 0;
  float humi = 0;
  int err_code = 0;

  // lcd.print("T: "); 

  err_code = dht11.read(humi, temp);
  delay(DHT11_RETRY_DELAY); //delay for reread    

  if(err_code == 0) {
    Serial.println("["+String(++tmp_cnt)+"] dht11(temp,humi)=("+String(temp)+","+String(humi)+")");
  }
  else {
    Serial.println("\nError No :"+String(err_code));
  }

#if 1
  if(temp >= 26) {
    analogWrite(RGB_BLUE, 50);
  } else if(temp >= 18) {
    analogWrite(RGB_GREEN, 50);
  } else {
    analogWrite(RGB_RED, 50);
  }
#endif
  // lcd.setCursor(0, 1);
  // lcd.print((int)temp);
}
