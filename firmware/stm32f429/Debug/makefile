################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include TouchGFX/target/subdir.mk
-include TouchGFX/gui/src/screen1_screen/subdir.mk
-include TouchGFX/gui/src/model/subdir.mk
-include TouchGFX/gui/src/common/subdir.mk
-include TouchGFX/generated/texts/src/subdir.mk
-include TouchGFX/generated/images/src/__designer/subdir.mk
-include TouchGFX/generated/images/src/subdir.mk
-include TouchGFX/generated/gui_generated/src/screen1_screen/subdir.mk
-include TouchGFX/generated/gui_generated/src/common/subdir.mk
-include TouchGFX/generated/fonts/src/subdir.mk
-include TouchGFX/build/MINGW32_NT-6.2/touchgfx/framework/source/platform/hal/simulator/sdl2/subdir.mk
-include TouchGFX/build/MINGW32_NT-6.2/touchgfx/framework/source/platform/driver/touch/subdir.mk
-include TouchGFX/build/MINGW32_NT-6.2/simulator/subdir.mk
-include TouchGFX/build/MINGW32_NT-6.2/gui/src/screen1_screen/subdir.mk
-include TouchGFX/build/MINGW32_NT-6.2/gui/src/model/subdir.mk
-include TouchGFX/build/MINGW32_NT-6.2/gui/src/common/subdir.mk
-include TouchGFX/build/MINGW32_NT-6.2/generated/texts/src/subdir.mk
-include TouchGFX/build/MINGW32_NT-6.2/generated/images/src/__designer/subdir.mk
-include TouchGFX/build/MINGW32_NT-6.2/generated/images/src/subdir.mk
-include TouchGFX/build/MINGW32_NT-6.2/generated/gui_generated/src/screen1_screen/subdir.mk
-include TouchGFX/build/MINGW32_NT-6.2/generated/gui_generated/src/common/subdir.mk
-include TouchGFX/build/MINGW32_NT-6.2/generated/fonts/src/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/subdir.mk
-include Middlewares/ST/TouchGFX/touchgfx/os/subdir.mk
-include Middlewares/ST/TouchGFX/touchgfx/framework/source/touchgfx/widgets/canvas/subdir.mk
-include Middlewares/ST/TouchGFX/touchgfx/framework/source/touchgfx/widgets/subdir.mk
-include Middlewares/ST/TouchGFX/touchgfx/framework/source/touchgfx/containers/scrollers/subdir.mk
-include Middlewares/ST/TouchGFX/touchgfx/framework/source/touchgfx/containers/progress_indicators/subdir.mk
-include Middlewares/ST/TouchGFX/touchgfx/framework/source/touchgfx/containers/clock/subdir.mk
-include Middlewares/ST/TouchGFX/touchgfx/framework/source/touchgfx/containers/subdir.mk
-include Middlewares/ST/TouchGFX/touchgfx/framework/source/platform/driver/touch/subdir.mk
-include Drivers/STM32F4xx_HAL_Driver/Src/subdir.mk
-include Drivers/BSP/STM32F429I-Discovery/subdir.mk
-include Drivers/BSP/Components/ts3510/subdir.mk
-include Drivers/BSP/Components/stmpe811/subdir.mk
-include Drivers/BSP/Components/ili9341/subdir.mk
-include Drivers/BSP/Components/exc7200/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
cs301_proj.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
cs301_proj.list \


# All Target
all: cs301_proj.elf secondary-outputs

# Tool invocations
cs301_proj.elf: $(OBJS) $(USER_OBJS) C:\Users\tonny\STM32CubeIDE\workspace_1.1.0\cs301_proj\STM32F429ZITX_FLASH.ld
	arm-none-eabi-g++ -o "cs301_proj.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"C:\Users\tonny\STM32CubeIDE\workspace_1.1.0\cs301_proj\STM32F429ZITX_FLASH.ld" --specs=nosys.specs -Wl,-Map="cs301_proj.map" -Wl,--gc-sections -static -L../Middlewares/ST/TouchGFX/touchgfx/lib/core/cortex_m4f/gcc --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -lstdc++ -lsupc++ -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

cs301_proj.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "cs301_proj.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
