#include <Arduino.h>
#include <SPI.h>
#include <mcp2515.h>

struct can_frame canMsg;
MCP2515 mcp2515(5); // CS Pin is 5

void setup() {
  Serial.begin(115200);
  
  mcp2515.reset();
  mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ);
  mcp2515.setNormalMode();
  
  Serial.println("------- CAN Read ----------");
  Serial.println("ID  DLC   DATA   Priority  Source ECU  Message Type");
}

void loop() {
  // Check if a message has been received
  if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK) {
    // Print the arbitration ID (CAN ID)
    Serial.print(canMsg.can_id, HEX);  // Print the CAN ID in HEX
    Serial.print(" ");
    
    // Print the Data Length Code (DLC)
    Serial.print(canMsg.can_dlc, HEX);  // Print the DLC in HEX
    Serial.print(" ");
    
    // Print the data bytes
    for (int i = 0; i < canMsg.can_dlc; i++) {
      Serial.print(canMsg.data[i], HEX);
      Serial.print(" ");
    }

    // Extract arbitration fields (for standard 11-bit CAN IDs)
    uint32_t arbitrationID = canMsg.can_id;

    // Extract the Priority (bits 10:8)
    uint8_t priority = (arbitrationID >> 8) & 0x07;

    // Extract the Source ECU (bits 7:5)
    uint8_t sourceECU = (arbitrationID >> 5) & 0x07;

    // Extract the Message Type (bits 4:0)
    uint8_t messageType = arbitrationID & 0x1F;

    // Print the formatted arbitration fields
    Serial.print(" ");
    Serial.print("Priority: ");
    Serial.print(priority);
    Serial.print(", Source ECU: ");
    Serial.print(sourceECU);
    Serial.print(", Message Type: ");
    Serial.println(messageType);
  }
}
