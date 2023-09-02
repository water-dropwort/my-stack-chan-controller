#ifndef STACKCHANREMOTECONTROLLER_HPP_
#define STACKCHANREMOTECONTROLLER_HPP_

#include <BLEDevice.h>
#include <BLEServer.h>
#include <M5Atom.h>

#define JOYSTICK_X_PIN  25
#define JOYSTICK_Y_PIN  33
#define JOYSTICK_SW_PIN 21

#define SERVICE_UUID        "c36489fd-110d-4bd5-8844-49f947fab85f"
#define CHARACTERISTIC_UUID "d2fbe672-a9c3-47d5-af29-186acfc34c21"
#define DEVICE_NAME         "Stack-Chan-Controller"

#define LED_DISCONNECT 0xff0000
#define LED_CONNECT    0x00ff00

class StackChanRemoteController : public BLEServerCallbacks {
  public:
    StackChanRemoteController();
    void init();
    void onConnect(BLEServer* server);
    void onDisconnect(BLEServer* server);
    void sendData();
  private:
    BLEServer* m_server = nullptr;
    BLECharacteristic* m_characteristic = nullptr;
};

#endif
