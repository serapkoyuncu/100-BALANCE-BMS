/*Reciever code*/

#include "LoRa_E22.h"
#include <SoftwareSerial.h>
SoftwareSerial mySerial(2,3 ); // Arduino RX <-- e22 TX, Arduino TX --> e22 RX
LoRa_E22 E22(&mySerial);
#define M0 8
#define M1 9

struct veriler {
uint8_t dataUart[64];
} data;

byte dataUart[64];
uint16_t cells[20];
uint16_t sumVoltage, soc, powerWatt, cellsVoltage[20], maxVPosition, minVPosition, differantiePressure,
    temps[4], maxTemp, minTemp, meanTemp, current, minVoltage, maxVoltage;
int count = 0;

void setup()
{
    Serial.begin(9600);
    Serial1.begin(9600);
}

void loop()
{
  
    for(int i = 0; i < 64; i++) {
        dataUart[i] = 0;
    }

    count = 0;
    delay(1200);

    for (int i = 0; i < 64; i++)
    {
        dataUart[i] = Serial1.read();
    }

    /* for(int i = 0; i < 64; i++) {
      Serial.print(dataUart[i]);
      Serial.print(" ");
    } 

    Serial.println(""); */


    sumVoltage = (dataUart[0] * 256 + dataUart[1]) / 10;
    soc = (dataUart[2] * 256 + dataUart[3]) / 10;
    powerWatt = (dataUart[4] * 256 + dataUart[5]) / 1000;
    maxVPosition = dataUart[48];
    minVPosition = dataUart[49];
    differantiePressure = dataUart[50];
    maxTemp = dataUart[55] - 40;
    minTemp = dataUart[57] - 40;
    meanTemp = dataUart[59] - 40;
    current = (dataUart[4] * 256 + dataUart[5]) / 63;
    maxVoltage = (dataUart[46] * 256 + dataUart[47]) / 100;
    minVoltage = (dataUart[62] * 256 + dataUart[63]) / 100;

    for (int i = 0; i < 20; i++)
    {
        cells[i] = (dataUart[count + 6] * 256 + dataUart[count + 7]);
        count += 2;
    }

    for (int i = 0; i < 4; i++)
    {
        temps[i] = dataUart[i + 51] - 40;
    }

    Serial.print("Sum Voltage: ");
    Serial.println(sumVoltage);

    Serial.print("SOC: ");
    Serial.println(soc);

    Serial.print("Sum Voltage: ");
    Serial.println(sumVoltage);

    Serial.print("Power Watt: ");
    Serial.println(powerWatt);

    Serial.print("MaxV Position: ");
    Serial.println(maxVPosition);

    Serial.print("MinV Position: ");
    Serial.println(minVPosition);

    Serial.print("Differantie Pressure: ");
    Serial.println(differantiePressure);

    Serial.print("Max Temp: ");
    Serial.println(maxTemp);

    Serial.print("Min Temp: ");
    Serial.println(minTemp);

    Serial.print("Mean Temp: ");
    Serial.println(meanTemp);

    Serial.print("Current: ");
    Serial.println(current);

    Serial.print("Max Voltage: ");
    Serial.println(current);

    Serial.print("Min Voltage: ");
    Serial.println(minVoltage);

    Serial.print("Current: ");
    Serial.println(current);

    Serial.println("********** TEMPERATURE ***********");

    Serial.print("Temp 1: ");
    Serial.println(temps[0]);

    Serial.print("Temp 2: ");
    Serial.println(temps[1]);

    Serial.print("Temp 3: ");
    Serial.println(temps[2]);

    Serial.print("Temp 4: ");
    Serial.println(temps[3]);

    Serial.println("************* CELLS **************");

    for (int i = 0; i < 20; i++)
    {
        Serial.print(cells[i]);
        Serial.print(" ");
    }
    Serial.println(" ");
}