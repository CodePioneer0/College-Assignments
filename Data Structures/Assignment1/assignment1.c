#include <stdio.h>
#include<string.h>
#define MAX_STUDENTS 10
struct Student{
    char name[20];
    int roll;
    char telephone[11];
    char address[20];
};
struct SReg{
    int count;
    struct Student studentArray[MAX_STUDENTS];
};
struct Student read(){
    struct Student s;
    printf("Enter the name : ");
    scanf("%s",s.name);
    printf("Enter the roll : ");
    scanf("%d",&s.roll);
    printf("Enter the telephone : ");
    scanf("%s",s.telephone);
    printf("Enter the address : ");
    scanf("%s",s.address);
    return s;
}
void display(struct Student s){
    printf("Name: %s\n",s.name);
    printf("Roll Number: %d\n",s.roll);
    printf("Telephone: %s\n",s.telephone);
    printf("Address: %s\n",s.address);
}

int add(struct SReg *sr, struct Student s){
    for (int i = 0; i < sr->count; i++)
    {
        if (sr->studentArray[i].roll == s.roll)
            return 0;
    }
    sr->studentArray[sr->count++] = s;
    return 1;
}

struct Student get(struct SReg *sr, int r){
    for (int i = 0; i < sr->count; i++)
    {
        if (sr->studentArray[i].roll == r)
            return sr->studentArray[i];
    }
    struct Student s = sr->studentArray[sr->count];
    s.roll = 0;
    return s;
}

int getCount(struct SReg *sr){
    return sr->count;
}
int modify(struct SReg *sr, struct Student s){
    for (int i = 0; i < sr->count; i++){
        if (sr->studentArray[i].roll == s.roll){
            sr->studentArray[i] = s;
            return 1;
        }
    }
    return 0;
}
int delete(struct SReg *sr, int r){
    for (int i = 0; i < sr->count; i++)
    {
        if (sr->studentArray[i].roll == r){
            for (int j = i; j < sr->count - 1; j++){
                sr->studentArray[j] = sr->studentArray[j + 1];
            }
            sr->count--;
            return 1;
        }
    }
    return 0;
}
void sortStudents(struct SReg *sr){
    for(int i=0;i<sr->count-1;i++){
        for(int j=0;j<sr->count - i - 1;j++){
            if(strcmp(sr->studentArray[j].name,sr->studentArray[j+1].name)>0){
                struct Student s = sr->studentArray[j];
                sr->studentArray[j] = sr->studentArray[j+1];
                sr->studentArray[j+1]=s; 
            }
        }
    }
}
void export(struct SReg *sr , char *fname){
    FILE *file;
    file=fopen(fname,"w");
    if(file == NULL ){
        printf("Error while opening the file!\n");
        return;
    }
    for(int i=0;i<sr->count;i++){
        fprintf(file,"%s %d %s %s\n",sr->studentArray[i].name,sr->studentArray[i].roll,sr->studentArray[i].telephone,sr->studentArray[i].address);
    }
    fclose(file);
    printf("Data Exported Successfully!\n");
}
void load(struct SReg *sr,char *fname){
    FILE *file;
    file = fopen(fname,"r");
    if(file == NULL){
        printf("Error while opening!\n");
        return;
    }
    while(!feof(file) && sr->count<MAX_STUDENTS){
        struct Student s;
        fscanf(file,"%s %d %s %s\n",s.name,&s.roll,s.telephone,s.address);
        sr->studentArray[sr->count++]=s;
    }
    printf("Files loaded Successfully!\n");
}
int main(){
    struct SReg sr = {0};
    int n;
    printf("Perform the following functions by choosing the right option\n");
    printf("1.Add\n2.Get\n3.Delete\n4.Modify\n5.SortStudents\n6.GetCount\n7.Export\n8.Load\n");
    printf("Enter 9 to exit\n");
    do
    {
        printf("Enter your option\n");
        scanf("%d", &n);
        switch (n)
        {
        case 1:
            if (add(&sr, read())){
                printf("The student got added!\n");
            }
            else{
                printf("Student already present\n");
            }
            break;
        case 2:
            int r;
            printf("Enter the roll of the student to be found!\n");
            scanf("%d", &r);
            display(get(&sr, r));
            break;
        case 3:
            int d;
            printf("Enter the roll to be deleted!\n");
            scanf("%d", &d);
            if (delete (&sr, d)){
                printf("Successfully deleted!\n");
            }
            else{
                printf("No such student found!\n");
            }
            break;
        case 4:
            printf("Enter the student details to be modified!\n");
            if (modify(&sr, read())){
                printf("Modified Successfully!\n");
            }
            else{
                printf("No such student exist\n");
            }
            break;
        case 5:
            sortStudents(&sr);
            printf("Students got Successfully Sorted!\n");
            break;    
        case 6:
            printf("Student Count : %d\n", getCount(&sr));
            break;
        case 7:
            printf("Enter the file name to be created!\n");
            char fname[10];
            scanf("%s",fname);
            export(&sr,fname);
            break;
        case 8:
            printf("Enter the file from where to load!\n");
            char ch[10];
            scanf("%s",ch);
            load(&sr,ch);
            break;        
        default:
            printf("No such option!\n");
        }
    } while (n != 9);
}