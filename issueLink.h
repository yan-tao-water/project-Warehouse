#ifndef _ISSUELINK_H
#define _ISSUELINK_H
#define FILEISSUE "issue.txt"
typedef struct issue
{
    int issueNumber;//彩票发行期号
    int price;//彩票单价
    char status[20];//彩票状态
    int winningNumbers[8];//中奖号码
    int countlottery;//销售彩票总数
    float countMoney;//销售总金额
} Issue;
typedef struct issueLink//彩票链表
{
    Issue issue;//彩票数据
    struct issueLink *next;//发行彩票链表下一个节点
} IssueLink;
IssueLink *issueCreatHead();//发行彩票链表头节点初始化
IssueLink *issueCreatNode(Issue issue);//创建新的发行彩票数据
void issueInsertTail(IssueLink *headIssue, Issue issue);//将新节点放到链表尾部
int signAdmin();//管理员登录 
void addIssue(IssueLink *headIssue);//添加新的发行期号
void displayAllIssue(IssueLink *headIssue);//显示所有发行的彩票期号
void freeIssueLink(IssueLink *headIssue);//释放彩票发行链表
IssueLink *findIssueNew(IssueLink *headIssue);//查找彩票发行期号
void displayIssue(IssueLink *I);//显示彩票发行期号
void issueLoadFromFile(const char *path, IssueLink *headIssue);//从文件读取彩票发行链表
void issueSaveToFile(const char *path, IssueLink *headIssue);//把彩票发行链表保存到文件
IssueLink *findIssueIssuenum(IssueLink *headIssue, int issuenum);//根据发行期号查找彩票发行链表
#endif
