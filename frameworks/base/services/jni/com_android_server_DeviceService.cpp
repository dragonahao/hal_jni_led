#include "jni.h"
#include "JNIHelp.h"
#include "android_runtime/AndroidRuntime.h"
#include <utils/misc.h>
#include <utils/Log.h>
#include <hardware/hardware.h>
#include <stdio.h>
#include <hardware/mydevice/led.h>

namespace android
{
	struct led_device_t* led_device = NULL;

	static inline jint setLed(JNIEnv* env, jobject clazz, jint ledNo, jint value)
	{
		int no = ledNo;
		int val = value;
		LOGI("led jni: set no=%d value=%d to device.", ledNo, val);

		if ( !led_device )
		{
			LOGI("LED JNI: device is not open.");
			return 1;
		}
		led_device->set_led(led_device, ledNo, value);
		return 0;
	}

	static inline int led_device_open(const hw_module_t* module, struct led_device_t** device)
	{
		return module->methods->open(module, LED_HARDWARE_MODULE_ID, (struct hw_device_t**)device);
	}
	static jboolean led_init(JNIEnv* env, jclass clazz)
	{
		led_module_t* module;

		LOGI("led jni: initializing....");

		if ( hw_get_module(LED_HARDWARE_MODULE_ID,(const struct hw_module_t**)&module) == 0)
		{
			LOGI("LED JNI: LED STUB FOUND.");
			if(led_device_open(&(module->common), &led_device) == 0)
			{
				LOGI("led jni: led jni is open");
				return 0;
			}
			LOGE("led jni: failed to open led device");
			return 1;
		}
		
		LOGE("led jni: failed to get led stub module");
		return 2;
	}
	static const JNINativeMethod method_table[]=
	{
		{"openLed", "()Z", (void*)led_init},
		{"set_Led", "(II)I", (void*)setLed},
	};

	int register_android_server_device(JNIEnv * env)
	{
		return jniRegisterNativeMethods(env, "com/android/server/DeviceService", method_table, NELEM(method_table));
	}
};
