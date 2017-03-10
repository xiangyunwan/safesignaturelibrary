LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := jrSafeSignature
LOCAL_LDFLAGS := -Wl,--build-id
LOCAL_SRC_FILES := \
	D:\leJR-Source\mobile_android\safesignaturelibrary\src\main\jni\com_letv_jr_safesignaturelibrary_JrSignature.cpp \

LOCAL_C_INCLUDES += D:\leJR-Source\mobile_android\safesignaturelibrary\src\main\jni
LOCAL_C_INCLUDES += D:\leJR-Source\mobile_android\safesignaturelibrary\src\release\jni

include $(BUILD_SHARED_LIBRARY)
