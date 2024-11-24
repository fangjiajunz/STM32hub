
#include "MPU6050_Reg.h"
#include "i2c.h"
#include "stdio.h"
// #define MPU6050_ADDRESS 0xD0 // MPU6050的I2C从机地址
extern I2C_HandleTypeDef hi2c1;
/**
 * 函    数：MPU6050写寄存器
 * 参    数：RegAddress 寄存器地址，范围：参考MPU6050手册的寄存器描述
 * 参    数：Data 要写入寄存器的数据，范围：0x00~0xFF
 * 返 回 值：无
 */
#define MPU6050_ADDRESS 0x68 << 1 // 注意：HAL 库中的 I2C 地址需要左移一位，表示 7 位地址

/**
 * 函数：MPU6050 写寄存器
 * 参数：
 *   - hi2c: I2C 句柄
 *   - RegAddress: 寄存器地址
 *   - Data: 要写入的数据
 * 返回值：无
 */
void MPU6050_WriteReg(I2C_HandleTypeDef *hi2c, uint8_t RegAddress, uint8_t Data) {
    uint8_t buffer[2];
    buffer[0] = RegAddress; // 设置寄存器地址
    buffer[1] = Data; // 设置要写入的数据

    // 使用 HAL 库进行数据传输
    HAL_I2C_Master_Transmit(hi2c, MPU6050_ADDRESS, buffer, 2, HAL_MAX_DELAY);
}

/**
 * 函数：MPU6050 读寄存器
 * 参数：
 *   - hi2c: I2C 句柄
 *   - RegAddress: 寄存器地址
 * 返回值：寄存器读取到的数据
 */
uint8_t MPU6050_ReadReg(I2C_HandleTypeDef *hi2c, uint8_t RegAddress) {
    uint8_t Data;

    // 发送寄存器地址
    HAL_I2C_Master_Transmit(hi2c, MPU6050_ADDRESS, &RegAddress, 1, HAL_MAX_DELAY);

    // 读取寄存器数据
    HAL_I2C_Master_Receive(hi2c, MPU6050_ADDRESS, &Data, 1, HAL_MAX_DELAY);

    return Data;
}
/**
 * 函    数：MPU6050初始化
 * 参    数：无
 * 返 回 值：无
 */
void MPU6050_Init(void) {
    // 配置电源管理寄存器1，取消睡眠模式，选择时钟源为X轴陀螺仪
    uint8_t pwr_mgmt_1_data = 0x01;
    HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDRESS, MPU6050_PWR_MGMT_1, I2C_MEMADD_SIZE_8BIT, &pwr_mgmt_1_data, 1, HAL_MAX_DELAY);

    // 配置电源管理寄存器2，保持默认值0，所有轴均不待机
    uint8_t pwr_mgmt_2_data = 0x00;
    HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDRESS, MPU6050_PWR_MGMT_2, I2C_MEMADD_SIZE_8BIT, &pwr_mgmt_2_data, 1, HAL_MAX_DELAY);

    // 配置采样率分频寄存器
    uint8_t smplrt_div_data = 0x09;
    HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDRESS, MPU6050_SMPLRT_DIV, I2C_MEMADD_SIZE_8BIT, &smplrt_div_data, 1, HAL_MAX_DELAY);

    // 配置DLPF
    uint8_t config_data = 0x06;
    HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDRESS, MPU6050_CONFIG, I2C_MEMADD_SIZE_8BIT, &config_data, 1, HAL_MAX_DELAY);

    // 陀螺仪满量程选择为±2000°/s
    uint8_t gyro_config_data = 0x18;
    HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDRESS, MPU6050_GYRO_CONFIG, I2C_MEMADD_SIZE_8BIT, &gyro_config_data, 1, HAL_MAX_DELAY);

    // 加速度计满量程选择为±16g
    uint8_t accel_config_data = 0x18;
    HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDRESS, MPU6050_ACCEL_CONFIG, I2C_MEMADD_SIZE_8BIT, &accel_config_data, 1, HAL_MAX_DELAY);
}

/**
 * 函数：MPU6050获取ID号
 * 返回值：MPU6050的ID号
 */
uint8_t MPU6050_GetID(void) {
    uint8_t id;
    HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDRESS, MPU6050_WHO_AM_I, I2C_MEMADD_SIZE_8BIT, &id, 1, HAL_MAX_DELAY);
    return id;
}

/**
 * 函数：MPU6050获取加速度和陀螺仪数据
 * 参数：输出参数 AccX, AccY, AccZ 为加速度计数据，GyroX, GyroY, GyroZ 为陀螺仪数据
 */
void MPU6050_GetData(int16_t *AccX, int16_t *AccY, int16_t *AccZ, int16_t *GyroX, int16_t *GyroY, int16_t *GyroZ) {
    uint8_t accel_gyro_data[14];

    // 连续读取加速度、温度和陀螺仪数据寄存器
    HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDRESS, MPU6050_ACCEL_XOUT_H, I2C_MEMADD_SIZE_8BIT, accel_gyro_data, 14, HAL_MAX_DELAY);

    // 将数据拼接为16位数据
    *AccX = (int16_t) (accel_gyro_data[0] << 8 | accel_gyro_data[1]);
    *AccY = (int16_t) (accel_gyro_data[2] << 8 | accel_gyro_data[3]);
    *AccZ = (int16_t) (accel_gyro_data[4] << 8 | accel_gyro_data[5]);
    *GyroX = (int16_t) (accel_gyro_data[8] << 8 | accel_gyro_data[9]);
    *GyroY = (int16_t) (accel_gyro_data[10] << 8 | accel_gyro_data[11]);
    *GyroZ = (int16_t) (accel_gyro_data[12] << 8 | accel_gyro_data[13]);
}
void show_mup() {
    char buffer[20];
    int16_t datebuff[6];
    MPU6050_GetData(&datebuff[0], &datebuff[1], &datebuff[2], &datebuff[3], &datebuff[4], &datebuff[5]);
    printf("   AccX: %d  ", datebuff[0]);
    printf("   AccY: %d    ", datebuff[1]);
    printf("   AccZ: %d    ", datebuff[2]);
    printf("   GyroX: %d   ", datebuff[3]);
    printf("   GyroX: %d   ", datebuff[4]);
    printf("   GyroX: %d\n   ", datebuff[5]);
    sprintf(buffer, "ID: %d\n", MPU6050_GetID());

    printf("%s", buffer);
}