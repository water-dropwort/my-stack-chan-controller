#include "StackChanRemoteController.hpp"

StackChanRemoteController::StackChanRemoteController() {

}

void StackChanRemoteController::init() {
  M5.begin(true, false, true);
  pinMode(JOYSTICK_SW_PIN, INPUT_PULLUP);

  
  BLEDevice::init(DEVICE_NAME);

  m_server = BLEDevice::createServer();
  m_server->setCallbacks(this);

  BLEService* service = m_server->createService(SERVICE_UUID);

  m_characteristic =
    service->createCharacteristic(CHARACTERISTIC_UUID, BLECharacteristic::PROPERTY_WRITE);

  service->start();

  BLEAdvertising* advertising = m_server->getAdvertising();
  advertising->addServiceUUID(service->getUUID());

  M5.dis.drawpix(0, LED_DISCONNECT);
  advertising->start();

  //m_characteristic->setValue(0);
}


void StackChanRemoteController::onConnect(BLEServer* server) {
  M5.dis.drawpix(0, LED_CONNECT);
}

void StackChanRemoteController::onDisconnect(BLEServer* server) {
  M5.dis.drawpix(0, LED_DISCONNECT);
  m_server->getAdvertising()->start();
}

void StackChanRemoteController::sendData() {
  M5.update();
  uint32_t data = 0;
  if(M5.Btn.isPressed()) {
    data = 1;
  }

  int x = analogRead(JOYSTICK_X_PIN);
  int y = analogRead(JOYSTICK_Y_PIN);
  int sw = digitalRead(JOYSTICK_SW_PIN);

  if(x < 1000) { // 0 ~ 999
    data = data | 0b01 << 1;
  }
  else if(1000 <= x && x <= 3095) {
    // data = data;
  }
  else {
    data = data | 0b10 << 1;
  }

  if(y < 1000) {
    data = data | 0b01 << 3;
  }
  else if(1000 <= y && y <= 3095) {
    // data = data;
  }
  else {
    data = data | 0b10 << 3;
  }

  if(sw == 0) {
    data = data | 1 << 5;
  }
  else {
    //data = data;
  }

  m_characteristic->setValue(data);
}
