#include<bits/stdc++.h>
using namespace std;
int a[30];
char s[105];
int main()
{
    a[1] = 2;
    a[2] = 3;
    a[3] = 5;
    a[4] = 7;
    a[5] = 11;
    a[6] = 13;
    a[7] = 17;
    a[8] = 23;
    a[9] = 31;
    a[10] = 37;
    a[11] = 53;
    a[12] = 71;
    a[13] = 73;
    a[14] = 113;
    a[15] = 131;
    a[16] = 137;
    a[17] = 173;
    a[18] = 311;
    a[19] = 317;
    int T;
    scanf("%d", &T);
    for (int ks = 1; ks <= T; ks++)
    {
        scanf("%s", s);
        char *ss = s;
        while (ss[0] == '0')
            ss++;
        int len = strlen(ss);
        printf("Case #%d: ", ks);
        if (len >= 4)
        {
            printf("317\n");
            continue;
        }
        int ret = 0;
        for (int i = 0; i < len; i++)
        {
            ret = ret * 10 + ss[i] - '0';
        }
        for (int i = 19; i >= 1; i--)
        {
            if (a[i] <= ret)
            {
                printf("%d\n", a[i]);
                break;
            }
        }
    }
    return 0;
}
