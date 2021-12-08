﻿# 前言

本文的目的是为了给将要制作的ESP32手环做技术储备

准备学习下ESP32，还有嵌入式GUI框架LVGL，通过做几个小项目练手是不错的选择，最终目标是做一个ESP32的手环

做一个ESP32手环任务量还是比较大的，涉及到很多新技术，我认为步子不能迈的太大容易翻车，决定先做一个ESP32的智能花盆

# 开源链接

**20211205 所有软硬件设计制作均已完成 资料开源至github**
**后续有时间还会发布一些小教程，可以在我的csdn上找到**

代码和外壳3D打印文件链接

[https://github.com/FranHawk/esp32-smart-pow](https://github.com/FranHawk/esp32-smart-pow)

GITHUB仓库结构
0.doc 相关文档
1.hardware pcb和3D打印所需资料
2.software  代码工程，有两个版本，gui版本可烧进任意ESP32或ESP32开发板，接屏幕和键盘即可，esp32-smart-pow为完成代码工程
3.simulator 存放lvgl的pc模拟器，用vs2019打开

PCB文件链接

[https://oshwhub.com/FranHawk/green-esp32/](https://oshwhub.com/FranHawk/green-esp32/)

视频演示链接

https://www.bilibili.com/video/BV11P4y137k2/

# 功能

- 时间天气实时更新并显示
- 课程表，显示一周内的课程
- 电脑性能显示，通过局域网获取所使用的电脑当前的CPU内存等占用情况
- WIFI配网
- 亮度调节
- 蓝牙键盘，可作为一个蓝牙键盘控制电脑音量，ppt翻页，换歌等功能

# 功能展示

![在这里插入图片描述](https://img-blog.csdnimg.cn/c237c0907065450f9ddc6258beb8c64f.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBA5byg56ue6LGq,size_20,color_FFFFFF,t_70,g_se,x_16)
可以使用任意兼容QI标准的无线充电底座为其充电，市面上的充电底座几乎都可以

![在这里插入图片描述](https://img-blog.csdnimg.cn/5e082f190e5644b1af6c067158e9b842.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBA5byg56ue6LGq,size_20,color_FFFFFF,t_70,g_se,x_16)
主界面显示天气时间温湿度，并且有利用lvgl8.1的gif解码器，有动图效果
![在这里插入图片描述](https://img-blog.csdnimg.cn/d9f577e8731a454d82fc56f78f3ab832.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBA5byg56ue6LGq,size_13,color_FFFFFF,t_70,g_se,x_16)
天气界面

![在这里插入图片描述](https://img-blog.csdnimg.cn/a28413fe872b4c8d82ec988507ef3017.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBA5byg56ue6LGq,size_15,color_FFFFFF,t_70,g_se,x_16)

课程表界面

![在这里插入图片描述](https://img-blog.csdnimg.cn/91ba93882ed342c8b9313a87cbec43e9.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBA5byg56ue6LGq,size_17,color_FFFFFF,t_70,g_se,x_16)
电脑性能监控界面
![在这里插入图片描述](https://img-blog.csdnimg.cn/43da34b4f54f4020a8e4b6df2354d26a.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBA5byg56ue6LGq,size_17,color_FFFFFF,t_70,g_se,x_16)
WIFI配网界面
![在这里插入图片描述](https://img-blog.csdnimg.cn/ce25bc613d6c4d508594fd2dfe758dc4.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBA5byg56ue6LGq,size_18,color_FFFFFF,t_70,g_se,x_16)
亮度调节界面

![在这里插入图片描述](https://img-blog.csdnimg.cn/4649aa3540fb4074bab59f3a3a43c549.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBA5byg56ue6LGq,size_20,color_FFFFFF,t_70,g_se,x_16)
蓝牙键盘界面

**界面间通过一个滚动菜单选择**，可以使用模拟器模拟界面

下面是项目之初(20210920)写的需求分析和设计文档

# 需求分析

智能花盆所需要实现的功能如下：

- 基本花盆的功能：下端有透气孔，可以承载一株多肉植物，形状：长宽65mm正方形，高度根据实际情况调整的白色花盆，尽量保证外形的美观
- 带锂电池，无线充电模块，可以通过type-c口或者无线充电口为电池充电，同时为花盆供电。在无外部电源的时候，可以通过电池为花盆供电
- 板载USB转串口芯片，便于烧写代码
- 板载SD卡插槽，用户可将信息文件放入SD卡，ESP32可以读取
- ESP32 通过wifi功能，通过网络获取天气，时间等信息，通过局域网获取电脑性能等信息，后期可考虑加入wifi配网功能
- 通过一块1.54寸 240*240分辨率显示信息，信息如下，每一行代表一个页面
  	1. 当天时间和当天基本天气信息显示光照信息，检测当前是否充电，带**罗小黑动画效**果，通过晃动花盆可以切换动画效果
       2. 三天基本天气信息
       3. 电脑性能，内存占用等信息
       4. 课程表，显示当天课程
       5. 课程表，显示明天课程
       6. 显示当前植物信息

# 技术分析

- 首先硬件方面需要原理图PCB绘制和制作3D打印外壳技术，原理图PCB绘制采用立创EDA，外壳3D建模采用SW2020，去淘宝找厂家3D打印外壳 

  技能掌握情况：基本掌握

- 软件方面采用基于arduino的ESP32+LVGL框架，学习ESP32+LVGL基本使用，同时需要学习并移植XTRACK的页面生命周期管理API，根据需求分析需要掌握技术：LVGL移植到ESP32，ESP32连接到网络获取天气等信息，ESP32获取MPU6050数据，ESP32获取光敏电阻数据，LVGL文件系统移植，通过文件系统获取SD卡中信息，LVGL显示中文显示图片...

  20211002 基本掌握

## 任务细分

- 原理图和PCB绘制，投板制版并测试

  20210903 完成原理图和PCB绘制，已经投板，还未进入焊接阶段

  20210910 所有原件均到货，完成PCB制作，并完成测试，CH340不应该用5V供电，MPU6050少接一个电容工作不正常，其他部分工作正常，排线接口位置别扭，现有板子暂时能用，但是还是要再投一版

  20210915 新版本pcb投板并制作完成，测试完毕

  **已完成**

  

- 外壳设计与制作

  20210911 完成外壳设计工作

  20211120 完成外壳3D打印

  **已完成**



- 无线充电底座购买和无线充电模块测试

  20210910 无线充电底座到货，现有无线接收模块谐振频率不对，电压达不到5V，准备购买兼容QI协议的无线接收模块
  20211110 无线接收模块测试完毕
  **已达成**

  

- LVGL移植到ESP32

  20210817 完成LVGL移植

  **已达成**

  

- ESP32连接网络，获取天气，时间信息

  20210829 实现通过网络获取天气信息

  20210911 实现通过网络获取时间信息

  **已达成**

  

- ESP32连接网络，获取电脑性能信息

  20210825 实现通过网络获取电脑性能信息

  **已达成**

  

- ESP32获取MPU6050和光敏电阻的数据

  20210823 完成MPU6050数据获取

  

- ESP32上SD卡操作与LVGL文件系统移植

  20210830 完成SD卡操作与LVGL文件系统移植

  **已达成**

  

- LVGL中文和图片显示

  20210906 完成LVGL中文和图片显示

  **已达成**

  

- LVGL的PC模拟器使用

  20210906 初步完成LVGL的PC模拟器使用

  **已达成**

  

- LVGL移植XTRACK的页面生命周期管理API

  2021821 完成页面生命周期管理API学习，还未完成移植

  20210910 完成PC模拟器上菜单选择界面UI设计，发现XTRACK的页面生命周期管理暂时还用不到，先用纯LVGL开发

  **已达成**

  

- LVGL的PC模拟器设计UI交互页面

  20210910 完成PC模拟器上菜单选择界面UI设计，接下来完成子页面的设计

  20211120 完成所有子页面设计

  **已达成**

  

- UI交互页面移植到ESP32上，系统联调

  20211125 完成

  **已达成**

  

- ESP32上LVGL按键输入功能移植

  20210907 完成ESP32上LVGL按键输入功能移植

  **已达成**

  

# 硬件架构设计

 

![image-20210906164213161](https://img-blog.csdnimg.cn/img_convert/4481665827ee5830a792415531440723.png)



