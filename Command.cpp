#include "Command.h"

Command getCommand(const String& commandStr) {
  if (commandStr == "GET_WIFI_CONN") return Command(GET_WIFI_CONN);
  if (commandStr == "GET_IP_ADDR")   return Command(GET_IP_ADDR);
  if (commandStr == "GET_MAC_ADDR")  return Command(GET_MAC_ADDR);
  if (commandStr == "GET_SSID")      return Command(GET_SSID);
  if (commandStr == "GET_CHANNEL")   return Command(GET_CHANNEL);
  if (commandStr == "GET_HOSTNAME")  return Command(GET_HOSTNAME);

  if (commandStr.startsWith("SET_SSID="))    return Command(SET_SSID, commandStr.substring(9));
  if (commandStr.startsWith("SET_PASS="))    return Command(SET_PASS, commandStr.substring(9));
  if (commandStr.startsWith("SET_CHANNEL=")) return Command(SET_CHANNEL, commandStr.substring(12));

  if (commandStr == "CONNECT")    return Command(CONNECT);
  if (commandStr == "DISCONNECT") return Command(DISCONNECT);
  if (commandStr == "RESET") return Command(RESET);
  
  return Command(UNKNOWN);
}