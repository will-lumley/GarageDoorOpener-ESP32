#include "Command.h"

Command getCommand(const String& commandStr) {
  if (commandStr == "GET_WIFI_CONN") return Command(GET_WIFI_CONN);
  if (commandStr == "GET_IP_ADDR")   return Command(GET_IP_ADDR);
  if (commandStr == "GET_MAC_ADDR")  return Command(GET_MAC_ADDR);
  if (commandStr == "GET_HOSTNAME")  return Command(GET_HOSTNAME);

  if (commandStr == "CONNECT")    return Command(CONNECT);
  if (commandStr == "DISCONNECT") return Command(DISCONNECT);
  if (commandStr == "RESET") return Command(RESET);

  if (commandStr == "OPEN_GARAGE") return Command(OPEN_GARAGE);
  if (commandStr == "CLOSE_GARAGE") return Command(CLOSE_GARAGE);
  
  return Command(UNKNOWN);
}