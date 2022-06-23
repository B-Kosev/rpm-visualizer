#include "BluetoothSerial.h"
#include "ELMduino.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <NeoPixelBus.h>


BluetoothSerial SerialBT;
#define ELM_PORT   SerialBT
#define DEBUG_PORT Serial

const uint16_t PixelCount = 8;
const uint8_t PixelPin = 2;

#define Cred     RgbColor(255, 0, 0)
#define Cblue    RgbColor(0, 0, 255)
#define Cgreen   RgbColor(0, 255, 0)
#define Cyellow  RgbColor(255, 255, 0)
#define Cblack   RgbColor(0) 

ELM327 myELM327;

LiquidCrystal_I2C lcd(0x27,20,4);

NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip(PixelCount, PixelPin);

uint32_t rpm = 0;

//String MACadd = "DC:0D:30:48:8D:60";                         //enter the ELM327 MAC address
//uint8_t address[6]  = {0xDC, 0x0D, 0x30, 0x48, 0x8D, 0x60};  //enter the ELM327 MAC address after the 0x


void setup()
{
#if LED_BUILTIN
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
#endif

  Serial.println("Connecting...");
  
  Serial.begin(115200);
  while (!Serial);

  Serial.println();
  Serial.println("Initializing...");
  Serial.flush();

  strip.Begin();
  strip.Show();


  Serial.println();
  Serial.println("Running...");

  lcd.init();
  lcd.init();
  lcd.backlight();
    
  Serial.begin(115200);
//  SerialBT.setPin("1234");
  ELM_PORT.begin("ArduHUD", true);

  lcd.setCursor(0,0);
  lcd.print("Connecting...");
  
  if (!ELM_PORT.connect("OBDII"))
  {
    Serial.println("Couldn't connect to OBD scanner - Phase 1");
    lcd.setCursor(0,0);
    lcd.print("Couldn't connect ");
    lcd.setCursor(0,1);
    lcd.print("to OBD scanner");
    while(1);
  }

  if (!myELM327.begin(ELM_PORT, true, 2000))
  {
    Serial.println("Couldn't connect to OBD scanner - Phase 2");
    lcd.setCursor(0,0);
    lcd.print("Couldn't connect");
    lcd.setCursor(0,1);
    lcd.print("to OBD scanner");
    while (1);
  }

  lcd.setCursor(0,0);
  lcd.print("Connected to");
  lcd.setCursor(0,1);
  lcd.print("ELM327");
}


void loop()
{
  float tempRPM = myELM327.rpm();

  if (myELM327.nb_rx_state == ELM_SUCCESS)
  {
    rpm = (uint32_t)tempRPM;

    lcd.setCursor(0,0);
    lcd.print("Mazda3 Kose Bose");
    lcd.setCursor(0,1);
    lcd.print("RPM:                         ");
    lcd.setCursor(5,1);
    lcd.print(rpm);
    
    for(int i = 0; i < PixelCount; i++) {
        strip.SetPixelColor(i, Cblack);
        strip.Show();
    }
      
    if( rpm > 1000 ) {
      strip.SetPixelColor(0, Cgreen);
      strip.Show();
    }
    if( rpm > 1500 ) {
      strip.SetPixelColor(1, Cgreen);
      strip.Show();
    }
    if( rpm > 2000 ) {
      strip.SetPixelColor(2, Cgreen);
      strip.Show();
    }
    if( rpm > 2500 ) {
      strip.SetPixelColor(3, Cyellow);
      strip.Show();
    }
    if( rpm > 3000 ) {
      strip.SetPixelColor(4, Cyellow);
      strip.Show();
    }
    if( rpm > 3500 ) {
      strip.SetPixelColor(5, Cyellow);
      strip.Show();
    }
    if( rpm > 4000 ) {
      strip.SetPixelColor(6, Cred);
      strip.Show();
    }
    if( rpm > 4250 ) {
      strip.SetPixelColor(7, Cred);
      strip.Show();
    }
    if( rpm > 4500 ) {
      for(int i = 0; i < PixelCount; i++) {
        strip.SetPixelColor(i, Cblue);
        strip.Show();
      }
      delay(50);
      for(int i = 0; i < PixelCount; i++) {
        strip.SetPixelColor(i, Cblack);
        strip.Show();
      }
    }
  }
}
