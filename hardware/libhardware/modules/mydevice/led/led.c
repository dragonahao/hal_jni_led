#include <hardware/hardware.h>
#include <hardware/mydevice/led.h>
#include <fcntl.h>
#include <errno.h>
#include <cutils/log.h>
#include <cutils/atomic.h>

/* 打开设备和关闭设备 */
static int led_device_open(const struct hw_module_t* module, const char* name, struct hw_device_t** device);
static int led_device_close(struct hw_device_t* device);

/* 设置led设备 */
static int led_device_set_val(struct led_device_t* dev, int ledNo, int val); 


/* 模块方法表 */
static struct hw_module_methods_t led_module_methods = 
{
	.open = led_device_open
};

/* 模块实例变量 */
struct led_module_t HAL_MODULE_INFO_SYM = 
{
common:
	{
	 tag: HARDWARE_MODULE_TAG,
	 version_major: 1,
	 version_minor: 0,
	 id: LED_HARDWARE_MODULE_ID,
     name: MODULE_NAME,
	 author: MODULE_AUTHOR,
	 methods: &led_module_methods,
	}
};


/*  方法实现 */

static int led_device_open(const struct hw_module_t* module, const char* name, struct hw_device_t** device)
{
	struct led_device_t* dev;
	dev = (struct led_device_t*) malloc(sizeof(struct led_device_t));

	if(!dev)
	{
		LOGE("led stub: failed to alloc space");
		return -EFAULT;
	}
	memset(dev, 0x00, sizeof(struct led_device_t));
	dev->common.version = 0;
	dev->common.module = (hw_module_t*)module;
	dev->common.close = led_device_close;
	dev->set_led = led_device_set_val;

	if ( ( dev->fd = open(DEVICE_NAME, O_RDWR)) == -1)
	{
		LOGE("led stub: failed to open /dev/myled --%s", strerror(errno));
		free(dev);
		return -EFAULT;
	}
	*device = &(dev->common);
	LOGI("led stub: open /dev/myled successfully");

	return 0;
}
static int led_device_close(struct hw_device_t* device)
{
	struct led_device_t* led_device = (struct led_device_t*)device;
	if(led_device)
	{
		LOGI("led stub: close /dev/myled closed");
		close(led_device->fd);
		free(led_device);
	}
	return 0;
}

static int led_device_set_val(struct led_device_t* dev, int ledNo, int val) 
{
	ioctl(dev->fd, val, ledNo);
	LOGI("led stub: ledNo= %dr val= %d /dev/myled setted", ledNo, val);
	return 0;
}
