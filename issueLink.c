#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "issueLink.h"
#define CLEAR()               \
    while (getchar() != '\n') \
        ;
IssueLink *issueCreatHead()//发行彩票链表头节点初始化
{
    IssueLink *p = (IssueLink *)malloc(sizeof(IssueLink));
    if (NULL == p)
    {
        return NULL;
    }
    memset(p, 0, sizeof(IssueLink));
    return p;
}
IssueLink *issueCreatNode(Issue issue)//创建新的发行彩票数据
{
    IssueLink *p = (IssueLink *)malloc(sizeof(IssueLink));
    if (NULL == p)
    {
        return NULL;
    }
    memset(p, 0, sizeof(IssueLink));
    p->issue = issue;
    p->next = NULL;
    return p;
}
void issueInsertTail(IssueLink *headIssue, Issue issue)//将新节点放到链表尾部
{
    IssueLink *p = NULL;
    IssueLink *node = NULL;
    if (NULL == headIssue)
    {
        printf("%s:%d", __FILE__, __LINE__);
        return;
    }
    node = issueCreatNode(issue);
    p = headIssue;
    while (p->next != NULL)
    {
        p = p->next;
    }
    p->next = node;
    node->next = NULL;
}
void addIssue(IssueLink *headIssue)//添加新的发行期号
{
    Issue issue = {0};
    IssueLink *p = NULL;
    p = headIssue;
    int i = 1;
    while (p->next != NULL)
    {
        i++;
        p = p->next;
    }
    if (strcmp(p->issue.status, "未开奖") == 0)
    {
        printf("第%d期彩票还未开奖，不能发行新的彩票！！\n", p->issue.issueNumber);
        return;
    }
    printf("彩票发行期号为：%d\n", 2020000 + i);
    issue.issueNumber = 2020000 + i;
    printf("请输入彩票单价：");
    int price1;
    scanf("%d", &price1);
    CLEAR();
    issue.price = price1;
    strcpy(issue.status, "未开奖");
    for (int i = 0; i < 8; i++)
    {
        issue.winningNumbers[i] = 0;
    }
    issue.countlottery = 0;
    issue.countMoney = 0;
    issueInsertTail(headIssue, issue);
}
void displayAllIssue(IssueLink *headIssue)//打印所有彩票发行期号
{
    IssueLink *p = NULL;
    if (NULL == headIssue)
    {
        printf("%s %d:head is NULL\n", __FILE__, __LINE__);
        return;
    }
    p = headIssue;
    system("clear");
    while (p->next != NULL)
    {
        displayIssue(p);
        p = p->next;
    }
    return;
}
IssueLink *findIssue(IssueLink *headIssue, int num)//根据发行号查找发行彩票
{
    IssueLink *p = NULL;
    if (NULL == headIssue)
    {
        printf("%s %d:head is NULL\n", __FILE__, __LINE__);
        return NULL;
    }
    p = headIssue;
    while (p->next != NULL)
    {
        if (p->next->issue.issueNumber == num)
        {
            return p->next;
        }
        p = p->next;
    }
    return NULL;
}
void freeIssueLink(IssueLink *headIssue)
{
    IssueLink *p = NULL, *q = NULL;
    if (NULL == headIssue)
    {
        printf("%s %d:headis NULL\n", __FILE__, __LINE__);
        return;
    }
    p = headIssue->next;
    while (p != NULL)
    {
        q = p;
        p = p->next;
        free(q);
    }
    free(headIssue);
}
IssueLink *findIssueNew(IssueLink *headIssue)//查找未开奖的发行彩票(新发行的彩票）
{
    IssueLink *p = NULL;
    if (NULL == headIssue)
    {
        printf("%s %d:head is NULL\n", __FILE__, __LINE__);
        return NULL;
    }
    p = headIssue;
    while (p->next != NULL)
    {
        if (strcmp(p->next->issue.status, "未开奖") == 0)
        {
            return p;
        }
        p = p->next;
    }
    return NULL;
}
void displayIssue(IssueLink *I)//格式化打印彩票发行信息
{
    printf("\n----------第%d期----------\n", I->next->issue.issueNumber);
    printf("\t单价:%d\n", I->next->issue.price);
    printf("\t开奖状态：%s\n", I->next->issue.status);
    printf("\t开奖号码为:");
    if (strcmp(I->next->issue.status, "未开奖") == 0)//判断改期彩票是否开奖
    {
        for (int i = 0; i < 8; i++)
        {
            printf("** ");//未开奖中奖号码用** 表示
        }
    }
    else
    {
        for (int i = 0; i < 8; i++)
        {
            printf("%d ", I->next->issue.winningNumbers[i]);//开奖打印开奖号码
        }
    }
    printf("\n\t销售注数：%d注\n", I->next->issue.countlottery);
    printf("\t销售总额：%.2f元\n", I->next->issue.countMoney);
}
void issueLoadFromFile(const char *path, IssueLink *headIssue)//从文件读取彩票发行链表
{
    Issue issue = {0};
    FILE *fp = NULL;
    if (NULL == headIssue  || NULL == path)
    {
        printf("%s %d:head or file path is NULL\n", __FILE__, __LINE__);
        return;
    }
    fp = fopen(path, "rb");
    if (NULL == fp)
    {
        printf("error");
        return;
    }
    while (fread(&issue, sizeof(issue), 1, fp) > 0)
    {
        issueInsertTail(headIssue, issue);
    }
    if (ferror(fp))
    {
		printf("error");
    }
    fclose(fp);
    fp = NULL;
}
void issueSaveToFile(const char *path, IssueLink *headIssue)//将彩票发行链表保存到文件
{
    FILE *fp = NULL;
    IssueLink *p = NULL;
    if (NULL == headIssue || NULL == path)
    {
        printf("%s %d:head or file path is NULL\n", __FILE__, __LINE__);
        return;
    }
    fp = fopen(path, "wb");
    if (NULL == fp)
    {
        printf("error");
        return;
    }
    p = headIssue->next;
    while (NULL != p)
    {
        fwrite(&p->issue, sizeof(p->issue), 1, fp);
        p = p->next;
    }
    if (ferror(fp))
    {
        printf("error");
    }
    fclose(fp);
    fp = NULL;
}
IssueLink *findIssueIssuenum(IssueLink *headIssue,int issuenum)//根据发行期号查找彩票发行链表
{
    IssueLink *p = NULL;
    if (NULL == headIssue)
    {
        printf("%s %d:head is NULL\n", __FILE__, __LINE__);
        return NULL;
    }
    p = headIssue;
    while (p->next != NULL)
    {
        if (p->next->issue.issueNumber==issuenum)
        {
            return p;
        }
        p = p->next;
    }
    return NULL;
}
