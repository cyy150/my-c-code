#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<math.h>
#define m 4
#define n 2
//任务：构建m*n矩阵，并且编写得分计算算法(m个对象，n个指标)
void columnprocess(double arr[m][n], double column[m], int J)
{
	double sum = 0;
	for (int i = 0;i < m;i++)
	{
		sum += column[i] * column[i];
	}
	for (int i = 0;i < m;i++)
	{
		column[i] = column[i] / sqrt(sum);
		arr[i][J] = column[i];
	}
}//标准化操作，这是已经正向化后的处理
void dataprocess(double arr[m][n], int TYPE[n])
{
	for (int j = 0;j < n;j++)
	{
		double column[m] = { 0 };
		for (int i = 0;i < m;i++)
		{
			column[i] = arr[i][j];
		}
		switch (TYPE[j])
		{
		case 1:
			columnprocess(arr, column, j);
			break;
		case 2:
		{
			double max = column[0];
			double min = column[0];
			for (int i = 0;i < m;i++)
			{
				if (max < column[i])
					max = column[i];
				if (min > column[i])
					min = column[i];

			}
			for (int i = 0;i < m;i++)
			{
				column[i] = max - column[i];
				arr[i][j] = column[i];
			}
			columnprocess(arr, column, j);
			break;
		}
		case 3:
		{
			printf("现在在处理第%d列数据，输入它的最优值:", (j + 1));
			double best = 0;
			scanf("%lf", &best);
			double far = fabs(column[0] - best);
			for (int i = 0;i < m;i++)
			{
				if (far < fabs(column[i] - best))
					far = fabs(column[i] - best);
			}
			for (int i = 0;i < m;i++)
			{
				column[i] = 1 - fabs(column[i] - best) / (far);
				arr[i][j] = column[i];
			}
			columnprocess(arr, column, j);

			break;
		}
		case 4:
		{
			printf("现在在处理第%d列数据，输入它最优区间[a,b]", (j + 1));
			double a, b;
			scanf("%lf %lf", &a, &b);
			double far = 0;
			for (int i = 0;i < m;i++)
			{
				if (column[i] > b)
				{
					if (column[i] - b > far)
						far = column[i] - b;
				}
				if (column[i] < a)
				{
					if (a - column[i] > far)
						far = a - column[i];
				}
			}
			for (int i = 0;i < m;i++)
			{
				if (column[i] >= a && column[i] <= b)
				{
					column[i] = 1;
					arr[i][j] = column[i];

				}
				else if (column[i] < a)
				{
					column[i] = 1 - (a - column[i]) / far;
					arr[i][j] = column[i];
				}
				else if (column[i] > b)
				{
					column[i] = 1 - (column[i] - b) / far;
					arr[i][j] = column[i];
				}
			}
			columnprocess(arr, column, j);

			break;
		}


		}
	}
}//我们得到了一个所有指标全部正向化和标准化的arr矩阵
double distance(double Z[n], double row[n])
{
	double sum = 0;
	for (int i = 0;i < n;i++)
	{
		sum += (Z[i] - row[i]) * (Z[i] - row[i]);
	}
	double result = sqrt(sum);
	return result;
}
void normalize(double arr[m][n], double score[m])
{
	double Z[n] = { 0 };
	double z[n] = { 0 };
	for (int j = 0;j < n;j++)
	{
		Z[j] = arr[0][j];
		z[j] = arr[0][j];
		for (int i = 0;i < m;i++)
		{
			if (Z[j] < arr[i][j])
				Z[j] = arr[i][j];
			if (z[j] > arr[i][j])
				z[j] = arr[i][j];
		}
	}
	for (int i = 0;i < m;i++)
	{
		double row[n] = { 0 };
		for (int j = 0;j < n;j++)
		{
			row[j] = arr[i][j];
		}
		score[i] = distance(z, row) / (distance(z, row) + distance(Z, row));

	}

}
void scoreprocess(double score[m])
{
	double sum = 0;

	for (int i = 0;i < m;i++)
	{
		sum += score[i];
	}
	for (int i = 0;i < m;i++)
	{
		score[i] = score[i] / sum;
	}
}//得分的归一化

int main()
{
	double arr[m][n] = { 0 };
	int TYPE[n] = { 0 };
	double score[m] = { 0 };
	for (int j = 0;j < n;j++)
	{
		printf("输入数据类型");//极大极小中间区间
		scanf("%d", &TYPE[j]);
		for (int i = 0;i < m;i++)
		{
			scanf("%lf", &arr[i][j]);
		}
	}
	dataprocess(arr, TYPE);
	normalize(arr, score);
	scoreprocess(score);
	for (int i = 0;i < m;i++)
	{
		printf("第%d个对象的得分是：%lf", (i + 1), score[i]);
	}
	return 0;
}