//#include <SPI.h>
//#include <MFRC522.h>
//
//#define RST_PIN 11 //9
//#define SS_PIN  53 //10
//
//MFRC522 mfrc522(SS_PIN, RST_PIN);
//
//void setup() {
//  Serial.begin(9600);
//  while (!Serial);
//  SPI.begin();
//  mfrc522.PCD_Init();
//  delay(4);
//  mfrc522.PCD_DumpVersionToSerial();
//  Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
//}
//
//void loop() {
//  if ( ! mfrc522.PICC_IsNewCardPresent()) {
//    return;
//  }
//
//  if ( ! mfrc522.PICC_ReadCardSerial()) {
//    return;
//  }
//  mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
//}


#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN   11    // Define the reset pin 9 for uno, pin 11 for mega
#define SS_PIN    53   // Define the slave select pin 10 for uno, pin 53 for mega

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create instance of MFRC522

void setup() {
  Serial.begin(9600);  // Initialize serial communication
  SPI.begin();         // Initialize SPI communication
  mfrc522.PCD_Init();  // Initialize MFRC522

  Serial.println("Ready to read RFID cards!");
}

void loop() {
  // Look for new cards
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    Serial.println("Found an RFID card!");

    // Print UID
    Serial.print("Card UID: ");
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
      Serial.print(mfrc522.uid.uidByte[i], HEX);
    }
    Serial.println();

    // Halt PICC
    mfrc522.PICC_HaltA();
    mfrc522.PCD_StopCrypto1();
  }
}
