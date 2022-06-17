#include "BluetoothSerial.h"
#include "ELMduino.h"


BluetoothSerial SerialBT;
#define ELM_PORT   SerialBT
#define DEBUG_PORT Serial


ELM327 myELM327;


uint32_t rpm = 0;

//String MACadd = "DC:0D:30:48:8D:60";                         //enter the ELM327 MAC address
//uint8_t address[6]  = {0xDC, 0x0D, 0x30, 0x48, 0x8D, 0x60};  //enter the ELM327 MAC address after the 0x


void setup()
{
#if LED_BUILTIN
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
#endif

  DEBUG_PORT.begin(115200);
  //SerialBT.setPin("1234");
  ELM_PORT.begin("ArduHUD", true);
  
  if (!ELM_PORT.connect("OBDII"))
  // if(!ELM.PORT.connect(address))   //"OBDII" replaced by "address"
  {
    DEBUG_PORT.println("Couldn't connect to OBD scanner - Phase 1");
    while(1);
  }

  if (!myELM327.begin(ELM_PORT, true, 2000))
  {
    Serial.println("Couldn't connect to OBD scanner - Phase 2");
    while (1);
  }

  Serial.println("Connected to ELM327");
}


void loop()
{
  float tempRPM = myELM327.rpm();

  delay(500);
  if (myELM327.nb_rx_state == ELM_SUCCESS)
  {
    rpm = (uint32_t)tempRPM;
    Serial.print("RPM: "); 
    Serial.println(rpm);
  }
  //else if (myELM327.nb_rx_state != ELM_GETTING_MSG)
    //myELM327.printError();
  /* else {
    printError();
  } */
}

void printError()
{
  Serial.print("Received: ");
  for (byte i = 0; i < myELM327.recBytes; i++)
    Serial.write(myELM327.payload[i]);
  Serial.println();

  if (myELM327.nb_rx_state == ELM_SUCCESS)
    Serial.println(F("\tELM_SUCCESS"));
  else if (myELM327.nb_rx_state == ELM_NO_RESPONSE)
    Serial.println(F("\tERROR: ELM_NO_RESPONSE"));
  else if (myELM327.nb_rx_state == ELM_BUFFER_OVERFLOW)
    Serial.println(F("\tERROR: ELM_BUFFER_OVERFLOW"));
  else if (myELM327.nb_rx_state == ELM_UNABLE_TO_CONNECT)
    Serial.println(F("\tERROR: ELM_UNABLE_TO_CONNECT"));
  else if (myELM327.nb_rx_state == ELM_NO_DATA)
    Serial.println(F("\tERROR: ELM_NO_DATA"));
  else if (myELM327.nb_rx_state == ELM_STOPPED)
    Serial.println(F("\tERROR: ELM_STOPPED"));
  else if (myELM327.nb_rx_state == ELM_TIMEOUT)
    Serial.println(F("\tERROR: ELM_TIMEOUT"));
  else if (myELM327.nb_rx_state == ELM_TIMEOUT)
    Serial.println(F("\tERROR: ELM_GENERAL_ERROR"));

  delay(100);
}
