#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "user.h"
#define CLEAR()               \
    while (getchar() != '\n') \
        ;
//创建头节点
LinkUser *userCreatHead()
{
	LinkUser *p = (LinkUser *)malloc(sizeof(LinkUser));
	if(NULL==p)
	{	
		printf("创建节点失败");
		return NULL;
	}
	memset(p,0,sizeof(LinkUser));
	return p;
}
//创建用户节点
LinkUser *userCreatNode(User user)
{	
	LinkUser *p = (LinkUser *)malloc(sizeof(LinkUser));
	if(NULL==p)
	{	
		printf("创建节点失败");
		return NULL;
	}
	memset(p,0,sizeof(LinkUser));
	p->user = user;
	return p;
}
//尾插入节点
void userInsertTail(LinkUser *headUser,User user)
{
	if (NULL == headUser)
      {
        return ;
      }
	LinkUser *node = userCreatNode(user);
	LinkUser *p = headUser;
	while(p->next != NULL)
	{
		p = p->next;
	}
	p->next = node;
	node->next = NULL;
}
//释放用户链表
void freeUserLink(LinkUser *headUser)
{
	LinkUser *p = NULL;
	LinkUser *q = NULL;
	if (NULL == headUser)
      {
        return ;
      }
	p = headUser->next;
	while(p != NULL)
	{
		q = p;
		p = p->next;
		free(q);	
	}
	free(headUser);
}
//从文件读取用户链表
void userLoadFromFile(const char *path,LinkUser *headUser)
{
	User user = {"\0"};
	FILE *fp = NULL;
	if (NULL == headUser || NULL == path)
      {
        return ;
      }
	fp = fopen(path,"rb");
	if(NULL == fp)
	{
		printf("打开文件失败");
		return;	
	}
	while(fread(&user,sizeof(User),1,fp) > 0)
	{
		userInsertTail(headUser,user);
	}
	if (ferror(fp))
      {
            perror("load file error");
      }
	fclose(fp);
	fp = NULL;
} 
//将链表保存到文件
void userSaveToFile(const char *path,LinkUser *headUser)
{
	FILE *fp = NULL;
	LinkUser *p = NULL;
	if (NULL == headUser || NULL == path)
      {
           return ;
      }
	fp = fopen(path,"wb");
	if(NULL == fp)
	{
		printf("打开文件失败");
		return;	
	}
	while (NULL != p)
      {
            fwrite(&p->user, sizeof(&p->user), 1, fp);
            p = p->next;
      }
	if (ferror(fp))
      {
           printf("load file error");
      }
      fclose(fp);
      fp = NULL;
}
//根据名字查找用户
LinkUser *findUserName(LinkUser *headUser,char *namekey)
{
	LinkUser *p = NULL;
	if (NULL == headUser)
      {
           return NULL;
      }
	p = headUser;
	while(p->next != NULL)
	{
		if(strcmp(p->next->user.name,namekey)==0)
		{
			return p;
		}	
		p = p->next;
	}
	return NULL;
}
//显示用户信息
void display(LinkUser *p)
{
    printf("%s\t%.2f\t%d\n",p->next->user.name, p->next->user.balance,p->next->user.count);
}
//修改密码
void changepasswd(LinkUser *p)
{
    printf("请输入原来密码：");
    char passkey[20] = {"\0"};
    myInputPasswd(passkey);
    if (strcmp(p->next->user.passwd, passkey) == 0)
    {
        printf("请输入新密码：");
        char passnew[20] = {"\0"};
        myInputPasswd(passnew);
        printf("请再次确认新密码：");
        char passnew1[20] = {"\0"};
        myInputPasswd(passnew1);
        if (strcmp(passnew, passnew1) == 0)
        {
            strcpy(p->next->user.passwd, passnew);
            printf("修改完毕！\n");
        }
        else
        {
            printf("密码输入错误！");
        }
    }
    else
    {
        printf("密码输入错误！");
    }
    
}
//充值
void recharge(LinkUser *p)
{
    float addMoney;
    printf("请输入充值金额：");
    scanf("%f", &addMoney);
    CLEAR();
    if(addMoney<0){
        printf("充值金额不能为负！！\n");
        printf("充值失败！！");
    }
    else{
        p->next->user.balance += addMoney ;
        printf("当前余额为：%.2f\n",p->next->user.balance);
        printf("充值完毕\n");
    }
}
//删除节点
void deleteNode(LinkUser *p)
{
    LinkUser *pdel;
    pdel = p->next;
    p->next = pdel->next;
    free(pdel);
}
//添加用户（注册）
void addUser(LinkUser *headUser)
{
	User user = {"\0"};
	char user_name[20];
	printf("请输入用户名：");
        scanf("%s", user_name);
        CLEAR();
	if(findUserName(headUser, user_name) == NULL && strcmp("admin",user_name)!=0 && strcmp("notary",user_name)!=0)
	{
		strcpy(user.name,user_name);
		printf("“%s”您的初始密码：123456\n", user_name);
            	strcpy(user.passwd, "123456");
		user.balance = 0;
		user.count = 0;
		userInsertTail(headUser, user);
		printf("注册成功!\n");
		return;
	}
	else
	{
		printf("用户名不可用，请重新输入！");
		return;
		
	}
}
//根据用户余额排序
void sortBalance(LinkUser *headUser)
{
    LinkUser *p = NULL, *q = NULL;
    User temp = {"\0"};
    if (NULL == headUser || headUser->next == NULL)
    {
        printf("%s %d:head or head->next is NULL\n", __FILE__, __LINE__);
        return;
    }
    p = headUser->next;
    while (NULL != p->next)
    {
        q = p->next;
        while (NULL != q)
        {
            if (p->user.balance < q->user.balance)
            {
                temp = p->user;
                p->user = q->user;
                q->user = temp;
            }
            q = q->next;
        }
        p = p->next;
    }
}
void myInputPasswd(char *passwd)
{
    int i = 0;
    while(i < 20)
    {
        int a = getchar();
        if (a == 10 || a == 13)//判断是否是回车（若为回车则判定密码输入完毕）
        {
            passwd[i] = '\0';
            break;
        }

        else if ((a == 8 || a == 127) && i>0)//判断是否是退格键（若是则删除前一个元素）
        {
            putchar('\b');
            putchar(' ');
            putchar('\b');
            i--;
            passwd[i] = '\0';
        }
        else 
        {
            passwd[i] = (char)a;//输入符合要求
            putchar('*');//屏幕显示为*
            i++;
        }
    }
    printf("\n");
}

