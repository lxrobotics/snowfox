##########################################################################
# DRIVER #################################################################
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
  set(SPECTRE_LIBRARY_DRIVER ${SPECTRE_LIBRARY_DRIVER} ${DRIVER_MEMORY_SRC_PATH}/AT45DBx.cpp)
endif()

if(${DRIVER_MEMORY_PCF8570} STREQUAL "yes")
  set(SPECTRE_LIBRARY_DRIVER ${SPECTRE_LIBRARY_DRIVER} ${DRIVER_MEMORY_SRC_PATH}/PCF8570.cpp)
endif()

##########################################################################

set(DRIVER_SENSOR_SRC_PATH src/driver/sensor)

if(${DRIVER_SENSOR_AD7151} STREQUAL "yes")
  set(SPECTRE_LIBRARY_DRIVER ${SPECTRE_LIBRARY_DRIVER} ${DRIVER_SENSOR_SRC_PATH}/AD7151.cpp)
endif()

if(${DRIVER_SENSOR_AS5600} STREQUAL "yes")
  set(SPECTRE_LIBRARY_DRIVER ${SPECTRE_LIBRARY_DRIVER} ${DRIVER_SENSOR_SRC_PATH}/AS5600.cpp)
endif()

if(${DRIVER_SENSOR_BMG160} STREQUAL "yes")
  set(SPECTRE_LIBRARY_DRIVER ${SPECTRE_LIBRARY_DRIVER} ${DRIVER_SENSOR_SRC_PATH}/BMG160.cpp)
endif()

if(${DRIVER_SENSOR_INA220} STREQUAL "yes")
  set(SPECTRE_LIBRARY_DRIVER ${SPECTRE_LIBRARY_DRIVER} ${DRIVER_SENSOR_SRC_PATH}/INA220.cpp)
endif()

if(${DRIVER_SENSOR_L3GD20} STREQUAL "yes")
  set(SPECTRE_LIBRARY_DRIVER ${SPECTRE_LIBRARY_DRIVER} ${DRIVER_SENSOR_SRC_PATH}/L3GD20.cpp)
endif()

if(${DRIVER_SENSOR_LIS2DSH} STREQUAL "yes")
  set(SPECTRE_LIBRARY_DRIVER ${SPECTRE_LIBRARY_DRIVER} ${DRIVER_SENSOR_SRC_PATH}/LIS2DSH.cpp)
endif()

if(${DRIVER_SENSOR_LIS3DSH} STREQUAL "yes")
  set(SPECTRE_LIBRARY_DRIVER ${SPECTRE_LIBRARY_DRIVER} ${DRIVER_SENSOR_SRC_PATH}/LIS3DSH.cpp)
endif()

if(${DRIVER_SENSOR_LIS3MDL} STREQUAL "yes")
  set(SPECTRE_LIBRARY_DRIVER ${SPECTRE_LIBRARY_DRIVER} ${DRIVER_SENSOR_SRC_PATH}/LIS3MDL.cpp)
endif()

if(${DRIVER_SENSOR_TPA81} STREQUAL "yes")
  set(SPECTRE_LIBRARY_DRIVER ${SPECTRE_LIBRARY_DRIVER} ${DRIVER_SENSOR_SRC_PATH}/TPA81.cpp)
endif()

##########################################################################

