################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers_huy/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.c \
../Drivers_huy/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_adc.c \
../Drivers_huy/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_adc_ex.c \
../Drivers_huy/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.c \
../Drivers_huy/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_crc.c \
../Drivers_huy/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.c \
../Drivers_huy/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma_ex.c \
../Drivers_huy/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_exti.c \
../Drivers_huy/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash.c \
../Drivers_huy/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ex.c \
../Drivers_huy/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ramfunc.c \
../Drivers_huy/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.c \
../Drivers_huy/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_hcd.c \
../Drivers_huy/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_i2c.c \
../Drivers_huy/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_i2c_ex.c \
../Drivers_huy/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_i2s.c \
../Drivers_huy/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_i2s_ex.c \
../Drivers_huy/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_iwdg.c \
../Drivers_huy/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr.c \
../Drivers_huy/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr_ex.c \
../Drivers_huy/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.c \
../Drivers_huy/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc_ex.c \
../Drivers_huy/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rtc.c \
../Drivers_huy/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rtc_ex.c \
../Drivers_huy/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_spi.c \
../Drivers_huy/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim.c \
../Drivers_huy/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim_ex.c \
../Drivers_huy/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_uart.c \
../Drivers_huy/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_wwdg.c \
../Drivers_huy/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_adc.c \
../Drivers_huy/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_usb.c 

OBJS += \
./Drivers_huy/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.o \
./Drivers_huy/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_adc.o \
./Drivers_huy/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_adc_ex.o \
./Drivers_huy/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.o \
./Drivers_huy/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_crc.o \
./Drivers_huy/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.o \
./Drivers_huy/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma_ex.o \
./Drivers_huy/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_exti.o \
./Drivers_huy/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash.o \
./Drivers_huy/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ex.o \
./Drivers_huy/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ramfunc.o \
./Drivers_huy/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.o \
./Drivers_huy/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_hcd.o \
./Drivers_huy/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_i2c.o \
./Drivers_huy/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_i2c_ex.o \
./Drivers_huy/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_i2s.o \
./Drivers_huy/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_i2s_ex.o \
./Drivers_huy/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_iwdg.o \
./Drivers_huy/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr.o \
./Drivers_huy/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr_ex.o \
./Drivers_huy/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.o \
./Drivers_huy/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc_ex.o \
./Drivers_huy/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rtc.o \
./Drivers_huy/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rtc_ex.o \
./Drivers_huy/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_spi.o \
./Drivers_huy/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim.o \
./Drivers_huy/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim_ex.o \
./Drivers_huy/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_uart.o \
./Drivers_huy/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_wwdg.o \
./Drivers_huy/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_adc.o \
./Drivers_huy/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_usb.o 

C_DEPS += \
./Drivers_huy/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.d \
./Drivers_huy/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_adc.d \
./Drivers_huy/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_adc_ex.d \
./Drivers_huy/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.d \
./Drivers_huy/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_crc.d \
./Drivers_huy/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.d \
./Drivers_huy/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma_ex.d \
./Drivers_huy/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_exti.d \
./Drivers_huy/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash.d \
./Drivers_huy/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ex.d \
./Drivers_huy/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ramfunc.d \
./Drivers_huy/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.d \
./Drivers_huy/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_hcd.d \
./Drivers_huy/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_i2c.d \
./Drivers_huy/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_i2c_ex.d \
./Drivers_huy/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_i2s.d \
./Drivers_huy/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_i2s_ex.d \
./Drivers_huy/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_iwdg.d \
./Drivers_huy/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr.d \
./Drivers_huy/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr_ex.d \
./Drivers_huy/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.d \
./Drivers_huy/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc_ex.d \
./Drivers_huy/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rtc.d \
./Drivers_huy/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rtc_ex.d \
./Drivers_huy/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_spi.d \
./Drivers_huy/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim.d \
./Drivers_huy/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim_ex.d \
./Drivers_huy/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_uart.d \
./Drivers_huy/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_wwdg.d \
./Drivers_huy/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_adc.d \
./Drivers_huy/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_usb.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers_huy/STM32F4xx_HAL_Driver/Src/%.o: ../Drivers_huy/STM32F4xx_HAL_Driver/Src/%.c Drivers_huy/STM32F4xx_HAL_Driver/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers_huy/STM32F4xx_HAL_Driver/Inc -I../Drivers_huy/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers_huy/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers_huy/CMSIS/Include -I../Drivers/CMSIS/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I"C:/Users/Admin/Embedded-C/My_workspace/project_2/project2/src/common/inc" -I"C:/Users/Admin/Embedded-C/My_workspace/project_2/project2/src/hal/inc" -I"C:/Users/Admin/Embedded-C/My_workspace/project_2/project2/src/inc/api" -I"C:/Users/Admin/Embedded-C/My_workspace/project_2/project2/src/inc/internal" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

