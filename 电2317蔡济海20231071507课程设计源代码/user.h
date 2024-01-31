#pragma once
#ifndef __USER_H
#define __USER_H
#include<graphics.h>

typedef struct {
	char name[20];
	char password[20];
}user;

void registers();
int Input_login();
#endif