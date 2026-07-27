#!/bin/bash
# ============================================================
#  火影战记 NarutoSenki — macOS 启动脚本(双击即可运行)
#  对应 win32 版的「启动游戏.bat」。
#
#  资源已打包进 .app(通过 Contents/Resources),无需手动
#  设置工作目录。App 为 x86_64,在 Apple Silicon 上经 Rosetta 2
#  自动运行。
#
#  首次运行若尚未编译,脚本会自动用 xcodebuild 编译一次(较慢),
#  之后直接启动已编译产物。
# ============================================================

# 切到脚本所在目录(projects/NarutoSenki)
cd "$(dirname "$0")" || exit 1

PROJ="proj.mac/NarutoSenki.xcodeproj"

find_app() {
    find "$HOME/Library/Developer/Xcode/DerivedData"/NarutoSenki-*/Build/Products/Debug \
        -maxdepth 1 -name "NarutoSenki.app" 2>/dev/null | head -1
}

APP="$(find_app)"

if [ -z "$APP" ] || [ ! -d "$APP" ]; then
    echo "未找到已编译的 App,正在编译(x86_64,首次较慢)……"
    xcodebuild -project "$PROJ" -scheme NarutoSenki -configuration Debug \
        CODE_SIGNING_ALLOWED=NO build || {
        echo
        echo "[错误] 编译失败。请先在 Xcode 中打开 $PROJ 手动编译,或检查上方日志。"
        echo "按任意键关闭……"
        read -r -n1
        exit 1
    }
    APP="$(find_app)"
fi

if [ -z "$APP" ] || [ ! -d "$APP" ]; then
    echo "[错误] 编译后仍未找到 NarutoSenki.app。"
    read -r -n1
    exit 1
fi

echo "启动:$APP"
open "$APP"
