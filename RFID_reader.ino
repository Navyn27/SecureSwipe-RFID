#include <SPI.h>
#include <MFRC522.h>
#define SS_PIN 10
#define RST_PIN 9

int buzzer = 5;
int redLED = 7;
int greenLED = 6;

int id = 0;
int j = 0;

String authenticatedUID = "cb16c814";

bool valid = false;

MFRC522 rfid(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key;
byte nuidPICC[4];

String cardUid;


void authenticate() {
    if (valid) {
      digitalWrite(buzzer, HIGH);
      digitalWrite(greenLED, HIGH);
      delay(500);
      digitalWrite(buzzer, LOW);
      digitalWrite(greenLED, LOW);
    } else {
      for (j = 0; j <= 4; j++) {
        digitalWrite(redLED, HIGH);
        digitalWrite(buzzer, HIGH);
        delay(100);
        digitalWrite(buzzer, LOW);
        digitalWrite(redLED, LOW);
        delay(100);
      }
    }
}

void setup() {
  pinMode(buzzer,OUTPUT);
  pinMode(redLED,OUTPUT);
  pinMode(greenLED,OUTPUT);

  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();
  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }
}

void loop() {
  if (!rfid.PICC_IsNewCardPresent()) {
    return;
  }
  if (!rfid.PICC_ReadCardSerial()) {
    return;
  }
  for (byte i = 0; i < 4; i++) {
    nuidPICC[i] = rfid.uid.uidByte[i];
  }
  printHex(rfid.uid.uidByte, rfid.uid.size);
  /*
 * Halt PICC
 * Stop encryption on PCD
 */
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
  char monitorData;
  monitorData = Serial.read();
  if(monitorData=='t'){
    valid = true;
  }
  else{
    valid = false;
  }
  authenticate();
  delay(3000);
  Serial.flush();
}


void printHex(byte *buffer, byte bufferSize) {
  cardUid = "";
  for (byte i = 0; i < bufferSize; i++) {
    cardUid += String(buffer[i], HEX);
  }
  Serial.println(cardUid);
}