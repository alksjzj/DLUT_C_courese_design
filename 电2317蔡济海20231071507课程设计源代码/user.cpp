//本文件主要对用户注册与登录进行封装
#include"user.h"
#include"button.h"
#include<conio.h>
#include<stdio.h>

ExMessage msg;

/*注册账号*/
void registers()  //按结构体的大小，一次写入或者读入1个结构体大小
{
	EndBatchDraw();//使界面可以得到切换
	system("cls");
	IMAGE background;
	loadimage(&background, "background.jpg", 1024, 768);
	putimage(0, 0, &background);
	writetitle("请在控制台进行注册", 150);

	user a;//结构体 The_users 重命名定义
	FILE* fp;
	char temp[20];
	int count = 0;
	printf("欢迎来到注册界面！\n");

	printf("请输入账号:\n");
	scanf_s("%s", &a.name,20);

	printf("请输入密码:\n");
	scanf(" %s", &a.password);
	printf("请确认密码:\n");
	scanf("%s", &temp);
	do {
		if (!strcmp(a.password, temp)) {
			fopen_s(&fp,"users.txt", "a");
			fwrite(&a, sizeof(user), 1, fp);//向文件中写入该结构体
			printf("账号注册成功，请登录！\n");
			fclose(fp);
			return;
		}
		else {
			printf("两次密码不匹配！请重新输入密码:");
			scanf("%s", &a.password);
			printf("请确认密码:");
			scanf("%s", &temp);
		}
	} while (1);
}

/*登录系统*/
int Input_login()
{
	EndBatchDraw();//使界面可以得到切换
	system("cls");
	IMAGE background;
	loadimage(&background, "background.jpg", 1024, 768);
	putimage(0, 0, &background);
	writetitle("请在控制台进行登录", 150);

	user a, b;//定义结构体The_users别名

	FILE* fp;
	printf("欢迎来到登录界面！\n");

	fopen_s(&fp,"users.txt", "r");

	fread(&b, sizeof(user), 1, fp); //读入一个结构体字符块 写入b
	printf("请输入账号:\n");
	scanf_s("%s", &a.name,20);

	while (1)
	{
		if (strcmp(a.name, b.name) == 0)         //如果有此用户名
		{
			break;
		}

		else
		{
			if (!feof(fp))  //如果文件没有读完                            

			{
				fread(&b, sizeof(user), 1, fp);
			}

			else
			{
				printf("此用户名不存在，请重新登录！\n");
				fclose(fp);
				return 0;
			}
		}
	}
	printf("请输入密码:\n");
	scanf_s("%s", &a.password,20);
	do {

		if (strcmp(a.password, b.password) == 0)            /*如果密码匹配*/

		{
			fclose(fp);
			printf("登录成功,欢迎使用!");
			return 1;
		}
		else
		{
			printf("密码不正确!请重新登录\n");
			return 0;
		}
	} while (strcmp(a.password, b.password) == 0);

}
