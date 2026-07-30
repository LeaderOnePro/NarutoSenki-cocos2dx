## 构建指南

详见根目录 [README.md](../../README.md) 中的 Android、macOS 与 Windows 构建指南。

## 项目结构

```
NarutoSenki/
├── Classes/          # 游戏 C++ 源码(27 个 .cpp + sqlite3.c)
├── Resources/        # 游戏资源(音频/图片/配置)
├── proj.android/     # Android 工程(Gradle + NDK)
├── proj.mac/         # macOS 工程(Xcode, x86_64 / Rosetta 2)
├── proj.win32/       # Windows 工程(VS2026)
├── 启动游戏.command  # macOS 一键启动脚本
├── 启动游戏.bat      # Windows 一键启动脚本
├── 项目现状.md       # 项目当前状态
└── 安卓移植计划.md   # 安卓移植方案
```
