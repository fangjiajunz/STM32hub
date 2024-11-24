#ifndef __MPU6050_REG_H
#define __MPU6050_REG_H

// �����ʷ�Ƶ�Ĵ�����ַ
#define MPU6050_SMPLRT_DIV 0x19 // �����ʷ�Ƶ�����üĴ���

// ���üĴ�����ַ
#define MPU6050_CONFIG 0x1A // ���������Ǻ͵�ͨ�˲�������

// ���������üĴ�����ַ
#define MPU6050_GYRO_CONFIG 0x1B // ���������ǵĲ�����Χ

// ���ٶȼ����üĴ�����ַ
#define MPU6050_ACCEL_CONFIG 0x1C // ���ü��ٶȼƵĲ�����Χ

// ���ٶȼ�����Ĵ���
#define MPU6050_ACCEL_XOUT_H 0x3B // X����ٶȸ��ֽ�
#define MPU6050_ACCEL_XOUT_L 0x3C // X����ٶȵ��ֽ�
#define MPU6050_ACCEL_YOUT_H 0x3D // Y����ٶȸ��ֽ�
#define MPU6050_ACCEL_YOUT_L 0x3E // Y����ٶȵ��ֽ�
#define MPU6050_ACCEL_ZOUT_H 0x3F // Z����ٶȸ��ֽ�
#define MPU6050_ACCEL_ZOUT_L 0x40 // Z����ٶȵ��ֽ�

// �¶�����Ĵ���
#define MPU6050_TEMP_OUT_H 0x41 // �¶ȸ��ֽ�
#define MPU6050_TEMP_OUT_L 0x42 // �¶ȵ��ֽ�

// ����������Ĵ���
#define MPU6050_GYRO_XOUT_H 0x43 // X�������Ǹ��ֽ�
#define MPU6050_GYRO_XOUT_L 0x44 // X�������ǵ��ֽ�
#define MPU6050_GYRO_YOUT_H 0x45 // Y�������Ǹ��ֽ�
#define MPU6050_GYRO_YOUT_L 0x46 // Y�������ǵ��ֽ�
#define MPU6050_GYRO_ZOUT_H 0x47 // Z�������Ǹ��ֽ�
#define MPU6050_GYRO_ZOUT_L 0x48 // Z�������ǵ��ֽ�

// ��Դ����Ĵ���
#define	MPU6050_PWR_MGMT_1		0x6B  // ��Դ����1�Ĵ��������ڳ�ʼ����ʱ������
#define	MPU6050_PWR_MGMT_2		0x6C  // ��Դ����2�Ĵ�������������/������ʹ���ģʽ����

// �豸ID�Ĵ���
#define	MPU6050_WHO_AM_I		0x75  // �豸ID�Ĵ�������ȡ����MPU6050���豸ID

#endif

