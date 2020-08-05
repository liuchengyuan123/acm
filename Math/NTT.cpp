const ll mod = 998244353;
const ll g = 3;
ll Pow(ll a, ll b)
{
	ll ans = 1;
	while (b)
	{
		if (b & 1)
			ans = ans * a % mod;
		a = a * a % mod;
		b >>= 1;
	}
	return ans;
}

void change(ll y[],int len)
{
    for(int i = 1, j = len / 2; i < len - 1; i++)
    {
        if (i < j)
			swap(y[i], y[j]);
        int k = len / 2;
        while (j >= k)
        {
            j -= k;
            k /= 2;
        }
        if (j < k)
	    j += k;
    }
}
void ntt(ll y[], int len, int on)
{
    change(y, len);
    for(int h = 2; h <= len; h <<= 1)
    {
        ll wn = Pow(g, (mod-1) / h);
        if(on == -1)
			wn = Pow(wn, mod-2);
        for(int j = 0; j < len; j += h)
        {
            ll w = 1LL;
            for (int k = j; k < j + h / 2; k++)
            {
                ll u = y[k];
                ll t = w * y[k + h / 2] % mod;
                y[k] = (u + t) % mod;
                y[k + h / 2] = (u - t + mod) % mod;
                w = w * wn % mod;
            }
        }
    }
    if (on == -1)
    {
        ll t = Pow(len, mod-2);
        for(int i = 0; i < len; i++)
            y[i] = y[i] * t % mod;
    }
}
