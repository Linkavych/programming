/*
 * Design a struct which will have the following members: last name, first name, employee ID num,
 * last 4 ssn, title.
 *
 * Design a second struct which will store two employees as members. The employees will be structs of the type of your first struct.
 * Inside of main(), prompt the user to enter each employee's credentials
 * and store them. Finally, print employee info to terminal.
 */
#include <stdio.h>
#include <stdlib.h>

struct data {
	char lname[20];
	char fname[20];
	int id_num;
	int ssn;
	char title[20];
};

struct people {
	struct data employee1;
	struct data employee2;
} admin;

int main(void){
	for (int i = 0; i < 2; i++){
		struct data *employee = &admin.employee1;
		if (i > 0)
			employee = &admin.employee2;

		printf("Enter the employee last name: ");
		scanf("%s", &employee->lname);

		printf("Enter the employee first name: ");
		scanf("%s", &employee->fname);

		printf("Enter the employee ID number: ");
		scanf("%d", &employee->id_num);

		printf("Enter the employee SSN: ");
		scanf("%d", &employee->ssn);

		printf("Enter the employee title: ");
		scanf("%s", &employee->title);

		puts("");
	}
	for (int i = 0; i < 2; i++){
		struct data *employee = &admin.employee1;
		if(i > 0)
			employee = &admin.employee2;

		printf("\nEmployee information for %s %s", employee->fname, employee->lname);
		printf("\nID: %d", employee->id_num);
		printf("\nSSN: %d", employee->ssn);
		printf("\nTitle: %s\n", employee->title);
	}
	return 0;
}
