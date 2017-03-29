LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE := fbconfig
LOCAL_MODULE_TAGS := optional
LOCAL_SRC_FILES := fbconfig.c
include $(BUILD_EXECUTABLE)
