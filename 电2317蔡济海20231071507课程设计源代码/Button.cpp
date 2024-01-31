//本文件主要对可交互按钮进行封装处理
#include<string.h>
#include"Button.h"
//初始化按钮的函数，返回的是按钮的指针
button* createbutton(int x, int y, int width, int height, COLORREF color, const char* ptext) {
	button* PB =(button*)malloc(sizeof(button));
	PB->x = x;
	PB->y = y;
	PB->width = width;
	PB->height = height;
	PB->color = color;
	PB->ptext = (char*)malloc(strlen(ptext) + 1);
	strcpy_s(PB->ptext, strlen(ptext) + 1, ptext);
	return PB;
	//将输入的所有参数传入一个指向结构体指针，该指针中蕴含着按钮的所有信息
}

//绘制按钮的函数
void setbutton(button *PB,int i) {
	setfillcolor(PB->color);//设置填充颜色
	settextstyle(i, 0, "楷体");

	setlinecolor(BLACK);//调整边框的颜色
	settextcolor(BLACK);//设置文字的颜色
	setbkmode(TRANSPARENT);//设置背景的颜色
	fillrectangle(PB->x, PB->y, PB->x + PB->width, PB->y + PB->height);//画出按钮
	outtextxy(PB->x + 50, PB->y + 10,PB->ptext);//绘制按钮上的文字，偏差值要微调才能使文字处于正中央
}

//判断鼠标是否在按钮里面
int Mouse_in_button(button*PB, ExMessage msg) {
	if (PB->x <= msg.x && PB->x + PB->width >= msg.x && PB->y <= msg.y && msg.y <= PB->y + PB->height) {
		PB->color = YELLOW;
		return 1;
	}
	PB->color = RED;
	return 0;
}

//判断鼠标是否点击按钮
int clickButton(button* PB, ExMessage msg) {
	if (Mouse_in_button(PB, msg) && msg.message == WM_LBUTTONDOWN)
		return 1;
	return 0;
}

//写切换后的标题
void writetitle(const char* title, int x) {
	settextcolor(WHITE);
	settextstyle(85, 0, "楷体");
	outtextxy(x, 100, title);
}