################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../TouchGFX/generated/images/src/BitmapDatabase.cpp \
../TouchGFX/generated/images/src/bg2.cpp 

OBJS += \
./TouchGFX/generated/images/src/BitmapDatabase.o \
./TouchGFX/generated/images/src/bg2.o 

CPP_DEPS += \
./TouchGFX/generated/images/src/BitmapDatabase.d \
./TouchGFX/generated/images/src/bg2.d 


# Each subdirectory must supply rules for building sources it contributes
TouchGFX/generated/images/src/BitmapDatabase.o: ../TouchGFX/generated/images/src/BitmapDatabase.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F429xx -c -I../TouchGFX/gui/include -I../USB_HOST/App -I../TouchGFX/generated/fonts/include -I../Drivers/BSP/Components/ts3510 -I../Drivers/BSP/STM32F429I-Discovery -I../TouchGFX/generated/texts/include -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../TouchGFX/generated/images/include -I../Drivers/BSP/Components/ili9341 -I../Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Core/Inc -I../Middlewares/ST/TouchGFX/touchgfx/framework/include -I../TouchGFX/generated/gui_generated/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Drivers/BSP/Components/exc7200 -I../Drivers/BSP/Components/stmpe811 -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Drivers/CMSIS/Include -I../Drivers/BSP/Components/Common -I../USB_HOST/Target -I../Drivers/BSP/Components/ampire480272 -I../TouchGFX/target -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-threadsafe-statics -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"TouchGFX/generated/images/src/BitmapDatabase.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
TouchGFX/generated/images/src/bg2.o: ../TouchGFX/generated/images/src/bg2.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F429xx -c -I../TouchGFX/gui/include -I../USB_HOST/App -I../TouchGFX/generated/fonts/include -I../Drivers/BSP/Components/ts3510 -I../Drivers/BSP/STM32F429I-Discovery -I../TouchGFX/generated/texts/include -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../TouchGFX/generated/images/include -I../Drivers/BSP/Components/ili9341 -I../Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Core/Inc -I../Middlewares/ST/TouchGFX/touchgfx/framework/include -I../TouchGFX/generated/gui_generated/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Drivers/BSP/Components/exc7200 -I../Drivers/BSP/Components/stmpe811 -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Drivers/CMSIS/Include -I../Drivers/BSP/Components/Common -I../USB_HOST/Target -I../Drivers/BSP/Components/ampire480272 -I../TouchGFX/target -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-threadsafe-statics -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"TouchGFX/generated/images/src/bg2.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

