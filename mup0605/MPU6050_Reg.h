#ifndef __MPU6050_REG_H
#define __MPU6050_REG_H

// 采样率分频寄存器地址
#define MPU6050_SMPLRT_DIV 0x19 // 采样率分频器配置寄存器

// 配置寄存器地址
#define MPU6050_CONFIG 0x1A // 配置陀螺仪和低通滤波器参数

// 陀螺仪配置寄存器地址
#define MPU6050_GYRO_CONFIG 0x1B // 配置陀螺仪的测量范围

// 加速度计配置寄存器地址
#define MPU6050_ACCEL_CONFIG 0x1C // 配置加速度计的测量范围

// 加速度计输出寄存器
#define MPU6050_ACCEL_XOUT_H 0x3B // X轴加速度高字节
#define MPU6050_ACCEL_XOUT_L 0x3C // X轴加速度低字节
#define MPU6050_ACCEL_YOUT_H 0x3D // Y轴加速度高字节
#define MPU6050_ACCEL_YOUT_L 0x3E // Y轴加速度低字节
#define MPU6050_ACCEL_ZOUT_H 0x3F // Z轴加速度高字节
#define MPU6050_ACCEL_ZOUT_L 0x40 // Z轴加速度低字节

// 温度输出寄存器
#define MPU6050_TEMP_OUT_H 0x41 // 温度高字节
#define MPU6050_TEMP_OUT_L 0x42 // 温度低字节

// 陀螺仪输出寄存器
#define MPU6050_GYRO_XOUT_H 0x43 // X轴陀螺仪高字节
#define MPU6050_GYRO_XOUT_L 0x44 // X轴陀螺仪低字节
#define MPU6050_GYRO_YOUT_H 0x45 // Y轴陀螺仪高字节
#define MPU6050_GYRO_YOUT_L 0x46 // Y轴陀螺仪低字节
#define MPU6050_GYRO_ZOUT_H 0x47 // Z轴陀螺仪高字节
#define MPU6050_GYRO_ZOUT_L 0x48 // Z轴陀螺仪低字节

// 电源管理寄存器
#define	MPU6050_PWR_MGMT_1		0x6B  // 电源管理1寄存器，用于初始化和时钟配置
#define	MPU6050_PWR_MGMT_2		0x6C  // 电源管理2寄存器，用于启用/禁用轴和待机模式设置

// 设备ID寄存器
#define	MPU6050_WHO_AM_I		0x75  // 设备ID寄存器，读取返回MPU6050的设备ID

#endif

