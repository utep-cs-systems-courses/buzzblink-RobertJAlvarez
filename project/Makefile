# makfile configuration
COMMON_OBJECTS  = 
CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} -I./h
LDFLAGS		= -L/opt/ti/msp430_gcc/include

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-as

all: timLib proj.elf 

timLib:
	(cd timerLib && make install)

#additional rules for files
proj.elf: ${COMMON_OBJECTS} buzzer.o interrupt_handler.o main.o stateMachines.o led.o switches.o  ./lib/libTimer.a
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^

load: proj.elf
	msp430loader.sh proj.elf

clean:
	rm -rf h lib
	rm -f *.o *.elf

led.o: led.c led.h switches.h
switches.o: switches.c switches.h led.h buzzer.h
stateMachines.o: led.h stateMachines.h buzzer.h
buzzer.c: buzzer.h
main.c: buzzer.h led.h switches.h

