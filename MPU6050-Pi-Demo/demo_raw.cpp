#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include "I2Cdev.h"
#include "MPU6050.h"

// class default I2C address is 0x68
// specific I2C addresses may be passed as a parameter here
// AD0 low = 0x68 (default for InvenSense evaluation board)
// AD0 high = 0x69
MPU6050 accelgyro;
MPU6050 accelgyro2(0x69);

int16_t ax, ay, az;
int16_t gx, gy, gz;
int16_t axx, ayy, azz;
int16_t gxx, gyy, gzz;

void setup() {
    // initialize device
    printf("Initializing I2C devices...\n");
    accelgyro.initialize();
    accelgyro2.initialize();
    // verify connection
    printf("Testing device connections...\n");
    printf(accelgyro.testConnection() ? "MPU6050 connection successful\n" : "MPU6050 connection failed\n");
    printf(accelgyro2.testConnection() ? "MPU6050-2 connection successful\n" : "MPU6050 connection failed\n");
}

void loop(FILE *fptr1,FILE *fptr2) {
    // read raw accel/gyro measurements from device
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    accelgyro2.getMotion6(&axx,&ayy,&azz,&gxx,&gyy,&gzz);

    // these methods (and a few others) are also available
    //accelgyro.getAcceleration(&ax, &ay, &az);
    //accelgyro.getRotation(&gx, &gy, &gz);

    // display accel/gyro x/y/z values
     printf("a/g: %6hd %6hd %6hd   %6hd %6hd %6hd\n",ax,ay,az,gx,gy,gz);
     printf("a2/g2: %6hd %6hd %6hd   %6hd %6hd %6hd\n",axx,ayy,azz,gxx,gyy,gzz);
     fprintf(fptr1,"a/g: %6hd %6hd %6hd   %6hd %6hd %6hd\n",ax,ay,az,gx,gy,gz);
     fprintf(fptr2,"a2/g2: %6hd %6hd %6hd   %6hd %6hd %6hd\n",axx,ayy,azz,gxx,gyy,gzz);
}

int main()
{
    FILE *fptr1,*fptr2;
    fptr1=fopen("g-sensor1.txt","w");
    fptr2=fopen("g-sensor2.txt","w");
    setup();
    for (;;)
        loop(fptr1,fptr2);
    fclose(fptr1);
    fclose(fptr2);
}
