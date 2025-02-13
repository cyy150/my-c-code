#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define maxintergration 1000//最大迭代次数
#define percision 0.000001
#define size 3//定义矩阵规模
typedef struct vector
{
	double data[size];
}vector;//定义向量结构体
//任务：编写矩阵运算，向量运算等函数，实现AK+1=QTAKQ迭代计算，最终实现求特征值
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
}//创建了一个求向量乘法函数，返回求得的值
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
void getvectorj(double a[size][size], int j, vector* b)//取第j行的列向量函数
{

	for (int k = 0;k < size;k++)
	{
		b->data[k] = a[k][j];
	}

}//取出来的b是一个转置的列向量
void vectorminus(double a[size], double b[size], double c[size])
{

	for (int i = 0;i < size;i++)
		c[i] = a[i] - b[i];

}//向量减法
void vec_multiply(double a[size], double k, double c[size])
{
	for (int i = 0;i < size;i++)
	{
		c[i] = k * a[i];
	}
}//数乘

void vectorplus(double a[size], double b[size], double c[size])
{
	for (int i = 0;i < size;i++)
		c[i] = a[i] + b[i];
}
void supervetorminus(double A[size][size], double q[size][size])
{
	vector* a = (vector*)malloc(sizeof(vector) * size);//存放β
	vector* b = (vector*)malloc(sizeof(vector) * size);//存放α
	for (int j = 0;j < size;j++)
	{
		getvectorj(A, j, &b[j]);//得到α
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

}//返回正向化矩阵q
void getQ(double A[size][size], double Q[size][size])//Q用于接受正交矩阵
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
}//check函数用于检查是否满足上三角条件



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
	double maxvalue = A[0][0];//最大特征值
	for (int i = 1;i < size;i++)
	{
		if (maxvalue < A[i][i])
			maxvalue = A[i][i];
	}
	double CI = (maxvalue - size) / (size - 1);
	double RI;//0,0,0.52,0.89,1.12
	printf("输入RI");
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
		printf("第%d个特征值为:%lf ", (i + 1), A[i][i]);

	}
	printf("\n迭代次数为：%d", intergration);

}



