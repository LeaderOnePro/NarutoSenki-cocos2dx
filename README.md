# NarutoSenki-cocos2dx

这是一个火影战记的 C++ 移植与现代化重构版本。基于 **Cocos2d-x 2.2.6** 框架构建，针对 Windows 平台及现代开发环境（VS2026）进行了全面适配与体验优化。

---

## 🎮 火影战记快速上手指南

### 1. 开发环境要求
- **操作系统**: Windows 10/11
- **开发工具**: Visual Studio 2026
- **编译器工具集**: `v145` (VS2026)
- **Windows SDK**: `10.0` 及以上版本

### 2. 编译步骤 (Visual Studio)
1. 双击打开项目解决方案：
   `projects/NarutoSenki/proj.win32/NarutoSenki.sln`
2. 在 VS 顶部工具栏确认配置：
   - 解决方案配置：**Debug** 或 **Release**
   - 解决方案平台：**Win32** (必须是 32位 平台)
3. 编译项目：
   - 快捷键：`Ctrl + Shift + B`
   - 或者菜单栏选择：**生成 (Build)** -> **生成解决方案 (Build Solution)**
   - 编译输出产物将保存在 `projects/NarutoSenki/proj.win32/Debug.win32/` 或 `Release.win32/` 目录下。

### 3. 运行游戏
由于游戏资源依赖当前工作目录（CWD），请勿直接双击运行编译出的 `.exe`。
- **推荐运行方式**: 双击运行根目录或项目目录下的启动脚本：
  `projects/NarutoSenki/启动游戏.bat`
- **在 VS 中直接调试运行 (F5)**:
  若需要直接在 VS 中按 F5 调试，必须先设置工作目录：
  1. 右键 **NarutoSenki** 项目 -> **属性 (Properties)**
  2. 左侧导航选择 **配置属性 (Configuration Properties)** -> **调试 (Debugging)**
  3. 将 **工作目录 (Working Directory)** 改为：`$(ProjectDir)..\Resources`
  4. 保存后，即可按 `F5` 启动调试。

### 4. 已修复与优化的“测试态”行为
- **羁绊模式默认启用**: 移除了原来写死 Tsunade (纲手) 的训练模式，Training 按钮直接重定向至 NetworkLayer 组队选人界面，开启多人离线大乱斗。
- **AI 角色行动**: 启用了 AI 决策回路，修复了原版 AI 开局原地不动的 Bug。
- **还原三页选人**: 还原了经典的 1.22 版本三页角色选择界面，默认解锁所有角色。
- **PC 键位与返回键**: 移除了仅限 Android 平台的按键保护守卫，现在 PC 上按 `ESC` 或 `F1` 键可正常触发菜单返回。
- **分辨率与窗口放大**: 将 Win32 窗口分辨率由原来的 480x320 放大到 **2x (960x640)**，并新增了 PC 专属的 **Exit (退出)** 按钮。
- **健壮性修复**: 修复了游戏内缺失精灵帧（Sprite Frame）时的崩溃问题，匹配安卓 Release 版的容错表现。

---

# cocos2d-x
=========

[![Build Status](https://travis-ci.org/cocos2d/cocos2d-x.png?branch=v2)](https://travis-ci.org/cocos2d/cocos2d-x)

[cocos2d-x][1] is a multi-platform 2D game framework in C++, branched on
[cocos2d-iphone][2] and licensed under MIT.  The master branch on github uses
OpenGL ES 2.0 rendering, while the old gles11 branch uses OpenGL ES 1.1
rendering. Currently we focus on gles20 development.

Supported Platforms
-------------------

   * iOS:  stable, well tested on iOS 5.x ~ 6.x SDK.
   * Android: stable, well tested on 2.0~4.x, ndk r5 ~ r8. If you use gles20
     branch or cocos2d-x v2.0 above, only android 2.3 and higher are supported
   * Windows Phone 8 and Windows Store Apps (WinRT)
   * Bada: cocos2d-x v1.x supports Bada SDK 1.0 & 2.0. Bada support was
     deprecated since cocos2d-x v2.0.
   * BlackBerry: stable, contributed by staffs in RIM, supports Playbook & BB10.
   * Marmalade: stable since cocos2d-x v0.11.0, contributed by Marmalade's staff.
   * Native Client (NaCl): contributed by the Native Client authors.
   * Windows: stable, well tested on WinXP/Vista/Win7. Please upgrde the drive
     of your video card if you meet problems on OpenGL functions
   * Linux: support but not very stable.
   * Emscripten: Alpha-level. Most features implemented. Needs testing.
     Contributed by Zynga staff.
   * Tizen: Experimental. Essential features implemented. Needs more implementing.
     Contributed by Lee, Jae-Hong.

You can visit our continuous integration system http://ci.cocos2d-x.org to
check the stability on edge version.

Supported Programming Languages
-------------------------------

   * C++ is the major programming language of cocos2d-x. Tons of top-chart
     cocos2d-x games were written in C++.
   * Lua binding is also widely used. Glu mobile, Zynga, UCWEB, 4399, Renren
     Games are using lua on cocos2d-x.
   * Javascript binding is our recommendation since 2012 H2. Cocos2d community
     are cooperating on the same Javasciprt API on cocos2d-iphone/-x/-html5.

Documentations
--------------

   * Wiki: [wiki.cocos2d-x.org][3]
   * [Online API References][4]

Contact us
----------

   * Forum: [http://forum.cocos2d-x.org][5]
   * Twitter: [http://www.twitter.com/cocos2dx][6]
   * Weibo: [http://t.sina.com.cn/cocos2dx][7]

[1]: http://www.cocos2d-x.org "cocos2d-x"
[2]: http://www.cocos2d-iphone.org "cocos2d for iPhone"
[3]: http://wiki.cocos2d-x.org "wiki.cocos2d-x.org"
[4]: http://www.cocos2d-x.org/projects/cocos2d-x/wiki/Reference "API References"
[5]: http://forum.cocos2d-x.org "http://forum.cocos2d-x.org"
[6]: http://www.twitter.com/cocos2dx "http://www.twitter.com/cocos2dx"
[7]: http://t.sina.com.cn/cocos2dx "http://t.sina.com.cn/cocos2dx"
