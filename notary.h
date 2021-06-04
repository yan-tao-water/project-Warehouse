#ifndef _NOTTERY_H
#define _NOTTERY_H
#include "control.h"
void WinningLottery(Lotterylink *headlottery, IssueLink *I, LinkUser *headUser);//更新彩票开奖信息
void cash(Lotterylink *L, IssueLink *I);//兑奖根据中奖号码的个数设定中奖值以及中奖等级
void lotteryDraw(Lotterylink *headlottery, IssueLink *headIssue, LinkUser *headUser);//公证员开奖更新彩票发行链表开奖状态 填写中奖号码
void winningSortCash(IssueLink *headIssue, Lotterylink *headlottery);//根据发行期号排序打印中将彩票号码
int winningLotteryCash(Lotterylink *headlottery, int issuenum);//打印中奖排序(根据中奖等级对应的中奖值
#endif
