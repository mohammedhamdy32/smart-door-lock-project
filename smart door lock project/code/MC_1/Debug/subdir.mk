################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Buzzer.c \
../Timer1.c \
../UART.c \
../application.c \
../dc_motor.c \
../external_eeprom.c \
../gpio.c \
../keypad.c \
../lcd.c \
../main.c \
../twi.c 

OBJS += \
./Buzzer.o \
./Timer1.o \
./UART.o \
./application.o \
./dc_motor.o \
./external_eeprom.o \
./gpio.o \
./keypad.o \
./lcd.o \
./main.o \
./twi.o 

C_DEPS += \
./Buzzer.d \
./Timer1.d \
./UART.d \
./application.d \
./dc_motor.d \
./external_eeprom.d \
./gpio.d \
./keypad.d \
./lcd.d \
./main.d \
./twi.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


