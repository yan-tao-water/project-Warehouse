#ifndef _SIGN_H
#define _SIGN_H
#include "user.h"
LinkUser *signUser(LinkUser *headUser, char *namekey);//用户登录
int confirmPassword(char *passkey);//验证登录密码

#endif
