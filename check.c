int check(void)
{
	int check;
	printf("ban co muon tiep tuc\nco:   1\nkhong:0\n");
	do
	{
		scanf("%d",&check);
		getchar();
	}
	while(check!=1 && check!=0);
	return check;
}