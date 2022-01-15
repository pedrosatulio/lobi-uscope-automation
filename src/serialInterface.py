#   Automation of LOBI's Eclipse TE2000 Inverted Microscope
#   Computer <--> Arduino interface

#   Developer:
#       MSc. Tulio Pedrosa(tulio.pedrosa@ufpe.br)
#       Hardware Engineer

#   LOBI - Laboratório de Óptica Biomédica e Imagens
#   Date: January 15th, 2022


import time
import serial
import keyboard

arduino = serial.Serial('COM17', 9600, timeout=0.1) # Initializing serial

while True:
    try:
        if keyboard.is_pressed('page up'):                # If key 'w' is pressed
            arduino.write(str.encode('w'))
            print('z-axis foward step')
        if keyboard.is_pressed('page down'):                # If key 's' is pressed
            arduino.write(str.encode('s'))
            print('z-axis backward step')
        time.sleep(0.05)
    except:
        break                                       # Break loop if another key is pressed