#include"revise.h"
FILE* revisep;


void revisedata()//�����ļ�������
{
	IMAGE background;
	loadimage(&background, "background.jpg", 1024, 768);

	//�����������Ͱ�ť����
	ExMessage m2;
	button* createfile = createbutton(210, 350, 300, 70, RED, "�����ļ�");
	button* createdata = createbutton(540, 350, 300, 70, RED, "��������");
	button* modifydata = createbutton(362, 460, 300, 70, RED, "�޸�����");
	button* _return2 = createbutton(362, 570, 300, 70, RED, "���ز˵�");

	while (1) {
		BeginBatchDraw();
		putimage(0, 0, &background);
		getmessage(&m2);
		writetitle("��ѡ��Ҫ�����ѡ��", 150);

		setbutton(createfile, 50);
		setbutton(createdata, 50);
		setbutton(modifydata, 50);
		setbutton(_return2, 50);
		outtextxy(170, 670, "ѡ������ڿ���̨������ʾ����");
		//ѡ���жϵ��߼�
		if (clickButton(createfile, m2))
			create();
		if (clickButton(createdata, m2))
			created();
		if (clickButton(modifydata, m2))
			modify();
		if (clickButton(_return2, m2))
			break;
		EndBatchDraw();
	}
}

void create() {
	system("cls");
	FILE* fileP=NULL;
	char fileName[30];     

	printf("��������Ҫ�����ļ������֣�����չ������");
	scanf_s("%s", fileName, 30);
	//ʹ�á����롱��ʽ���ļ�
	errno_t err = fopen_s(&fileP, fileName, "r");
	if (err) {
		//����޷��򿪣�����á�д�롱�ķ�ʽ���ļ�
		fopen_s(&fileP, fileName, "w");
		printf("�ļ��Ѵ����ɹ�");
	}
	else
		printf("�ļ��Ѵ���");
	fclose(fileP);
}

void created() {
	system("cls");
	FILE* fileP;
	char fileName[30];
	printf("��������Ҫ׷�����ݵ��ļ������֣�����չ����:");
	scanf_s("%s", fileName, 20);
	//ʹ�á����롱��ʽ���ļ�
	errno_t err = fopen_s(&fileP, fileName, "r");

	while (err) {
		//����޷��򿪣������������ļ�������
		printf("�ļ���ʧ�ܣ�����������:");
		scanf_s("%s", fileName, 20);
		err = fopen_s(&fileP, fileName, "r");
	}

	//�������ȶ��ļ������е����ݽ��ж���
	int i,datacount;//����iΪ����
	double datax[N], datay[N];

	for (i = 0; i < N; i++)
	{
		fscanf(fileP, "%lf %lf", &datax[i], &datay[i]);
		if (feof(fileP) != 0) // ����Ѿ������ļ�ĩβ��ֹͣ���ļ���
			break;
	}//��ʱi��ֵ����data������
	fclose(fileP);//�ر��ļ�
	
	datacount = i + 1;//׷�Ӻ�����ݸ���Ϊdatacount���������������ѭ��

	printf("�ļ��򿪳ɹ���������׷�ӵ����ݣ������ո�ָ��Ա����������:\n");
	scanf_s("%lf %lf", &datax[i], &datay[i]);

	fopen_s(&fileP, fileName, "w");
	
	for (i = 0; i < datacount; i++)
	{
		fprintf(fileP,"%lf %lf\n", datax[i], datay[i]);
	}

	printf("����׷�ӳɹ�,�뷵�ش���");
	fclose(fileP);
}



void modify() {
	system("cls");
	FILE* fileP;
	char fileName[30];
	printf("��������Ҫ�������ݵ��ļ������֣�����׺��:");
	scanf_s("%s", fileName, 20);
	//ʹ�á����롱��ʽ���ļ�
	errno_t err = fopen_s(&fileP, fileName, "r");

	while (err) {
		//����޷��򿪣������������ļ�������
		printf("�ļ���ʧ�ܣ�����������:");
		scanf_s("%s", fileName, 20);
		err = fopen_s(&fileP, fileName, "r");
	}

	//�������ȶ��ļ������е����ݽ��ж���
	int i,datacount;
	double datax[N], datay[N],modify_x, modify_y;//modify_x��modify_y��ͨ����λҪ�޸ĵ�x��y������

	for (i = 0; i < N; i++)
	{
		fscanf(fileP, "%lf %lf", &datax[i], &datay[i]);
		if (feof(fileP) != 0) // ����Ѿ������ļ�ĩβ��ֹͣ���ļ���
			break;
	}//��ʱi��ֵ����data������

	datacount = i;
	fclose(fileP);


	printf("�ļ��򿪳ɹ���������Ҫ���ĵ����ݣ������ո�ָ��Ա����������:\n");
	scanf_s("%lf %lf", &modify_x, &modify_y);
	for (i = 0; i < datacount; i++)
		if (datax[i]==modify_x&&datay[i]==modify_y)
			break;
	if (i == datacount)
	{
		printf("û����һ�����ݣ��������ڴ���ѡ�����");
		return;
	}

	fopen_s(&fileP, fileName, "w");

	printf("���ҵ���Ҫ���ĵ����ݣ��������滻�����ݣ������ո�ָ��Ա����������:\n");
	scanf_s("%lf %lf", &modify_x, &modify_y);
	datax[i] = modify_x; datay[i] = modify_y;//��������¸�ֵ

	for (i = 0; i < datacount; i++)
	{
		fprintf(fileP, "%lf %lf\n", datax[i], datay[i]);//����д��
	}

	printf("���ݸ��ĳɹ�,�뷵�ش���");
	fclose(fileP);
}



