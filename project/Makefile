# makfile configuration
COMMON_OBJECTS  = main.o
CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU}
LDFLAGS		= -L/opt/ti/msp430_gcc/include
OBJ = buzzer.o stateMachines.o led.o wdInterruptHandler.o

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-as

all: project.elf 

# additional rules for files
project.elf: ${COMMON_OBJECTS} ${OBJ} libTimer.a
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^

load: project.elf
	msp430loader.sh $^

clean: $^
	rm -f *.o *.elf

led.o: led.h led.c
wdInterruptHandler.o: led.h wdInterruptHandler.h
stateMachines.o: led.h stateMachines.h
buzzer.c: buzzer.h
main.c: buzzer.h led.h wdInterruptHandler.h

