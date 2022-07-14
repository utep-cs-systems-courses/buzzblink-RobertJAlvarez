# makfile configuration
COMMON_OBJECTS  = buzzer.o interrupt_handler.o main.o stateMachines.o led.o switches.o
CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} -I./h
LDFLAGS		= -L/opt/ti/msp430_gcc/include

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-as

all: timLib proj-c.elf# proj-s.elf

timLib:
	(cd timerLib && make install)

#additional rules for files
proj-c.elf: ${COMMON_OBJECTS} select_SM-c.o  ./lib/libTimer.a
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^

#proj-s.elf: ${COMMON_OBJECTS} select_SM-s.o ./lib/libTimer.a
#	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^

load-c: proj-c.elf
	msp430loader.sh $^

#load-s: proj-s.elf
#	msp430loader.sh $^

clean:
	rm -rf h lib
	rm -f *.o *.elf

led.o: led.c led.h switches.h
switches.o: switches.c switches.h led.h buzzer.h
stateMachines.o: led.h stateMachines.h buzzer.h
buzzer.c: buzzer.h
main.c: buzzer.h led.h switches.h

