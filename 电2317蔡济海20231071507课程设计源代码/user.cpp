//���ļ���Ҫ���û�ע�����¼���з�װ
#include"user.h"
#include"button.h"
#include<conio.h>
#include<stdio.h>

ExMessage msg;

/*ע���˺�*/
void registers()  //���ṹ��Ĵ�С��һ��д����߶���1���ṹ���С
{
	EndBatchDraw();//ʹ������Եõ��л�
	system("cls");
	IMAGE background;
	loadimage(&background, "background.jpg", 1024, 768);
	putimage(0, 0, &background);
	writetitle("���ڿ���̨����ע��", 150);

	user a;//�ṹ�� The_users ����������
	FILE* fp;
	char temp[20];
	int count = 0;
	printf("��ӭ����ע����棡\n");

	printf("�������˺�:\n");
	scanf_s("%s", &a.name,20);

	printf("����������:\n");
	scanf(" %s", &a.password);
	printf("��ȷ������:\n");
	scanf("%s", &temp);
	do {
		if (!strcmp(a.password, temp)) {
			fopen_s(&fp,"users.txt", "a");
			fwrite(&a, sizeof(user), 1, fp);//���ļ���д��ýṹ��
			printf("�˺�ע��ɹ������¼��\n");
			fclose(fp);
			return;
		}
		else {
			printf("�������벻ƥ�䣡��������������:");
			scanf("%s", &a.password);
			printf("��ȷ������:");
			scanf("%s", &temp);
		}
	} while (1);
}

/*��¼ϵͳ*/
int Input_login()
{
	EndBatchDraw();//ʹ������Եõ��л�
	system("cls");
	IMAGE background;
	loadimage(&background, "background.jpg", 1024, 768);
	putimage(0, 0, &background);
	writetitle("���ڿ���̨���е�¼", 150);

	user a, b;//����ṹ��The_users����

	FILE* fp;
	printf("��ӭ������¼���棡\n");

	fopen_s(&fp,"users.txt", "r");

	fread(&b, sizeof(user), 1, fp); //����һ���ṹ���ַ��� д��b
	printf("�������˺�:\n");
	scanf_s("%s", &a.name,20);

	while (1)
	{
		if (strcmp(a.name, b.name) == 0)         //����д��û���
		{
			break;
		}

		else
		{
			if (!feof(fp))  //����ļ�û�ж���                            

			{
				fread(&b, sizeof(user), 1, fp);
			}

			else
			{
				printf("���û��������ڣ������µ�¼��\n");
				fclose(fp);
				return 0;
			}
		}
	}
	printf("����������:\n");
	scanf_s("%s", &a.password,20);
	do {

		if (strcmp(a.password, b.password) == 0)            /*�������ƥ��*/

		{
			fclose(fp);
			printf("��¼�ɹ�,��ӭʹ��!");
			return 1;
		}
		else
		{
			printf("���벻��ȷ!�����µ�¼\n");
			return 0;
		}
	} while (strcmp(a.password, b.password) == 0);

}
