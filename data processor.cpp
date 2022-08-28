#include "access.h"
using namespace std;
int main()
{
	bool a[8][8] = { 0 };
	bool dp[8] = { 0 };
	int n = 8;
	int b = 100;
	bool tmp = 0;
	bool tmp1 = 0;
	int value = 0;
	bool x[8] = { 1,0,1,0,1,0,1,0 };
	bool y[8] = { 0,1,0,1,0,1,0,1 };
	bool z[8] = { 0 };

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> a[i][j];
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			dp[j] = a[i][j];
		cout << "输入序列" << endl;
		//check(dp, n);
		for (int k = 0; k < b; k++)
		{
			tmp = dp[0];
			for (int j = 0; j < n - 1; j++)
				dp[j] = dp[j] ^ dp[j + 1];
			dp[n - 1] = dp[n - 1] ^ tmp1;
			tmp = dp[0];
			for (int j = 0; j < n - 1; j++)
				dp[j] = dp[j + 1];
			dp[n - 1] = tmp;
			value = 0;
			for (int j = 0; j < n; j++)
			{
				z[j] = x[j] ^ dp[j];
				if (z[j] == 0)
					value++;
			}
			if (value == 8)
			{
				cout << "回归值为" << k << endl;
				for (int j = 0; j < n; j++)
					cout << dp[j] << " ";
				cout << endl;

			}
		}
	}
	return 0;
}