#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLECharacteristic.h>
#include <BLE2902.h>
#include <Arduino.h>

// Define BLE service and characteristics UUIDs
#define SERVICE_UUID        "5b6e68f2-beb7-4f07-b5b4-6094d740fc82" // Custom service UUID
#define CHARACTERISTIC_UUID "3d601b60-6b6d-11eb-9439-0242ac130002" // Custom characteristic UUID

BLECharacteristic *pCharacteristic;
BLEServer *pServer;
BLEService *pService;

int arr[3];  // Array to store RGB values from the laptop

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(115200);
  delay(1000); // Allow time for Serial Monitor to initialize
  Serial.println("ESP32 BLE RGB LED Controller - Debug Mode");

  // Initialize BLE
  BLEDevice::init("ESP32_BLE_RGB");  // Device name
  Serial.println("BLE Device Initialized");
  
  pServer = BLEDevice::createServer();
  Serial.println("BLE Server Created");
  
  // Create BLE service
  pService = pServer->createService(SERVICE_UUID);
  Serial.println("BLE Service Created");

  // Create BLE characteristic
  pCharacteristic = pService->createCharacteristic(
      CHARACTERISTIC_UUID,
      BLECharacteristic::PROPERTY_WRITE
  );
  pCharacteristic->addDescriptor(new BLE2902());
  Serial.println("BLE Characteristic Created");

  // Start the service
  pService->start();
  Serial.println("BLE Service Started");

  // Start advertising the BLE service
  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising->setMinPreferred(0x06);  // More aggressive advertising
  pAdvertising->setMaxPreferred(0x12);  // Adjust max interval as well
  pAdvertising->start();
  Serial.println("Advertising Started");
  
  // Pin initialization for RGB LEDs
  pinMode(25, OUTPUT);
  pinMode(26, OUTPUT);
  pinMode(27, OUTPUT);

  Serial.println("Pin Modes Set. Ready to Pair.");
}

void split(String inarr) {
  String substr;
  int count = 0;
  for (int i = 0; i < inarr.length(); i++) {
    if (inarr[i] != ' ') {
      substr.concat(inarr[i]);
    }
    else if (inarr[i] == ' ') {
      arr[count] = substr.toInt();
      count++;
      substr = "";
    }
  }
  arr[count] = substr.toInt();
}

void loop() {
  // Print a simple message every loop cycle to show the program is running
  // Serial.println("Looping...");
  
  // Check if there is data available in the characteristic
  if (pCharacteristic->getValue().length() > 0) {
    String str = pCharacteristic->getValue().c_str();
    Serial.println("Data received:");
    Serial.println(str);  // Print the received string

    split(str);  // Split the received string into RGB values
    Serial.println("RGB values:");
    for (int i = 0; i < 3; i++) {
      Serial.print("arr[");
      Serial.print(i);
      Serial.print("]: ");
      Serial.println(arr[i]);
    }

    // Set the RGB LEDs according to received values
    ledcWrite(0, arr[0]);  // Set PWM on channel 0 for pin 25
    ledcWrite(1, arr[1]);  // Set PWM on channel 1 for pin 26
    ledcWrite(2, arr[2]);  // Set PWM on channel 2 for pin 27
  }

  delay(10);  // Small delay to avoid excessive CPU usage
}
