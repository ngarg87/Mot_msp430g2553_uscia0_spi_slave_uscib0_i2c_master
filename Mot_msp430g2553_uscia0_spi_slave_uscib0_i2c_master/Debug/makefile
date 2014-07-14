################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/TI2/ccsv5/tools/compiler/msp430_4.1.5

ORDERED_OBJS += \
$(GEN_CMDS__FLAG) \
"./i2c_drv/uscib0_i2c_drv.obj" \
"./i2c_drv/i2c_msg.obj" \
"./os/os_tasks.obj" \
"./os/os.obj" \
"./sdq_drv/sdq_writebyte.obj" \
"./sdq_drv/msp430_sdqlib.obj" \
"./sdq_drv/eprom_sdq.obj" \
"./spi_drv/uscia0_spi_drv.obj" \
"./spi_drv/spi_com.obj" \
"./main.obj" \
"./app_status.obj" \
-l"libc.a" \
"../lnk_msp430g2553.cmd" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include spi_drv/subdir_vars.mk
-include sdq_drv/subdir_vars.mk
-include os/subdir_vars.mk
-include i2c_drv/subdir_vars.mk
-include subdir_rules.mk
-include spi_drv/subdir_rules.mk
-include sdq_drv/subdir_rules.mk
-include os/subdir_rules.mk
-include i2c_drv/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: Mot_msp430g2553_uscia0_spi_slave_uscib0_i2c_master.out

# Tool invocations
Mot_msp430g2553_uscia0_spi_slave_uscib0_i2c_master.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: MSP430 Linker'
	"C:/TI2/ccsv5/tools/compiler/msp430_4.1.5/bin/cl430" -vmsp --abi=eabi -g --advice:power="all" --define=__MSP430G2553__ --diag_warning=225 --display_error_number --diag_wrap=off --printf_support=minimal -z --stack_size=80 -m"Mot_msp430g2553_uscia0_spi_slave_uscib0_i2c_master.map" --heap_size=80 -i"C:/TI2/ccsv5/ccs_base/msp430/include" -i"C:/TI2/ccsv5/tools/compiler/msp430_4.1.5/lib" -i"C:/TI2/ccsv5/tools/compiler/msp430_4.1.5/include" --reread_libs --warn_sections --display_error_number --diag_wrap=off --rom_model -o "Mot_msp430g2553_uscia0_spi_slave_uscib0_i2c_master.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '
	@$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(MSP430_EXECUTABLE_OUTPUTS__QUOTED) "Mot_msp430g2553_uscia0_spi_slave_uscib0_i2c_master.out"
	-$(RM) "app_status.pp" "main.pp" "spi_drv\spi_com.pp" "spi_drv\uscia0_spi_drv.pp" "sdq_drv\eprom_sdq.pp" "sdq_drv\msp430_sdqlib.pp" "os\os.pp" "os\os_tasks.pp" "i2c_drv\i2c_msg.pp" "i2c_drv\uscib0_i2c_drv.pp" 
	-$(RM) "app_status.obj" "main.obj" "spi_drv\spi_com.obj" "spi_drv\uscia0_spi_drv.obj" "sdq_drv\eprom_sdq.obj" "sdq_drv\msp430_sdqlib.obj" "sdq_drv\sdq_writebyte.obj" "os\os.obj" "os\os_tasks.obj" "i2c_drv\i2c_msg.obj" "i2c_drv\uscib0_i2c_drv.obj" 
	-$(RM) "sdq_drv\sdq_writebyte.pp" 
	-@echo 'Finished clean'
	-@echo ' '

post-build:
	-@echo 'Create flash image: TI-TXT'
	-"C:/TI2/ccsv5/tools/compiler/msp430_4.1.5/bin/hex430" --ti_txt "Mot_msp430g2553_uscia0_spi_slave_uscib0_i2c_master.out" -o "Mot_msp430g2553_uscia0_spi_slave_uscib0_i2c_master.txt" -order MS -romwidth 16
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
