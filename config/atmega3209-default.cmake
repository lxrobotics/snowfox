##########################################################################

set(MCU_ARCH avr)

##########################################################################
# AVR ####################################################################
########################################################################## 

set(MCU_TYPE atmega3209)
set(MCU_SPEED 16000000UL)

##########################################################################
# DRIVER #################################################################
##########################################################################

set(DRIVER_CAN_MCP2515 yes)

set(DRIVER_GLCD_RA6963 yes)

set(DRIVER_HAPTIC_DRV2605 yes)

set(DRIVER_IOEXPANDER_MCP23017 yes)
set(DRIVER_IOEXPANDER_PCA9547 yes)

set(DRIVER_LORA_RFM9x yes)

set(DRIVER_MEMORY_AT45DBX yes)
set(DRIVER_MEMORY_PCF8570 yes)

set(DRIVER_SENSOR_AD7151 yes)
set(DRIVER_SENSOR_AS5600 yes)
set(DRIVER_SENSOR_BMG160 yes)
set(DRIVER_SENSOR_INA220 yes)
set(DRIVER_SENSOR_L3GD20 yes)
set(DRIVER_SENSOR_LIS2DSH yes)
set(DRIVER_SENSOR_LIS3DSH yes)
set(DRIVER_SENSOR_LIS3MDL yes)

set(DRIVER_SERIAL yes)

set(DRIVER_STEPPER_TMC26x yes)

set(DRIVER_TLCD_HD44780 yes)

##########################################################################
# COMSTACK ###############################################################
##########################################################################

set(COMSTACK_CANOPEN yes)

##########################################################################