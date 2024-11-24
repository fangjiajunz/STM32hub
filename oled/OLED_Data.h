#ifndef __OLED_DATA_H
#define __OLED_DATA_H

#include <stdint.h>

/*字符集定义*/
/*以下两个宏定义只可解除其中一个的注释*/
#define OLED_CHARSET_UTF8 // 定义字符集为UTF8
// #define OLED_CHARSET_GB2312		//定义字符集为GB2312

/*字模基本单元*/
typedef struct {

#ifdef OLED_CHARSET_UTF8 // 定义字符集为UTF8
    char Index[5]; // 汉字索引，空间为5字节
#endif

#ifdef OLED_CHARSET_GB2312 // 定义字符集为GB2312
    char Index[3]; // 汉字索引，空间为3字节
#endif

    uint8_t Data[32]; // 字模数据
} ChineseCell_t;

/*ASCII字模数据声明*/
extern const uint8_t OLED_F8x16[][16];
extern const uint8_t OLED_F6x8[][6];

/*汉字字模数据声明*/
extern const ChineseCell_t OLED_CF16x16[];

/*图像数据声明*/
extern const uint8_t Diode[];
/*按照上面的格式，在这个位置加入新的图像数据声明*/
//...
extern const uint8_t BMP1[];

extern const uint8_t clockData[];

extern const uint8_t tim1[];
extern const uint8_t tim2[];
extern const uint8_t tim3[];
extern const uint8_t tim4[];
extern const uint8_t tim5[];
extern const uint8_t tim6[];
extern const uint8_t tim7[];
extern const uint8_t tim8[];
extern const uint8_t tim9[];
extern const uint8_t tim10[];
extern const uint8_t tim11[];
extern const uint8_t tim12[];
extern const uint8_t tim13[];
extern const uint8_t tim14[];
extern const uint8_t tim15[];
extern const uint8_t tim16[];
extern const uint8_t tim17[];
extern const uint8_t tim18[];
extern const uint8_t tim19[];
extern const uint8_t tim20[];
extern const uint8_t tim21[];
extern const uint8_t tim22[];
extern const uint8_t tim23[];
extern const uint8_t tim24[];
extern const uint8_t tim25[];
extern const uint8_t tim26[];
extern const uint8_t tim27[];
#endif

/*****************江协科技|版权所有****************/
/*****************jiangxiekeji.com*****************/
