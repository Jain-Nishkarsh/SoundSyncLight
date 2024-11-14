#include <BluetoothSerial.h>
// #include <esp_now.h>
// #include <WiFi.h>

// BluetoothSerial is used to communicate over Bluetooth
BluetoothSerial SerialBT;

int arr[3];  // Array to store RGB values from the laptop

// Pin for the LED to blink on connection
const int ledPin = 2;  // Use GPIO 2 for the LED

// Flag to check if the device is connected
bool isConnected = false;

void setup() {
  // Initialize serial communication
  Serial.begin(115200);
  SerialBT.begin("ESP32_Bluetooth");  // ESP32 Bluetooth device name

  // Pin initialization for RGB LEDs
  pinMode(25, OUTPUT);
  pinMode(26, OUTPUT);
  pinMode(27, OUTPUT);
  
  // Initialize the LED pin
  pinMode(ledPin, OUTPUT);
  
  Serial.println("Bluetooth device is ready to pair.");
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
  // Check if Bluetooth is connected
  if (SerialBT.hasClient() && !isConnected) {
    Serial.println("Bluetooth device is connected.");
    
    // Blink LED once to indicate Bluetooth connection
    digitalWrite(ledPin, HIGH);  // Turn the LED on
    delay(500);  // Delay for 500ms
    digitalWrite(ledPin, LOW);   // Turn the LED off
    delay(500);  // Delay for 500ms

    isConnected = true;  // Mark as connected to avoid blinking repeatedly
  } 
  // Check if Bluetooth is disconnected
  else if (!SerialBT.hasClient() && isConnected) {
    Serial.println("Bluetooth device is disconnected.");
    isConnected = false;  // Reset the connection status
  }

  // If the Bluetooth is connected, continue to receive and process data
  if (SerialBT.available() > 0) {
    String str = SerialBT.readStringUntil('\n');
    split(str);

    Serial.println(str);  // Print received string

    // Set the RGB LEDs according to received values
    analogWrite(25, arr[0]);
    analogWrite(26, arr[1]);
    analogWrite(27, arr[2]);
  }

  delay(100);  // Small delay to avoid excessive CPU usage
}