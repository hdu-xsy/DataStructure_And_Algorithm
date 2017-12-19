#define LQ(a,b) ((a)<=(b))
#define MAXSIZE
void merge_sort(int a[], int n)
{
	MSort(a, a, 1, n);
}

void Merge(int SR[], int TR[], int i, int m, int n)
{
	int j, k;
	for (j = m + 1, k = i; i <= m&&j <= n; ++k)
	{
		if (LQ(SR[i], SR[j]))
			TR[k] = SR[i++];
		else
			TR[k] = SR[j++];
	}
	while (i <= m)
		TR[k++] = SR[i++];
	while (j <= n)
		TR[k++] = SR[j++];
}

void MSort(int SR[], int TR[], int s, int t)
{
	int m;
	int TR2[MAXSIZE + 1];
	if (s == t)
		TR[s] = SR[s];
	else
	{
		m = (s + t) / 2;
		MSort(SR, TR2, s, m);
		MSort(SR, TR2, m + 1, t);
		Merge(TR2, TR, s, m, t);
	}
}