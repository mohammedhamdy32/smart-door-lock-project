# smart-door-lock-project
This is a smart door lock project using a password

I used two atmega32 microcontrollers to make this project ,the two controllers communicate with each other by serial UART protocol,The first microcontroller is used in interfacing with the user,it is connected with an LCD and a keypad ,The second microcontroller is used to check the password and open the door, It's connected with an external EEPROM to save the password in it, and a motor which open or close the door, and a buzzer to make a sound it the password is entered 3 times incorrect.

