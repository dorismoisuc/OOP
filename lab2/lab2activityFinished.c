#include<stdio.h>
#include<string.h>
#include<time.h>

//checks if a year is a leap year
int checkLeap(int year)
{
	if ((year%4)==0 && (year%100)!=0 || (year%400)==0)
	{
		return 1;
	}
	return 0;
}

//verifies how many years since birth were leap years
int check_howmany(int year, int* thedays)
{
	time_t now = time(NULL);
	struct tm* t = localtime(&now);
	int dayT = t->tm_mday;
	int monthT = t->tm_mon + 1;
	int yearT = t->tm_year + 1900;
	while (year <= yearT)
	{
		if (checkLeap(year)==0)
		{
			thedays += 0;
		}
		else
		{
			thedays += 1;
		}
		year += 1; 
	}

	return thedays;
}

//input: year,month,thedays
//output: -1 if the month>2
//		 thedays, if the month <2

int minusOne(int month, int year, int* thedays)
{
	if (checkLeap(year) == 1)
	{
		if (month > 2)
			thedays -= 1; 
	}
	return thedays;
}

//calculating the days that have passed
//until the end of the month

int birthdayMonthPassed(int day, int month, int year, int* thedays)
{
	time_t now = time(NULL);
	struct tm* t = localtime(&now);
	int dayT = t->tm_mday;
	int monthT = t->tm_mon + 1;
	int yearT = t->tm_year + 1900;
	int months[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if (yearT == year && monthT == month)
		thedays += 0;
	else 
		thedays = months[month - 1] - day;
	return thedays;
}

int until_currentDate(int month, int *thedays)
{
	month = month + 1;
	time_t now = time(NULL);
	struct tm* t = localtime(&now);
	int dayT = t->tm_mday;
	int monthT = t->tm_mon + 1;
	int yearT = t->tm_year + 1900;
	int months[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	while (month < monthT)
	{
		thedays += months[month - 1];
		month += 1;
	}
	return thedays;
}

//calculating the total nr of years that the person has
//lived and then transforming it in days

int allYearsLived(int month, int year, int* thedays)
{
	time_t now = time(NULL);
	struct tm* t = localtime(&now);
	int dayT = t->tm_mday;
	int monthT = t->tm_mon + 1;
	int yearT = t->tm_year + 1900;
	int months[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	thedays = (yearT - year) * 365;
	if (yearT != year)
	{
		while (month >= monthT)
		{
			thedays -= months[month - 1];
			month -= 1;
		}
	}
	return thedays;
}

int passedThisMonth(int month, int year, int day, int* thedays)
{
	time_t now = time(NULL);
	struct tm* t = localtime(&now);
	int dayT = t->tm_mday;
	int monthT = t->tm_mon + 1;
	int yearT = t->tm_year + 1900;
	int months[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if (yearT == year && monthT == month)
	{
		thedays = dayT - day + 1;
	}
	else
	{
		thedays += dayT;
	}
	return thedays;

}

void days1(void)
{
	char str[11];
	char year[5], month[3], day[3], delim[] = "-";
	int yearInt, monthInt, dayInt, ok = 0, dayT, monthT, yearT, diffBetYearsinDays;
	char exit[] = "exit";
	time_t now = time(NULL);
	struct tm* t = localtime(&now);
	dayT = t->tm_mday;
	monthT = t->tm_mon + 1;
	yearT = t->tm_year + 1900;
	int nrOfDays=0,thedays=0;
	scanf("%s", str);
	while (strcmp(exit, str) != 0)
	{
		char* p = strtok(str, delim);
		while (p != NULL)
		{
			if (ok == 0)
			{
				strcpy(day, p);
			}
			if (ok == 1)
			{
				strcpy(month, p);
			}
			if (ok == 2)
			{
				strcpy(year, p);
			}
			p = strtok(NULL, delim);
			ok += 1;
		}
		yearInt = atoi(year);
		monthInt = atoi(month);
		dayInt = atoi(day);
		ok = 0;
		nrOfDays = check_howmany(yearInt, thedays);
		nrOfDays += allYearsLived(monthInt, yearInt, thedays);
		nrOfDays += minusOne(monthInt, yearInt, thedays);
		nrOfDays += until_currentDate(monthInt, thedays);
		nrOfDays += passedThisMonth(monthInt, yearInt, dayInt, thedays);
		nrOfDays += birthdayMonthPassed(dayInt, monthInt, yearInt, thedays);
		if (nrOfDays <= 10000)
		{
			printf("%s-%s-%s", day, month, year);
		}
		scanf("%s", str);
	}
}

int GCD(int nr1, int nr2)
{
	while (nr1 != nr2)
	{
		if (nr1 > nr2)
			nr1 -= nr2;
		else
			nr2 -= nr1;
	}
	return nr1;
}

void relativelyPrime(void)
{
	int Number=0;
	scanf("%d", &Number);
	for (int i = 1; i < Number; i++)
	{
		if (GCD(i, Number) == 1)
			printf("Relatively prime to the given Number = %d\n", i);
	}
}

void menu()
{
	int choice;
	do
	{
		printf("Menu\n");
		printf("1. Enter a date and prints those who are <10000 days\n");
		printf("2. Enter a number and prints the numbers which are relatively prime and < number");
		scanf("%d", &choice);

		switch (choice)
		{
		case 1:
			days1();
			break;
		case 2:
			relativelyPrime();
			break;
		case 3:
			printf("Exiting the program!\n");
			exit(0);
			break;
		default:
			printf("Invalid choice!\n");
			break;
		}
	} while (choice != 3);
}

int main(void)
{
	menu();
	return 0;
}

