LOCAL_PATH := $(call my-dir)

filterdir = $(foreach obj, $(wildcard $1/*), $(if $(realpath $(wildcard $(obj)/.)), $(obj)))

rwildcard = $(foreach dir, $(call filterdir, $1), $(call rwildcard, $(dir)) $(dir))


include $(CLEAR_VARS)
LOCAL_MODULE := libcrypto_static
LOCAL_SRC_FILES := prebuilt/$(TARGET_ARCH_ABI)/libcrypto.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_CPP_EXTENSION := .cc .cpp .c

LOCAL_SRC_FILES := hellocpp/main.cpp
                   
myClassesDir := $(LOCAL_PATH)/../../Classes
myClassesDir += $(call rwildcard, $(myClassesDir))
myClassesDir := $(sort $(myClassesDir))

myCpps := $(foreach dir, $(myClassesDir), $(wildcard $(dir)/*.cpp))
myCpps := $(myCpps:$(LOCAL_PATH)/%=%)

LOCAL_SRC_FILES  += $(myCpps)

LOCAL_C_INCLUDES := $(myClassesDir)

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES := protobuf_static
LOCAL_WHOLE_STATIC_LIBRARIES += messagepack_static
LOCAL_SHARED_LIBRARIES += libcrypto_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,$(LOCAL_PATH)/../../cocos2d/external/protobuf)
$(call import-module,libMessagePack)
$(call import-module,.)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
