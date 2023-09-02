#include "StackChanRemoteController.hpp"

StackChanRemoteController* g_remoteController = nullptr;

void setup() {
  g_remoteController = new StackChanRemoteController();
  g_remoteController->init();
}

void loop() {
  g_remoteController->sendData();
  delay(10);
}
