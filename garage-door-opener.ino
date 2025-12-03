#include <EEPROM.h>
#include <HomeSpan.h>
#include <WiFi.h>

#include "Command.h"
#include "GarageDoorAccessory.h"
#include "WiFiHelpers.h"

#define RELAY_PIN 23

String ssid = "";
String pass = "";
int connectionTimeout = 300;

std::shared_ptr<GarageDoorAccessory> garage;

void setup() {
  pinMode(RELAY_PIN, 0X00);
  // pinMode(RELAY_PIN, OUTPUT);

  Serial.begin(115200);
  delay(500);

  WiFi.mode(WIFI_STA);
  homeSpan.setPairingCode("11112222");

  Serial.println("* ESP32 booted up.");


  ssid = "ssid";
  pass = "password";
  
  delay(2000);
  connect();
#endif
}

void loop() {
  // If we have content available, let's parse it
  if (Serial.available()) {
    // Get our raw command string and remove any extra newline characters
    String rawCommand = Serial.readStringUntil('\n');
    rawCommand.trim();

    // Interpret the raw string into a `Command` enum and handle it
    Command command = getCommand(rawCommand);
    handleCommand(command);
  }

  // If we're connected to the WiFi network, poll HomeSpan
  if (isConnected()) {
    homeSpan.poll();
  }
}

void handleCommand(Command command) {
  switch (command.type) {
    case GET_WIFI_CONN:
      {
        getWiFiConnectionStatus();
        break;
      }
    case GET_IP_ADDR:
      {
        getIPAddress();
        break;
      }
    case GET_MAC_ADDR:
      {
        getMACAddress();
        break;
      }
    case GET_HOSTNAME:
      {
        getHostName();
        break;
      }
    case CONNECT:
      {
        connect();
        break;
      }
    case DISCONNECT:
      {
        disconnect();
        break;
      }
    case RESET:
      {
        reset();
        break;
      }
    case OPEN_GARAGE: {
      garage->open();
      break;
    }
    case CLOSE_GARAGE: {
      garage->close();
      break;
    }
    default:
      {
        Serial.println("* Unknown command");
        break;
      }
  }
}

void getWiFiConnectionStatus() {
  Serial.println(wifiStatusDescription(WiFi.status()));
}

void getIPAddress() {
  Serial.println(WiFi.localIP().toString());
}

void getMACAddress() {
  Serial.println(WiFi.macAddress());
}

void getHostName() {
  Serial.println(WiFi.getHostname());
}

void connect() {
  // Pull out our SSID and password
  const char* ssidChar = ssid.c_str();
  const char* passChar = pass.c_str();

  // Connect to our WiFi
  WiFi.begin(ssidChar, passChar);
  int timeout = 0;
  while (WiFi.status() != WL_CONNECTED && timeout < connectionTimeout) {
    delay(1000);
    timeout++;

    Serial.println("* Connecting for " + String(timeout) + " seconds.");
  }

  homeSpan.begin(Category::GarageDoorOpeners, "Garage Door");
  homeSpan.setWifiCredentials(ssidChar, passChar);

  // Create a new accessory
  new SpanAccessory();
  
  // Add Accessory Information Service with required characteristics
  new Service::AccessoryInformation();
    new Characteristic::Identify();
    new Characteristic::Name("Garage Door");
    new Characteristic::Manufacturer("William Lumley");
    new Characteristic::SerialNumber("123456789");
    new Characteristic::Model("ESP32 Garage Door");
    new Characteristic::FirmwareRevision("1.0");

  garage = std::make_shared<GarageDoorAccessory>();
  garage->onOpen = []() {
    toggleRelayPin();
  };
  garage->onClose = []() {
    toggleRelayPin();
  };

  Serial.println("* WiFi Connection: " + String(wifiStatusDescription(WiFi.status())));
}
void disconnect() {
  WiFi.disconnect();
  Serial.println("* Disconnected from WiFi.");
}

void reset() {
  // Tell the HomeSpan to unpair
  homeSpan.processSerialCommand("U");
}

void toggleRelayPin() {
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH);
  delay(1000);
  digitalWrite(RELAY_PIN, LOW);
  pinMode(RELAY_PIN, 0x00);
}

bool isConnected() {
  return WiFi.status() == WL_CONNECTED;
}
