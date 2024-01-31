//���ļ���Ҫ�Կɽ�����ť���з�װ����
#include<string.h>
#include"Button.h"
//��ʼ����ť�ĺ��������ص��ǰ�ť��ָ��
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
	//����������в�������һ��ָ��ṹ��ָ�룬��ָ�����̺��Ű�ť��������Ϣ
}

//���ư�ť�ĺ���
void setbutton(button *PB,int i) {
	setfillcolor(PB->color);//���������ɫ
	settextstyle(i, 0, "����");

	setlinecolor(BLACK);//�����߿����ɫ
	settextcolor(BLACK);//�������ֵ���ɫ
	setbkmode(TRANSPARENT);//���ñ�������ɫ
	fillrectangle(PB->x, PB->y, PB->x + PB->width, PB->y + PB->height);//������ť
	outtextxy(PB->x + 50, PB->y + 10,PB->ptext);//���ư�ť�ϵ����֣�ƫ��ֵҪ΢������ʹ���ִ���������
}

//�ж�����Ƿ��ڰ�ť����
int Mouse_in_button(button*PB, ExMessage msg) {
	if (PB->x <= msg.x && PB->x + PB->width >= msg.x && PB->y <= msg.y && msg.y <= PB->y + PB->height) {
		PB->color = YELLOW;
		return 1;
	}
	PB->color = RED;
	return 0;
}

//�ж�����Ƿ�����ť
int clickButton(button* PB, ExMessage msg) {
	if (Mouse_in_button(PB, msg) && msg.message == WM_LBUTTONDOWN)
		return 1;
	return 0;
}

//д�л���ı���
void writetitle(const char* title, int x) {
	settextcolor(WHITE);
	settextstyle(85, 0, "����");
	outtextxy(x, 100, title);
}