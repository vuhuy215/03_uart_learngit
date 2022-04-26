################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/iec60870/cs101/cs101_asdu.c \
../src/iec60870/cs101/cs101_bcr.c \
../src/iec60870/cs101/cs101_information_objects.c \
../src/iec60870/cs101/cs101_master.c \
../src/iec60870/cs101/cs101_master_connection.c \
../src/iec60870/cs101/cs101_queue.c \
../src/iec60870/cs101/cs101_slave.c 

OBJS += \
./src/iec60870/cs101/cs101_asdu.o \
./src/iec60870/cs101/cs101_bcr.o \
./src/iec60870/cs101/cs101_information_objects.o \
./src/iec60870/cs101/cs101_master.o \
./src/iec60870/cs101/cs101_master_connection.o \
./src/iec60870/cs101/cs101_queue.o \
./src/iec60870/cs101/cs101_slave.o 

C_DEPS += \
./src/iec60870/cs101/cs101_asdu.d \
./src/iec60870/cs101/cs101_bcr.d \
./src/iec60870/cs101/cs101_information_objects.d \
./src/iec60870/cs101/cs101_master.d \
./src/iec60870/cs101/cs101_master_connection.d \
./src/iec60870/cs101/cs101_queue.d \
./src/iec60870/cs101/cs101_slave.d 


# Each subdirectory must supply rules for building sources it contributes
src/iec60870/cs101/%.o: ../src/iec60870/cs101/%.c src/iec60870/cs101/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers_huy/STM32F4xx_HAL_Driver/Inc -I../Drivers_huy/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers_huy/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers_huy/CMSIS/Include -I../Drivers/CMSIS/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I"C:/Users/huy/Embedded-C/My_workspace/project_2/project2/src/common/inc" -I"C:/Users/huy/Embedded-C/My_workspace/project_2/project2/src/hal/inc" -I"C:/Users/huy/Embedded-C/My_workspace/project_2/project2/src/inc/api" -I"C:/Users/huy/Embedded-C/My_workspace/project_2/project2/src/inc/internal" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

