This project is developed using Tuya SDK, which enables you to quickly develop branded apps connecting and controlling smart scenarios of many devices.For more information, please check Tuya Developer Website.
# mico-pat-iot-sdk-v1
cerate-a-pet-eat-iot

一、方案标题
===============

宠物自动喂食器

二、方案应用场景
===============

该方案应用于铲屎官们家中的宠物喂食，比如猫咪和狗狗。

喂养宠物的铲屎官都明白，宠物平时的最大消耗就是他们的宠粮，每天要加几次宠粮才能满足宠物对食物的需求。但是每天需要上班赚取生活费的铲屎官，在家里的时间并不多，宠物白天的饮食就是一个大问题，如果早上过多的添加宠粮，会造成宠物不停地进食，造成肥胖等疾病，但是如果添加的过少，在白天家中无人的情况下宠物有得不到及时的食物补充，对宠物的生长也不利。这时候一块自动的定时宠粮喂食器便显得尤为重要。特别是在铲屎官因故长期不在家，造成宠物得不到进食的问题。
该方案设计以下几点功能：
1.自动定时投食
2.自定义每次投食量
3.断粮提醒
4.手机远程投食
5.可查看投食记录

技术要点：
-------------

1.STM32MCU作为主控，控制逻辑
2.涂鸦WiFi模组作为通信模块用来连接stm32和涂鸦IOT云平台
3.涂鸦IOT云平台提供云端数据储存
4.减速电机的控制
5.外壳的搭建

三、开发计划
=============

4月10前完成.
1.3月12前准备物料
2.3月14-25日嵌入式开发、云开发
3.3月30日前整体调试。
