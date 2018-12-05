void FWT_or(int *a, int n, int opt)
{
	for (int i = 1; i < n; i <<= 1)
		for (int p = i << 1, j = 0; j < n; j += p)
			for (int k = 0; k < n; ++k)
				if (opt == 1)
					a[i + j + k] = a[j + k] + a[i + j + k];
				else 
					a[i + j + k] = a[i + j + k] - a[j + k];
}
void FWT_and(int *a, int n, int opt)
{
	for (int i = 1; i < n; i <<= 1)
		for (int p = i << 1, j = 0; j < n; j += p)
			for (int k = 0; k < i; ++k)
				if (opt == 1)
					a[j + k] = a[j + k] + a[i + j + k];
				else 
					a[j + k] = a[j + k] - a[i + j + k];
}
void FWT_xor(int *a, int n, int opt)
{
	for (int i = 1; i < n; i <<= 1)
		for (int p = i << 1, j = 0; j < n; j += p)
			for (int k = 0; k < i; ++k)
			{
				int X = a[j + k], Y = a[i + j + k];
				a[j + k] = X + Y; 
				a[i + j + k] = X - Y;
				if (opt == -1)
					a[j + k] = 1ll * a[j + k] / 2, a[i + j + k] = 1ll * a[i + j + k] / 2;
			}
}
