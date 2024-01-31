#include "gui.h"


extern int COLOR[16];

void _deal() {//�����ļ�ͼ�λ�����ĺ���
	system("cls");
	IMAGE background;
	loadimage(&background, "background.jpg", 1024, 768);

	ExMessage m1;
	button* _001 = createbutton(600, 300, 260, 70, RED, "001.txt");
	button* _002 = createbutton(600, 400, 260, 70, RED, "002.txt");
	button* _003 = createbutton(600, 500, 260, 70, RED, "003.txt");
	button* _004 = createbutton(600, 600, 260, 70, RED, "004.txt");
	button* other = createbutton(50, 400, 300, 70, RED, "�����ļ�");
	button* _return1 = createbutton(50, 600, 300, 70, RED, "�����ϼ�");


	while (1) {
		BeginBatchDraw();
		putimage(0, 0, &background);
		getmessage(&m1);
		writetitle("��ѡ��Ҫ������ļ�", 150);

		setbutton(_001, 50);	
		setbutton(_002, 50);
		setbutton(_003, 50);
		setbutton(_004, 50);
		setbutton(other, 50);
		setbutton(_return1, 50);

		//ѡ���жϵ��߼�
		if (clickButton(_001, m1))
			drawing((char*)"001.txt");
		if (clickButton(_002, m1))
			drawing((char*)"002.txt");
		if (clickButton(_003, m1))
			drawing((char*)"003.txt");
		if (clickButton(_004, m1))
			drawing((char*)"004.txt");
		if (clickButton(other, m1)) {
			char tempname[20];//����һ�����飬�������ļ���
			outtextxy(50,490 , "���ڿ���̨�����ļ���");
			EndBatchDraw();
			printf("����������Ҫ������ļ���������չ):");
			scanf_s("%s", tempname, 20);
			drawing(tempname);
		}
		if (clickButton(_return1, m1))
			break;
		EndBatchDraw();
	}
}


//���ݴ�����
void drawing(char *filename) {

	EndBatchDraw();
	BeginBatchDraw();
	initgraph(1024, 768, EX_SHOWCONSOLE);
	FILE* fp = NULL;//����Ҫ�����ļ���ָ��

	//���´����Ǵ���Ѵ������ļ�����Ϣ
	POLYFITINFO pinfo[10];//�Ѿ�������ļ���������Ϣ

	FILE* result=NULL;//��Ŵ��������ļ�
	fopen_s(&result, "result.txt", "rb");//�򿪴������ļ�
	int j = 0,pause=-1;//��λҪ������ļ����ڸýṹ�������еĵڼ���Ԫ��,j��������


	while (!feof(result)) {
		fread(&pinfo[j],sizeof(POLYFITINFO),1,result);
		if (strcmp(filename, pinfo[j].filename) == 0)
			pause=j;//��������ļ��������ٴ���ģ��Ǿͱ���j��ֵ
		j++;
	}//���ļ��ж����Ѵ�����ļ�����Ϣ������pinfo����ṹ��������
	
	if (pause == -1)
		pause = j-1;//���ȷʵ���������ٴ���ģ��Ǿ��½�һ����j��
	fclose(result);

	//���´����ǽ�һ�������ļ���������Ϣ���뵽������
	int i, datacount = 0;//�ֱ������ݵĴ�С�ͼ���
	double datax[N], datay[N], fity[N],_fityerror[N];//�����ҷֱ���x�����ݣ�y�����ݡ���Ϻ��y�����ݺ���Ϻ���������
	double fiterror;		// ĳһ�������µ�������
	int order; // ����ʽ�Ľ״�

	PLOTAREA  parea = { 200,400,824,700 }; // ֱ��ͼ��ʾ����
	PLOTAREA  farea = { 10,600,80,700 };   // ������ʾ���� 
	PLOTAREA dataarea = { 50,10,950,300 }; // ����������ʾ����
	
	errno_t err = fopen_s(&fp, filename, "r+");	

	if (err) {
		printf("��������ļ�������");
		return;
	}

	for (i = 0; i < N; i++)
	{
		fscanf(fp, "%lf %lf", &datax[i], &datay[i]);
		if (feof(fp) != 0) // ����Ѿ������ļ�ĩβ��ֹͣ���ļ���
			break;
	}

	datacount = i; // ���ݵ�������
	fclose(fp);

	//���ļ����������洢����
	strcpy(pinfo[pause].filename, filename);
	pinfo[pause].row = datacount;

	settextcolor(WHITE);
	settextstyle(30, 0, "����");
	outtextxy(300, 10, "���ڿ���̨ѡ��Ҫ����Ĳ���");

	// ������С����ȷ������ʽ��ϵ�ϵ��
	for (order = 1; order <= 9; order++)
	{
		polyfit(datacount, datax, datay, order, pinfo[pause].polyCoeff[order]);
	}
	EndBatchDraw();
	
	// ���㲢��¼�����
	for (order = 1; order <= 9; order++)
	{
		fiterror = 0;
		for (i = 0; i < datacount; i++)
		{
			fity[i] = fx(datax[i], pinfo[pause].polyCoeff[order], order);
			fiterror += (fity[i] - datay[i]) * (fity[i] - datay[i]);
		}
		pinfo[pause].fitError[order] = fiterror;
	}

	pinfo[pause].OptiOrder = 0;//�Ƚ������ϴ�������0����Ϊ֮���Ƿ���д���ı�׼

	//ѡ�����
	system("cls");
	int option=0;
	printf("***************ͼ�λ����ݴ������***************\n");
	printf("*****�����ڴ���%s�ļ�\n", filename);
	printf("*****��Ҫ������Ѷ���ʽ����Ͻ����ſ���������\n");
	printf("*****1����ʾԭʼ����\n");
	printf("*****2����ʾĳһ��������ݵ�ͼ��С�ڵ���9��\n");
	printf("*****3����ʾ������ϵ����ݵ�ͼ��\n");
	printf("*****4����ʾ�������ֱ��ͼ\n");
	printf("*****5��������Ѷ���ʽ����Ͻ���\n");
	printf("*****6��������������е�ͼ��\n");
	printf("*****7�����������\n");
	printf("*****������ѡ��1-7:");
	scanf_s("%d", &option);

	while (option != 7) {
		while (!(option <= 8 && option >= 1)) {
			printf("*****����ѡ����������������:");
			scanf_s("%d", &option);
		}
		//���ѡ��Ϊ8��û�н��й�������Ҫ��������
		while (option == 8 && pinfo[pause].OptiOrder == 0) {
			printf("*****����ѡ����������������:");
			scanf_s("%d", &option);
		}

		switch (option) {
		case 1:showdata(datax, datay, datacount, RED, dataarea); break;//����ԭʼ��ͼ��		
		//��ʾָ��������ݵ�ͼ��
		case 2:
			printf("��������Ҫ�鿴����Ͻ���(1-9):");
			scanf_s("%d", &order);
			for (i = 0; i < datacount; i++)
			{
				fity[i] = fx(datax[i], pinfo[pause].polyCoeff[order], order);
			}
			showdata(datax, fity, datacount, COLOR[order], dataarea);
			break;
		//��ʾ����������ݵ�ͼ��
		case 3:
			for (order = 1; order <= 9; order++)
			{
				for (i = 0; i < datacount; i++)
				{
					fity[i] = fx(datax[i], pinfo[pause].polyCoeff[order], order);
				}
				showdata(datax, fity, datacount, COLOR[order], dataarea);
			}
			break;

		case 4:
			showhisto(pinfo[pause].fitError, 9, parea); break; // ��parea ��ʾֱ��ͼ
		case 5:
			// ������ѵĶ���ʽ��Ͻ״Ρ�
			printf("��������ѵĶ���ʽ��Ͻ״Σ���1-9��");
			rewind(stdin);
			scanf_s("%d", &pinfo[pause].OptiOrder);

			//�����ڸ���Ͻ״��£����ľ�ֵ�ͷ���
			for (i = 0; i < datacount; i++) {
				fity[i] = fx(datax[i], pinfo[pause].polyCoeff[pinfo[pause].OptiOrder], pinfo[pause].OptiOrder);
				_fityerror[i] = fity[i] - datay[i];
			}

			pinfo[pause].OptiOrder_fitError_mean = mean(_fityerror, datacount);
			pinfo[pause].OptiOrder_fitError_variance = variance(_fityerror, datacount);

			printf("�����Ͻ״ε������ͳ����ϣ���������ѡ��8�鿴���ͼ��\n�鿴ͼ��ǰ�������������ͼ��\n");
			break;
		case 6:
			initgraph(1024, 768, EX_SHOWCONSOLE);
			settextcolor(WHITE);
			settextstyle(30, 0, "����");
			outtextxy(300, 10, "���ڿ���̨ѡ��Ҫ����Ĳ���");
			break;
		//��������ϴ���������ͼ��
		case 8:
			showdata(datax, _fityerror, datacount, WHITE, dataarea);
			break;
		}

		printf("��ѡ����һ������ִ��:");
		scanf_s("%d", &option);
	}

	//�ж��Ƿ��н��й�����
	if (pinfo[pause].OptiOrder != 0) {
		showpinfo(pinfo[pause], farea);
		pinfo[pause].status = 'Y';

		fopen_s(&result, "result.txt", "wb");//�򿪴������ļ�
		if(pause==j-1)//˵�����½���
			fwrite(&pinfo, sizeof(POLYFITINFO), j, result);
		else
			fwrite(&pinfo, sizeof(POLYFITINFO), j-1, result);
		fclose(result);
	}

	else{
		printf("����δ�ɹ��������ݴ����������½���");
		pinfo[pause].status = 'N';
	}
	printf("\nʹ�ûس�������");
	rewind(stdin);
	getchar();					// ���ش���
}
