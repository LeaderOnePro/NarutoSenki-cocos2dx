LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := narutosenki_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

# JNI 入口 + 全部游戏逻辑(27 个 .cpp + MyUtils/sqlite3.c)。
# 与 win32 工程一致地全量编入;NetworkLayer 一并保留(依赖的 curl 已随 third_party/android 补回)。
LOCAL_SRC_FILES := narutosenki/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/ActionButton.cpp \
                   ../../Classes/ActionManager.cpp \
                   ../../Classes/BGLayer.cpp \
                   ../../Classes/Characters.cpp \
                   ../../Classes/CreditsLayer.cpp \
                   ../../Classes/Effect.cpp \
                   ../../Classes/Element.cpp \
                   ../../Classes/GameLayer.cpp \
                   ../../Classes/GameOver.cpp \
                   ../../Classes/GameScene.cpp \
                   ../../Classes/GearLayer.cpp \
                   ../../Classes/HPBar.cpp \
                   ../../Classes/HudLayer.cpp \
                   ../../Classes/JoyStick.cpp \
                   ../../Classes/LoadLayer.cpp \
                   ../../Classes/NetworkLayer.cpp \
                   ../../Classes/PauseLayer.cpp \
                   ../../Classes/RankingLayer.cpp \
                   ../../Classes/SelectLayer.cpp \
                   ../../Classes/SkillLayer.cpp \
                   ../../Classes/StartMenu.cpp \
                   ../../Classes/MyUtils/CCScrewLayer.cpp \
                   ../../Classes/MyUtils/CCShake.cpp \
                   ../../Classes/MyUtils/CCStrokeLabel.cpp \
                   ../../Classes/MyUtils/KTools.cpp \
                   ../../Classes/MyUtils/MD5ChecksumDefines.cpp \
                   ../../Classes/MyUtils/sqlite3.c

LOCAL_C_INCLUDES := $(LOCAL_PATH) \
                    $(LOCAL_PATH)/../../Classes \
                    $(LOCAL_PATH)/../../Classes/MyUtils \
                    $(LOCAL_PATH)/../../../../cocos2dx

# 整库静态链接 extensions——它已 whole-link cocos2dx/CocosDenshion/curl/Box2D/chipmunk/websockets
LOCAL_WHOLE_STATIC_LIBRARIES := cocos_extension_static

include $(BUILD_SHARED_LIBRARY)

# extensions 模块会级联 import 其全部依赖(cocos2dx、CocosDenshion、libcurl、Box2D、chipmunk、libwebsockets)
$(call import-module,extensions)
