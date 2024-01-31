#ifndef __BUTTON_H
#define __BUTTON_H
#include<graphics.h>


//定义按钮变量
typedef struct {
	int x;//按钮左上角坐标
	int y;//按钮右上角坐标
	int width;//按钮的宽度
	int height;//按钮的高度
	COLORREF color;  //按钮的颜色
	char* ptext;	//按钮上的文字
}button;


button* createbutton(int x, int y, int width, int height, COLORREF color, const char* ptext);
void setbutton(button* PB,int i);
int Mouse_in_button(button* PB, ExMessage msg);
int clickButton(button* PB, ExMessage msg);
void writetitle(const char* title, int x);
#endif