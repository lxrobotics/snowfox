##########################################################################
# DRIVER #################################################################
##########################################################################

set(DRIVER_GLCD_SRC_PATH src/driver/glcd)

if(${DRIVER_GLCD_RA6963} STREQUAL "yes")
  set(DRIVER_GLCD_RA6963_SRCS
  	${DRIVER_GLCD_SRC_PATH}/RA6963/RA6963_Data.cpp
    ${DRIVER_GLCD_SRC_PATH}/RA6963/RA6963_IO_GPIO_8Bit.cpp
  )
  set(SPECTRE_LIBRARY_DRIVER ${SPECTRE_LIBRARY_DRIVER} ${DRIVER_GLCD_RA6963_SRCS})
endif()

##########################################################################

set(DRIVER_HAPTIC_SRC_PATH src/driver/haptic)

if(${DRIVER_HAPTIC_DRV2605} STREQUAL "yes")
  set(DRIVER_HAPTIC_DRV2605_SRCS
    ${DRIVER_HAPTIC_SRC_PATH}/DRV2605/DRV2605_IO_I2C.cpp
    ${DRIVER_HAPTIC_SRC_PATH}/DRV2605/DRV2605.cpp
  )
  set(SPECTRE_LIBRARY_DRIVER ${SPECTRE_LIBRARY_DRIVER} ${DRIVER_HAPTIC_DRV2605_SRCS})
endif()

##########################################################################

set(DRIVER_IOEXPANDER_SRC_PATH src/driver/ioexpander)

if(${DRIVER_IOEXPANDER_PCA9547} STREQUAL "yes")
  set(DRIVER_IOEXPANDER_PCA9547_SRCS
    ${DRIVER_IOEXPANDER_SRC_PATH}/PCA9547/PCA9547_IO_I2C.cpp
    ${DRIVER_IOEXPANDER_SRC_PATH}/PCA9547/PCA9547.cpp
  )
  set(SPECTRE_LIBRARY_DRIVER ${SPECTRE_LIBRARY_DRIVER} ${DRIVER_IOEXPANDER_PCA9547_SRCS})
endif()

##########################################################################

set(DRIVER_MEMORY_SRC_PATH src/driver/memory)

if(${DRIVER_MEMORY_AT45DBX} STREQUAL "yes")
  set(DRIVER_MEMORY_AT45DBX_SRCS
    ${DRIVER_MEMORY_SRC_PATH}/AT45DBx/AT45DBx.cpp
  )
  set(SPECTRE_LIBRARY_DRIVER ${SPECTRE_LIBRARY_DRIVER} ${DRIVER_MEMORY_AT45DBX_SRCS})  

endif()

if(${DRIVER_MEMORY_PCF8570} STREQUAL "yes")
  set(DRIVER_MEMORY_PCF8570_SRCS
	${DRIVER_MEMORY_SRC_PATH}/PCF8570/PCF8570_IO_I2C.cpp    
    ${DRIVER_MEMORY_SRC_PATH}/PCF8570/PCF8570.cpp
  )
  set(SPECTRE_LIBRARY_DRIVER ${SPECTRE_LIBRARY_DRIVER} ${DRIVER_MEMORY_PCF8570_SRCS})
endif()

##########################################################################

set(DRIVER_SENSOR_SRC_PATH src/driver/sensor)

if(${DRIVER_SENSOR_AD7151} STREQUAL "yes")
  set(DRIVER_SENSOR_AD7151_SRCS
    ${DRIVER_SENSOR_SRC_PATH}/AD7151/AD7151_IO_I2C.cpp
    ${DRIVER_SENSOR_SRC_PATH}/AD7151/AD7151.cpp
  )
  set(SPECTRE_LIBRARY_DRIVER ${SPECTRE_LIBRARY_DRIVER} ${DRIVER_SENSOR_AD7151_SRCS})
endif()

if(${DRIVER_SENSOR_AS5600} STREQUAL "yes")
  set(DRIVER_SENSOR_AS5600_SRCS
    ${DRIVER_SENSOR_SRC_PATH}/AS5600/AS5600_IO_I2C.cpp
    ${DRIVER_SENSOR_SRC_PATH}/AS5600/AS5600.cpp
  )
  set(SPECTRE_LIBRARY_DRIVER ${SPECTRE_LIBRARY_DRIVER} ${DRIVER_SENSOR_AS5600_SRCS})
endif()

if(${DRIVER_SENSOR_BMG160} STREQUAL "yes")
  set(DRIVER_SENSOR_BMG160_SRCS
    ${DRIVER_SENSOR_SRC_PATH}/BMG160/BMG160_IO_I2C.cpp
    ${DRIVER_SENSOR_SRC_PATH}/BMG160/BMG160.cpp
  )
  set(SPECTRE_LIBRARY_DRIVER ${SPECTRE_LIBRARY_DRIVER} ${DRIVER_SENSOR_BMG160_SRCS})
endif()

if(${DRIVER_SENSOR_INA220} STREQUAL "yes")
  set(DRIVER_SENSOR_INA220_SRCS
    ${DRIVER_SENSOR_SRC_PATH}/INA220/INA220_IO_I2C.cpp
    ${DRIVER_SENSOR_SRC_PATH}/INA220/INA220.cpp
  )
  set(SPECTRE_LIBRARY_DRIVER ${SPECTRE_LIBRARY_DRIVER} ${DRIVER_SENSOR_INA220_SRCS})
endif()

if(${DRIVER_SENSOR_L3GD20} STREQUAL "yes")
  set(DRIVER_SENSOR_L3GD20_SRCS
    ${DRIVER_SENSOR_SRC_PATH}/L3GD20/L3GD20_IO_I2C.cpp
    ${DRIVER_SENSOR_SRC_PATH}/L3GD20/L3GD20.cpp
  )
  set(SPECTRE_LIBRARY_DRIVER ${SPECTRE_LIBRARY_DRIVER} ${DRIVER_SENSOR_L3GD20_SRCS})
endif()

if(${DRIVER_SENSOR_LIS2DSH} STREQUAL "yes")
  set(DRIVER_SENSOR_LIS2DSH_SRCS
    ${DRIVER_SENSOR_SRC_PATH}/LIS2DSH/LIS2DSH_IO_I2C.cpp
    ${DRIVER_SENSOR_SRC_PATH}/LIS2DSH/LIS2DSH.cpp
  )
  set(SPECTRE_LIBRARY_DRIVER ${SPECTRE_LIBRARY_DRIVER} ${DRIVER_SENSOR_LIS2DSH_SRCS})
endif()

if(${DRIVER_SENSOR_LIS3DSH} STREQUAL "yes")
  set(DRIVER_SENSOR_LIS3DSH_SRCS
    ${DRIVER_SENSOR_SRC_PATH}/LIS3DSH/LIS3DSH_IO_I2C.cpp
    ${DRIVER_SENSOR_SRC_PATH}/LIS3DSH/LIS3DSH.cpp
  )
  set(SPECTRE_LIBRARY_DRIVER ${SPECTRE_LIBRARY_DRIVER} ${DRIVER_SENSOR_LIS3DSH_SRCS})
endif()

if(${DRIVER_SENSOR_LIS3MDL} STREQUAL "yes")
  set(DRIVER_SENSOR_LIS3MDL_SRCS
    ${DRIVER_SENSOR_SRC_PATH}/LIS3MDL/LIS3MDL_IO_I2C.cpp
    ${DRIVER_SENSOR_SRC_PATH}/LIS3MDL/LIS3MDL.cpp
  )
  set(SPECTRE_LIBRARY_DRIVER ${SPECTRE_LIBRARY_DRIVER} ${DRIVER_SENSOR_LIS3MDL_SRCS})
endif()

if(${DRIVER_SENSOR_TPA81} STREQUAL "yes")
  set(DRIVER_SENSOR_TPA81_SRCS
    ${DRIVER_SENSOR_SRC_PATH}/TPA81/TPA81_IO_I2C.cpp
    ${DRIVER_SENSOR_SRC_PATH}/TPA81/TPA81.cpp
  )
  set(SPECTRE_LIBRARY_DRIVER ${SPECTRE_LIBRARY_DRIVER} ${DRIVER_SENSOR_TPA81_SRCS})
endif()

##########################################################################

