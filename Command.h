#ifndef COMMANDS_H
#define COMMANDS_H

#include <Arduino.h>

enum CommandType {
  GET_WIFI_CONN,
  GET_IP_ADDR,
  GET_MAC_ADDR,
  GET_HOSTNAME,
  
  CONNECT,
  DISCONNECT,
  RESET,

  OPEN_GARAGE,
  CLOSE_GARAGE,

  UNKNOWN
};

struct Command {
  CommandType type;
  String value;

  Command(CommandType type, const String& value = "") : type(type), value(value) {}
};

Command getCommand(const String& commandStr);

#endif // COMMANDS_H