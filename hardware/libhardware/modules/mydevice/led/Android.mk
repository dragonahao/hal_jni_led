include $(CLEAR_VARS)
LOCAL_MODULE_TAGS:=optional
LOCAL_PRELINK_MODULE:=false
LOCAL_MODULE_PATH:=$(TARGET_OUT_SHARED_LIBRARIES)/hw
LOCAL_SHARED_LIBRARIES:=liblog
LOCAL_SRC_FILES:=led/led.c
LOCAL_MODULE:=led.default
include $(BUILD_SHARED_LIBRARY)

