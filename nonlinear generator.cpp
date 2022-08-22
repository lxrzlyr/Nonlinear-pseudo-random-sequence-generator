// nonlinear generator.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "access.h"
using namespace std;

void nonlinear(bool**& dp, vector<bool> & m, vector<bool> &s, int n);
void dataprocessor(bool**& dp, int n, int b);
void synchronizer(bool**& dp, int n, vector<int> b);
void check(bool**& dp, int n);
int main()
{
	bool seed1[32] = { 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1 };
	bool seed2[32] = { 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1 };
	//bool seed1[32] = { 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0 };
	//bool seed2[32] = { 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0 };
	int  seed3[32] = { 10,10,10,100,100,100,100,100, 100,100,100,100,100,100,100,100, 100,100,100,100,100,100,100,100, 100,100,100,100,100,100,100,100 };
	vector<bool> m;
	vector<bool> s;
	vector<int> b;	
	int n = 32;

	bool **dp = new bool * [32];
	for (int i = 0; i < n; i++)
		dp[i] = new bool[32];

	 // cout << "请输入Seed1" << endl;
	for (int i = 0; i < n; i++)
	{
		//cin >> seed1[i];
		m.push_back(seed1[i]);
	}
	//cout << "请输入Seed2" << endl;
	for (int i = 0; i < n; i++)
	{
		//cin >> seed2[i];
		s.push_back(seed2[i]);
	}
	cout << "请输入Seed3" << endl;
	for (int i = 0; i < n; i++)
	{
		//cin >> seed2[i];
		b.push_back(seed3[i]);
	}

	cout << "数据初始化完毕" << endl;
	cout << endl;
	cout << "非线性伪随机序列生成器开始工作" << endl;
	cout << endl;

	for (int i = 0; i < 100; i++)
		nonlinear(dp, m, s, n);

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			cout << dp[i][j] << " ";
		cout << endl;
	}


	cout << "数据处理器开始工作" << endl;
	cout << endl;
	
	dataprocessor(dp, n, 1000);


	return 0;
}

void nonlinear(bool**& dp, vector<bool> &m, vector<bool> &s,int n )
{
	//check(dp, n);
	cout << "当前mLFSR寄存器状态值：" << endl;
	for (int i = 0; i < n; i++)
		cout << m[i] << " ";
	cout << endl;
	cout << "当前SR寄存器状态值：" << endl;
	for (int i = 0; i < n; i++)
		cout << s[i] << " ";
	cout << endl;

	cout << "计算开始。。。。。。。。" << endl;
	vector<bool> a(32);
	bool tmp = 0;
	bool si = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			for (int k = 0; k < n; k++)
			{
				tmp = m[0] ^ m[25] ^ m[27] ^ m[29] ^ m[30] ^ m[31];
				a[k] = tmp;
				m.erase(m.begin());
				m.push_back(tmp);
			}
			for (int k = 0; k < n; k++)
				si = si ^ (s[k] * a[k]);
			s.erase(s.begin());
			s.push_back(si);
			dp[i][j] = si;
		}
	//check(dp, n);
}

void dataprocessor(bool**& dp,int n,int b)
{
	bool tmpc[32] = { 0 };
	bool tmpr[32] = { 0 };
	check(dp, n);
	for (int k = 0; k < b; k++)
	{
		for (int i = 0; i < n; i++)
		{
			tmpc[i] = dp[0][i];
			tmpr[i] = dp[i][0];
		}
		for (int i = 0; i < n - 1; i++)
			for (int j = 0; j < n - 1; j++)
				dp[i][j] = dp[i][j] ^ dp[i + 1][j + 1];
		for (int i = 0; i < n; i++)
		{
			dp[n - 1][i] = tmpc[i];
			dp[i][n - 1] = tmpr[i];
		}
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				dp[i][j] = fmod(dp[i][j] + 1, 2);
	}
	check(dp, n);
}

void synchronizer(bool**& dp, int n, vector<int> b)
{
	check(dp, n);
	bool tmp = 0;

	for (int i = 0; i < n; i++)
	{
		for (int k = 0; k < b[i]; k++)
		{
			tmp = dp[i][0];
			for (int j = 0; j < n - 1; j++)
				dp[i][j] = dp[i][j] ^ dp[i][j + 1];
			dp[i][n - 1] = dp[i][n - 1] ^ tmp;
			tmp = dp[i][0];
			for (int j = 0; j < n - 1; j++)
				dp[i][j] = dp[i][j + 1];
			dp[i][n - 1] = tmp;
			for (int j = 0; j < n; j++)
				dp[i][j] = fmod(dp[i][j] + 1, 2);
		}
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			cout << dp[i][j] << " ";
		cout << endl;
	}



	check(dp, n);

}

void check(bool**& dp, int n)
{
	double g = 0;
	vector<int> e(32);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			e[i] = e[i] + dp[i][j];
	for (int i = 0; i < n; i++)
	{
		
		cout << e[i] << " ";
		if (e[i] < 8 || e[i] >= 24)
			g++;
	}
	cout << endl;
	cout << "偏移序列的比例为" << g*1.0 / 32 << endl;
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
