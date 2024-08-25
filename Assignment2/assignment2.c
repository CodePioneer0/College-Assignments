#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max_address 100
#define max_name 50
typedef struct Student
{
    char *name;
    int roll;
    char telephone[11];
    char *address;
} Student;
typedef struct SReg
{
    int maxStuds;
    int count;
    Student **arrStudPtr;
} SReg;
void display(Student s)
{
    printf("Name: %s\n", s.name);
    printf("Roll Number: %d\n", s.roll);
    printf("Telephone: %s\n", s.telephone);
    printf("Address: %s\n", s.address);
}
int add(SReg *sr, Student *s)
{
    for (int i = 0; i < sr->count; i++)
    {
        if (sr->arrStudPtr[i]->roll == s->roll)
            return 0;
    }
    sr->arrStudPtr[sr->count++] = s;
    return 1;
}
Student get(SReg *sr, int r)
{
    for (int i = 0; i < sr->count; i++)
    {
        if (sr->arrStudPtr[i]->roll == r)
            return *sr->arrStudPtr[i];
    }
    Student s = *sr->arrStudPtr[sr->count];
    s.roll = 0;
    return s;
}
int delete(SReg *sr, int r)
{
    for (int i = 0; i < sr->count; i++)
    {
        if (sr->arrStudPtr[i]->roll == r)
        {
            for (int j = i; j < sr->count - 1; j++)
            {
                sr->arrStudPtr[j] = sr->arrStudPtr[j + 1];
            }
            sr->count--;
            return 1;
        }
    }
    return 0;
}
int modify(SReg *sr, Student *s)
{
    for (int i = 0; i < sr->count; i++)
    {
        if (sr->arrStudPtr[i]->roll == s->roll)
        {
            sr->arrStudPtr[i] = s;
            return 1;
        }
    }
    return 0;
}

void sortStudents(SReg *sr)
{
    for (int i = 0; i < sr->count - 1; i++)
    {
        for (int j = 0; j < sr->count - i - 1; j++)
        {
            if (strcmp(sr->arrStudPtr[j]->name, sr->arrStudPtr[j + 1]->name) > 0)
            {
                Student *s = sr->arrStudPtr[j];
                sr->arrStudPtr[j] = sr->arrStudPtr[j + 1];
                sr->arrStudPtr[j + 1] = s;
            }
        }
    }
}
int getCount(SReg *sr)
{
    return sr->count;
}
void export(struct SReg *sr, char *fname)
{
    FILE *file;
    file = fopen(fname, "w");
    if (file == NULL)
    {
        printf("Error while opening the file!\n");
        return;
    }
    for (int i = 0; i < sr->count; i++)
    {
        fprintf(file, "%s %d %s %s\n", sr->arrStudPtr[i]->name, sr->arrStudPtr[i]->roll, sr->arrStudPtr[i]->telephone, sr->arrStudPtr[i]->address);
    }
    fclose(file);
    printf("Data Exported Successfully!\n");
}
void load(SReg *sr, char *fname)
{
    FILE *file;
    file = fopen(fname, "r");
    if (file == NULL)
    {
        printf("Error while opening!\n");
        return;
    }
    while (!feof(file) && sr->count < sr->maxStuds)
    {
        Student *s = (Student *)malloc(sizeof(Student));
        s->name = (char *)malloc(max_name * sizeof(char));
        s->address = (char *)malloc(max_address * sizeof(char));
        if (s == NULL)
        {
            fclose(file);
            printf("Memory Allocation failure\n");
            return;
        }
        fscanf(file, "%s %d %s %s\n", s->name, &s->roll, s->telephone, s->address);
        sr->arrStudPtr[sr->count++] = s;
    }
    printf("Files loaded Successfully!\n");
}

Student *createStudentRecord()
{
    Student *newStu = (Student *)malloc(sizeof(Student));
    if (newStu == NULL)
    {
        printf("Memory Allocation Failed\n");
        return NULL;
    }
    newStu->name = (char *)malloc(max_name * sizeof(char));
    newStu->address = (char *)malloc(max_address * sizeof(char));
    printf("Enter the name : ");
    scanf("%s", newStu->name);
    printf("Enter roll number: ");
    scanf("%d", &newStu->roll);
    printf("Enter telephone number: ");
    scanf("%s", newStu->telephone);
    printf("Enter address: ");
    scanf("%s", newStu->address);
    return newStu;
}
Student *createStudentRecordFromFile(char *fname)
{
    FILE *file;
    file = fopen(fname, "r");
    if (file == NULL)
    {
        printf("Error opening file\n");
        return NULL;
    }
    Student *s = (Student *)malloc(sizeof(Student));
    s->name = (char *)malloc(max_name * sizeof(char));
    s->address = (char *)malloc(max_address * sizeof(char));
    if (s == NULL)
    {
        fclose(file);
        printf("Memory Allocation failure\n");
        return NULL;
    }
    fscanf(file, "%s %d %s %s\n", s->name, &s->roll, s->telephone, s->address);
    fclose(file);
    return s;
}

void freeStudentRecord(Student *sp)
{
    if (sp)
    {
        free(sp->name);
        free(sp->address);
        free(sp);
    }
}

int main()
{
    SReg sr;
    printf("Enter the maximum number of students\n");
    scanf("%d", &sr.maxStuds);
    sr.count = 0;
    sr.arrStudPtr = (Student **)malloc(sr.maxStuds * sizeof(Student *));

    printf("1.Add\n2.Get\n3.Delete\n4.Modify\n5.SortStudents\n6.GetCount\n7.Export\n8.Load\n");
    int n;
    do
    {
        printf("Enter your option\n");
        scanf("%d", &n);
        if (n == 1)
        {
            if (add(&sr, createStudentRecord()))
            {
                printf("Successfully Added!\n");
            }
            else
            {
                printf("Failed to Add!\n");
            }
        }
        else if (n == 2)
        {
            int r;
            printf("Enter the roll of the student to be found!\n");
            scanf("%d", &r);
            display(get(&sr, r));
        }
        else if (n == 3)
        {
            int r;
            printf("Enter the roll to be deleted!\n");
            scanf("%d", &r);
            if (delete (&sr, r))
                printf("Successfully Deleted!\n");
            else
                printf("Unable to delete!\n");
        }
        else if (n == 4)
        {
            printf("Enter the student details to be modified!\n");
            if (modify(&sr, createStudentRecord()))
            {
                printf("Modified Successfully!\n");
            }
            else
            {
                printf("No such student exist\n");
            }
        }
        else if (n == 5)
        {
            sortStudents(&sr);
            printf("Students got Successfully Sorted!\n");
        }
        else if (n == 6)
        {
            printf("The number of students : %d\n", getCount(&sr));
        }
        else if (n == 7)
        {
            printf("Enter the file name to be created!\n");
            char fname[10];
            scanf("%s", fname);
            export(&sr, fname);
        }
        else if (n == 8)
        {
            printf("Enter the file from where to load!\n");
            char ch[10];
            scanf("%s", ch);
            load(&sr, ch);
        }
    } while (n != 9);

    return 0;
}