#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "notary.h"
void lotteryDraw(Lotterylink *headlottery, IssueLink *headIssue, LinkUser *headUser)//公证员开奖更新彩票发行链表开奖状态 填写中奖号码
{
    IssueLink *I = NULL;
    I = findIssueNew(headIssue);//查找当前发行未开奖的发行彩票链表节点
    if (I == NULL)
    {
        printf("彩票还未发行！！！\n");
        return;
    }
    strcpy(I->next->issue.status, "已开奖");//更新彩票发行链表状态为已开奖
    int arr[8] = {0};
    selectLottoryNumber(arr, 8);//选择开奖方式（机选或手动输入）
    printf("中奖彩票号码：\n\n\t");
    for (int j = 0; j < 8; j++)
    {
        I->next->issue.winningNumbers[j] = *(arr + j);//写入中奖号码
        printf("%d ", *(arr + j));
    }
    printf("\n");
    WinningLottery(headlottery, I, headUser);//更新彩票开奖信息
    system("clear");
    displayIssue(I);//打印开奖的发行彩票链表
}
void cash(Lotterylink *L, IssueLink *I)//兑奖根据中奖号码的个数设定中奖值以及中奖等级
{
    strcpy(L->next->lottery.status, "已开奖");//更新彩票开奖状态
    for (int i = 0; i < 8; i++)
    {
        L->next->lottery.winningNumbers[i] = I->next->issue.winningNumbers[i];//更新彩票中奖号码
    }
    int grade = 0;
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            if (L->next->lottery.lottoryNumber[i] == I->next->issue.winningNumbers[j])//判断购买号码与开奖（前七位）相同的号码的个数
            {
                grade += 10;//若与普通号码相同则加10
            }
        }
    }
    for (int k = 0; k < 7; k++)//判断购买号码是否与开奖（第八位号码）相同
    {
        if (L->next->lottery.lottoryNumber[k] == I->next->issue.winningNumbers[7])
        {
            grade = grade + 1;//与特别号码相同则加1
        }
    }
    if (grade == 31 || grade == 40)//若买中3个普通号码加特别号码或4个普通号码为七等奖
    {
        strcpy(L->next->lottery.winninggrade, "七等奖");//更新彩票中奖等级
        L->next->lottery.bonus = (L->next->lottery.count) * 5;//更新中奖金额（每注5元）
    }
    else if (grade == 41)//若买中4个普通号码加特别号码
    {
        strcpy(L->next->lottery.winninggrade, "六等奖");//更新彩票中奖等级
        L->next->lottery.bonus = (L->next->lottery.count) * 10;//更新中奖金额（每注10元）
    }
    else if (grade == 50)//若买中5个普通号码
    {
        strcpy(L->next->lottery.winninggrade, "五等奖");//更新彩票中奖等级
        L->next->lottery.bonus = (L->next->lottery.count) * 50;//更新中奖金额（每注50元）
    }
    else if (grade == 51)//若买中5个普通号码加特别号码
    {
        strcpy(L->next->lottery.winninggrade, "四等奖");//更新彩票中奖等级
        L->next->lottery.bonus = (L->next->lottery.count) * 200;//更新中奖金额（每注200元）
    }
    else if (grade == 60)//若买中6个普通号码
    {
        strcpy(L->next->lottery.winninggrade, "三等奖");//更新彩票中奖等级
        L->next->lottery.bonus = (L->next->lottery.count) * 400;//更新中奖金额（每注400元）
    }
    else if (grade == 61)//若买中6个普通号码加特别号码
    {
        strcpy(L->next->lottery.winninggrade, "二等奖");//更新彩票中奖等级
        L->next->lottery.bonus = (L->next->lottery.count) * 800;//更新中奖金额（每注800元）
    }
    else if (grade == 70)//若买中7个普通号码
    {
        strcpy(L->next->lottery.winninggrade, "一等奖");//更新彩票中奖等级
        L->next->lottery.bonus = (L->next->lottery.count) * 1600;//更新中奖金额（每注1600元）
    }
    else
    {
        strcpy(L->next->lottery.winninggrade, "未中奖");//更新彩票中奖等级
    }
    L->next->lottery.cash = grade;//更新中奖对应的中奖值
}
void WinningLottery(Lotterylink *headlottery, IssueLink *I, LinkUser *headUser)//更新彩票开奖信息
{
    Lotterylink *L = NULL;
    LinkUser *U = NULL;
    if (NULL == headlottery)
    {
        printf("%s %d:head is NULL\n", __FILE__, __LINE__);
        return;
    }
    L = headlottery;
    while (L->next != NULL)
    {
        if (L->next->lottery.issueNumber == I->next->issue.issueNumber)//判断购买彩票的期号是否是最新开奖期号
        {
            cash(L, I);//兑奖根据中奖号码的个数设定中奖值以及中奖等级
            U = findUserName(headUser, L->next->lottery.name);//判断彩票持有人
            if (U != NULL)
            {
                U->next->user.balance = L->next->lottery.bonus + U->next->user.balance;//更新彩票持有人的余额
                U->next->user.count = 0;//重置用户购买注为0，下期发行可购买5注
            }
            else if (U == NULL)
            {
                printf("%s 的用户已注销，无法将奖金打到该用户账户余额！！！\n", L->next->lottery.name);
            }
        }
        L = L->next;
    }
    return;
}
int winningLotteryCash(Lotterylink *headlottery, int issuenum)//打印中奖彩票
{
    Lotterylink *L = NULL;
    if (NULL == headlottery)
    {
        printf("%s %d:head is NULL\n", __FILE__, __LINE__);
        return 0;
    }
    L = headlottery;
    int i = 0;
    system("clear");
    printf("等级  \t奖金  \t获奖者 \t注数  \t彩票ID \t发行期 \t 彩票号码\n");
    while (L->next != NULL)
    {
        if (L->next->lottery.cash > 30 && L->next->lottery.issueNumber == issuenum)
        {
            displayLotteryCash(L);
            i++;
        }
        L = L->next;
    }
    return i;
}
void winningSortCash(IssueLink *headIssue, Lotterylink *headlottery)//根据发行期号排序打印中将彩票号码
{
    IssueLink *I;
    system("clear");
    printf("请输入所需查询的期号：");
    int issuenum;
    scanf("%d", &issuenum);
    CLEAR();
    I = findIssueIssuenum(headIssue, issuenum);
    if (I == NULL)
    {
        printf("%d是未发行的彩票期号！！\n", issuenum);
        return;
    }
    else
    {
        sortLotteryCash(headlottery, issuenum);//中奖排序
        int i = winningLotteryCash(headlottery, issuenum);//根据发行期号排序打印中将彩票号码
        if (i == 0)
        {
            printf("本期彩票无人中奖！！\n");
        }
        else
        {
            printf("以上是本期彩票%d条中奖信息\n", i);
        }
    }
}
