#ifndef ANDROID_LED_INTERFACE_H
#define ANDROID_LED_INTERFACE_H
#include <hardware/hardware.h>
__BEGIN_DECLS
/* 定义模块ID */
#define LED_HARDWARE_MODULE_ID "led"
#define DEVICE_NAME "/dev/leds"
#define MODULE_NAME "led"
#define MODULE_AUTHOR "bottle.gj@gmail.com"

/* 定义模块结构体  */
struct led_module_t
{
	struct hw_module_t common;
};

/* 硬件接口结构体 */
struct led_device_t
{
	struct hw_device_t common;
	int fd;
	int (*set_led)(struct led_device_t* dev, int ledNo, int val);
};
__END_DECLS
#endif
