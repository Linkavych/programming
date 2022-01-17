#include <stdio.h>

int main(void)
{
	int hour, min, comp;

	int time1 = 8 * 60,
			time2 = (9 * 60) + 43,
			time3 = (11 * 60) + 19,
			time4 = (12 * 60) + 47,
			time5 = (14 * 60),
			time6 = (15 * 60) + 45,
			time7 = (19 * 60),
			time8 = (21 * 60) + 45;

	printf("Enter a 24-hour time (hh:mm): ");
	scanf("%d:%d", &hour, &min);

	comp = (hour * 60) + min;
  
	printf("Closest departure time is ");

	if (comp <= time1 + (time2 - time1) / 2 )
		printf("08:00 a.m., arriving at 10:16 a.m.\n");
	else if (comp <= time2 + (time3 - time2) / 2 )
		printf("09:43 a.m., arriving at 11:52 a.m.\n");
	else if (comp <= time3 + (time4 - time3) / 2 )
		printf("11:19 a.m., arriving at 01:31 p.m.\n");
	else if (comp <= time4 + (time5 - time4) / 2 )
		printf("12:47 p.m., arriving at 03:00 p.m.\n");
	else if (comp <= time5 + (time6 - time5) / 2 )
		printf("02:00 p.m., arriving at 04:08 p.m.\n");
	else if (comp <= time6 + (time7 - time6) / 2 )
		printf("03:45 p.m., arriving at 05:55 p.m.\n");
	else if (comp <= time7 + (time8 - time7) / 2 )
		printf("07:00 p.m., arriving at 09:20 p.m.\n");
	else
		printf("09:45 p.m., arriving at 11:58 p.m.\n");

	return 0;
}
