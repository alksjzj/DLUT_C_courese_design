#include"Button.h"
#include"user.h"
#include"Polyfit/Polyhead.h"
#include"gui.h"
#include"revise.h"
#include"display.h"
int main() {
	//�����������Ϣ�ĳ�ʼ��
	initgraph(1024, 768);
	ExMessage msg;
	IMAGE background;
	loadimage(&background,"background.jpg",1024,768);
	//������������ť�ĳ�ʼ��
	button *signup=createbutton(387, 350, 250, 90, RED, "ע��");
	button *login= createbutton(387, 460, 250, 90, RED, "����");
	button *_exit = createbutton(387, 570, 250, 90, RED, "�˳�");
	//��½��������İ�ť��ʼ��
	button* deal = createbutton(210, 350, 300, 70, RED, "�����ļ�");
	button* revise = createbutton(540, 350, 300, 70, RED, "�޸��ļ�");
	button* display = createbutton(230, 460, 600, 70, RED, "�ļ�����ͳ����Ϣ��ʾ");
	button* _return = createbutton(362 ,570 , 300, 70, RED, "�˳���¼");

	//�ܷ��¼���жϱ�־
	int i = 0;

	while (1) {
		BeginBatchDraw();
		putimage(0, 0, &background);
		setbutton(signup,70);
		setbutton(login,70);
		setbutton(_exit,70);
		writetitle("���ݴ�������Ϣ����ϵͳ", 45);
		//��ȡ�����Ϣ
		getmessage(&msg);
		//�ж�������Ϣ
		if (clickButton(signup, msg))
			registers();
		if (clickButton(login, msg))
			i=Input_login();//�ж��Ƿ��½�ɹ�
		if (clickButton(_exit, msg)) 
			exit(0);
		
		//�����¼�ɹ����������ѭ��
		while (i) {
			getmessage(&msg);
			
			BeginBatchDraw();
			putimage(0, 0, &background);
			writetitle("���ݴ�������Ϣ����ϵͳ", 45);
			//��ʼ���ĸ���ť������ȡ�����Ϣ
			setbutton(deal,50);
			setbutton(revise,50);
			setbutton(display,50);
			setbutton(_return,50);
			getmessage(&msg);

			if (clickButton(deal, msg))
				_deal();
			if (clickButton(revise, msg))
				revisedata();
			if (clickButton(display, msg))
				_display();
			if (clickButton(_return, msg)) {
				i = 0;
				break;
			}
			EndBatchDraw();
		}
		EndBatchDraw();
	}
	closegraph();

	return 0;
}