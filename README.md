# Safe
This project is a Safe (a closed box where you keep your money safe) which asks user to create a password if it runs for its first time but if it is turned off and turned on after creating password it asks user for password to enter to compare it to previously created password



## Devices used:

-Atmega32 (where we put our code to do specific functions)

-LCD 16x2 (for displaying each number of password instantaneously then turning each number into astrisk(*) and for displayed instructions to follow and results of entered password)

-Keypad 4x4 (is used for setting password (create password if no password is stored in EEPROM yet) and for entering password if there is a password stored in EEPROM)

-Internal EEPROM (where created password is stored to be compared to entered passwords)

## tools used:

-Proteus 8 Professional

-Atmel Studio 6.0


## Disadvantages:

-It needs a Servo motor that opens it automatically if the entered password is correct

## note:
