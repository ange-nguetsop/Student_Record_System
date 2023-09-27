#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#pragma warning(disable : 4996)


struct student
{
	char  fistname[50];
	char  lastname[50];
	int   age;
	float grade[6] = { 0.0 }; //
	// perd - temps de Daryl
};

struct name
{
	char name[50];
};

struct student* add_student_record(int size);
void Display_student_record(struct student* ptr, int size);
struct student* search(struct student* ptr, char lastname[], char firstname[], int size);
void average_grade(struct student* ptr, int size);
void search_sort(struct student* ptr, struct name* _ptr, int size);
void Sorting_method_name(struct student* ptr, int size);
void Sorting_method_age(struct student* ptr, int size);
void Display_once(struct student* ptr, int size, int c);
void Sorting_method_note(struct student* ptr, int size);
void store_Data(struct student* ptr, int size);
void modify_data(struct student* ptr, int size);

void main(void)
{
	/*
	Project: Student Record System

Create a C program to manage student records using structs, enums, and unions.
The program should allow the user to perform the following operations:

	1. Add a new student record with fields for name, age, and grades.
	2. Display the list of student records.
	3. Search for a student by name and display their details.
	4. Calculate and display the average grade for all students.
	5. Allow the user to choose a sorting method (e.g., by name, age, or grade) and display the sorted list of student records.
	6. Modify the data of student
	7.Store the data in a text datei
	8. Quit the program.

	*/

	int choice = 1000;
	int size = 0;
	struct student* ptr = nullptr;
	struct student* sptr = nullptr;
	int validInput = 0;
	int choice1 = 0;
	int c;
	int check = 0;
	char d = 'e';

	printf("Welcome to the new Student Record System\n");
	printf("=========================================\n\n\n");
	while (choice != 0)
	{
	start:
		printf("Please choose the operation you want to perform \n\n\n");
		printf("Add a new student record:             1\n");
		printf("Display the list of student records:  2\n");
		printf("Search for a student:                 3\n");
		printf("Average grade for all students:       4\n");
		printf("Sort the list of student              5\n");
		printf("Store the data                        6\n");
		printf("Modify the data of a student	      7\n");
		printf("Exit:                                 0\n\n");
		printf("Your choice:                          ");
		int flag = scanf("%i", &choice);
		while ((c = getchar()) != '\n' && c != EOF);
		if (flag != 1 || (choice < 0 || choice >7))
		{
			printf("Invalid Input\nPlease Try again\n");
			goto start;
		}

		switch (choice)
		{
		case 1:
		loop:
			printf("How many students do you want to enter in the system?> ");
			check = scanf("%i", &size);
			while ((c = getchar()) != '\n' && c != EOF);
			if (check == 1)
			{
				if (size == 0)
				{
					printf("Invalid Input\n");
					goto loop;
				}

				while ((c = getchar()) != '\n' && c != EOF);
				ptr = add_student_record(size);
				Display_student_record(ptr, size);
			}
			else
			{
				size = 0; // Reset size to 0 for invalid input
				printf("\nInvalid input.Please enter a valid number.\n");
				goto loop;
			}
			break;

		case 2:

			if (ptr == nullptr)
			{
				printf("Any student was registerd yet.\n");
				printf("Can display anything\n");
				break;
			}
			else
			{
				printf("List of students\n");
				printf("_____________________\n");
				Display_student_record(ptr, size);
			}

			break;

		case 4:
			if (ptr == nullptr)
			{
				printf("Any student was registerd yet.\n");
				printf("Can display anything\n");
				break;
			}
			else
			{
				printf("Average Grade for all Students");
				printf("\n__________________________________");
				average_grade(ptr, size);
			}
			break;

		case 3:
			char firstname[50];
			char lastname[50];
			if (ptr == nullptr)
			{
				printf("Any student was registerd yet.\n");
				printf("Can display anything\n");
				break;
			}
			printf("Please enter the firstname of the student: ");
			fgets(firstname, sizeof(firstname), stdin);
			firstname[strcspn(firstname, "\n")] = '\0';
			printf("Please enter the lastname of the student: ");
			fgets(lastname, sizeof(lastname), stdin);
			lastname[strcspn(lastname, "\n")] = '\0';
			
			sptr = search(ptr, lastname, firstname, size);
			printf("\nAddress %p", sptr);
			printf("\n");
			printf("\tFirst name\tLast name\tAge\tMathematics\tPhysics\tChemistry\tBiology\tEnglisch\tGerman\n\n");
			printf("\t%s\t%s\t%i\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f",sptr->fistname, sptr->lastname, sptr->age, sptr->grade[0], sptr->grade[1], ptr->grade[2], ptr->grade[3], ptr->grade[4], ptr->grade[5]);
	
			break;

		case 5:
			if (ptr == nullptr)
			{
				printf("Any student was registerd yet.\n");
				printf("Can display anything\n");
				break;
			}
			Sort:
			printf("How do you want to sort the list?\n");
			printf("With name			enter 1\n");
			printf("With Age			enter 2\n");
			printf("With Grade			enter 3\n");
			printf("Your choice >>            ");
			scanf("%i", &choice1);
			while ((c = getchar()) != '\n' && c != EOF);
			switch (choice1)
			{
			case 1:
				Sorting_method_name(ptr, size);
				break;
			case 2:
				Sorting_method_age(ptr, size);
				break;
			case 3:
				Sorting_method_note(ptr, size);
				break;
			default:
				printf("\nInvalid Input\n");
				goto Sort;
			}
			break;

		case 6:
			if (ptr == nullptr)
			{
				printf("Any student was registerd yet.\n");
				printf("Can display anything\n");
				break;
			}
			store_Data(ptr, size);
			break;
			
		case 0:
			printf("\nGood Bye!!! <3");
			break;

		case 7:
			if (ptr == nullptr)
			{
				printf("Any student was registerd yet.\n");
				printf("Can display anything\n");
				break;
			}
			modify_data(ptr, size);
			break;

		default:
			printf("\nInvalid input.Please enter a valid number.\n");

		}
		printf("\nWeiter mit <ENTER>");
		scanf("%c", &d);
		while ((c = getchar()) != '\n' && c != EOF);
		printf("\n");
	}
	if (ptr != NULL) 
	{
		free(ptr);
		ptr = NULL; // Set the pointer to NULL to avoid accessing freed memory
	}
}

struct student* add_student_record(int size)
{
	struct student* stdptr = nullptr;

	int age = 0;
	float gpa = 0.0f;

	while (stdptr == nullptr)
	{

		//Allocate memory for size student
		stdptr = (struct student*)calloc(size, sizeof(struct student));

		//Check if memory allocation has failed

		if (stdptr == nullptr)
		{
			printf("The memory's size is too small for the demanded allocation\n");
			printf("Memory allocation failed");
			printf("\nPlease try again\n");
			system("cls");
		}

	}

	int s = 0;
loop_start:
	printf("Please note that you have the choice between: Mathematics, Physics, Chemistry, Biology, English and German\n");
	printf("-----------------------------------------------------------------------------------------------------------\n\n");
	printf("For Mathematics >>		   1\n");
	printf("For Physics     >>		   2\n");
	printf("For Chemistry   >>		   3\n");
	printf("For Biology     >>		   4\n");
	printf("For Englich     >>		   5\n");
	printf("For German      >>		   6\n\n");
	printf("Your Choice:    >>		   ");
	scanf("%i", &s);
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
	printf("\n\n");

	switch (s)
	{
	case 1:
	{
		int i = 0;
		while (size != 0)
		{
			char lastname[50] = "";
			char firstname[50] = "";
			printf("First Name Student: ");
			fgets(firstname, sizeof(firstname), stdin);
			firstname[strcspn(firstname, "\n")] = '\0';
			printf("Last Name Student: ");
			fgets(lastname, sizeof(lastname), stdin);
			lastname[strcspn(lastname, "\n")] = '\0';
			printf("Age: ");
			scanf("%i", &age);
			while ((c = getchar()) != '\n' && c != EOF);
			printf("Note: ");
			scanf("%f", &gpa);
			while ((c = getchar()) != '\n' && c != EOF);


			for (int j = 0; j < 4; j++)
			{
				strcpy(stdptr[i].fistname, firstname);
				strcpy(stdptr[i].lastname, lastname);
				stdptr[i].age = age;
				stdptr[i].grade[0] = gpa;
			}
			i++;
			size = size - 1;
		}
		break;
	}

	case 2:
	{
		int i = 0;
		while (size != 0)
		{
			char lastname[50] = "";
			char firstname[50] = "";
			printf("First Name Student: ");
			fgets(firstname, sizeof(firstname), stdin);
			firstname[strcspn(firstname, "\n")] = '\0';
			printf("Last Name Student: ");
			fgets(lastname, sizeof(lastname), stdin);
			lastname[strcspn(lastname, "\n")] = '\0';
			printf("Age: ");
			scanf("%i", &age);
			while ((c = getchar()) != '\n' && c != EOF);
			printf("Note: ");
			scanf("%f", &gpa);
			while ((c = getchar()) != '\n' && c != EOF);


			for (int j = 0; j < 4; j++)
			{
				strcpy(stdptr[i].fistname, firstname);
				strcpy(stdptr[i].lastname, lastname);
				stdptr[i].age = age;
				stdptr[i].grade[1] = gpa;
			}
			i++;
			size = size - 1;
		}
		break;
	}

	case 3:
	{
		int i = 0;
		while (size != 0)
		{
			char lastname[50] = "";
			char firstname[50] = "";
			printf("First Name Student: ");
			fgets(firstname, sizeof(firstname), stdin);
			firstname[strcspn(firstname, "\n")] = '\0';
			printf("Last Name Student: ");
			fgets(lastname, sizeof(lastname), stdin);
			lastname[strcspn(lastname, "\n")] = '\0';
			printf("Age: ");
			scanf("%i", &age);
			while ((c = getchar()) != '\n' && c != EOF);
			printf("Note: ");
			scanf("%f", &gpa);
			while ((c = getchar()) != '\n' && c != EOF);


			for (int j = 0; j < 4; j++)
			{
				strcpy(stdptr[i].fistname, firstname);
				strcpy(stdptr[i].lastname, lastname);
				stdptr[i].age = age;
				stdptr[i].grade[2] = gpa;
			}
			i++;
			size = size - 1;
		}
		break;
	}
	case 4:
	{
		int i = 0;
		while (size != 0)
		{
			char lastname[50] = "";
			char firstname[50] = "";
			printf("First Name Student: ");
			fgets(firstname, sizeof(firstname), stdin);
			firstname[strcspn(firstname, "\n")] = '\0';
			printf("Last Name Student: ");
			fgets(lastname, sizeof(lastname), stdin);
			lastname[strcspn(lastname, "\n")] = '\0';
			printf("Age: ");
			scanf("%i", &age);
			while ((c = getchar()) != '\n' && c != EOF);
			printf("Note: ");
			scanf("%f", &gpa);
			while ((c = getchar()) != '\n' && c != EOF);


			for (int j = 0; j < 4; j++)
			{
				strcpy(stdptr[i].fistname, firstname);
				strcpy(stdptr[i].lastname, lastname);
				stdptr[i].age = age;
				stdptr[i].grade[3] = gpa;
			}
			i++;
			size = size - 1;
		}
		break;
	}
	case 5:
	{
		int i = 0;
		while (size != 0)
		{
			char lastname[50] = "";
			char firstname[50] = "";
			printf("First Name Student: ");
			fgets(firstname, sizeof(firstname), stdin);
			firstname[strcspn(firstname, "\n")] = '\0'; // newline delete
			printf("Last Name Student: ");
			fgets(lastname, sizeof(lastname), stdin);
			lastname[strcspn(lastname, "\n")] = '\0'; //newline delete
			printf("Age: ");
			scanf("%i", &age);
			while ((c = getchar()) != '\n' && c != EOF);
			printf("Note: ");
			scanf("%f", &gpa);
			while ((c = getchar()) != '\n' && c != EOF);


			for (int j = 0; j < 4; j++)
			{
				strcpy(stdptr[i].fistname, firstname);
				strcpy(stdptr[i].lastname, lastname);
				stdptr[i].age = age;
				stdptr[i].grade[4] = gpa;
			}
			i++;
			size = size - 1;
		}
		break;
	}
	case 6:
	{
		int i = 0;
		while (size != 0)
		{
			char lastname[50] = "";
			char firstname[50] = "";
			printf("First Name Student: ");
			fgets(firstname, sizeof(firstname), stdin);
			firstname[strcspn(firstname, "\n")] = '\0';
			printf("Last Name Student: ");
			fgets(lastname, sizeof(lastname), stdin);
			lastname[strcspn(lastname, "\n")] = '\0';
			printf("Age: ");
			scanf("%i", &age);
			while ((c = getchar()) != '\n' && c != EOF);
			printf("Note: ");
			scanf("%f", &gpa);
			while ((c = getchar()) != '\n' && c != EOF);


			for (int j = 0; j < 4; j++)
			{
				strcpy(stdptr[i].fistname, firstname);
				strcpy(stdptr[i].lastname, lastname);
				stdptr[i].age = age;
				stdptr[i].grade[5] = gpa;
			}
			i++;
			size = size - 1;
		}
		break;
	}

	default:
		printf("Wrong selection. Please try again\n");
		system("cls");
		goto loop_start;
	}

	return stdptr;
}

void Display_student_record(struct student* ptr, int size)
{
	printf("\n\n");
	printf("studentID\tVorname\t\tNachname\tAge\tMaths\tPhy\tChem\tBio\tEng\tGer\n\n");
	printf("---------------------------------------------------------------------------------------------------\n");
	for (int i = 0; i < size; i++)
	{
		printf("student%i\t%s\t\t%s\t\t%i\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f", i, ptr[i].fistname, ptr[i].lastname, ptr[i].age, ptr[i].grade[0], ptr[i].grade[1], ptr[i].grade[2], ptr[i].grade[3], ptr[i].grade[4], ptr[i].grade[5]);
		printf("\n");
	}
}

struct student* search(struct student* ptr, char lastname[], char firstname[], int size)
{

	for (int i = 0; i < size; i++)
	{
		if (strcmp(ptr->fistname,firstname) == 0 && strcmp(ptr->lastname,lastname) == 0)
		{
			return ptr;
		}
		ptr++;
	}

	printf("\n\nNot found!\n");
	return NULL;
}

void average_grade(struct student* ptr, int size)
{
	float sum1 = 0, sum2 = 0, sum3 = 0, sum4 = 0, sum5 = 0, sum6 = 0;

	for (int i = 0; i < size; i++)
	{
		sum1 = sum1 + ptr->grade[0];
		sum2 = sum2 + ptr->grade[1];
		sum3 = sum3 + ptr->grade[2];
		sum4 = sum4 + ptr->grade[3];
		sum5 = sum5 + ptr->grade[4];
		sum6 = sum6 + ptr->grade[5];
	}

	sum1 = sum1 / size;
	sum2 = sum2 / size;
	sum3 = sum3 / size;
	sum4 = sum4 / size;
	sum5 = sum5 / size;
	sum6 = sum6 / size;

	printf("\n\nAverage GPA\n");
	printf("------------------\n");

	printf("\t\tMathematics\tPhysics\tChemistry\tBiology\tEnglisch\tGerman\n");
	printf("___________________________________________________________________________________________________________\n");
	printf("Average GPA \t%f\t%f\t%f\t%f\t%f\t%f", sum1, sum2, sum3, sum4, sum5, sum6);
	printf("\n");
}

void search_sort(struct student* ptr, struct name* _ptr, int size)
{
	printf("\n\nstudent\tFirstname\tLastname\tAge\tMathematics\tPhysics\tChemistry\tBiology\tEnglisch\tGerman\n\n");
	printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

	for (int i = 0; i < size; i++)
	{
		if (strcmp(_ptr->name, ptr->lastname) == 0)
		{
			printf("student%i\t%s\t%s\t%i\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f", i, ptr->fistname, ptr->lastname, ptr->age, ptr->grade[0], ptr->grade[1], ptr->grade[2], ptr->grade[3], ptr->grade[4], ptr->grade[5]);
			printf("\n");
		}
		ptr++;
	}
}

void Sorting_method_name(struct student* ptr, int size)
{
	//new list in Heap for lastname of students
	struct name* nptr = nullptr;
	struct student* sptr = nullptr;
	sptr = ptr;
	char temp[50];
	nptr = (struct name*)malloc(size * sizeof(struct name));

	for (int i = 0; i < size; i++)
	{
		strcpy(nptr[i].name, sptr->lastname);
		sptr++;
	}

	printf("\n");

	for (int i = 0; i < size; i++)
	{
		printf("Name %s\n", nptr[i].name);
	}

	for (int i = 0; i < size; i++)
	{
		for (int j = i + 1; j < size; j++)
		{
			if (strcmp(nptr[i].name, nptr[j].name) > 0)
			{
				strcpy(temp, nptr[i].name);
				strcpy(nptr[i].name, nptr[j].name);
				strcpy(nptr[j].name, temp);
			}
		}
	}

	printf("\n\nstudent\tFirstname\tLastname\tAge\tMathematics\tPhysics\tChemistry\tBiology\tEnglisch\tGerman\n\n");
	printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (strcmp(nptr[i].name, ptr[j].lastname) == 0)
			{
				printf("student%i\t%s\t%s\t%i\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f", i, ptr[j].fistname, ptr[j].lastname, ptr[j].age, ptr[j].grade[0], ptr[j].grade[1], ptr[j].grade[2], ptr[j].grade[3], ptr[j].grade[4], ptr[j].grade[5]);
				printf("\n");
			}
		}

	}
	free(nptr);
}

void Sorting_method_age(struct student* ptr, int size)
{
	struct student* tmp = nullptr;
	tmp = (struct student*)malloc(sizeof(struct student));

	for (int i = 0; i < size; i++)
	{
		for (int j = i + 1; j < size; j++)
		{
			if (ptr[i].age > ptr[j].age)
			{
				strcpy(tmp->fistname, ptr[i].fistname);
				strcpy(tmp->lastname, ptr[i].lastname);
				tmp->age = ptr[i].age;
				for (int i = 0; i < 6; i++)
				{
					tmp->grade[i] = ptr[i].grade[i];
				}

				strcpy(ptr[i].fistname, ptr[j].fistname);
				strcpy(ptr[i].lastname, ptr[j].lastname);
				ptr[i].age = ptr[j].age;
				for (int k = 0; k < 6; k++)
				{
					ptr[i].grade[k] = ptr[j].grade[k];
				}

				strcpy(ptr[j].fistname, tmp->fistname);
				strcpy(ptr[j].lastname, tmp->lastname);
				ptr[j].age = tmp->age;
				for (int k = 0; k < 6; k++)
				{
					ptr[j].grade[k] = tmp->grade[k];
				}


			}
		}
	}

	Display_student_record(ptr, size);

	free(tmp);
}

void Display_once(struct student* ptr, int size, int c)
{
	char matiere[6][50] = { "Mathematics","Physics","Chemistry","Biology","German","Englisch" };
	printf("\n\nStudent\tFirstname\tLastname\t%s\n", matiere[c - 1]);
	printf("_______________________________________________________\n");
	for (int i = 0; i < size; i++)
	{
		printf("student%i\t%s\t%s\t%i\t%.2f", i, ptr[i].fistname, ptr[i].lastname, ptr[i].age, ptr[i].grade[c-1]);
		printf("\n");
	}

}

void Sorting_method_note(struct student* ptr, int size)
{
	int choice;
	int c;
	struct student* tmp = nullptr;
	tmp = (struct student*)malloc(sizeof(struct student));

	char matiere[6][50] = { "Mathematics","Physics","Chemistry","Biology","German","Englisch" };
	Sort:
	printf("For witch subject do you want to sort the list?\n");
	printf("For Mathematics		>>			 1\n");
	printf("For Physics			>>			 2\n");
	printf("For Chemistry		>>			 3\n");
	printf("For Biology			>>			 4\n");
	printf("For Englich			>>			 5\n");
	printf("For German			>>			 6\n\n");
	printf("Your choice			>>			  ");
	scanf("%i", &choice);
	while ((c = getchar()) != '\n' && c != EOF);

	switch (choice)
	{
	case 1:

		for (int i = 0; i < size; i++)
		{
			for (int j = i + 1; j < size; j++)
			{
				if (ptr[i].grade[0] > ptr[j].grade[0])
				{
					strcpy(tmp->fistname, ptr[i].fistname);
					strcpy(tmp->lastname, ptr[i].lastname);
					tmp->age = ptr[i].age;
					for (int k = 0; k < 6; k++)
					{
						tmp->grade[k] = ptr[i].grade[k];
					}

					strcpy(ptr[i].fistname, ptr[j].fistname);
					strcpy(ptr[i].lastname, ptr[j].lastname);
					ptr[i].age = ptr[j].age;
					for (int k = 0; k < 6; k++)
					{
						ptr[i].grade[k] = ptr[j].grade[k];
					}

					strcpy(ptr[j].fistname, tmp->fistname);
					strcpy(ptr[j].lastname, tmp->lastname);
					ptr[j].age = tmp->age;
					for (int k = 0; k < 6; k++)
					{
						ptr[j].grade[k] = tmp->grade[k];
					}


				}
			}
		}

		Display_once(ptr, size,choice);
		break;

	case 2:
		for (int i = 0; i < size; i++)
		{
			for (int j = i + 1; j < size; j++)
			{
				if (ptr[i].grade[1] > ptr[j].grade[1])
				{
					strcpy(tmp->fistname, ptr[i].fistname);
					strcpy(tmp->lastname, ptr[i].lastname);
					tmp->age = ptr[i].age;
					for (int k = 0; k < 6; i++)
					{
						tmp->grade[k] = ptr[i].grade[k];
					}

					strcpy(ptr[i].fistname, ptr[j].fistname);
					strcpy(ptr[i].lastname, ptr[j].lastname);
					ptr[i].age = ptr[j].age;
					for (int k = 0; k < 6; k++)
					{
						ptr[i].grade[k] = ptr[j].grade[k];
					}

					strcpy(ptr[j].fistname, tmp->fistname);
					strcpy(ptr[j].lastname, tmp->lastname);
					ptr[j].age = tmp->age;
					for (int k = 0; k < 6; k++)
					{
						ptr[j].grade[k] = tmp->grade[k];
					}


				}
			}
		}

		Display_once(ptr, size, choice);
		break;

	case 3:
		for (int i = 0; i < size; i++)
		{
			for (int j = i + 1; j < size; j++)
			{
				if (ptr[i].grade[2] > ptr[j].grade[2])
				{
					strcpy(tmp->fistname, ptr[i].fistname);
					strcpy(tmp->lastname, ptr[i].lastname);
					tmp->age = ptr[i].age;
					for (int k = 0; k < 6; k++)
					{
						tmp->grade[k] = ptr[i].grade[k];
					}

					strcpy(ptr[i].fistname, ptr[j].fistname);
					strcpy(ptr[i].lastname, ptr[j].lastname);
					ptr[i].age = ptr[j].age;
					for (int k = 0; k < 6; k++)
					{
						ptr[i].grade[k] = ptr[j].grade[k];
					}

					strcpy(ptr[j].fistname, tmp->fistname);
					strcpy(ptr[j].lastname, tmp->lastname);
					ptr[j].age = tmp->age;
					for (int k = 0; k < 6; k++)
					{
						ptr[j].grade[k] = tmp->grade[k];
					}


				}
			}
		}

		Display_once(ptr, size, choice);
		break;

	case 4:
		for (int i = 0; i < size; i++)
		{
			for (int j = i + 1; j < size; j++)
			{
				if (ptr[i].grade[3] > ptr[j].grade[3])
				{
					strcpy(tmp->fistname, ptr[i].fistname);
					strcpy(tmp->lastname, ptr[i].lastname);
					tmp->age = ptr[i].age;
					for (int k = 0; k < 6; k++)
					{
						tmp->grade[k] = ptr[i].grade[k];
					}

					strcpy(ptr[i].fistname, ptr[j].fistname);
					strcpy(ptr[i].lastname, ptr[j].lastname);
					ptr[i].age = ptr[j].age;
					for (int k = 0; k < 6; k++)
					{
						ptr[i].grade[k] = ptr[j].grade[k];
					}

					strcpy(ptr[j].fistname, tmp->fistname);
					strcpy(ptr[j].lastname, tmp->lastname);
					ptr[j].age = tmp->age;
					for (int k = 0; k < 6; k++)
					{
						ptr[j].grade[k] = tmp->grade[k];
					}


				}
			}
		}

		Display_once(ptr, size, choice);
		break;

	case 5:
		for (int i = 0; i < size; i++)
		{
			for (int j = i + 1; j < size; j++)
			{
				if (ptr[i].grade[4] > ptr[j].grade[4])
				{
					strcpy(tmp->fistname, ptr[i].fistname);
					strcpy(tmp->lastname, ptr[i].lastname);
					tmp->age = ptr[i].age;
					for (int k = 0; k < 6; k++)
					{
						tmp->grade[k] = ptr[i].grade[k];
					}

					strcpy(ptr[i].fistname, ptr[j].fistname);
					strcpy(ptr[i].lastname, ptr[j].lastname);
					ptr[i].age = ptr[j].age;
					for (int k = 0; k < 6; k++)
					{
						ptr[i].grade[k] = ptr[j].grade[k];
					}

					strcpy(ptr[j].fistname, tmp->fistname);
					strcpy(ptr[j].lastname, tmp->lastname);
					ptr[j].age = tmp->age;
					for (int k = 0; k < 6; k++)
					{
						ptr[j].grade[k] = tmp->grade[k];
					}


				}
			}
		}

		Display_once(ptr, size, choice);
		break;

	case 6:
		for (int i = 0; i < size; i++)
		{
			for (int j = i + 1; j < size; j++)
			{
				if (ptr[i].grade[5] > ptr[j].grade[5])
				{
					strcpy(tmp->fistname, ptr[i].fistname);
					strcpy(tmp->lastname, ptr[i].lastname);
					tmp->age = ptr[i].age;
					for (int k = 0; k < 6; k++)
					{
						tmp->grade[k] = ptr[i].grade[k];
					}

					strcpy(ptr[i].fistname, ptr[j].fistname);
					strcpy(ptr[i].lastname, ptr[j].lastname);
					ptr[i].age = ptr[j].age;
					for (int k = 0; k < 6; k++)
					{
						ptr[i].grade[k] = ptr[j].grade[k];
					}

					strcpy(ptr[j].fistname, tmp->fistname);
					strcpy(ptr[j].lastname, tmp->lastname);
					ptr[j].age = tmp->age;
					for (int k = 0; k < 6; k++)
					{
						ptr[j].grade[k] = tmp->grade[k];
					}


				}
			}
		}

		Display_once(ptr, size, choice);
		break;
	default:
		printf("Invalid Input\n");
		goto Sort;

	}

	free(tmp);
}

void store_Data(struct student* ptr, int size)
{
	FILE* filePointer;

	filePointer = fopen("Student_data.txt", "w");
	if (filePointer == NULL)
	{
		perror("\nError opening the file");
	}

	fprintf(filePointer, "Vorname\t\tNachname\tAge\tMaths\tPhy\tChem\tBio\tEng\tGer\n");

	for (int i = 0; i < size; i++)
	{
		fprintf(filePointer,"%s\t\t%s\t\t%i\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f",ptr[i].fistname, ptr[i].lastname, ptr[i].age, ptr[i].grade[0], ptr[i].grade[1], ptr[i].grade[2], ptr[i].grade[3], ptr[i].grade[4], ptr[i].grade[5]);
		fprintf(filePointer, "\n");
	}

	fclose(filePointer);

	printf("\nStudent data has been written to the file Student_data.txt .\n\n");
}

void modify_data(struct student* ptr, int size)
{
	struct name first;
	struct name last;
	int Age;
	float gpa;
	int choice;
	int choice1;
	int c;

	struct student* stdptr = nullptr;
	printf("\n\nEnter the last name of the student >> ");
	fgets(last.name, sizeof(last.name), stdin);
	last.name[strcspn(last.name, "\n")] = '\0';

	printf("\nEnter the first name of the student >>  ");
	fgets(first.name, sizeof(first.name), stdin);
	first.name[strcspn(first.name, "\n")] = '\0';
	printf("\n\n");
	stdptr = search(ptr, last.name, first.name, size);

	if (stdptr == NULL)
	{
		printf("\nStudent was not found\n");
	}

	else
	{
		printf("What do you want to modify?\n");
		printf("The last name		>>		1\n");
		printf("The first name		>>		2\n");
		printf("The age			>>		3\n");
		printf("The grade		>>		4\n\n");
		printf("Your choice:		>>		");
		scanf("%i", &choice);
		while ((c = getchar()) != '\n' && c != EOF);

		switch (choice)
		{
		case 1:
			printf("\nEnter the last name >>	");
			fgets(last.name, sizeof(last.name), stdin);
			last.name[strcspn(last.name, "\n")] = '\0';
			strcpy(stdptr->lastname, last.name);
			break;


		case 2:
			printf("\nEnter the first name >>	");
			fgets(first.name, sizeof(first.name), stdin);
			last.name[strcspn(first.name, "\n")] = '\0';
			strcpy(stdptr->fistname, first.name);
			break;

		case 3:
			printf("\nEnter the age >> ");
			scanf("%i", &Age);
			while ((c = getchar()) != '\n' && c != EOF);
			stdptr->age = Age;
			break;

		case 4:
			char matiere[6][50] = { "Mathematics","Physics","Chemistry","Biology","German","Englisch" };
		Sort:
			printf("For witch subject do you want to modify the value?\n");
			printf("For Mathematics		>>			 1\n");
			printf("For Physics		>>			 2\n");
			printf("For Chemistry	>>			 3\n");
			printf("For Biology		>>			 4\n");
			printf("For Englich		>>			 5\n");
			printf("For German		>>			 6\n\n");
			printf("Your choice		>>			  ");
			scanf("%i", &choice1);
			while ((c = getchar()) != '\n' && c != EOF);

			switch (choice1)
			{
			case 1:
				printf("\nEnter the mark >> ");
				scanf("%f", &gpa);
				while ((c = getchar()) != '\n' && c != EOF);
				stdptr->grade[0] = gpa;
				break;

			case 2:
				printf("\nEnter the mark >> ");
				scanf("%f", &gpa);
				while ((c = getchar()) != '\n' && c != EOF);
				stdptr->grade[1] = gpa;
				break;

			case 3:
				printf("\nEnter the mark >> ");
				scanf("%f", &gpa);
				while ((c = getchar()) != '\n' && c != EOF);
				stdptr->grade[2] = gpa;
				break;

			case 4:
				printf("\nEnter the mark >> ");
				scanf("%f", &gpa);
				while ((c = getchar()) != '\n' && c != EOF);
				stdptr->grade[3] = gpa;
				break;

			case 5:
				printf("\nEnter the mark >> ");
				scanf("%f", &gpa);
				while ((c = getchar()) != '\n' && c != EOF);
				stdptr->grade[4] = gpa;
				break;

			case 6:
				printf("\nEnter the mark >> ");
				scanf("%f", &gpa);
				while ((c = getchar()) != '\n' && c != EOF);
				stdptr->grade[5] = gpa;
				break;

			default:
				printf("\nInvalid Value\n\n");
				goto Sort;
			}


		}

	}

}
