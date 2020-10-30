// Mifare classic.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <math.h>
#include<fstream>
#include <ctime>

using namespace std;
clock_t start，end;

int main()
{
	int fa1,fa2,fb1,fb2,fb3,fc;
	int k[48];
	long x = 0;
	int m = 0;
	clock_t start = clock();
	ifstream in("input.txt");    //使用ifstream创建一个in对象
	for (int i = 0; i < 48; i++)
		in >> k[i];  
	int tap;
	ofstream out("output.txt");
	for (long long j = 0; 1; j++)//2^31
	{
		tap = k[0] ^ k[5] ^ k[9] ^ k[10] ^ k[12] ^ k[14] ^ k[15] ^ k[17] ^ k[19] ^ k[24] ^ k[25] ^ k[27] ^ k[29] ^ k[35] ^ k[39] ^ k[41] ^ k[42] ^ k[43];
		for (int i = 0; i <48; i++)
			k[i] = k[i + 1];
		k[47] = tap;
		fa1 = (k[9] & !k[13] & !k[15]) | ((!k[11]) & k[13] & k[15]) | k[11] & (k[9] & k[13] | !k[9] & !k[13]);
		fb1 = (!k[17] & !k[19] & k[21]) | (k[17] & k[19]) | (k[17] | k[19]) & !k[21] & k[23];
		fb2 = (!k[25] & !k[27] & k[29]) | (k[25] & k[29]) | (k[25] | k[27]) & !k[29] & k[31];
		fa2 = (k[33] & !k[37] & !k[39]) | ((!k[35] & k[37]) & k[39]) | k[35] & (k[33] & k[37] | !k[33] & !k[37]);
		fb3 = (!k[41] & !k[43] & k[45]) | (k[41] & k[43]) | (k[41] | k[43]) & !k[45] & k[47];
		fc = (fa1 | fb1) & fb2 & fa2 | !fa1 & !fa2 & fb3 | fb1 & fa2 & fb3 | fa1 & !fb1 & !fb2 & !fa2 | fa1 & fb1 & !fb2 & !fb3;
		out << fc << endl;
		if (j == 1000000000)
			break;	
	}
	clock_t end = clock();
	double endtime = (double)(end - start) / CLOCKS_PER_SEC;
	cout << "1G次运算时间" << endtime << endl;
	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
//
/*

		
		fa1 = ((k[9] | k[11]) ^ (k[9] & k[15])) ^ (k[13] & ((k[9] ^ k[11]) | k[15]));
		fa2 = ((k[33] | k[35]) ^ (k[33] & k[39])) ^ (k[37] & ((k[33] ^ k[35]) | k[39]));
		fb1 = ((k[17] & k[19]) | k[21]) ^ ((k[17] ^ k[19]) & (k[21] | k[23]));
		fb2 = ((k[25] & k[27]) | k[29]) ^ ((k[25] ^ k[27]) & (k[29] | k[31]));
		fb3 = ((k[41] & k[43]) | k[45]) ^ ((k[41] ^ k[43]) & (k[45] | k[47]));
		fc = (fa1 | ((fb1 | fb3) & (fa2 ^ fb3))) ^ ((fa1 ^ (fb1 & fa2)) & ((fb2 ^ fa2) | (fb1 & fb3)));
*/


/*if (j == 1000000)
		{
			clock_t end = clock();
			double endtime = (double)(end - start) / CLOCKS_PER_SEC;
			cout << "1M次运算时间" << endtime << endl;
		}

		if (j == 5000000)
		{
			clock_t end = clock();
			double endtime = (double)(end - start) / CLOCKS_PER_SEC;
			cout << "5M次运算时间" << endtime << endl;
		}

		if (j == 10000000)
		{
			clock_t end = clock();
			double endtime = (double)(end - start) / CLOCKS_PER_SEC;
			cout << "10M次运算时间" << endtime << endl;
		}

		if (j == 50000000)
		{
			clock_t end = clock();
			double endtime = (double)(end - start) / CLOCKS_PER_SEC;
			cout << "50M次运算时间" << endtime << endl;

		}*/
		/*
				if (j == 1000000000)
				{
					clock_t end = clock();
					double endtime = (double)(end - start) / CLOCKS_PER_SEC;
					cout << "1G次运算时间" << endtime << endl;

				}
				if (j == 5000000000)
				{
					clock_t end = clock();
					double endtime = (double)(end - start) / CLOCKS_PER_SEC;
					cout << "5G次运算时间" << endtime << endl;

				}
				if (j == 10000000000)
				{
					clock_t end = clock();
					double endtime = (double)(end - start) / CLOCKS_PER_SEC;
					cout << "10G次运算时间" << endtime << endl;

				}*/