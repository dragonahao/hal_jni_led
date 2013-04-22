package com.android.server;
import android.content.Context;
import android.os.IDeviceService;
import android.util.Slog;
public class DeviceService extends IDeviceService.Stub
{
	private static final String TAG = "DeviceService";
	DeviceService()
	{
		openLed();
	}
	public void SetLed(int no, int val)
	{
		set_Led(no, val);
	}

	private static native boolean openLed();
	private static native int set_Led(int no, int val);
};
