#ifndef GARAGEDOORACCESSORY_H
#define GARAGEDOORACCESSORY_H

#include <functional>
#include <HomeSpan.h>

struct GarageDoorAccessory : Service::GarageDoorOpener {
  using Function = std::function<void()>;

  Characteristic::CurrentDoorState *currentState;
  Characteristic::TargetDoorState *targetState;
  SpanCharacteristic *obstruction;

  Function onOpen;
  Function onClose;

  GarageDoorAccessory();

  void open();
  void close();
  void loop();

  private:
    boolean update();
};

#endif