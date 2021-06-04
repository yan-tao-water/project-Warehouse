#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "control.h"
void conMain(Lotterylink *headlottery, LinkUser *headUser, IssueLink *headIssue) //控制主函数
{
    while (1)
    {
        viewMain(); //主界面
        int a = -1;
        printf("请输入选项：");
        scanf("%d", &a);
        system("clear");
        CLEAR();
        if (a == 1) //登录
        {
            conSign(headlottery, headUser, headIssue); //登录控制程序（识别 ：普通用户，管理员，公证员）
        }
        else if (a == 2) //用户注册
        {
            addUser(headUser);                  
            userSaveToFile(FILEUSER, headUser); 
            CON_ENTER();
        }
        else if (a == 0) //退出
        {
            break;
        }
        else
        {
            printf("输入错误！！\n");
        }
    }
}
void conUser(Lotterylink *headlottery, IssueLink *headIssue, LinkUser *headUser, LinkUser *p) //用户界面控制
{
    while (1)
    {
        CON_ENTER();
        system("clear");
        viewUser(); //用户控制界面
        int a = -1;
        printf("请输入选项：");
        scanf("%d", &a);
        CLEAR();
        system("clear");
        if (a == 1)//查看个人信息
        {
		printf("姓名\t余额\t彩票注数\n");
		display(p);
        }
        else if (a == 2) //修改个人信息（修改密码）
        {
            	changepasswd(p);
		userSaveToFile(FILEUSER,headUser);
        }
        else if (a == 3) //注销个人信息
        {
         	deleteNode(p);   
		userSaveToFile(FILEUSER,headUser);
		printf("注销成功。");
			
        }
        else if (a == 4)//充值
        {
           	recharge(p);
		userSaveToFile(FILEUSER,headUser);
        }
        else if (a == 5)//查询中奖记录
        {
           	 winningSortCash(headIssue, headlottery);
        }
	else if (a == 6)//买票
        {
           	Lotterylink *L = NULL;
		L = buyLottery(headlottery,headIssue,p);
		if(NULL == L)
		{
			printf("购买彩票失败。");
		}
		else
		{
			system("clear");
			displayLottery(L);
			userSaveToFile(FILEUSER,headUser);
			lotterySaveToFile(FILELOTTERY,headlottery);
		}
        }
	else if (a == 7)//查询购票记录
        {
           	int i = findlottery(headlottery, p->next->user.name);
		if(i==0)
		{
			printf("未购买彩票。");
		}
		else
		{
			printf("\n---------以上%d条彩票购买记录---------\n", i);
		}
        }
        else if (a == 0) //退出
        {
            break;
        }
        else
        {
            printf("输入错误！！\n");
        }
    }
}
void conSign(Lotterylink *headlottery, LinkUser *headUser, IssueLink *headIssue) //登录控制程序（识别 ：普通用户，管理员，公证员）
{

    system("clear");
    printf("请输入用户名：");
    char namekey[20] = {"\0"};
    scanf("%s", namekey);
    CLEAR();
    if (strcmp(namekey, "admin") == 0)
    {
        char passkey[20] = "123456";
        if (confirmPassword(passkey) == 1)
        {
            conAdmin(headUser, headIssue, headlottery); //管理员操作界面
            return;
        }
    }
    else if (strcmp(namekey, "notary") == 0)
    {
        char passkey[20] = "123456";
        if (confirmPassword(passkey) == 1)
        {
            conNotary(headlottery, headIssue, headUser); //公证员操作界面
            return;
        }
    }
    else
    {
        LinkUser *p = NULL;
        p = signUser(headUser, namekey);
        if (p != NULL)
        {
            conUser(headlottery, headIssue, headUser, p); //普通用户操作界面
            return;
        }
    }
    CON_ENTER();
}
void conAdmin(LinkUser *headUser, IssueLink *headIssue, Lotterylink *headlottery) //管理员操作界面
{
    while (1)
    {
        CON_ENTER();

        viewAdmin();
        int a = -1;
        printf("请输入选项：");
        scanf("%d", &a);
        CLEAR();
        system("clear");
        if (a == 1) //发行彩票
        {
            addIssue(headIssue);                   
            issueSaveToFile(FILEISSUE, headIssue); 
        }
        else if (a == 2) //按用户账户账号查询
        {
            sortLotteryID(headlottery);
            purchaseHistory(headUser, headlottery);
        }
        else if (a == 3)//按余额查找用户
        {
            sortBalance(headUser);          
        }
        else if (a == 0) //退出
        {
            break;
        }
        else
        {
            printf("输入错误！！\n");
        }
    }
}
void conNotary(Lotterylink *headlottery, IssueLink *headIssue, LinkUser *headUser) //公证员操作界面
{
    while (1)
    {
        CON_ENTER();
        viewNotary();
        int a = -1;
        printf("请输入选项：");
        scanf("%d", &a);
        CLEAR();
        if (a == 1) //开奖
        {
            lotteryDraw(headlottery, headIssue, headUser); 
            userSaveToFile(FILEUSER, headUser);           
            issueSaveToFile(FILEISSUE, headIssue);       
            lotterySaveToFile(FILELOTTERY, headlottery);  
        }
        else if (a == 2)
        {
            displayAllIssue(headIssue); //查看发行记录
        }
        else if (a == 0) //退出
        {
            break;
        }
        else
        {
            printf("输入错误！！\n");
        }
    }
}

