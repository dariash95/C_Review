#include "stdio.h"
#include "stdint.h"
#include "string.h"

typedef struct{
	int student_id;
	char name[60];
	char date_of_birth[20];
	char career[80];
	int semester;
}StudentRecord_t;

StudentRecord_t g_students_records[10];
int g_records_count = 0;

void display_all_records(StudentRecord_t* p_student_records, int count);
void add_record(StudentRecord_t* p_student_records, int count);
void delete_record(StudentRecord_t* p_student_records, int count);
int check_coincidentes(int id, StudentRecord_t *record, int8_t max_record);

int main(void) {

	while (1){
	    printf("----------------------------------------------\n");
		printf("Student management program... Select an option\n");
		printf("Display records: 1\n");
		printf("Add record: 2\n");
		printf("Delete record: 3\n");
		printf("Enter option: ");

		int option = 0;
		scanf("%d", &option);

		switch(option){
			case 1:
				printf("Displaying\n");

				// No & becaUse it is a pointer already :)
				display_all_records(g_students_records, g_records_count);
				break;
			case 2:
				printf("Adding\n");
				add_record(g_students_records, g_records_count);
				break;
			case 3:
				printf("Deleting\n");
				delete_record(g_students_records, g_records_count);
				break;
			default:
				printf("Please enter a valid option\n");
		}

	}

	return 0;

}

void display_all_records(StudentRecord_t* p_student_records, int count){

	if (count == 0){
		printf("No records to display\n");
		return;
	}

	for (int i = 0; i < count; i++){
		printf("-------Student info-------\n");
		printf("Student ID: %d\n", p_student_records[i].student_id);
		printf("Student name: %s\n", p_student_records[i].name);
		printf("Student date of birth: %s\n", p_student_records[i].date_of_birth);
		printf("Student career: %s\n", p_student_records[i].career);
		printf("Student semester: %d\n", p_student_records[i].semester);

	}
}

int check_coincidences(int id, StudentRecord_t *record, int8_t max_record){

	for (int i = 0; i < max_record; i++){
		if (record[i].student_id == id){
			printf("Student in record already");
			return 1;
		}
	}

	return 0;

}

void add_record(StudentRecord_t* p_student_records, int count){

	// Check if there is space on the table to store
	if(g_records_count == 10){
		printf("There is no space for a new record, please delete one first");
		return;
	}

	printf("Enter new student ID: ");
	int new_id;
	scanf("%d", &new_id);

	int check = check_coincidences(new_id, p_student_records, count);

	if (check){
		return;
	}

	printf("Creating new record\n");
	p_student_records[g_records_count].student_id = new_id;

	printf("Enter new student semester: ");
	scanf("%d", &p_student_records[g_records_count].semester);

    getchar();
	printf("Enter new student name: ");
	scanf("%[^\n]s", p_student_records[g_records_count].name);
	getchar();

    printf("Enter new student date of birth: ");
	scanf("%[^\n]s", p_student_records[g_records_count].date_of_birth);
	getchar();

	printf("Enter new student career: ");
	scanf("%[^\n]s", p_student_records[g_records_count].career);


	g_records_count++;

	printf("New student added successfully. New total: %d\n", g_records_count);
}

void delete_record(StudentRecord_t* p_student_records, int count){

	if (count == 0){
		printf("There are no students recorded\n");
		return;
	}

	printf("Enter student ID: ");

	int std_id;
	scanf("%d", &std_id);

	int i;

	for (i = 0; i < g_records_count; i++){
		if (p_student_records[i].student_id == std_id){
			printf("Deleting record of student...\n");
			memset(&p_student_records[i],0,sizeof(StudentRecord_t));
			g_records_count--;
		}
	}

	if(i == g_records_count){
		printf("Student with student ID %d not found", std_id);
	}
}
