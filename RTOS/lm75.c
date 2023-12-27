// User include
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>

// User define
#define LM75_ADDRESS 0x91
#define REG_TEMP 0x00

int main()
{
    const char filename[] = "/dev/i2c-1";

    int file;
    char buf[5];
    int16_t temp_buf;
    float temp_c;

    // Open file for read/write
    if((file ==open(filename, O_RDWR))<0)
    {
        printf("failed to open bus i2c\n");
        exit(1);
    }

    // change to i2c address of LM75
    if(ioctl(file, I2C_SLAVE, LM75_ADDRESS))
    {
        printf("failed to accquired bus access or talk to device \n");
        exit(1);
    }

    // start read by writing location of temp register
    buf[0] = 0x00;
    if(write(file,buf,1)!=1)
    {
        printf("couldn't not write to i2c device \n");
        exit(1);
    }

    // read temp
    if(read(file,buf,2)!=2)
    {
        printf("couldn't not write to i2c device \n");
        exit(1);
    }

    // combine to 16bit value
    temp_buf = (buf[0]<<4)|(buf[1]>>4);

    // value negative fixed
    if temp_buf >0x7ff
    {
        temp_buf |= 0xF000;
    }

    temp_c = temp_buf*0.0625;

    printf("%.2f deg C\n", temp_c);

    return 0;
} 
