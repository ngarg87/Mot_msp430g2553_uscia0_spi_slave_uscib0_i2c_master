################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
sdq/msp430_sdqlib.obj: ../sdq/msp430_sdqlib.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti_v5.2.0.00069/ccsv5/tools/compiler/msp430_4.1.0/bin/cl430" -vmsp --abi=eabi -g --include_path="C:/Documents and Settings/a0220883/MyWorkspaceMSP430/msp430g2553_uscia0_spi_slave_uscib0_i2c_master/spi_drv" --include_path="C:/Documents and Settings/a0220883/MyWorkspaceMSP430/msp430g2553_uscia0_spi_slave_uscib0_i2c_master/os" --include_path="C:/Documents and Settings/a0220883/MyWorkspaceMSP430/msp430g2553_uscia0_spi_slave_uscib0_i2c_master/i2c_drv" --include_path="C:/ti_v5.2.0.00069/ccsv5/ccs_base/msp430/include" --include_path="C:/Documents and Settings/a0220883/MyWorkspaceMSP430/msp430g2553_uscia0_spi_slave_uscib0_i2c_master" --include_path="C:/ti_v5.2.0.00069/ccsv5/tools/compiler/msp430_4.1.0/include" --advice:power=all --define=__MSP430G2553__ --diag_warning=225 --display_error_number --diag_wrap=off --printf_support=minimal --preproc_with_compile --preproc_dependency="sdq/msp430_sdqlib.pp" --obj_directory="sdq" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

sdq/sdq_writebyte.obj: ../sdq/sdq_writebyte.asm $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti_v5.2.0.00069/ccsv5/tools/compiler/msp430_4.1.0/bin/cl430" -vmsp --abi=eabi -g --include_path="C:/Documents and Settings/a0220883/MyWorkspaceMSP430/msp430g2553_uscia0_spi_slave_uscib0_i2c_master/spi_drv" --include_path="C:/Documents and Settings/a0220883/MyWorkspaceMSP430/msp430g2553_uscia0_spi_slave_uscib0_i2c_master/os" --include_path="C:/Documents and Settings/a0220883/MyWorkspaceMSP430/msp430g2553_uscia0_spi_slave_uscib0_i2c_master/i2c_drv" --include_path="C:/ti_v5.2.0.00069/ccsv5/ccs_base/msp430/include" --include_path="C:/Documents and Settings/a0220883/MyWorkspaceMSP430/msp430g2553_uscia0_spi_slave_uscib0_i2c_master" --include_path="C:/ti_v5.2.0.00069/ccsv5/tools/compiler/msp430_4.1.0/include" --advice:power=all --define=__MSP430G2553__ --diag_warning=225 --display_error_number --diag_wrap=off --printf_support=minimal --preproc_with_compile --preproc_dependency="sdq/sdq_writebyte.pp" --obj_directory="sdq" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


