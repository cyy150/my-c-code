#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define maxintergration 1000//����������
#define percision 0.000001
#define size 3//��������ģ
typedef struct vector
{
	double data[size];
}vector;//���������ṹ��
//���񣺱�д�������㣬��������Ⱥ�����ʵ��AK+1=QTAKQ�������㣬����ʵ��������ֵ
void matrixtranspos(double Q[size][size], double QT[size][size])
{
	for (int i = 0;i < size;i++)
	{
		for (int j = 0;j < size;j++)
		{
			QT[j][i] = Q[i][j];
		}
	}
}
double vector_multiply(double* a, double* b)
{
	double result = 0;
	for (int i = 0;i < size;i++)
	{
		result += a[i] * b[i];
	}
	return result;
}//������һ���������˷�������������õ�ֵ
void matrix_multiply(double a[size][size], double b[size][size], double c[size][size])
{
	double d[size][size] = { 0 };
	for (int i = 0;i < size;i++)
	{
		for (int j = 0;j < size;j++)
		{
			double sum = 0;
			for (int k = 0;k < size;k++)
			{
				sum += a[i][k] * b[k][j];
			}
			d[i][j] = sum;
		}
	}
	for (int i = 0;i < size;i++)
	{
		for (int j = 0;j < size;j++)
		{
			c[i][j] = d[i][j];
		}
	}
}
void getvectorj(double a[size][size], int j, vector* b)//ȡ��j�е�����������
{

	for (int k = 0;k < size;k++)
	{
		b->data[k] = a[k][j];
	}

}//ȡ������b��һ��ת�õ�������
void vectorminus(double a[size], double b[size], double c[size])
{

	for (int i = 0;i < size;i++)
		c[i] = a[i] - b[i];

}//��������
void vec_multiply(double a[size], double k, double c[size])
{
	for (int i = 0;i < size;i++)
	{
		c[i] = k * a[i];
	}
}//����

void vectorplus(double a[size], double b[size], double c[size])
{
	for (int i = 0;i < size;i++)
		c[i] = a[i] + b[i];
}
void supervetorminus(double A[size][size], double q[size][size])
{
	vector* a = (vector*)malloc(sizeof(vector) * size);//��Ŧ�
	vector* b = (vector*)malloc(sizeof(vector) * size);//��Ŧ�
	for (int j = 0;j < size;j++)
	{
		getvectorj(A, j, &b[j]);//�õ���
	}
	for (int j = 0;j < size;j++)
	{
		if (j == 0)
		{
			getvectorj(A, j, &a[j]);
		}
		else
		{
			double d[size] = { 0 };
			for (int k = 0;k < j;k++)
			{
				double c[size];
				vec_multiply(a[k].data, (vector_multiply(b[j].data, a[k].data) / vector_multiply(a[k].data, a[k].data)), c);
				vectorplus(d, c, d);
			}
			vectorminus(b[j].data, d, a[j].data);
		}
	}
	for (int i = 0;i < size;i++)
	{
		for (int j = 0;j < size;j++)
		{
			q[i][j] = 0;
		}
	}
	for (int j = 0;j < size;j++)
	{
		for (int i = 0;i < size;i++)
		{
			q[i][j] = a[j].data[i];
		}
	}
	free(b);
	free(a);

}//�������򻯾���q
void getQ(double A[size][size], double Q[size][size])//Q���ڽ�����������
{
	supervetorminus(A, Q);
	for (int j = 0;j < size;j++)
	{
		double sum = 0;
		for (int i = 0;i < size;i++)
		{
			sum += Q[i][j] * Q[i][j];
		}
		sum = sqrt(sum);
		for (int i = 0;i < size;i++)
		{
			Q[i][j] /= sum;
		}
	}
}
int check(double A[size][size])
{
	for (int i = 0;i < size;i++)
		for (int j = 0;j < size;j++)
		{
			if (i != j && fabs(A[i][j]) > percision)
				return 0;
		}
	return 1;
}//check�������ڼ���Ƿ���������������



int main()
{
	double A[size][size] = { {1,2,0},{0,2,0},{-1,0,3} };
	double Q[size][size] = { 0 };
	double QT[size][size] = { 0 };
	getQ(A, Q);
	matrixtranspos(Q, QT);
	int intergration = 0;
	while (check(A) == 0 && intergration < maxintergration)
	{
		matrix_multiply(A, Q, A);
		matrix_multiply(QT, A, A);
		getQ(A, Q);
		matrixtranspos(Q, QT);
		intergration++;
	}
	double maxvalue = A[0][0];//�������ֵ
	for (int i = 1;i < size;i++)
	{
		if (maxvalue < A[i][i])
			maxvalue = A[i][i];
	}
	double CI = (maxvalue - size) / (size - 1);
	double RI;//0,0,0.52,0.89,1.12
	printf("����RI");
	scanf("%lf", &RI);
	double CR;
	CR = CI / RI;
	if (CR >= 0.1)
	{
		printf("CR=%lf", CR);
		return 0;
	}
	for (int i = 0;i < size;i++)
	{
		printf("��%d������ֵΪ:%lf ", (i + 1), A[i][i]);

	}
	printf("\n��������Ϊ��%d", intergration);

}



