################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
app_status.obj: ../app_status.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/TI2/ccsv5/tools/compiler/msp430_4.1.5/bin/cl430" -vmsp --abi=eabi -g --include_path="C:/Users/a0272323/Desktop/Bay/Motorola/Arris 7-5-13 2.08/Arris 6-24-13 2.07/Mot 6-7-13 2.04_battery_update/2-21-12 Mot spi-i2c/Mot SPI/Mot_msp430g2553_uscia0_spi_slave_uscib0_i2c_master/spi_drv" --include_path="C:/Users/a0272323/Desktop/Bay/Motorola/Arris 7-5-13 2.08/Arris 6-24-13 2.07/Mot 6-7-13 2.04_battery_update/2-21-12 Mot spi-i2c/Mot SPI/Mot_msp430g2553_uscia0_spi_slave_uscib0_i2c_master/sdq_drv" --include_path="C:/Users/a0272323/Desktop/Bay/Motorola/Arris 7-5-13 2.08/Arris 6-24-13 2.07/Mot 6-7-13 2.04_battery_update/2-21-12 Mot spi-i2c/Mot SPI/Mot_msp430g2553_uscia0_spi_slave_uscib0_i2c_master/os" --include_path="C:/Users/a0272323/Desktop/Bay/Motorola/Arris 7-5-13 2.08/Arris 6-24-13 2.07/Mot 6-7-13 2.04_battery_update/2-21-12 Mot spi-i2c/Mot SPI/Mot_msp430g2553_uscia0_spi_slave_uscib0_i2c_master/i2c_drv" --include_path="C:/TI2/ccsv5/ccs_base/msp430/include" --include_path="C:/Users/a0272323/Desktop/Bay/Motorola/Arris 7-5-13 2.08/Arris 6-24-13 2.07/Mot 6-7-13 2.04_battery_update/2-21-12 Mot spi-i2c/Mot SPI/Mot_msp430g2553_uscia0_spi_slave_uscib0_i2c_master" --include_path="C:/TI2/ccsv5/tools/compiler/msp430_4.1.5/include" --advice:power="all" --define=__MSP430G2553__ --diag_warning=225 --display_error_number --diag_wrap=off --printf_support=minimal --preproc_with_compile --preproc_dependency="app_status.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

main.obj: ../main.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/TI2/ccsv5/tools/compiler/msp430_4.1.5/bin/cl430" -vmsp --abi=eabi -g --include_path="C:/Users/a0272323/Desktop/Bay/Motorola/Arris 7-5-13 2.08/Arris 6-24-13 2.07/Mot 6-7-13 2.04_battery_update/2-21-12 Mot spi-i2c/Mot SPI/Mot_msp430g2553_uscia0_spi_slave_uscib0_i2c_master/spi_drv" --include_path="C:/Users/a0272323/Desktop/Bay/Motorola/Arris 7-5-13 2.08/Arris 6-24-13 2.07/Mot 6-7-13 2.04_battery_update/2-21-12 Mot spi-i2c/Mot SPI/Mot_msp430g2553_uscia0_spi_slave_uscib0_i2c_master/sdq_drv" --include_path="C:/Users/a0272323/Desktop/Bay/Motorola/Arris 7-5-13 2.08/Arris 6-24-13 2.07/Mot 6-7-13 2.04_battery_update/2-21-12 Mot spi-i2c/Mot SPI/Mot_msp430g2553_uscia0_spi_slave_uscib0_i2c_master/os" --include_path="C:/Users/a0272323/Desktop/Bay/Motorola/Arris 7-5-13 2.08/Arris 6-24-13 2.07/Mot 6-7-13 2.04_battery_update/2-21-12 Mot spi-i2c/Mot SPI/Mot_msp430g2553_uscia0_spi_slave_uscib0_i2c_master/i2c_drv" --include_path="C:/TI2/ccsv5/ccs_base/msp430/include" --include_path="C:/Users/a0272323/Desktop/Bay/Motorola/Arris 7-5-13 2.08/Arris 6-24-13 2.07/Mot 6-7-13 2.04_battery_update/2-21-12 Mot spi-i2c/Mot SPI/Mot_msp430g2553_uscia0_spi_slave_uscib0_i2c_master" --include_path="C:/TI2/ccsv5/tools/compiler/msp430_4.1.5/include" --advice:power="all" --define=__MSP430G2553__ --diag_warning=225 --display_error_number --diag_wrap=off --printf_support=minimal --preproc_with_compile --preproc_dependency="main.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


