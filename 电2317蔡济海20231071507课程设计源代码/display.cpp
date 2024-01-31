#include"display.h"
#include"Polyfit/Polyhead.h"

//��ʼ������ϵͳ����
void _display() {
	system("cls");
	IMAGE background;
	loadimage(&background, "background.jpg", 1024, 768);
	ExMessage m3;

	button* search = createbutton(362, 350, 300, 70, RED, "�����ļ�");
	button* watch = createbutton(230, 460, 600, 70, RED, "�鿴�Ѿ���������ļ�");
	button* ___return = createbutton(362, 570, 300, 70, RED, "�����ϼ�");


	//���´����Ǵ���Ѵ������ļ�����Ϣ
	POLYFITINFO watchinfo[10];//�Ѿ�������ļ���������Ϣ

	FILE* result = NULL;//��Ŵ��������ļ�
	fopen_s(&result, "result.txt", "rb");//�򿪴������ļ�
	int j = 0;

	while (!feof(result)) {
		fread(&watchinfo[j], sizeof(POLYFITINFO), 1, result);
		j++;
	}//���ļ��ж����Ѵ�����ļ�����Ϣ������pinfo����ṹ��������
	fclose(result);

	while (1) {
		BeginBatchDraw();
		putimage(0, 0, &background);
		setbutton(search, 50);
		setbutton(watch, 50);
		setbutton(___return, 50);
		writetitle("��Ϣ������ϵͳ", 230);
		
		if (j == 1) {
			settextstyle(40, 0, "����");
			outtextxy(220, 680, "����û�гɹ�������κ������ļ�");
		}
		//��ȡ�����Ϣ
		getmessage(&m3);
		//�ж�������Ϣ
		if (clickButton(search, m3)) {
			system("cls");
			char tempname[20];//����һ�����飬�������ļ���
			settextstyle(40, 0, "����");
			outtextxy(220,300 , "���ڿ���̨������Ҫ���ҵ��ļ���");
			EndBatchDraw();
			printf("����������Ҫ���ҵ��ļ���������չ��):");
			scanf_s("%s", tempname, 20);
			f_search(tempname);
		}
		if (clickButton(watch, m3)) {
			if (j != 1) 
				f_watch(watchinfo,j-1);//j-1�������������ʵ����ֵ
		}
		if (clickButton(___return, m3))
			break;

		EndBatchDraw();
	}
}


void f_watch(POLYFITINFO *info,int j) {
	IMAGE background;
	loadimage(&background, "background.jpg", 1024, 768);
	ExMessage m4; int i;
	POLYFITINFO temp;//��Ϊ����ʱ����м����
	int min;//��������õ���ѡ���������Զ�����Сֵ���±�

	button* sort = createbutton(362, 300, 300, 70, RED, "Ĭ������");
	button* opti_sort = createbutton(230, 390, 600, 70, RED, "�������ϵĴ�С����");
	button* mean_sort = createbutton(230, 480, 600, 70, RED, "����ѵ�����ֵ����");
	button* variance_sort = createbutton(230, 570, 600, 70, RED, "����ѵ���������");
	button* ____return = createbutton(362, 660, 300, 70, RED, "�����ϼ�");

	while (1) {
		BeginBatchDraw();
		putimage(0, 0, &background);
		setbutton(sort, 50);
		setbutton(opti_sort, 50);
		setbutton(mean_sort, 50);
		setbutton(variance_sort, 50);
		setbutton(____return, 50);
		writetitle("ѡ������ķ�ʽ", 230);

		settextstyle(40, 0, "����");
		outtextxy(220, 200, "ѡ������ڿ���̨�ϲ鿴������");
		
		
		//��ȡ�����Ϣ
		getmessage(&m4);
		//�ж�������Ϣ
		if (clickButton(sort, m4)) {
			system("cls");
			printf("�ļ���\t������\t�����ϴ���\t�������ֵ\t�������\n");
			for (i = 0; i < j; i++) {
				printf("%s\t%d\t%d\t\t%.3lf\t\t%.3lf\n", info[i].filename, info[i].row, info[i].OptiOrder, info[i].OptiOrder_fitError_mean, info[i].OptiOrder_fitError_variance);
			}
		}
		if (clickButton(opti_sort, m4)) {
			system("cls");

			for (i = 0; i < j; i++) {
				min = i;
				for (int k = i + 1; k < j; k++) {
					if (info[k].OptiOrder < info[min].OptiOrder)
						min = k;
				}
				temp = info[min]; info[min] = info[i]; info[i] = temp;
			}

			printf("�ļ���\t������\t�����ϴ���\t�������ֵ\t�������\n");
			for (i = 0; i < j; i++) {
				printf("%s\t%d\t%d\t\t%.3lf\t\t%.3lf\n", info[i].filename, info[i].row, info[i].OptiOrder, info[i].OptiOrder_fitError_mean, info[i].OptiOrder_fitError_variance);
			}
		}
		if (clickButton(mean_sort, m4)) {
			system("cls");

			for (i = 0; i < j; i++) {
				min = i;
				for (int k = i + 1; k < j; k++) {
					if (info[k].OptiOrder_fitError_mean < info[min].OptiOrder_fitError_mean)
						min = k;
				}
				temp = info[min]; info[min] = info[i]; info[i] = temp;
			}

			printf("�ļ���\t������\t�����ϴ���\t�������ֵ\t�������\n");
			for (i = 0; i < j; i++) {
				printf("%s\t%d\t%d\t\t%.3lf\t\t%.3lf\n", info[i].filename, info[i].row, info[i].OptiOrder, info[i].OptiOrder_fitError_mean, info[i].OptiOrder_fitError_variance);
			}
		}
		if (clickButton(variance_sort, m4)) {
			system("cls");

			for (i = 0; i < j; i++) {
				min = i;
				for (int k = i + 1; k < j; k++) {
					if (info[k].OptiOrder_fitError_variance < info[min].OptiOrder_fitError_variance)
						min = k;
				}
				temp = info[min]; info[min] = info[i]; info[i] = temp;
			}

			printf("�ļ���\t������\t�����ϴ���\t�������ֵ\t�������\n");
			for (i = 0; i < j; i++) {
				printf("%s\t%d\t%d\t\t%.3lf\t\t%.3lf\n", info[i].filename, info[i].row, info[i].OptiOrder, info[i].OptiOrder_fitError_mean, info[i].OptiOrder_fitError_variance);
			}
		}
		if (clickButton(____return, m4))
			break;

		EndBatchDraw();
	}



}

void f_search(char* filename) {

	FILE* fp = NULL;
	errno_t err=fopen_s(&fp, filename, "r");

	if (err) {
		printf("�ļ�������\n");
		return;
	}//���ļ��ж����Ѵ�����ļ�����Ϣ������pinfo����ṹ��������

	printf("�������ҵ��ļ����ڣ�����û�ж���������ݴ�����Գ��Խ��д���\n");
	fclose(fp);

}