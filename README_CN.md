
[English](README.md) | 简体中文

# CASIM

![screenshot.png](./assets/screenshot.png)

一个元胞自动机模拟器（**C**ellular **A**utomata **SIM**ulator）。

可以使用 Lua 语言的脚本对元胞自动机规则进行定义，支持一维至三维元胞自动机的可视化。

## 使用方法

### 下载运行

直接从侧边的 `发行版` 或 `Release` 页面中下载最新发布版本（目前为 v0.0.0）并解压运行。

### 编译运行

1. 克隆或直接下载这个仓库的代码；
2. 确认 qt 及 opengl 配置完成；
3. 使用 `qmake && make` 命令或双击 `casim.pro` 在 Qt Creator 中打开。

## 依赖的库

Casim 调用了 `xtensor` `xlt` `lua` 和 `freeglut`. 这些库的开源许可证都位于 `third_party` 中相应的文件夹下。

## 开源许可

使用 MIT 协议开源，具体参见[本项目的开源协议](LICENSE)。

## 关于这个项目

这是本学期高级语言程序设计大作业的源代码仓库。
