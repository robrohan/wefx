
unsigned int abs(int n)
{
	int mask = n >> 31;
	return ((n + mask) ^ mask);
}
