#ifndef __BUTTON_H
#define __BUTTON_H
#include<graphics.h>


//���尴ť����
typedef struct {
	int x;//��ť���Ͻ�����
	int y;//��ť���Ͻ�����
	int width;//��ť�Ŀ��
	int height;//��ť�ĸ߶�
	COLORREF color;  //��ť����ɫ
	char* ptext;	//��ť�ϵ�����
}button;


button* createbutton(int x, int y, int width, int height, COLORREF color, const char* ptext);
void setbutton(button* PB,int i);
int Mouse_in_button(button* PB, ExMessage msg);
int clickButton(button* PB, ExMessage msg);
void writetitle(const char* title, int x);
#endif