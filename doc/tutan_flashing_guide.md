TuTan's step by step flashing guide for Arduino Pro Micro on Windows 10
==================================================

# Install tools
My first reference was this: http://fab.cba.mit.edu/classes/863.16/doc/projects/ftsmin/windows_avr.html
#### Mingw
You can use Git BASH as a Mingw shell and skip this step.

#### GNU make
https://www.gnu.org/software/make/

#### AVR toolchain
I used this: 
https://ww1.microchip.com/downloads/archive/avr-toolchain-installer-3.4.1.1195-win32.win32.x86.exe

Or you can go to [this site](https://www.microchip.com/en-us/development-tools-tools-and-software/avr-and-sam-downloads-archive#AVR%20and%20ARM%20Toolchains) for other versions. (Small hint: some links in the site use http and won't open on Chrome, you'll need to change them to https)

#### avrdude & USB drivers
I just installed [Arduino IDE](https://www.arduino.cc/en/software) and enjoy avrdude & drivers that come along.
Or you can follow the instructions from [my first reference](http://fab.cba.mit.edu/classes/863.16/doc/projects/ftsmin/windows_avr.html) to install them separately.

#### Add PATH
Mine looks something like this:

    C:\Program Files (x86)\GnuWin32\bin
    C:\Program Files (x86)\Atmel\AVR Tools\AVR Toolchain\avr\bin

If you install avrdude separately instead of using Arduino IDE, you should have to add its path as well.

#### Sanity check
Go to _keyboards\split_keyboard_ then start Git BASH (Note: You may have to start Git BASH as Admin.)

In the bash shell, use these commands:

- `make -v`

Output:

    GNU Make 3.81
    Copyright (C) 2006  Free Software Foundation, Inc.
    ...

- `avr-gcc --version`

Output:

    avr-gcc.exe (AVR_8_bit_GNU_Toolchain_3.4.1_798) 4.6.2
    Copyright (C) 2011 Free Software Foundation, Inc.
    ...

- `avrdude`

Output:

    Usage: avrdude.exe [options]
    Options:
    ...
    avrdude version 5.10, URL: <http://savannah.nongnu.org/projects/avrdude/>

# Flash

#### Compile firmware
Go to _keyboards\split_keyboard_ then start Git BASH (Note: You may have to start Git BASH as Admin.)

In the bash shell, use this command:

`make`

The output should end with something like:

	Creating load file for Flash: split_keyboard.hex
	avr-objcopy -O ihex -R .eeprom -R .fuse -R .lock -R .signature split_keyboard.elf split_keyboard.hex
	
	Creating load file for EEPROM: split_keyboard.eep
	avr-objcopy -j .eeprom --set-section-flags=.eeprom="alloc,load" \
        --change-section-lma .eeprom=0 --no-change-warnings -O ihex split_keyboard.elf split_keyboard.eep || exit 0
	
	Creating Extended Listing: split_keyboard.lss
	avr-objdump -h -S -z split_keyboard.elf > split_keyboard.lss
	
	Creating Symbol Table: split_keyboard.sym
	avr-nm -n split_keyboard.elf > split_keyboard.sym
	
	Size after:
		text    data     bss     dec     hex filename
		23500      74     256   23830    5d16 split_keyboard.elf
	
		-------- end --------
	
#### Check COM connection
- Connect your Arduino Pro Micro to PC
- Open Device Manager, under Port... you should find Arduino Leonardo (COM#1) (COM and a number. e.g. COM3)
- Reset your Arduino (Connect RST pin to ground then disconnect)\
- In Device Manager, under Port, you should now find Arduino Leonardo bootloader (COM#2) (COM and another number, normaly #2 = #1 + 1. e.g. COM4)

(Note: If you do nothing, the Arduino board will stay in bootloader mode for only 8s)
- Go to Makefile, change COM_PORT=COM#2 

e.g.

    COM_PORT=COM4
    

#### Flash EEPROM

EEPROM code define if this half is the left half or right.
- Connect your Arduino Pro Micro to PC
- Reset your Arduino
- Within 8s of bootloader mode, run command:

either

    make eeprom-right
    

or

    make eeprom-left
    

depending on which half you are flashing.

#### Flash firmware
- Connect your Arduino Pro Micro to PC
- Reset your Arduino
- Within 8s of bootloader mode, run command:

	make program
	

And that should do it.
