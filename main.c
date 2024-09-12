#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <conio.h>

char fileName[25];
struct subject
{
    char name[20];
    int max_marks;
};

struct student
{
    int id;
    char name[20];
    float marks[5];
    float obtained_marks;
    float percentage;
    char Grade[4];
};

void numOfStudents_Subjects(int *, int *);
float inputSubjectName(struct subject subjects[], int *num_subject);
void inputStudentData(int, int, struct subject subjects[], struct student students[], float);
void findGrade(char Grade[], float percentage);
void printResult(int, int, struct subject subjects[], struct student students[]);
void writeInFile(int, int, struct subject subjects[], struct student students[]);
void readFile();
void findStudentById(int, int, struct subject subjects[], struct student students[]);

int main()
{
    int num_students, num_subjects;
    numOfStudents_Subjects(&num_students, &num_subjects);

    struct subject subjects[num_subjects];
    struct student students[num_students];

    float total_marks = inputSubjectName(subjects, &num_subjects);
    inputStudentData(num_students, num_subjects, subjects, students, total_marks);
    printResult(num_students, num_subjects, subjects, students);
    writeInFile(num_students, num_subjects, subjects, students);
    readFile();
    findStudentById(num_students, num_subjects, subjects, students);
    return 0;
}

void findStudentById(int num_students, int num_subjects, struct subject subjects[], struct student students[])
{
    printf("Want to search student result (esc to exit): \n");
    int a = getch();
    if (a == 27)
    {
        system("cls");
        return;
    }

    int id = 1, i, j;
    do
    {
        printf("Enter Id to find the Student (0 to exit): ");
        scanf("%d", &id);

        for (i = 0; i < num_students; i++)
        {
            if (id == students[i].id)
            {
                printf("\t Student Result \n");
                printf("____________________________________________________________\n");

                printf("%d. %s.\n", i + 1, students[i].name);
                printf("Student Id : %d\n", students[i].id);
                printf("\n->Marksheet \n");
                for (j = 0; j < num_subjects; j++)
                {
                    printf("%d. %s Marks : %.1f\n", j + 1, subjects[j].name, students[i].marks[j]);
                }
                printf("Obtained Marks : %.1f \n", students[i].obtained_marks);
                printf("Percentage : %.1f \n", students[i].percentage);
                printf("Grade : %s \n\n", students[i].Grade);
                printf("____________________________________________________________\n");
            }
        }
    } while (id);
}

void readFile()
{
    FILE *ptr;
    ptr = fopen(fileName, "r+");
    char buffer[254];
    while (fgets(buffer, sizeof(buffer), ptr) != NULL)
    {
        printf("%s", buffer);
    }
}

void writeInFile(int num_students, int num_subjects, struct subject subjects[], struct student students[])
{
    printf("Want to create File (esc to exit): ");
    int a = getch();
    if (a == 27)
    {
        system("cls");
        return;
    }
    system("cls");
    printf("Enter filename : ");
    scanf("%s", &fileName);

    int i, j;
    FILE *fptr;
    fptr = fopen(fileName, "a+");
    fprintf(fptr, "\t Student Result \n");
    for (i = 0; i < num_students; i++)
    {
        fprintf(fptr, "%d. %s.\n", i + 1, students[i].name);
        fprintf(fptr, "Student Id : %d\n", students[i].id);
        fprintf(fptr, "\n->Marksheet \n");
        for (j = 0; j < num_subjects; j++)
        {
            fprintf(fptr, "%d. %s Marks : %.1f\n", j + 1, subjects[j].name, students[i].marks[j]);
        }
        fprintf(fptr, "Obtained Marks : %.1f \n", students[i].obtained_marks);
        fprintf(fptr, "Percentage : %.1f \n", students[i].percentage);
        fprintf(fptr, "Grade : %s \n", students[i].Grade);
        printf("____________________________________________________________\n");
    }
    fclose(fptr);
}

void printResult(int num_students, int num_subjects, struct subject subjects[], struct student students[])
{
    system("cls");
    int i, j;
    printf("\t Student Result \n");
    printf("____________________________________________________________\n\n");
    for (i = 0; i < num_students; i++)
    {
        printf("%d. %s.\n", i + 1, students[i].name);
        printf("Student Id : %d\n", students[i].id);
        printf("\n->Marksheet \n");
        for (j = 0; j < num_subjects; j++)
        {
            printf("%d. %s Marks : %.1f\n", j + 1, subjects[j].name, students[i].marks[j]);
        }
        printf("Obtained Marks : %.1f \n", students[i].obtained_marks);
        printf("Percentage : %.1f \n", students[i].percentage);
        printf("Grade : %s \n\n", students[i].Grade);
        printf("____________________________________________________________\n");
    }
}

void findGrade(char Grade[], float percentage)
{

    if (percentage >= 80)
    {
        strcpy(Grade, "A1");
    }
    else if (percentage >= 70)
    {
        strcpy(Grade, "A");
    }
    else if (percentage >= 60)
    {
        strcpy(Grade, "B");
    }
    else if (percentage >= 50)
    {
        strcpy(Grade, "C");
    }
    else if (percentage >= 40)
    {
        strcpy(Grade, "D");
    }
    else if (percentage >= 33)
    {
        strcpy(Grade, "E");
    }
    else if (percentage < 33)
    {
        strcpy(Grade, "Fail");
    }
}

void inputStudentData(int num_students, int num_subjects, struct subject subjects[], struct student students[], float total_marks)
{
    system("cls");
    int i, j;
    printf("\t Student Data \n");
    for (i = 0; i < num_students; i++)
    {
        printf("Enter the data of Student %d.\n", i + 1);
        printf("Student Id : ");
        scanf("%d", &students[i].id);

        printf("Student Name : ");
        scanf(" %[^\n]", &students[i].name);
        float sum = 0.0;
        for (j = 0; j < num_subjects; j++)
        {
            printf("Enter the marks of %s in %s : ", students[i].name, subjects[j].name);
            scanf("%f", &students[i].marks[j]);
            sum += students[i].marks[j];
        }
        students[i].obtained_marks = sum;
        students[i].percentage = (sum / total_marks) * 100;
        findGrade(students[i].Grade, students[i].percentage);
        system("cls");
    }
}

float inputSubjectName(struct subject subjects[], int *num_subject)
{
    float total_marks = 0;
    int i;
    for (i = 0; i < *num_subject; i++)
    {
        printf("Enter the name of Subject %d : ", i + 1);
        scanf(" %[^\n]", &subjects[i].name);
    }
    for (i = 0; i < *num_subject; i++)
    {
        printf("Maximum marks of %s : ", subjects[i].name);
        scanf("%d", &subjects[i].max_marks);
        total_marks += subjects[i].max_marks;
    }
    return total_marks;
}

void numOfStudents_Subjects(int *num_students, int *num_subject)
{
    printf("Enter number of Students here : ");
    scanf("%d", num_students);

    printf("Enter number of Subjects here : ");
    scanf("%d", num_subject);
}