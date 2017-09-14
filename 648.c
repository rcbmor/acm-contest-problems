/* 648 - Stamps (II)
Resumed problem statement:
Input: 2 lines, pairs of positive integer sequences, values of stamps and customer's requests.
Output: "best" combination. max 4 stamps, or "none".
The "best" = maximum number of stamp types.
If tie, fewest total stamps is best.
If still tie, highest single-value is best.
If still tie, print "tie".
*/

#include <stdio.h>

void sort(int *stamps, int stampCnt)
{
	int i = 0, j = 0 ;
	int min = 0 ;
	int tmp = 0 ;

	for(i = 0; i < stampCnt - 1; i++)
	{
		min = i ;
		for(j = i + 1; j < stampCnt; j++)
		{
			if(stamps[j] < stamps[min])
				min = j ;
		}
		
		tmp = stamps[i] ;
		stamps[i] = stamps[min] ;
		stamps[min] = tmp ;
	}
}

void printResult(int total, int *stamps, int stampCnt, int stampType, int tie)
{
	unsigned int i = 0 ;

	if(0 == stampCnt)
	{
		printf("%d ---- none\r\n", total) ;
	}
	else
	{
		printf("%d (%d):", total, stampType) ;
		if(tie)
		{
			printf(" tie\r\n") ;
		}
		else
		{
			sort(stamps, stampCnt) ;
		
			for(i = 0; i < stampCnt; i++)
				printf(" %d", stamps[i]) ;
			printf("\r\n") ;
		}
	}
}

void clac(int total, int *stamps, int stampCnt)
{
	int repeat = 1 ;
	int cnt = 0 ;
	int i = 0, j = 0, k = 0, m = 0 ;
	int result[4] = {0} ;
	int resultCnt = 0 ;
	int tie = 0 ;
	int tmpVal = 0 ;

	while(repeat <= 4)
	{
		for(i = 0; i < stampCnt; i++)
		{
			tmpVal = stamps[i] * repeat ;
			if(tmpVal > total)
				break ;
			
			if(tmpVal == total)
			{
				if(resultCnt > repeat)
					break ;
				if((resultCnt == repeat) && result[repeat-1] == stamps[i])
				{
					tie = 1;
					break ;
				}

				for(cnt = 0; cnt < repeat; cnt++)
					result[cnt] = stamps[i] ;
				resultCnt = cnt ;
				tie = 0 ;

				continue ;
			}

			if(repeat >= 4)
				continue ;

			for(j = (repeat==1)?(i+1):0; j < stampCnt; j++)
			{
				if(j == i)
					continue ;
				
				tmpVal = stamps[i] * repeat + stamps[j] ;
				if(tmpVal > total)
					break ;

				if(tmpVal == total)
				{
					if(resultCnt > repeat + 1)
						break ;
					if(resultCnt == repeat + 1)
					{
						if(result[repeat] == stamps[j])
							tie = 1 ;
						break ;
					}

					for(cnt = 0; cnt < repeat; cnt++)
						result[cnt] = stamps[i] ;
					result[cnt++] = stamps[j] ;
					resultCnt = cnt ;
					tie = 0 ;

					continue ;
				}

				if(repeat >= 3)
					continue ;

				for(k = j + 1; k < stampCnt; k++)
				{
					if(k == i)
						continue ;
					
					tmpVal = stamps[i] * repeat + stamps[j] + stamps[k] ;
					if(tmpVal > total)
						break ;

					if(tmpVal == total)
					{
						if(k < i)
						{
							tie = 1 ;
							break ;
						}
						if(resultCnt > repeat + 2)
							break ;
						if(resultCnt == repeat + 2)
						{
							if(result[repeat+1] == stamps[k])
								tie = 1 ;
							break ;
						}

						for(cnt = 0; cnt < repeat; cnt++)
							result[cnt] = stamps[i] ;
						result[cnt++] = stamps[j] ;
						result[cnt++] = stamps[k] ;
						resultCnt = cnt ;
						tie = 0 ;
						continue ;
					}

					if(repeat >= 2)
						continue ;

					for(m = k+1; m < stampCnt; m++)
					{
						tmpVal = stamps[i] + stamps[j] + stamps[k] + stamps[m];
						if(tmpVal > total)
							break ;

						if(tmpVal == total)
						{
							if(resultCnt == repeat + 3)
							{
								if(result[repeat+2] == stamps[m])
									tie = 1 ;
								break ;
							}

							result[0] = stamps[i] ;
							result[1] = stamps[j] ;
							result[2] = stamps[k] ;
							result[3] = stamps[m] ;
							resultCnt = 4;
							tie = 0 ;
							
							continue ;
						}
					}
				}
			}
		}
	
		if(resultCnt)
		{
			printResult(total, result, resultCnt, resultCnt - repeat + 1, tie) ;
			return ;
		}

		repeat++ ;
	}

	printResult(total, NULL, 0, 0, 0) ;
}

int main(int argc, char *argv[])
{
	int stamps[100] = {0} ;
	int stampCnt = 0 ;
	int total = 0 ;

	while(scanf("%d", &stamps[stampCnt]) != EOF)
	{
		if(stamps[stampCnt] != 0)
		{
			stampCnt++ ;
			continue ;
		}

		sort(stamps, stampCnt) ;

		while(scanf("%d", &total) && total)
		{
			clac(total, stamps, stampCnt) ;
		}

		stampCnt = 0 ;
	}

	return 0 ;
}
