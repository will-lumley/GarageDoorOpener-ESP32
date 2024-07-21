#ifndef COMMANDS_H
#define COMMANDS_H

#include <Arduino.h>

enum CommandType {
  GET_WIFI_CONN,
  GET_IP_ADDR,
  GET_MAC_ADDR,
  GET_SSID,
  GET_CHANNEL,
  GET_HOSTNAME,
  
  SET_SSID,
  SET_PASS,
  SET_CHANNEL,
  
  CONNECT,
  DISCONNECT,
  RESET,

  CREATE_GARAGE_DOOR,
  SET_POLL_HOMEKIT_TRUE,

  UNKNOWN
};

struct Command {
  CommandType type;
  String value;

  Command(CommandType type, const String& value = "") : type(type), value(value) {}
};

Command getCommand(const String& commandStr);

#endif // COMMANDS_H