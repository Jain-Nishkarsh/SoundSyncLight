import asyncio
from bleak import BleakClient
from PIL import ImageStat, Image
from mss import mss

# Define your ESP32 Bluetooth MAC address
ESP32_MAC_ADDRESS = "C8:C9:A3:CF:48:16"  # Replace with your ESP32's MAC address

def capture_screenshot():
    # Capture entire screen
    with mss() as sct:
        monitor = sct.monitors[1]
        sct_img = sct.grab(monitor)
        # Convert to PIL/Pillow Image
        return Image.frombytes('RGB', sct_img.size, sct_img.bgra, 'raw', 'BGRX')

# BLE communication with ESP32
async def send_data_to_esp32():
    async with BleakClient(ESP32_MAC_ADDRESS) as client:
        print("Connected to ESP32 Bluetooth!")

        while True:
            screenshot = capture_screenshot()
            l = list(round(i) for i in ImageStat.Stat(screenshot).mean)
            s = f"{l[0]} {l[1]} {l[2]}\n"
            print(s)

            # Send data over BLE (change the characteristic handle as needed)
            # Replace 'your_characteristic_uuid' with the actual UUID of the characteristic you're using
            await client.write_gatt_char('your_characteristic_uuid', bytes(s, 'utf-8'))

async def main():
    await send_data_to_esp32()

if __name__ == "__main__":
    asyncio.run(main())
