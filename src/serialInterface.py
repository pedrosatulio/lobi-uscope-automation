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
    light_ctrl = '\0'
    try:
        if keyboard.is_pressed('a'):                # If key 'a' is pressed
            arduino.write(str.encode('a'))
            print('x-axis backward step (left)')
        if keyboard.is_pressed('d'):                # If key 'd' is pressed
            arduino.write(str.encode('d'))
            print('x-axis forward step (right)')
        if keyboard.is_pressed('w'):                # If key 'w' is pressed
            arduino.write(str.encode('w'))
            print('y-axis forward step (up)')
        if keyboard.is_pressed('s'):                # If key 's' is pressed
            arduino.write(str.encode('s'))
            print('y-axis backward step (down)')
        if keyboard.is_pressed('page up'):          # If key 'page up' is pressed
            arduino.write(str.encode('+'))
            print('z-axis zoom-in')
        if keyboard.is_pressed('page down'):        # If key 'page down' is pressed
            arduino.write(str.encode('-'))
            print('z-axis zoom-out')
        if keyboard.is_pressed('q'):                # If key 'q' is pressed
            arduino.write(str.encode('q'))
            light_ctrl = 'q'
        if keyboard.is_pressed('e'):                # If key 'e' is pressed
            arduino.write(str.encode('e'))
            light_ctrl = 'e'
        time.sleep(0.05)
    except:
        break                                       # Break loop if another key is pressed

    if (light_ctrl == 'q'):
        print('Enter intensity percentage of white light')
        msDelayTime = input()
        arduino.write(str.encode(msDelayTime))
    elif (light_ctrl == 'e'):
        print('Enter intensity percentage of infrared light')
        msDelayTime = input()
        arduino.write(str.encode(msDelayTime))
