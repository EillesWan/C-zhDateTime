# C-zhDateTime 中式日期时间库

C 语言 下的 zhDateTime 库

一个简单小巧的轻量级中式日期时间库，支持农历公历互相转换，支持时辰刻数的时间表达转换，支持整数汉字化。

### zhDateTime

本仓库移植自 Python 语言写的 [zhDateTime](https://gitee.com/EillesWan/zhDateTime) 库，并使用同名 API。

在源库的基础上并不作过多改动，但由于 C 语言数据类型并不如 Python 那样灵活多变，很多成组的参数使用 结构体 进行传递。

### 用法

暂时没做好，等会写文档

### 授权

本库之授权与 [zhDateTime](https://gitee.com/EillesWan/zhDateTime) 一致，均采用 MPL 2.0 进行开源。

> 版权所有 © 2024 金羿ELS\
> Copyright (R) 2024 Eilles(EillesWan@outlook.com)\
> \
> This Source Code Form is subject to the terms of the Mozilla Public\
> License, v. 2.0. If a copy of the MPL was not distributed with this\
> file, You can obtain one at http://mozilla.org/MPL/2.0/.

### 参标

1. 本库的农历日期计算方法参照[《中华人民共和国国家标准 GB/T 33661—2017〈农历的编算和颁行〉》](https://openstd.samr.gov.cn/bzgk/gb/newGbInfo?hcno=E107EA4DE9725EDF819F33C60A44B296)
2. 本库的时刻表达方法参照[时辰\_百度百科](https://baike.baidu.com/item/%E6%97%B6%E8%BE%B0/524274)中，唐以后的“十二时辰制”，此制是目前最为广为人知的时辰表示方法；对于宋以后的“二十四时辰”制，本库虽有提供相关内容，但并不实际采用
3. 本库中的拼音参照[《中华人民共和国国家标准 GB/T 16159-2012〈汉语拼音正词法基本规则〉》](https://openstd.samr.gov.cn/bzgk/gb/newGbInfo?hcno=5645BD8DB9D8D73053AD3A2397E15E74)
4. 本库中的汉字大数表示方法，参照[徐岳．数术记遗．](https://ctext.org/wiki.pl?if=gb&res=249044&remap=gb)<font color=gray size=0.5>《周髀算经》，汉</font>
5. 本库中的汉字数字表示方法参照[读数法\_百度百科](https://baike.baidu.com/item/%E8%AF%BB%E6%95%B0%E6%B3%95/22670728)中，十进制读数法的相关内容
6. 本库的汉字数字用法参照[《中华人民共和国国家标准 GB/T 15835-2011〈出版物上数字用法的规定〉》](https://xb.sasu.edu.cn/__local/9/03/2D/4990C7C8DFC8D015AC7CD1FA1F9_237F574B_5DAA5.pdf)

### 致谢

1. 感谢[香港天文台](https://www.hko.gov.hk/tc/index.html)的[公历与农历日期对照表](https://www.hko.gov.hk/tc/gts/time/conversion1_text.htm)提供的自公历 1901 年至公历 2100 年的农历日期对照数据
2. 感谢[zhdate](https://github.com/CutePandaSh/zhdate)项目启发，以至于作者决定开发此项目，作者曾去那贡献过代码（awa）
3. 感谢[cnlunar 相关代码](https://github.com/OPN48/cnlunar/blob/master/cnlunar/config.py)为存储日期的方式样式提供启发
4. 感谢[中国哲学书电子化计划](https://ctext.org/zhs)为古代文献的查考提供便捷实用的途径
5. 感谢[通义灵码](https://tongyi.aliyun.com/lingma)为我编写代码提供辅助
6. 感谢[用C语言来描述对象（类、属性、方法及封装、继承和多态的概念）](https://blog.csdn.net/qq_29041843/article/details/131995120)一文为 C语言 的对象化实现提供灵感