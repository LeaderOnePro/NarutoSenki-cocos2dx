# NarutoSenki 安卓 native 构建配置(cocos2d-x 2.2.6 / NDK r10e)
APP_STL := gnustl_static
# -frtti:游戏用到 RTTI;chipmunk 集成宏与 win32 一致;关掉若干老代码在新 clang 下的告警转错误
APP_CPPFLAGS := -frtti -DCC_ENABLE_CHIPMUNK_INTEGRATION=1 -Wno-error=format-security -Wno-deprecated-declarations
APP_ABI := armeabi-v7a
APP_PLATFORM := android-9
