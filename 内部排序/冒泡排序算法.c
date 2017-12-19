#define LT(a,b) ((a)<(b))
void bubble_sort(int a[], int n)
{
	int i, j;
	int tmp;
	int tag;
	for (i = n; i >= 2; i--)
	{
		tag = FALSE;
		for (j = 1; j <= i - 1; j++)
		{
			if (LT(a[j + 1], a[j]))
			{
				tmp = a[j + 1];
				a[j + 1] = a[j];
				a[j] = tmp;
				tag = TRUE;
			}
		}
		if (!tag)
			break;
	}
}