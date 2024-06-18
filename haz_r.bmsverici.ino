/*Transmitter code*/

#include "LoRa_E22.h"
#include <SoftwareSerial.h>
SoftwareSerial mySerial(2,3 ); // Arduino RX <-- e22 TX, Arduino TX --> e22 RX
LoRa_E22 E22(&mySerial);
#define M0 8
#define M1 9

struct veriler
{
    uint8_t dataUart[64];
} data;

void setup()
{
    Serial.begin(9600);
    Serial1.begin(9600);
    Serial2.begin(9600);
    pinMode(M0, OUTPUT);
    pinMode(M1, OUTPUT);
    digitalWrite(M0, LOW);
    digitalWrite(M1, LOW);
    E22.begin();
    delay(500);
}
void loop()
{
    if (Serial2.available() == 53)
    {
        for (int i = 0; i < 53; i++)
        {
            data.dataUart[i] = Serial2.read();
        }
        ResponseStatus rs = E22.sendFixedMessage(0, 2, 18, &data, sizeof(veriler));
        Serial.println(rs.getResponseDescription());
        delay(500);
    }
}