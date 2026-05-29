import serial
import asyncio
import websockets
import json
import imufusion
import numpy as np

SERIAL_PORT = "COM4"     
BAUD_RATE = 115200
SAMPLE_RATE = 100

ahrs = imufusion.Ahrs()


connected_clients = set()

async def broadcast(message):
    if connected_clients:
        await asyncio.gather(*[c.send(message) for c in connected_clients])

async def ws_handler(websocket):
    connected_clients.add(websocket)
    try:
        await websocket.wait_closed()
    finally:
        connected_clients.remove(websocket)

async def read_serial():
    ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
    print(f"Connected to {SERIAL_PORT}")
    loop = asyncio.get_event_loop()

    while True:
        line = await loop.run_in_executor(None, ser.readline)
        try:
            parts = line.decode().strip().split(",")
            if len(parts) != 11:  
                continue

            #Hopper over første 5 ADC verdier
            ax, ay, az, gx, gy, gz = map(float, parts[5:])

            gyroscope    = np.array([np.degrees(gx), np.degrees(gy), np.degrees(gz)])
            accelerometer = np.array([ax, ay, az]) / 9.81

            ahrs.update_no_magnetometer(gyroscope, accelerometer, 1 / SAMPLE_RATE)

            q = ahrs.quaternion
            data = json.dumps({"w": q.w, "x": q.x, "y": q.y, "z": q.z})
            await broadcast(data)

        except Exception as e:
            print(f"Parse error: {e}")

async def main():
    print("Starting — open index.html in your browser")
    async with websockets.serve(ws_handler, "localhost", 8765):
        await read_serial()

asyncio.run(main())