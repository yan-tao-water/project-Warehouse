#include <stdio.h>
#include <stdlib.h>
#include"menuView.h"
void viewUser()
{
    printf("———————————欢迎进入用户界面———————————\n");
    printf("\n\n\t1、查看个人信息\n");
    printf("\t2、修改个人信息\n");
    printf("\t3、注销个人信息\n");
    printf("\t4、充      值\n");
    printf("\t5、查询中奖记录\n");
    printf("\t6、买       票\n");
    printf("\t7、查询购票记录\n");
    printf("\t0、返回上一级\n\n");
}
void viewMain()
{
    system("clear");
    printf("———————————欢迎登录彩票系统———————————\n");
    printf("\t1、登录\n");
    printf("\t2、用户注册\n\n");
    printf("\t0、退出\n\n");
}
void viewAdmin()
{
    system("clear");
    printf("———————————你好，管理员——————————————\n");
    printf("\n\n\t1、发行彩票\n");
    printf("\t2、按用户账号查询\n");
    printf("\t3、按用户余额排序\n");
    printf("\t0、退出\n\n");
}
void viewNotary()
{
    system("clear");
    printf("———————————你好，公证员————————————\n");
    printf("\n\n\t1、开奖\n");
    printf("\t2、查看历史发行\n");
    printf("\t0、退出\n\n");
}
