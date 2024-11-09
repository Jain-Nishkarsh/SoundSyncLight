from mss import mss
import math
from PIL import Image

def capture_screenshot():
    # Capture entire screen
    with mss() as sct:
        monitor = sct.monitors[1]
        sct_img = sct.grab(monitor)
        # Convert to PIL/Pillow Image
        return Image.frombytes('RGB', sct_img.size, sct_img.bgra, 'raw', 'BGRX')

# img = capture_screenshot()
# img.show()

# import numpy as np
from PIL import ImageGrab, ImageStat
# import time
import serial

l = []
arduino = serial.Serial(port = '/dev/cu.usbserial-0001', baudrate=115200, timeout=.1)

while True:
    wtf = capture_screenshot()
    # l:list = ImageStat.Stat(wtf).mean
    l = list(round(i) for i in ImageStat.Stat(wtf).mean)
    # red = min(math.floor((l[0]) * red_multiplier), 255)
    # green = min(math.floor((l[1]) * green_multiplier), 255)
    # blue = min(math.floor((l[2]) * blue_multiplier), 255)
    s = f"{l[0]} {l[1]} {l[2]}\n"
    print(s)
    arduino.write(bytes(s, 'utf-8'))
    # time.sleep(0.1)
