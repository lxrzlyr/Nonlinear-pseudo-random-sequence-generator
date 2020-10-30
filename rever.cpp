// rever.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <math.h>
#include <fstream>
using namespace std;


int main()
{
    ifstream in("Densitytable.txt");
    ofstream out("output.txt");
    //ofstream outfile("stud.dat", ios::binary);
    int a0[8], b0[8], c0[16];
    int ai[8], bi[8], ci[16];
    int a1[8], b1[8],a2[8],b2[8],b3[8];
    int s[6],t[5];//t[5]存储10进制转2进制的数（0-31），s[6]存储输入流密码
    int n[20],r[32];//r[32]存储10进制转2进制的数（0-15),n[20]存储输出流密码对应秘钥位
    for (int i = 0; i < 70; i++)//预制密值表
    {
        if (i < 8 )
            in >> a0[i];
        if (i >= 8 && i < 16)
            in >> b0[i - 8];
        if (i >= 16 && i < 32)
            in >> c0[i-16];
        if (i >= 32 && i < 40)
            in >> ai[i - 32];
        if (i >= 40 && i < 48 )
            in >> bi[i - 40];
        if (i >= 48 && i < 64)
            in >> ci[i - 48];
        if (i >= 64)
            in >> s[i - 64];//输入流密码
    }
   
    for (int i = 0; i < 6; i++)
    {
        int z = s[i];
        for (int j = 0; j < 16; j++)
        {
            int m = 0;
            if (z == 0)
                m = c0[j];//十进制转二进制
            else
                m = ci[j];
            for (int k = 4; k >= 0; k--)
            {
                t[k] = m % 2;
                m = m / 2;
            }
            for (int k = 0; k < 5; k++)//取得流密码对应的a和b数组值
            {
                

                int x = t[k];
                if (x == 0)
                {
                    if (k == 0)
                        for (int l = 0; l < 8; l++)
                            a1[l] = a0[l];
                    if (k == 1)
                        for (int l = 0; l < 8; l++)
                            b1[l] = b0[l];
                    if (k == 2)
                        for (int l = 0; l < 8; l++)
                            b2[l] = b0[l];
                    if (k == 3)
                        for (int l = 0; l < 8; l++)
                            a2[l] = a0[l];
                    if (k == 4)
                        for (int l = 0; l < 8; l++)
                            b3[l] = b0[l];
                }
                else
                {
                    if (k == 0)
                        for (int l = 0; l < 8; l++)
                            a1[l] = ai[l];
                    if (k == 1)
                        for (int l = 0; l < 8; l++)
                            b1[l] = bi[l];
                    if (k == 2)
                        for (int l = 0; l < 8; l++)
                            b2[l] = bi[l];
                    if (k == 3)
                        for (int l = 0; l < 8; l++)
                            a2[l] = ai[l];
                    if (k == 4)
                        for (int l = 0; l < 8; l++)
                            b3[l] = bi[l];
                }//获得t[k]对应的数组（十进制）
                for (int i1 = 0; i1 < 8; i1++)
                {
                    int x = a1[i1];
                    for (int k = 0; k<4; k++)
                    {
                        n[3-k] = x % 2;
                        x = x / 2;
                    }//n序列的0-3位填入
                    for (int i2 = 0; i2 < 8; i2++)
                    {
                        int x = b1[i2];
                        for (int k = 0; k < 4; k++)
                        {
                            n[7-k] = x % 2;
                            x = x / 2;
                        }//n序列的4-7位填入
                        for (int i3 = 0; i3 < 8; i3++)
                        {
                            int x = b2[i3];
                            for (int k = 0; k < 4; k++)
                            {
                                n[11-k] = x % 2;
                                x = x / 2;
                            }//n序列的8-11位填入
                            for (int i4 = 0; i4 < 8; i4++)
                            {
                                int x = a2[i4];
                                for (int k = 0; k < 4; k++)
                                {
                                    n[15-k] = x % 2;
                                    x = x / 2;
                                }//n序列的12-15位填入
                                for (int i5 = 0; i5 < 8; i5++)
                                {
                                    int x = b3[i5];
                                    cout << x << endl;
                                    n[19] = 0;
                                    n[18] = 0;
                                    n[17] = 0;
                                    n[16] = 0;
                                    for (int k = 0; k < 4; k++)
                                    {
                                        
                                        n[19-k] = x % 2;
                                        x = x / 2;
                                        cout << n[19 - k] << endl;;
                                    }//n序列16-19位填入
                                    if (i5==2)
                                    cin >> x;
                                    long result = 0;
                                    int e = 1;
                                    for (int i = 0; i < 20; i++)
                                        //outfile.write((char*)&n[i], 20);
                                    { 
                                        result = result + n[19 - i] * e;
                                        e = e * 2;
                                    }
                                    //cout << result << endl;
                                    out << result << endl;                                   
                                }
                            }
                        }
                    }
                    
                }
            }
            cout << "流密码位数" << i << endl;
            cout << "内循环次数" << j << endl;

        }
        
    }
    //outfile.close();
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
