/*������Ϸ  2018-6-22 01:37:25*/
/*����һ��ϸ����Χ��3����ϸ���������»غ�һ��Ϊ��ϸ���������Χֻ��������ϸ�����������ֵ�ǰ�Ļ��Բ��䣬������������ǻ����������»غ�Ϊ��ϸ��*/
/*�������õ��Ǵ��ļ��ж�ȡ���ǵĵ�ͼ���޸������*�ţ�*�ű�ʾ��ϸ��������Ϊ��ϸ��   1234567890ֻ��Ϊ�˷����Լ����ͼ��ʱ���ŷ��㣬����Ҫע��궨����M N���ļ���ͼ��Сƥ��Ӵ  ���Գ���������ɵ�ͼ�Զ�����   �����ֶ���������ѧϰ*/
/*ʹ��������ͼ��ͨ����ž����ĸ�Ϊ��ǰ��ͼ���ĸ�Ϊ��һ�غϵĵ�ͼ*/
#include<stdio.h>
#include<windows.h>
#define M 20
#define N 20
//ȫ�ֱ�����
int Map1[M][N] = {0};
int Map2[M][N] = {0};
int thisFlag = 1;

//����������
void ReadMap();//��ȡ��ʼ��ͼ
void Print(int thisMap[M][N]);//��ӡ��ǰ�ĵ�ͼ
void Run();//�������еĺ���
void Calculate(int nowMap[M][N],int lastMap[M][N]);//��RenewMap�������ĵ�ͼ���ݹ�������µĵ�ͼ
void RenewMap();//���ݵ�ͼ��ţ����ü��㺯�������뵱ǰ�ĵ�ͼ�������µ�ǰ�ĵ�ͼ���

int main(void)
{
	Run();
	return 0;
}


void RenewMap()
{
	//������ǰ�ĵ�ͼ����,���μ���ÿ�����ӵĺ�һ��״̬���������µĵ�ͼ
	if(1 == thisFlag)
	{
		Calculate(Map1,Map2);
		thisFlag = 2;
	}
	else
	{
		Calculate(Map2,Map1);
		thisFlag = 1;
	}	
}

void Calculate(int nowMap[M][N],int lastMap[M][N])
{
	int i = 0,j = 0,count = 0;
	for(i = 0;i < M;i++)
	{
		for(j = 0;j < N;j++)
		{
			//��Ϊ��ϸ����1������ֱ�ӽ��Լ���Χ��Ӧ�ĵ�ͼ������Ӿ��ǻ�ϸ������
			count = 0;
			//�оٳ����ֱ߽������������㣬�����������
			//��һ��   ���һ��  ����м�  �ұ��м�  ���м�
			if(0 == i)
			{
				//�ڵ�һ��
				if(0 == j)
				{
					count = nowMap[i][j+1]+nowMap[i+1][j]+nowMap[i+1][j+1];
				}
				else if(j == N-1)
				{
					count = nowMap[i][j-1]+nowMap[i+1][j]+nowMap[i+1][j-1];
				}
				else
				{
					count = nowMap[i][j-1]+nowMap[i+1][j-1]+nowMap[i][j+1]+nowMap[i+1][j]+nowMap[i+1][j+1];
				}
			}
			else if(M-1 == i)
			{
				if(0 == j)
				{
					count = nowMap[i][j+1]+nowMap[i-1][j]+nowMap[i-1][j+1];
				}
				else if(j == N-1)
				{
					count = nowMap[i][j-1]+nowMap[i-1][j]+nowMap[i-1][j-1];
				}
				else
				{
					count = nowMap[i][j-1]+nowMap[i-1][j-1]+nowMap[i][j+1]+nowMap[i-1][j]+nowMap[i-1][j+1];
				}
			}
			else if(0 == j)
				//Ҫע�⣬ǰ���Ѿ�������Ĳ����ڿ��ǣ��������ʱ�򣬿϶��ǿ�����м��
				count = nowMap[i-1][j]+nowMap[i-1][j+1]+nowMap[i][j+1]+nowMap[i+1][j+1]+nowMap[i+1][j];
			else if(N-1 == j)
				count = nowMap[i-1][j]+nowMap[i-1][j-1]+nowMap[i][j-1]+nowMap[i+1][j-1]+nowMap[i+1][j];
			else
				count = nowMap[i-1][j]+nowMap[i-1][j-1]+nowMap[i][j-1]+nowMap[i+1][j-1]+nowMap[i+1][j]+nowMap[i-1][j+1]+nowMap[i][j+1]+nowMap[i+1][j+1];
			//����count�Ľ�����ж��µĵ�ͼ��ϸ��������
			//if(0 != count)
			//	printf("��%d�� ��%d�� %d��\n",i+1,j+1,count);
			if(3 == count)
				lastMap[i][j] = 1;
			else if(2 == count)
				lastMap[i][j] = nowMap[i][j];
			else
				lastMap[i][j] = 0;
		}
	}
}
void Run()
{
	ReadMap();
	Print(Map1);
	while(1)
	{
		switch(getch())
		{
			case 'y':RenewMap();break;
			case 27:return ;
		}
		system("cls");
		if(1 == thisFlag)
			Print(Map2);
		else
			Print(Map1);
	}
	
}
void ReadMap()
{
	FILE *fp = fopen("LifeGameMap.txt","r");
	int i = 0,j = 0;
	char ch = '\0';
	for(i = 0;i < M;i++)
	{
		for(j = 0;j < N;j++)
		{
			fscanf(fp,"%c",&ch);
			if('*' != ch)
			{
				Map1[i][j] = 0;
				Map2[i][j] = 0;
			}
			else
			{//����Ϊ1��������ڼ�����Χ��ϸ��������ֱ���ۼӾ��У�
				Map1[i][j] = 1;
				Map2[i][j] = 1;
			}
		}
		fscanf(fp,"%c",&ch);
	}
}
void Print(int thisMap[M][N])
{
	int i = 0,j = 0;
	for(i = 0;i < M;i++)
	{
		for(j = 0;j < N;j++)
		{
			if(0 == thisMap[i][j])
				printf("��");
			else
				printf("��");
		}
		printf("\n");
	}
	printf("�밴Y(y)����������");
}