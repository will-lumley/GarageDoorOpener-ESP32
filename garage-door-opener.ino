#include <ESP8266WiFi.h>
#include <arduino_homekit_server.h>
#include <EEPROM.h>
#include <ESP8266mDNS.h>

#include "Command.h"
#include "WiFiHelpers.h"

#define RELAY_PIN 5

#define ESP_DEBUG true
#define EEPROM_SIZE 4096

String ssid = "";
String pass = "";
int channel = 0;
int connectionTimeout = 300;

bool pollHomeKit = false;

// Grab our HomeKit configuration from GarageDoorAccessory.c
extern "C" homekit_server_config_t config;
extern "C" homekit_characteristic_t homeKitGarage;

void setup() {
  Serial.begin(115200);
  delay(500);

  EEPROM.begin(EEPROM_SIZE);
  Serial.println("* ESP8266 booted up.");

  WiFi.persistent(false);
  WiFi.mode(WIFI_STA);
  // WiFi.onStationModeDisconnected(onWiFiDisconnect);

#if ESP_DEBUG
  ssid = "ravioli";
  pass = "tu2y259jhh";
  channel = 1;

  ssid = "Will's iPhone";
  pass = "password";
  channel = 0;

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

  arduino_homekit_loop();
  MDNS.announce();

  // If we've created the garage door accessory, and we're paired, let's poll
  // homekit_server_t *homekit_server = arduino_homekit_get_running_server();
  // if (homekit_server != nullptr && homekit_server->paired) {

  // } else {
    // Serial.println("Performing HomeKit loop.");
    // arduino_homekit_loop();
  // }
}

void handleCommand(Command command) {
  switch (command.type) {
    case GET_WIFI_CONN: {
      getWiFiConnectionStatus();
      break;
    }
    case GET_IP_ADDR: {
      getIPAddress();
      break;
    }
    case GET_MAC_ADDR: {
        getMACAddress();
        break;
      }
    case GET_SSID: {
      getSSID();
      break;
    }
    case GET_CHANNEL: {
      getChannel();
      break;
    }
    case GET_HOSTNAME: {
      getHostName();
      break;
    }
    case SET_SSID: {
      setSSID(command.value);
      break;
    }
    case SET_PASS: {
      setPassword(command.value);
      break;
    }
    case SET_CHANNEL: {
      setChannel(command.value.toInt());
      break;
    }
    case CONNECT: {
      connect();
      break;
    }
    case DISCONNECT: {
      disconnect();
      break;
    }
    case CREATE_GARAGE_DOOR: {
      createGarageDoor();
      break;
    }
    case SET_POLL_HOMEKIT_TRUE: {
      setPollHomeKit(true);
      break;
    }
    case RESET: {
      reset();
      break;
    }
    default: {
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

void getSSID() {
  Serial.println(ssid.c_str());
}

void getChannel() {
  Serial.println(String(channel));
}

void getHostName() {
  Serial.println(WiFi.hostname());
}

void setSSID(String newSSID) {
  ssid = newSSID;
  Serial.println(ssid);
}

void setPassword(String newPass) {
  pass = newPass;
  Serial.println(pass);
}

void setChannel(int newChannel) {
  channel = newChannel;
  Serial.println(String(channel));
}

void connect() {
  // Pull out our SSID and password
  const char* ssidChar = ssid.c_str();
  const char* passChar = pass.c_str();

  // Connect to our WiFi
  WiFi.begin(ssidChar, passChar, channel);
  int timeout = 0;
  while (WiFi.status() != WL_CONNECTED && timeout < connectionTimeout) {
    delay(1000);
    timeout++;

    Serial.println("* Connecting for " + String(timeout) + " seconds.");
  }

  Serial.println("* WiFi Connection: " + String(wifiStatusDescription(WiFi.status())));

  #if ESP_DEBUG
  createGarageDoor();
  #endif
}

void disconnect() {
  WiFi.disconnect();
  Serial.println("* Disconnected from WiFi.");
}

void createGarageDoor() {
  homeKitGarage.setter = homeKitUpdatedValue;
  arduino_homekit_setup(&config);
  setPollHomeKit(true);
  Serial.println("* Created Garage Door.");
}

void setPollHomeKit(bool newPollHomeKit) {
  pollHomeKit = newPollHomeKit;
  Serial.println("* PollHomeKit: " + String(pollHomeKit));
}

void reset() {
  // Reset the EEPROM
  /*--------------------------*/
  size_t eepromLength = EEPROM.length();
  Serial.println("* EEPROM.length(): " + String(eepromLength));

  for (int i = 0 ; i < eepromLength ; i++) {
    EEPROM.write(i, 0);
  }
  EEPROM.commit();
  Serial.println("* Reset EEPROM.");
  /*--------------------------*/

  // Reset the HomeKit server
  /*--------------------------*/
  homekit_server_t *homekit_server = arduino_homekit_get_running_server();
  if (homekit_server != nullptr) {
      homekit_storage_reset();

      Serial.println("* Reset HomeKit Server.");
      ESP.restart();
  } else{
    Serial.println("* Failed to reset HomeKit Server.");
  }
  /*--------------------------*/
}

void homeKitUpdatedValue(const homekit_value_t value) {
  bool on = value.bool_value;
  homeKitGarage.value.bool_value = on;

  if (on) {
    Serial.println("* HomeKit turned garage door ON.");
  } else {
    Serial.println("* HomeKit turned garage door OFF.");
  }
  // digitalWrite(PIN_SWITCH, on ? LOW : HIGH);
}