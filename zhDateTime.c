/*

版权所有 © 2024 金羿ELS
Copyright (R) 2024 Eilles(EillesWan@outlook.com)

This Source Code Form is subject to the terms of the Mozilla Public
License, v. 2.0. If a copy of the MPL was not distributed with this
file, You can obtain one at http://mozilla.org/MPL/2.0/.


*/

#include <stdio.h>
#include <time.h>

// 汉字数字
const char* HANNUM[] = { "〇", "一", "二", "三", "四",
                         "五", "六", "七", "八", "九" };

// 仅出现在十位的汉字计数单位
const char* HANUNIT10P[] = { "初", "十", "廿", "卅" };

// 小于万的汉字计数单位
const char* HANUNITLK[] = { "十", "百", "千" };

// 大于千的汉字计数单位
const char* HANUNITRW[] = { "万", "亿", "兆", "京", "垓", "秭",
                            "穰", "沟", "涧", "正", "载" };

// 十二个月，首位占位
const char* MONTHNUM[] = { "空", "正", "二", "三", "四", "五", "六",
                           "七", "八", "九", "十", "冬", "腊" };

// 十二生肖
const char* SHENGXIAO[] = { "鼠", "牛", "虎", "兔", "龙", "蛇",
                            "马", "羊", "猴", "鸡", "狗", "猪" };

// 十天干
const char* TIANGAN[] = { "甲", "乙", "丙", "丁", "戊",
                          "己", "庚", "辛", "壬", "癸" };

// 十二地支
const char* DIZHI[] = { "子", "丑", "寅", "卯", "辰", "巳",
                        "午", "未", "申", "酉", "戌", "亥" };

// 宋以后的二十四时辰表示法所用之时辰
const char* XXIVSHICHEN[] = {
  "子初", "子正", "丑初", "丑正", "寅初", "寅正", "卯初", "卯正",
  "辰初", "辰正", "巳初", "巳正", "午初", "午正", "未初", "未正",
  "申初", "申正", "酉初", "酉正", "戌初", "戌正", "亥初", "亥正",
};

/*
自1900年至2100年（首尾皆含）的农历新年所在的公历日期表（从首至尾）
每一位字节均表示一个日期，例如第一个字节 \x83 数字为 131 即表示 1900
年的农历新年是1月31日
*/
const unsigned char LUNAR_NEW_YEAR_DATE[201] = {
  '\x83', '\xdb', '\xd0', '\x81', '\xd8', '\xcc', '\x7d', '\xd5', '\xca',
  '\x7a', '\xd2', '\x82', '\xda', '\xce', '\x7e', '\xd6', '\xcb', '\x7b',
  '\xd3', '\xc9', '\xdc', '\xd0', '\x80', '\xd8', '\xcd', '\x7c', '\xd5',
  '\xca', '\x7b', '\xd2', '\x82', '\xd9', '\xce', '\x7e', '\xd6', '\xcc',
  '\x7c', '\xd3', '\x83', '\xdb', '\xd0', '\x7f', '\xd7', '\xcd', '\x7d',
  '\xd5', '\xca', '\x7a', '\xd2', '\x81', '\xd9', '\xce', '\x7f', '\xd6',
  '\xcb', '\x7c', '\xd4', '\x83', '\xda', '\xd0', '\x80', '\xd7', '\xcd',
  '\x7d', '\xd5', '\xca', '\x79', '\xd1', '\x82', '\xd9', '\xce', '\x7f',
  '\xd7', '\xcb', '\x7b', '\xd3', '\x83', '\xda', '\xcf', '\x80', '\xd8',
  '\xcd', '\x7d', '\xd5', '\xca', '\xdc', '\xd1', '\x81', '\xd9', '\xce',
  '\x7f', '\xd7', '\xcc', '\x7b', '\xd2', '\x83', '\xdb', '\xcf', '\x80',
  '\xd8', '\xcd', '\x7c', '\xd4', '\xc9', '\x7a', '\xd1', '\x81', '\xda',
  '\xcf', '\x7e', '\xd6', '\xcb', '\x7b', '\xd2', '\x83', '\xdb', '\xd0',
  '\x80', '\xd8', '\xcd', '\x7d', '\xd4', '\xc9', '\x7a', '\xd2', '\x81',
  '\xd9', '\xce', '\x7e', '\xd5', '\xcb', '\x7b', '\xd3', '\x83', '\xdb',
  '\xd0', '\x80', '\xd7', '\xcc', '\x7c', '\xd4', '\xc9', '\x7a', '\xd2',
  '\x82', '\xd9', '\xce', '\x7e', '\xd6', '\xca', '\x7b', '\xd3', '\xc9',
  '\xdb', '\xd0', '\x80', '\xd7', '\xcc', '\x7c', '\xd4', '\xca', '\x79',
  '\xd1', '\x81', '\xd9', '\xcd', '\x7e', '\xd6', '\xcb', '\x7b', '\xd3',
  '\x83', '\xdb', '\xcf', '\x7f', '\xd7', '\xcd', '\x7c', '\xd4', '\xca',
  '\x7a', '\xd1', '\x81', '\xd9', '\xce', '\x7e', '\xd6', '\xcb', '\x7c',
  '\xd2', '\x82', '\xda', '\xcf', '\x7f', '\xd7', '\xcd', '\x7d', '\xd4',
  '\xc9', '\x79', '\xd1'
};

/*
自1900年至2100年（首尾皆含）的每年的农历月份（从首至尾）
对于每个数据：
占有两个字节，共16位
首四位规定为闰的是哪一月，如 0101 为 5 即在当年5月之后闰一月
后十二位表示该年的大小月分布情况，如 010101010101 表示当年月份情况位
小大小大小大小大小大小大 月
！！注意：我不记得大小月分布状况的顺序是从左至右还是从右至左了，请依据实际代码来判断
*/
const unsigned short LUNAR_MONTH_PER_YEAR[201] = {
  33981, 1198,  2647,  21837, 3366,  3477,  18005, 1386,  2477,  9565,  1198,
  27227, 2637,  3365,  23845, 2900,  3434,  10970, 2395,  29847, 1175,  2635,
  23371, 1701,  1748,  19125, 694,   2391,  9519,  1175,  26198, 3402,  3749,
  22185, 1453,  694,   14446, 2350,  31885, 3221,  3402,  28042, 2901,  1386,
  19035, 605,   2349,  11563, 2709,  31573, 1738,  2901,  21813, 1242,  2651,
  13399, 1323,  35482, 3733,  1706,  27370, 2741,  1206,  19118, 2647,  1318,
  16166, 3477,  30133, 1386,  2413,  21725, 1197,  2637,  19789, 3365,  36181,
  2900,  2922,  26970, 2395,  1179,  19095, 2635,  43815, 1701,  1748,  27380,
  2742,  2391,  21679, 1175,  1611,  14154, 3749,  34485, 1452,  2742,  22893,
  2350,  3222,  19861, 3402,  3493,  10069, 1386,  31419, 605,   2349,  23723,
  2709,  2890,  19370, 2773,  38237, 1210,  2651,  25879, 1323,  2707,  18325,
  1706,  2773,  9653,  1206,  27246, 2638,  3366,  24230, 3411,  1450,  14186,
  2413,  46255, 1197,  2637,  27915, 3365,  3410,  24020, 2906,  1389,  9563,
  1179,  31319, 2635,  2725,  23333, 1746,  2778,  13494, 2359,  33951, 1175,
  1611,  26250, 3749,  1706,  19052, 2734,  2350,  15662, 3222,  32085, 3402,
  3493,  21973, 1386,  2669,  17757, 1325,  35483, 2709,  2890,  27498, 2773,
  1370,  19130, 2651,  1323,  15143, 1683,  30515, 1706,  2773,  21685, 1206,
  2647,  17742, 3350,  36502, 3410,  3498,  26282, 1389,  1198,  19101, 2605,
  3349,  12069, 3410
};

/*
分别是自1900年至2100年（首尾皆含）的农历闰月大小月（从尾至首）
1 为大月 30 日
0 为小月 29 日
*/
const unsigned long long int LEAP_SIZE[4] = {
  0b000000010,
  0b0000001000000000000000000000000001001000010010000000000100000000,
  0b0000000000100000000000000000000000000000000000001000000000000000,
  0b0000000010010000000100100101001000000010000010000100000001000000
};
/*
const bool LEAP_SIZE[201] = {
  false, false, false, false, false, false, false, true,  false, false, false,
  false, false, false, false, true,  false, false, false, false, false, false,
  false, false, false, false, false, false, false, false, false, false, false,
  false, false, false, false, false, false, false, false, false, true,  false,
  false, true,  false, false, false, false, true,  false, false, true,  false,
  false, false, false, false, false, false, false, false, false, true,  false,
  false, false, false, false, false, false, false, false, false, false, false,
  false, false, false, false, false, false, true,  false, false, false, false,
  false, false, false, false, false, false, false, false, false, false, false,
  false, false, false, false, false, false, false, false, false, false, false,
  false, false, false, false, false, false, false, false, false, false, false,
  true,  false, false, false, false, false, false, false, false, false, false,
  false, false, false, false, false, false, false, false, false, false, false,
  false, false, true,  false, false, true,  false, false, false, false, false,
  false, false, true,  false, false, true,  false, false, true,  false, true,
  false, false, true,  false, false, false, false, false, false, false, true,
  false, false, false, false, false, true,  false, false, false, false, true,
  false, false, false, false, false, false, false, true,  false, false, false,
  false, false, false
};

0b
000000010
0000001000000000000000000000000001001000010010000000000100000000
0000000000100000000000000000000000000000000000001000000000000000
0000000010010000000100100101001000000010000010000100000001000000

12603243328493723047405108687154840022568558660414467489856
*/

/*
charU-charU 结构体*/
typedef struct
{
  unsigned char uchar_a;
  unsigned char uchar_b;
} double_char_t;

// 农历年的每月天数及闰月月份结构体
typedef struct
{
  unsigned char year_days[13]; // 每月天数
  unsigned char leap_month;    // 闰月月份
} count_of_days_and_leap_t;

// 依据提供的公历年份，返回当年的农历新年所在的公历日期(月, 日)
double_char_t
get_lunar_new_year(unsigned short solar_year)
{
  unsigned char new_year_code = LUNAR_NEW_YEAR_DATE[solar_year - 1900];
  return (double_char_t){ new_year_code / 100, new_year_code % 100 };
}

// 依据提供的是否为大小月之布尔值，返回当月的天数
unsigned char
month_days_bs(big_or_small)
{
  return big_or_small ? 30 : 29;
}

// 依据提供的农历月份信息，求取所需的月份之天数
unsigned char
month_days_pusher(unsigned short month_code, unsigned char push_i)
{
  return month_days_bs((month_code >> push_i) & 1);
}

/*
  依据提供的农历月份信息码，求取当年每月天数之列表及闰月月份
  当无闰月时，返回结构体的 leap_month 为 0，且 year_days 长度为 12
  当存在闰月，leap_month 为闰的月份，且 year_days 长度为 13
  **请注意，C语言无法带默认参数，因此 leap_days 参数必须显式传入**
*/
count_of_days_and_leap_t
decode_lunar_month_code(unsigned short month_code, unsigned char leap_days)
{

  count_of_days_and_leap_t result;
  int leap_month = (month_code & 0b1111000000000000) >> 12;

  // 初始化设置所有 year_days 为 0
  memset(&result.year_days, 0, sizeof(result.year_days));

  if (leap_month) {
    // 当存在闰月时
    // 从月码的末位向前至 (12 - leap_month) 位，填充月份日期
    for (unsigned char i = 11; i >= 12 - leap_month; i--) {
      result.year_days[11 - i] = month_days_pusher(month_code, i);
    }

    // 插入闰月当月天数
    result.year_days[leap_month] = leap_days;

    // 填充剩余的每月天数
    for (unsigned char i = 11 - leap_month; i >= 0; i--) {
      result.year_days[12 - i] = month_days_pusher(month_code, i);
    }
  } else {
    // 正常顺序填充，不需加入闰月了
    for (unsigned char i = 11; i >= 0; i--) {
      result.year_days[11 - i] = month_days_pusher(month_code, i);
    }
  }

  result.leap_month = leap_month;
  return result;
}

// 依据提供的公历年份，返回当年的农历月份信息码
unsigned char
get_lunar_month_code(unsigned short solar_year)
{
  return LUNAR_MONTH_PER_YEAR[solar_year - 1900];
}

// 依据提供的公历年份，通过判断当年的农历中是否有大闰月，给出其闰月应为几天
unsigned char
get_lunar_leap_size(unsigned short solar_year)
{
  return month_days_bs(LEAP_SIZE[3 - ((solar_year - 1900) / 64)] >>
                       ((solar_year - 1900) % 64));
}

// 依据提供的公历年份，给出当年每月天数之列表及闰月月份
count_of_days_and_leap_t
get_lunar_month_list(unsigned short solar_year)
{
  return decode_lunar_month_code(get_lunar_month_code(solar_year),
                                 get_lunar_leap_size(solar_year));
}

/*
检查所给出之农历日期是否符合本库之可用性
这里不像 Python 那样给出多个数据，只是单纯地给出是否可用
*/
char
verify_lunar_date(int lunar_year, int lunar_month, char is_leap, int lunar_day)
{

  // 验证年份范围
  if (!(1900 <= lunar_year && lunar_year <= 2100)) {
    return 0;
  }

  // 验证月份范围
  if (!(1 <= lunar_month && lunar_month <= 12)) {
    return 0;
  }

  // 获取农历月份数据
  count_of_days_and_leap_t lunar_month_data = get_lunar_month_list(lunar_year);

  // 验证日期范围
  char verify_result =
    is_leap
      ? (1 <= lunar_day && lunar_day <= get_lunar_leap_size(lunar_year)) &&
          (lunar_month == lunar_month_data.leap_month)
      : (1 <= lunar_day &&
         lunar_day <= lunar_month_data.year_days[lunar_month - 1]);

  return verify_result;
}

// 将给出的地支时辰字符串转为时辰数
char
shichen2int(const char* dizhi, char xxiv)
{

  if (xxiv) {
    // 使用二十四时辰表示法
    for (int i = 0; i < sizeof(XXIVSHICHEN) / sizeof(XXIVSHICHEN[0]); i++) {
      if (strncmp(dizhi, XXIVSHICHEN[i], 2) == 0) {
        return i;
      }
    }
  } else {
    // 使用地支表示法
    for (int i = 0; i < sizeof(DIZHI) / sizeof(DIZHI[0]); i++) {
      if (dizhi[0] == DIZHI[i][0]) {
        return i;
      }
    }
  }

  return -1;
}

// 给出时辰和刻数，返回小时和分钟(时, 分)
double_char_t
shichen_ke_2_hour_minute(unsigned char shichen,
                         unsigned char quarter,
                         char xxiv)
{
  return xxiv ? (double_char_t){ (shichen - 1) % 24, quarter * 15 }
              : (double_char_t){ (23 + (shichen * 2) + (quarter / 4)) % 24,
                                 (quarter * 15) % 60 };
}

// 给出小时和分钟，返回时辰和刻数(时辰, 刻)
double_char_t
hour_minute_2_shichen_ke(unsigned char hours, unsigned char minutes, char xxiv)
{
  unsigned char shichen;
  return xxiv ? (double_char_t){ (hours + 1) % 24, minutes / 15 }
              : (double_char_t){
                  shichen = (((hours = hours + ((minutes / 60))) + 1) / 2) % 12,
                  (((hours - ((shichen * 2 - 1) % 24)) % 24) * 60 +
                   (minutes % 60)) /
                    15
                };
}

/*
整数分组，依据汉字标准
写不出来，等会写
TO-DO
======================
int_group
int_group_seperated
int_2_grouped_hàn_str
int_hànzìfy
======================
*/

// 辅助函数：连接多个字符串
char*
concat_strings(char* first, char* second)
{
  char* result = NULL;
  size_t len = strlen(first) + strlen(second) + 1;
  result = (char*)malloc(len * sizeof(char));
  if (!result) {
    return NULL;
  }
  strcpy(result, first);
  strcat(result, second);

  // 释放临时分配的内存
  free(first);
  free(second);
  return result;
}

// 万以内的数字汉字化
char*
lkint_hanzify(int integer)
{
  // 这个函数是 人工智能 写的，我也有点看不懂，如果能用那就行

  if (integer == 0) {
    return strdup("零");
  } else if (integer < 10) {
    return strdup(HANNUM[integer]);
  } else if (integer < 100) {
    if (integer % 10 == 0) {
      return concat_strings(HANNUM[integer / 10], "十");
    } else if (integer < 30) {
      if (integer > 20) {
        return concat_strings("廿", HANNUM[integer % 10]);
      } else if (integer > 10) {
        return concat_strings("十", HANNUM[integer % 10]);
      } else {
        return strdup(HANNUM[integer % 10]);
      }
    } else {
      return concat_strings(concat_strings(HANNUM[integer / 10], "十"),
                            HANNUM[integer % 10]);
    }
  } else if (integer < 1000) {
    if (integer % 100 == 0) {
      return concat_strings(HANNUM[integer / 100], "百");
    } else if ((integer / 10) % 10 == 0) {
      return concat_strings(concat_strings(HANNUM[integer / 100], "百零"),
                            HANNUM[integer % 10]);
    } else {
      char* middle = HANNUM[(integer / 10) % 10];
      char* last = HANNUM[integer % 10];
      return concat_strings(
        concat_strings(concat_strings(HANNUM[integer / 100], "百"),
                       middle ? concat_strings(middle, "十") : "十"),
        last ? last : "");
    }
  } else {
    if (integer % 1000 == 0) {
      return concat_strings(HANNUM[integer / 1000], "千");
    } else if ((integer / 100) % 10 == 0) {
      if ((integer / 10) % 10 == 0) {
        return concat_strings(concat_strings(HANNUM[integer / 1000], "千零"),
                              HANNUM[integer % 10]);
      } else {
        char* middle = HANNUM[(integer / 10) % 10];
        char* last = HANNUM[integer % 10];
        return concat_strings(
          concat_strings(
            concat_strings(concat_strings(HANNUM[integer / 1000], "千零"),
                           middle ? concat_strings(middle, "十") : "十"),
            last ? last : ""),
          "");
      }
    } else {
      char* rest = lkint_hanzify(integer % 1000);
      return concat_strings(concat_strings(HANNUM[integer / 1000], "千"), rest);
    }
  }
}



/*

两个类 zhDateTime
和 DateTime
在 C 语言环境肯定是写不出来的
但我们不妨碍用面对对象思想来写
看看这个：
https://blog.csdn.net/qq_29041843/article/details/131995120
等会再来写吧
 */
