# CLAUDE.md

本文件为 Claude Code (claude.ai/code) 在此代码库中工作时提供指导。

## 项目概述

这是 cocos2d-x 版本 2.2.6，一个基于 C++ 的多平台 2D 游戏框架，从 cocos2d-iphone 分支而来。于 2014 年 12 月发布，该版本包含 iOS 64 位支持和各种错误修复。

### 支持的平台
- iOS (5.x ~ 6.x SDK)
- Android (gles20 分支需 2.3+)
- Windows (XP/Vista/Win7)
- Windows Phone 8 和 Windows Store Apps (WinRT)
- BlackBerry (Playbook & BB10)
- Linux
- Mac OS X
- Marmalade
- Native Client (NaCl)
- Emscripten
- Tizen

### 支持的语言
- C++ (主要)
- Lua 绑定
- JavaScript 绑定

## 构建命令

### Windows
```bash
# 在 Windows 上构建整个框架 (需要 VS2010 或 VS2012)
build-win32.bat

# 使用 Visual Studio 解决方案文件手动构建：
# - cocos2d-win32.vc2010.sln (Visual Studio 2010)
# - cocos2d-win32.vc2012.sln (Visual Studio 2012)
# - cocos2d-winrt.vc2012.sln (WinRT)
# - cocos2d-winrt.vc2013.sln (WinRT 2013)
# - cocos2d-wp8.vc2012.sln (Windows Phone 8)
```

### Linux/Unix/Mac
```bash
# 构建整个框架 (默认为 linux 平台)
make all

# 清理构建产物
make clean

# 为特定平台构建
PLATFORM=emscripten make all
```

### 单独组件构建
组件按依赖顺序构建：
1. external/chipmunk
2. external/Box2D  
3. CocosDenshion (音频引擎)
4. extensions
5. cocos2dx (核心框架)
6. scripting/lua
7. 示例项目

## 架构概述

### 核心框架结构
- **cocos2dx/**: 主引擎源代码
  - **actions/**: 动画和动作系统
  - **base_nodes/**: 基础节点类 (CCNode, CCAtlasNode)
  - **sprite_nodes/**: 精灵渲染和动画
  - **layers_scenes_transitions_nodes/**: 场景管理和转换
  - **platform/**: 平台特定实现 (iOS, Android, Win32 等)
  - **cocoa/**: 核心数据结构和工具
  - **shaders/**: OpenGL 着色器管理
  - **support/**: 工具类和帮助器

### 关键类
- **CCDirector**: 管理场景和渲染循环的主要导演类
- **CCNode**: 所有视觉元素的基类  
- **CCScene**: 游戏场景的容器
- **CCLayer**: 游戏层的基类
- **CCSprite**: 2D 精灵渲染
- **CCAction**: 动画和动作系统基类

### 音频引擎
- **CocosDenshion/**: 跨平台音频引擎
  - 子目录中的平台特定实现
  - SimpleAudioEngine 接口提供基本音频功能

### 扩展
- **extensions/**: 额外功能
  - **CCBReader/**: CocosBuilder 文件格式支持
  - **CocoStudio/**: Cocos Studio 集成
  - **GUI/**: UI 组件系统  
  - **network/**: HTTP 客户端和 WebSocket 支持
  - **spine/**: Spine 骨骼动画支持

### 外部依赖
- **external/Box2D/**: 物理引擎
- **external/chipmunk/**: 替代物理引擎
- **external/libwebsockets/**: WebSocket 实现
- **external/sqlite3/**: 数据库支持

### 脚本支持
- **scripting/lua/**: Lua 绑定和运行时
- **scripting/javascript/**: JavaScript 绑定 (SpiderMonkey)

### 示例项目
- **samples/Cpp/**: C++ 示例项目
  - HelloCpp: 基础 "Hello World" 示例
  - TestCpp: 综合测试套件
  - SimpleGame: 基础游戏示例
- **samples/Lua/**: Lua 绑定示例
- **samples/Javascript/**: JavaScript 绑定示例

### 构建配置
- 每个平台都有自己的项目目录 (proj.win32, proj.ios, proj.android 等)
- Unix-like 系统的 Makefile 位于 proj.linux, proj.nacl, proj.emscripten
- 平台特定代码位于 cocos2dx/platform/

### 开发工具
- **tools/cocos2d-console/**: 命令行开发工具
- **tools/tolua++/**: Lua 绑定生成
- **tools/tojs/**: JavaScript 绑定生成
- **tools/project-creator/**: 新项目创建脚本

## Visual Studio 现代化迁移 (VS2026)

### 迁移状态
项目已从 VS2010 迁移到现代 Visual Studio 开发环境：
- ToolsVersion 升级到 17.0/Current
- PlatformToolset 升级到 `v145` (VS2026)
- WindowsTargetPlatformVersion 设置为 10.0 (自动使用系统已安装的最新 Win10/11 SDK)
- 添加现代 C++ 标准支持 (stdcpp14)
- 所有 `.vcxproj` 项目文件已被全局升级，可以直接在 VS2026 中打开并编译

### 编译命令

#### 使用 Visual Studio (推荐)
1. 双击打开 `projects/NarutoSenki/proj.win32/NarutoSenki.sln`。
2. 菜单栏选择：**生成 (Build)** -> **生成解决方案 (Build Solution)** (快捷键 `Ctrl+Shift+B`)。

#### 使用命令行 (MSBuild)
```bash
# 编译整个解决方案 (在包含 sln 的目录下)
msbuild cocos2d-win32.vc2012.sln /p:Configuration="Debug" /p:Platform="Win32" /m

# 编译游戏项目 (在 projects\NarutoSenki\proj.win32 目录下)
msbuild NarutoSenki.sln /p:Configuration="Debug" /p:Platform="Win32" /m
```

### 游戏项目
- **projects/NarutoSenki/**: 火影战记游戏项目
  - 基于 cocos2d-x 2.2.2，使用 2.2.6 框架
  - 完整的游戏逻辑、音效、图片资源
  - 已迁移至 VS2026 (v145) 兼容配置

### 常见问题与文档
- 参考 `projects/NarutoSenki/项目现状.md` 了解项目状态与测试态修复详情
- 参考 `projects/编译错误解决方案.md` 解决编译问题
- 参考 `projects/迁移指南.md` 了解迁移详情
- sprintf/strcpy 等函数已添加安全版本支持
- 添加了 legacy_stdio_definitions.lib 依赖