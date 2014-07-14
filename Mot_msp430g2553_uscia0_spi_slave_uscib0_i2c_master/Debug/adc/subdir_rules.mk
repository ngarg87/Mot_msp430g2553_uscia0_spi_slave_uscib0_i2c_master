################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
adc/adc10.obj: ../adc/adc10.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv5/tools/compiler/msp430_4.1.2/bin/cl430" -vmsp --abi=eabi -g --include_path="C:/DLara-wa/workspace_msp430_motorola/msp430g2553_uscia0_spi_slave_uscib0_i2c_master/spi_drv" --include_path="C:/DLara-wa/workspace_msp430_motorola/msp430g2553_uscia0_spi_slave_uscib0_i2c_master/adc" --include_path="C:/DLara-wa/workspace_msp430_motorola/msp430g2553_uscia0_spi_slave_uscib0_i2c_master/sdq_drv" --include_path="C:/DLara-wa/workspace_msp430_motorola/msp430g2553_uscia0_spi_slave_uscib0_i2c_master/os" --include_path="C:/DLara-wa/workspace_msp430_motorola/msp430g2553_uscia0_spi_slave_uscib0_i2c_master/i2c_drv" --include_path="C:/ti/ccsv5/ccs_base/msp430/include" --include_path="C:/DLara-wa/workspace_msp430_motorola/msp430g2553_uscia0_spi_slave_uscib0_i2c_master" --include_path="C:/ti/ccsv5/tools/compiler/msp430_4.1.2/include" --advice:power=all --define=__MSP430G2553__ --diag_warning=225 --display_error_number --diag_wrap=off --printf_support=minimal --preproc_with_compile --preproc_dependency="adc/adc10.pp" --obj_directory="adc" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


