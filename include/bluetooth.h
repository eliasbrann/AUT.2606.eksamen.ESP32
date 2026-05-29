#ifndef BLUETOOTH_H
#define BLUETOOTH_H

void bt_init();
void bt_send(int values[], int length);
bool bt_connected();

#endif