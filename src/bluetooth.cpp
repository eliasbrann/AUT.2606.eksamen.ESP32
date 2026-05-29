#include "bluetooth.h"
#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

void bt_init() {
    SerialBT.begin("ESP32_ADC");
}

void bt_send(int values[], int length) {
    if (SerialBT.hasClient()) {
        for (int i = 0; i < length; i++) {
            SerialBT.print(values[i]);
            if (i < length - 1) {
                SerialBT.print(",");
            }
        }
        SerialBT.println();
    }
}

bool bt_connected() {
    return SerialBT.hasClient();
}