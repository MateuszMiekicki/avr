import os
nameFile = "main"
portName = "COM6"
speedBand = "115200"
cmdSet = ["avr-gcc -Os -Wall -Wextra -std=c11 -DF_CPU=16000000UL -mmcu=atmega328p -c -o "+nameFile+".o "+nameFile+".c",
"avr-gcc -mmcu=atmega328p "+nameFile+".o "+"-o "+nameFile,
"avr-objcopy -O ihex -R .eeprom "+nameFile+" "+nameFile+".hex",
"avrdude -F -V -c arduino -p ATMEGA328P -P "+ portName+" -b "+speedBand+" "+"-U flash:w:"+nameFile+".hex"]
for command in cmdSet:
    os.system(command)