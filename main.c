#include<stdio.h>
#include"control.h"
int main(void)
{
    LinkUser *headUser = userCreatHead();//初始化用户链表头节点
    IssueLink *headIssue=issueCreatHead();//初始化彩票发行期链表头节点
    Lotterylink *headlottery=lotteryCreatHead();//初始化彩票信息链表头节点
    lotteryLoadFromFile(FILELOTTERY,headlottery);//从 ”lottery.txt“ 文件读取彩票链表信息
    issueLoadFromFile(FILEISSUE, headIssue);//从 ”issue.txt“ 文件读取彩票期号链表信息
    userLoadFromFile(FILEUSER , headUser);//从 ”user.txt“文件读取用户链表信息
    conMain(headlottery,headUser,headIssue);//主控制函数
    freeUserLink(headUser);//释放用户链表
    freeIssueLink(headIssue);//释放彩票发行期号链表
    freeLotteryLink(headlottery);//释放彩票链表
	return 0;
}
