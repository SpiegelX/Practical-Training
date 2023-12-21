# Device Tree + Device Driver Practical
This is the practical of device tree and device driver
# bcm2710-rpi-3-b-plus.dts
This is practical 1:
    Write a device tree for PCF8574 (I2C IO expander) - Work with raspberry pi 3B+

    With device tree of raspi 3B+ (linux source path: arch/arm/boot/dts/bcm2710-rpi-3-b-plus.dts), add more properties as below:
        • I2C addressing:
            - Use i2c1  
            - #address-cells  - should be <1>.
            - #size-cells - should be <0>.
        • IO Expander PCF8574:
            - This device is a child-node of I2C. 
            - This device has interrupt feature.

    Confirm the device is detected after mapping the device tree (not checking operation yet).

    1. Can add the pcf8574 device to raspberry pi 3B+ device tree as requirements.
    2. Can confirm the driver is detected after mapping.
    For example:
    ls /proc/device-tree/soc/i2c@7e804000/
