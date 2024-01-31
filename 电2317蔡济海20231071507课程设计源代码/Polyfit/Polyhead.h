#ifndef __Polyhead_H
#define __Polyhead_H


#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <math.h>
#include <string.h>

typedef struct
{
  char filename[20];//���ݵ�����
  int row;//���ݵ�������Ҳ�Ǳ���x������
  double polyCoeff[10][10];//����ʽ��ϵ��
  double fitError[10];//��ͬ�������µ�������
  int OptiOrder;//�����ϴ���
  double OptiOrder_fitError_mean;//�����ϴ��������ľ���ֵ
  double OptiOrder_fitError_variance;//�����ϴ��������ķ���
  char status;//״̬
}POLYFITINFO;   // ����ṹ��ĳ�Ա���Ը��������������޸ĺ����ӡ�


typedef struct 
{ 
	int x0,y0,x1,y1;  
}PLOTAREA;


extern int COLOR[16];

// ��������

// ����������� �ļ���arrayop.cpp
double arrayscale(double a[], int n);
double arraymin(double a[], int n);
double arraymax(double a[], int n);
void arraycopy(double target[],double source[],int n);
void arraysub(double x[],double y[],double z[],int n);// z=x-y;

// ����ʽ��Ϻ���
void polyfit(int n,double x[],double y[],int poly_n,double p[]);
void gauss_solve(int n,double A[],double x[],double b[]);
void reverseP(double arr[],int size);

// ����ʽ��������
double fx(double x, double coeffs[], int degree);


// ͼ����ʾ  �ļ��� datagraph.cpp
void showhisto(double result[],int n, PLOTAREA area);
void showpinfo(POLYFITINFO pinfo,PLOTAREA farea);
void showdata(double dataX[],double dataY[],int n, long color, PLOTAREA p);

double mean(double a[], int n);//ȡƽ����
double variance(double a[], int n);//�󷽲�ĺ���
#endif