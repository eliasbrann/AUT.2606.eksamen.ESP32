import serial

#bluetooth
bt = serial.Serial('/dev/rfcomm0', 115200, timeout=1)

#uart to mcu
uart = serial.Serial('/dev/serial0', 115200, timeout=1)


while True:
    data = bt.readline().decode(errors='ignore').strip()
    
    if data:
        try:
            values = list(map(int, data.split(',')))
            print("Received:", values)

            # Send same data over UART
            uart.write((data + '\n').encode())

        except:
            print("Parse error:", data) 