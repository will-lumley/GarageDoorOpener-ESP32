#include "GarageDoorAccessory.h"

GarageDoorAccessory::GarageDoorAccessory() : Service::GarageDoorOpener() {
  Serial.println("* Configuring Garage Door Opener");

  // // Set the default values
  currentState = new Characteristic::CurrentDoorState(Characteristic::CurrentDoorState::CLOSED);
  targetState = new Characteristic::TargetDoorState(targetState->CLOSED);
  obstruction = new Characteristic::ObstructionDetected(Characteristic::ObstructionDetected::NOT_DETECTED);

  Serial.println("* Configured Garage Door Opener");
}

void GarageDoorAccessory::open() {
  targetState->setVal(Characteristic::TargetDoorState::OPEN);
  update();
}

void GarageDoorAccessory::close() {
  targetState->setVal(Characteristic::TargetDoorState::CLOSED);
  update();
}

boolean GarageDoorAccessory::update() {
  if (targetState->getNewVal() == targetState->OPEN) {
    Serial.println("* Opening Garage Door.");
    currentState->setVal(currentState->OPENING);
    obstruction->setVal(false);

    if (onOpen) {
      onOpen();
    }
  } else {
    Serial.println("* Closing Garage Door.");
    currentState->setVal(currentState->CLOSING);
    obstruction->setVal(false);

    if (onClose) {
      onClose();
    }
  }

  return true;
}

void GarageDoorAccessory::loop() {
  if (currentState->getVal() == targetState->getVal() || currentState->getVal() == currentState->STOPPED) {
      return;
  }

  if(targetState->timeVal() > 5000) {
      currentState->setVal(targetState->getVal());
  }
}
