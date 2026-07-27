#!/bin/bash
# NarutoSenki 安卓 native 构建脚本(cocos2d-x 2.2.6)
# 经验证可用于 Apple Silicon Mac:
#   - 老 NDK r10e 不认 arm64 宿主 → 用 arch -x86_64 经 Rosetta 跑,uname 返回 x86_64
#   - import-module 需要 NDK_MODULE_PATH 指向框架根 + android 预编译库目录
set -e

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
ROOT="$( cd "$DIR/../../.." && pwd )"          # 框架根(含 cocos2dx/external/extensions…)

: "${NDK_ROOT:=$HOME/Library/Android/android-ndk-r10e}"
export NDK_ROOT
export NDK_MODULE_PATH="$ROOT:$ROOT/cocos2dx/platform/third_party/android/prebuilt"

echo "NDK_ROOT        = $NDK_ROOT"
echo "NDK_MODULE_PATH = $NDK_MODULE_PATH"
echo "构建目录        = $DIR"

# 经 Rosetta 调 ndk-build(arm64 宿主必需)
arch -x86_64 /bin/bash -c "\
  export NDK_ROOT='$NDK_ROOT'; \
  export NDK_MODULE_PATH='$NDK_MODULE_PATH'; \
  '$NDK_ROOT/ndk-build' -C '$DIR' \
     APP_ABI=armeabi-v7a NDK_DEBUG=0 -j4 \"\$@\"" -- "$@"

echo "✅ native 构建完成,产物在 $DIR/libs/"
