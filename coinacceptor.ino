#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <EEPROM.h>

#define OLED_RESET LED_BUILTIN  //4
Adafruit_SSD1306 display(OLED_RESET);

const int coinPin =  D3;
int coinsChange = 0;   
volatile float coinValue, coinSum = 0.00;
unsigned long pulseMili;
int eeprom_addr = 0;

void setup() {
  if (!Serial) {
    Serial.begin(115200);
  }
  pinMode(coinPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(coinPin), coinInserted, RISING);   

  EEPROM.begin(512);
  coinSum = EEPROM.read(eeprom_addr);
   
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Willkommen");
  display.println("bei MILI");
  display.println("Bitte werfen");
  display.println("Sie Geld ein");
  display.display();
}

void loop() {
  if (millis() - pulseMili > 1500 && coinValue != 0.0) 
  {
    display.clearDisplay();
    display.display();
    display.setCursor(0,0);
    display.println("Willkommen");
    display.println("bei MILI");

    Serial.print("Einwurf: ");
    Serial.print(coinValue);
    Serial.println(" Euro");

    display.print("Einwurf: ");
    display.print(coinValue);
    display.println(" Euro");

    coinSum += coinValue;
    coinValue = 0.0;
    EEPROM.write(eeprom_addr, coinSum);
    
    Serial.print("Summe: ");
    Serial.print(coinSum);
    Serial.println(" Euro");

    display.print("Summe: ");
    display.print(coinSum);
    display.println(" Euro");
    display.display();
  }
}

void coinInserted()    
{
  pulseMili = millis();
  coinValue += 0.05;
}
