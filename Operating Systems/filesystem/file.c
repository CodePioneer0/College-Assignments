#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<errno.h>
#include<sys/stat.h>
#include<unistd.h>
#include<string.h>
#include<sys/stat.h>
#include<limits.h>

#define FNAME_MAXLENGTH 50
#define MNAME_MAXLENGTH 50
#define SNAME_MAXLENGTH 50
#define DESC_MAXLENGTH 250

struct student {
    int roll;
    char fname[FNAME_MAXLENGTH];
    char mname[MNAME_MAXLENGTH];
    char sname[SNAME_MAXLENGTH];
    char desc[DESC_MAXLENGTH];
};

struct studentPrefix{
    int roll;
    int fnamesize;
    int mnamesize;
    int snamesize;
    int descsize;
};

struct student readStudent();

void printStudent(struct student s);

struct studentPrefix getStudentPrefix(struct student s);

int addStudentRecord(int datafd,int indexfd,struct student s);

int getStudentRecord(int datafd,int indexfd,int i,struct student *sP);

int deleteStudentRecord(int datafd,int indexfd,int i);

int searchStudentRecord(int datafd, int indexfd, int rollNo, struct student *sP);

int modifyStudentRecord(int datafd, int indexfd, int i, struct student sNew);

int compactionStudentRecords(int datafd, int indexfd);

int sortRecordsAscenRoll(int datafd, int indexfd);

int main(int argc, char *argv[]) {

	int datafd, indexfd;
	if (argc != 3) {
		fprintf(stderr, "Usage: %s <data file> <index file>\n", argv[0]);
		exit(1);
	}

	while(1) {
		int i;
		int n;
		int option;
		char choice;
		int flag;
		int count1=0;
		int count2=0;
		struct student s1;
//		struct studentPrefix sPref1;
		int dataOffset; /* to keep position of a record in data file */
		int rollNo;
		printf("0 (Initialize data and index files)\n");
		printf("1 (Addition of a student record)\n");
    	printf("2 (Deleting a student record)\n");
    	printf("3 (Searching of a student record)\n");
		printf("4 (Modifying a student record)\n");
    	printf("5 (Compaction of student data and student index files)\n");
    	printf("6 (Print a student from data and index files)\n");
		printf("7 (Sort records in ascending order of roll number)\n");
    	printf("8 (Exit)\n");
		printf("Choose an option: ");
		scanf("%d%*[^\n]", &option);
		switch(option) {
			case 0: printf("Intializing data file %s and index file %s!\n", argv[1], argv[2]);
				count1 = 0;
				count2 = 0;
				// int open(const char *pathname, int flags, ...  /* mode_t mode */ );
				datafd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
				if (datafd == -1) {
					perror("open() failed");
					exit(1);
				}
				indexfd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0777);
				if (indexfd == -1) {
					perror("open() failed");
					exit(1);
				}
				flag = write(datafd, &count1, sizeof(int));
				if (flag == -1 || flag != sizeof(int)) {
					perror("write() failed");
					exit(1);
				}
				flag = write(indexfd, &count2, sizeof(int));
				if (flag == -1 || flag != sizeof(int)) {
					perror("write() failed");
					exit(1);
				}
				printf("Done intializing data file %s and index file %s!\n", argv[1], argv[2]);
				close(datafd);
				close(indexfd);
				break;

			case 1: printf("Adding a student record in data file %s and index file %s!\n", argv[1], argv[2]);
				datafd = open(argv[1], O_RDWR);
				if (datafd == -1) {
					perror("open() failed");
					exit(1);
				}
				indexfd = open(argv[2], O_RDWR);
				if (indexfd == -1) {
					perror("open() failed");
					exit(1);
				}

				/* Fill up a struct student from stdin */
				s1 = readStudent();
				printStudent(s1);

				count1 = addStudentRecord(datafd, indexfd, s1);
				close(datafd);
				close(indexfd);
				printf("Done adding student no %d in data file %s and index file %s!\n", count1, argv[1], argv[2]);
				break;

			case 2: printf("Deleting a student record from data file %s and index file %s!\n", argv[1], argv[2]);
				printf("Which record to delete? (Number): ");
				scanf("%d%*[^\n]", &i);
				printf("i = %d\n", i);

				datafd = open(argv[1], O_RDWR);
				if (datafd == -1) {
					perror("open() failed");
					exit(1);
				}
				indexfd = open(argv[2], O_RDWR);
				if (indexfd == -1) {
					perror("open() failed");
					exit(1);
				}

				flag = getStudentRecord(datafd, indexfd, i, &s1);
				if (flag == -1 ) {
					fprintf(stderr, "Cannot Delete!\n");
					break;
				}

				printStudent(s1);
				printf("Do you want to delete? (y/n) :");
				scanf("%*c%c%*[^\n]\n", &choice);
				while(choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N') {
					printf("Do you want to delete? (y/n) :");
					scanf("%*c%c%*[^\n]\n", &choice);
				}
				if (choice == 'n' || choice == 'N') {
					break;
				}
				/* now delete the record */
				flag = deleteStudentRecord(datafd, indexfd, i);
				if (flag == -1 ) {
					fprintf(stderr, "Cannot Delete!\n");
					break;
				}
				close(datafd);
				close(indexfd);
				printf("Done adding student no %d in data file %s and index file %s!\n", count1, argv[1], argv[2]);
				break;
			case 3: printf("Searching for a student record in data file %s and index file %s!\n", argv[1], argv[2]);
			    printf("Enter Roll Number to search: ");
				scanf("%d%*[^\n]", &rollNo);
				datafd = open(argv[1], O_RDWR);
				if (datafd == -1) {
					perror("open() failed");
					exit(1);
				}
				indexfd = open(argv[2], O_RDWR);
				if (indexfd == -1) {
					perror("open() failed");
					exit(1);
				}
				flag = searchStudentRecord(datafd, indexfd, rollNo, &s1);
				if (flag == -1 ) {
					fprintf(stderr, "Cannot Search!\n");
					exit(1);
				}
				printf("Found Student Record!\n");
				close(datafd);
				close(indexfd);
				break;
			case 4: printf("Modifying a student record in data file %s and index file %s!\n", argv[1], argv[2]);
			    printf("Which record to modify? (Number): ");
				scanf("%d%*[^\n]", &i);
				datafd = open(argv[1], O_RDWR);
				if (datafd == -1) {
					perror("open() failed");
					exit(1);
				}
				indexfd = open(argv[2], O_RDWR);
				if (indexfd == -1) {
					perror("open() failed");
					exit(1);
				}
				s1 = readStudent();
				printStudent(s1);
				flag = modifyStudentRecord(datafd, indexfd, i, s1);
				if (flag == -1 ) {
					fprintf(stderr, "Cannot Modify!\n");
				}
				close(datafd);
				close(indexfd);
				printf("Done modifying student no %d in data file %s and index file %s!\n", i, argv[1], argv[2]);
				break;
			case 5: printf("Compacting data file %s and index file %s!\n", argv[1], argv[2]);
			    datafd = open(argv[1], O_RDWR);
				if (datafd == -1) {
					perror("open() failed");
					exit(1);
				}
				indexfd = open(argv[2], O_RDWR);
				if (indexfd == -1) {
					perror("open() failed");
					exit(1);
				}
				flag = compactionStudentRecords(datafd, indexfd);
				if (flag == -1 ) {
					fprintf(stderr, "Cannot Compact!\n");
				}
				close(datafd);
				close(indexfd);
				printf("Done compacting data file %s and index file %s!\n", argv[1], argv[2]);
				break;
			case 6: printf("Printing a student record from data file %s and index file %s!\n", argv[1], argv[2]);
				printf("Which record to print? (Number): ");
				scanf("%d%*[^\n]", &i);

				datafd = open(argv[1], O_RDWR);
				if (datafd == -1) {
					perror("open() failed");
					exit(1);
				}
				indexfd = open(argv[2], O_RDWR);
				if (indexfd == -1) {
					perror("open() failed");
					exit(1);
				}

				flag = getStudentRecord(datafd, indexfd, i, &s1);
				if (flag == -1 ) {
					fprintf(stderr, "Cannot Delete!\n");
					break;
				}

				printStudent(s1);
				close(datafd);
				close(indexfd);
				printf("Done printing student no %d in data file %s and index file %s!\n", i, argv[1], argv[2]);
				break;
			case 7: printf("Sorting records in ascending order of roll number in data file %s and index file %s!\n", argv[1], argv[2]);
			    datafd = open(argv[1], O_RDWR);
				if (datafd == -1) {
					perror("open() failed");
					exit(1);
				}
				indexfd = open(argv[2], O_RDWR);
				if (indexfd == -1) {
					perror("open() failed");
					exit(1);
				}
				flag = sortRecordsAscenRoll(datafd, indexfd);
				if (flag == -1 ) {
					fprintf(stderr, "Cannot Sort!\n");
					break;
				}
				close(datafd);
				close(indexfd);
				printf("Done sorting records in ascending order of roll number in data file %s and index file %s!\n", argv[1], argv[2]);
				break; 
			case 8: printf("Good Bye!\n");
				exit(0);	
			default: printf("Choose a correct option!\n");
		}
	}
}
struct student readStudent() {
	struct student s;
	printf("Roll Number (Number): ");
	scanf("%d", &s.roll);
	printf("First Name (No space): ");
	scanf("%s", s.fname);
	printf("Middle Name (No space): ");
	scanf("%s", s.mname);
	printf("Surname (No space): ");
	scanf("%s", s.sname);
	printf("Description (Ends at new line): ");
	scanf("\n%[^\n]s", s.desc);
	return (s);
}
void printStudent(struct student s) {
	printf("Roll Number: %d\n", s.roll);
	printf("First Name: %s\n", s.fname);
	printf("Middle Name: %s\n", s.mname);
	printf("Surname: %s\n", s.sname);
	printf("Description: %s\n", s.desc);
}
struct studentPrefix getStudentPrefix(struct student s) {
	struct studentPrefix sPref;
	sPref.roll = s.roll;
	sPref.fnamesize = strlen(s.fname);
	sPref.mnamesize = strlen(s.mname);
	sPref.snamesize = strlen(s.sname);
	sPref.descsize = strlen(s.desc);
	return (sPref);
}
int addStudentRecord(int datafd, int indexfd, struct student s) {
	int flag;
	int count1;
	int count2;
	int dataOffset; /* position of struct student in data file */
	struct studentPrefix sPref1;
	flag = read(datafd, &count1, sizeof(int));
	if (flag == -1 || flag != sizeof(int)) {
		perror("read() failed");
		exit(1);
	}
	flag = read(indexfd, &count2, sizeof(int));
	if (flag == -1 || flag != sizeof(int)) {
		perror("read() failed");
		exit(1);
	}
	if (count1 != count2) {
		fprintf(stderr, "counts in data and index files do not match!\n");
		exit(1);
	}

	sPref1 = getStudentPrefix(s);

	flag = lseek(datafd, 0, SEEK_END);
	if (flag == -1) {
		perror("lseek() failed");
		exit(1);
	}
	dataOffset = flag; /* lseek returns the position */
	flag = write(datafd, &sPref1, sizeof(struct studentPrefix));
	if (flag == -1 || flag != sizeof(struct studentPrefix)) {
		perror("write() failed");
		exit(1);
	}


	/* Now write actual fname, mname, sname */

	/* Writing fname of actual lenght */
	flag = write(datafd, s.fname,  sPref1.fnamesize);
	if (flag == -1 || flag != sPref1.fnamesize) {
		perror("write() failed");
		exit(1);
	}

	/* Writing mname of actual lenght */
	flag = write(datafd, s.mname,  sPref1.mnamesize);
	if (flag == -1 || flag != sPref1.mnamesize) {
		perror("write() failed");
		exit(1);
	}

	/* Writing sname of actual lenght */
	flag = write(datafd, s.sname,  sPref1.snamesize);
	if (flag == -1 || flag != sPref1.snamesize) {
		perror("write() failed");
		exit(1);
	}

	/* Writing desc of actual lenght */
	flag = write(datafd, s.desc,  sPref1.descsize);
	if (flag == -1 || flag != sPref1.descsize) {
		perror("write() failed");
		exit(1);
	}
	count1++; /* count of records incremented */

	/* new count to be updated at the top of the data file */
	flag = lseek(datafd, 0, SEEK_SET);
	if (flag == -1) {
		perror("lseek() failed");
		exit(1);
	}
	flag = write(datafd, &count1,  sizeof(int));
	if (flag == -1 || flag != sizeof(int)) {
		perror("write() failed");
		exit(1);
	}
	flag = lseek(indexfd, 0, SEEK_END);
	if (flag == -1) {
		perror("lseek() failed");
		exit(1);
	}

	/* writing the offset of the student record in index file */
	flag = write(indexfd, &dataOffset,  sizeof(int));
	if (flag == -1 || flag != sizeof(int)) {
		perror("write() failed");
		exit(1);
	}

	/* increment the count of records */
	count2++;
	flag = lseek(indexfd, 0, SEEK_SET);
	if (flag == -1) {
		perror("lseek() failed");
		exit(1);
	}
	flag = write(indexfd, &count2,  sizeof(int));
	if (flag == -1 || flag != sizeof(int)) {
		perror("write() failed");
		exit(1);
	}
	return (count1);
}
int getStudentRecord(int datafd, int  indexfd, int i, struct student *sP) {
	int flag;
	int count1;
	int count2;
	int dataOffset; /* position of struct student in data file */
	struct studentPrefix sPref1;
	flag = lseek(datafd, 0, SEEK_SET);
	flag = read(datafd, &count1, sizeof(int));
	if (flag == -1 || flag != sizeof(int)) {
		perror("read() failed");
		exit(1);
	}
	flag = lseek(indexfd, 0, SEEK_SET);
	flag = read(indexfd, &count2, sizeof(int));
	if (flag == -1 || flag != sizeof(int)) {
		perror("read() failed");
		exit(1);
	}
	if (count1 != count2) {
		fprintf(stderr, "counts do not match in data file and index file.\n");
		return(-1);
	}

	if (count1 <  i) {
		fprintf(stderr, "count = %d, cannot get %d th record!\n", count1, i);
		return(-1);
	}

	flag = lseek(indexfd, i*sizeof(int), SEEK_SET);
	if (flag == -1) {
		perror("lseek() failed");
		exit(1);
	}
	flag = read(indexfd, &dataOffset, sizeof(int));
	if (flag == -1 || flag != sizeof(int)) {
		perror("read() failed");
		exit(1);
	}
	flag = lseek(datafd, dataOffset, SEEK_SET);
	if (flag == -1) {
		perror("lseek() failed");
		exit(1);
	}
	flag = read(datafd, &sPref1, sizeof(struct studentPrefix));
	if (flag == -1 || flag != sizeof(struct studentPrefix)) {
		perror("read() failed");
		exit(1);
	}
	sP->roll = sPref1.roll;
	flag = read(datafd, sP->fname,  sPref1.fnamesize);
	if (flag == -1 || flag != sPref1.fnamesize) {
		perror("read() failed");
		exit(1);
	}
	flag = read(datafd, sP->mname,  sPref1.mnamesize);
	if (flag == -1 || flag != sPref1.mnamesize) {
		perror("read() failed");
		exit(1);
	}
	flag = read(datafd, sP->sname,  sPref1.snamesize);
	if (flag == -1 || flag != sPref1.snamesize) {
		perror("read() failed");
		exit(1);
	}
	flag = read(datafd, sP->desc,  sPref1.descsize);
	if (flag == -1 || flag != sPref1.descsize) {
		perror("read() failed");
		exit(1);
	}
	return(0);
}
int deleteStudentRecord(int datafd, int indexfd, int i) {
	int flag;
	int count1;
	int count2;
	int dataOffset;
	int deletedFlag = -1;
	struct studentPrefix sPref;
	flag = lseek(datafd,0,SEEK_SET);
	if(flag == -1){
		perror("lseek() failed");
		exit(1);
	}
	flag = read(datafd, &count1, sizeof(int));
	if (flag == -1 || flag != sizeof(int)) {
		perror("read() failed");
		exit(1);
	}
	flag = lseek(indexfd,0,SEEK_SET);
	if(flag==-1){
		perror("lseek() failed");
		exit(1);
	}
	flag = read(indexfd, &count2, sizeof(int));
	if (flag == -1 || flag != sizeof(int)) {
		perror("read() failed");
		exit(1);
	}
	if (count1 != count2) {
		fprintf(stderr, "counts in data and index files do not match.\n");
		exit(1);
	}
	if(i<=0 || i>count1){
		fprintf(stderr,"The ith index is invalid.\n");
		return -1;
	}
	flag = lseek(indexfd,i*sizeof(int),SEEK_SET);
	if(flag==-1){
		perror("lseek() failed");
		exit(1);
	}
	flag = read(indexfd,&dataOffset,sizeof(int));
	if(flag==-1 || flag!=sizeof(int)){
		perror("read() failed");
		exit(1);
	}

	if(dataOffset==-1){
	    fprintf(stderr,"Record %d is already deleted.\n",i);
	    return -1;
	}
	flag = lseek(indexfd,i*sizeof(int),SEEK_SET);
	if(flag==-1){
		perror("lseek() failed");
		exit(1);
	}
	flag = write(indexfd,&deletedFlag,sizeof(int));
	if(flag==-1 || flag!=sizeof(int)){
		perror("write() failed");
		exit(1);
	}
	flag = lseek(datafd,dataOffset,SEEK_SET);
	if(flag==-1){
		perror("lseek() failed");
		exit(1);
	}
	flag=read(datafd,&sPref,sizeof(struct studentPrefix));
	if(flag==-1 || flag!=sizeof(struct studentPrefix)){
		perror("read() failed");
		exit(1);
	}
	sPref.roll = -1;
	flag = lseek(datafd,dataOffset,SEEK_SET);
	if(flag==-1){
		perror("lseek() failed");
		exit(1);
	}
	flag = write(datafd,&sPref,sizeof(struct studentPrefix));
	if(flag==-1 || flag!=sizeof(struct studentPrefix)){
		perror("write() failed");
		exit(1);
	}
	return 1;
}
int searchStudentRecord(int datafd, int indexfd, int rollNo, struct student *sP) {
	if(rollNo <= 0){
		fprintf(stderr, "Invalid Roll Number\n");
		return -1;
	}
	int flag;
	int count1;
	int count2;
	lseek(datafd,0,SEEK_SET);
	flag = read(datafd, &count1, sizeof(int));
	if (flag == -1 || flag != sizeof(int)) {
		perror("read() failed");
		exit(1);
	}
	lseek(indexfd,0,SEEK_SET);
	flag = read(indexfd, &count2, sizeof(int));
	if (flag == -1 || flag != sizeof(int)) {
		perror("read() failed");
		exit(1);
	}
	if (count1 != count2) {
		fprintf(stderr, "counts in data and index files do not match!\n");
		exit(1);
	}
	for(int i=1;i<=count1;i++){
		flag = getStudentRecord(datafd,indexfd,i,sP);
		if(flag == -1){
			perror("Something went wrong in getStudentRecord()");
			exit(1);
		}
		if(sP->roll == rollNo){
			return 0;
		}
	}
	fprintf(stderr, "Record with Roll Number %d not found!\n", rollNo);
	return -1;
}
int modifyStudentRecord(int datafd, int indexfd, int i, struct student sNew){
	int flag;
	int count1;
	int count2;
	struct studentPrefix sPref;
	struct student s;
	flag = lseek(datafd,0,SEEK_SET);
	if(flag == -1){
		perror("lseek() failed");
		exit(1);
	}
	flag = read(datafd, &count1, sizeof(int));
	if (flag == -1 || flag != sizeof(int)) {
		perror("read() failed");
		exit(1);
	}
	flag = lseek(indexfd,0,SEEK_SET);
	if(flag == -1){
		perror("lseek() failed");
		exit(1);
	}
	flag = read(indexfd, &count2, sizeof(int));
	if (flag == -1 || flag != sizeof(int)) {
		perror("read() failed");
		exit(1);
	}
	if( count1 != count2) {
		fprintf(stderr, "counts in data and index files do not match!\n");
		exit(1);
	}
	if(i<=0 || i>count1){
		fprintf(stderr,"The ith index is invalid.\n");
		return -1;
	}
	flag = getStudentRecord(datafd,indexfd,i,&s);
	if(flag == -1){
		perror("Something went wrong in getStudentRecord()");
		exit(1);
	}
	if(s.roll == -1){
		fprintf(stderr, "Record %d is deleted. Cannot modify deleted record.\n", i);
		return -1;
	}
	strcpy(s.fname, sNew.fname);
	strcpy(s.mname, sNew.mname);
	strcpy(s.sname, sNew.sname);
	strcpy(s.desc, sNew.desc);
	sPref.roll = sNew.roll;
	sPref.fnamesize = strlen(s.fname);
	sPref.mnamesize = strlen(s.mname);
	sPref.snamesize = strlen(s.sname);
	sPref.descsize = strlen(s.desc);
	int dataOffset;
	flag = lseek(indexfd,i*sizeof(int),SEEK_SET);
	if(flag==-1){
		perror("lseek() failed");
		exit(1);
	}
	flag  = read(indexfd,&dataOffset,sizeof(int));
	if(flag==-1 || flag!=sizeof(int)){
		perror("read() failed");
		exit(1);
	}
	flag = lseek(datafd,dataOffset,SEEK_SET);
	if(flag==-1){
		perror("lseek() failed");
		exit(1);
	}
	flag = write(datafd,&sPref,sizeof(struct studentPrefix));
	if(flag==-1 || flag!=sizeof(struct studentPrefix)){
		perror("write() failed");
		exit(1);
	}
	flag = write(datafd, s.fname,  sPref.fnamesize);
	if (flag == -1 || flag != sPref.fnamesize) {
		perror("write() failed");
		exit(1);
	}
	flag = write(datafd, s.mname,  sPref.mnamesize);
	if (flag == -1 || flag != sPref.mnamesize) {
		perror("write() failed");
		exit(1);
	}
	flag = write(datafd, s.sname,  sPref.snamesize);
	if (flag == -1 || flag != sPref.snamesize) {
		perror("write() failed");
		exit(1);
	}
	flag = write(datafd, s.desc,  sPref.descsize);
	if (flag == -1 || flag != sPref.descsize) {
		perror("write() failed");
		exit(1);
	}
	return 0;
} 
int compactionStudentRecords(int datafd, int indexfd){
	int flag;
	int count1;
	int count2;
	lseek(datafd,0,SEEK_SET);
	flag = read(datafd, &count1, sizeof(int));
	if (flag == -1 || flag != sizeof(int)) {	
		perror("read() failed");
		exit(1);
	}
	lseek(indexfd,0,SEEK_SET);
	flag = read(indexfd, &count2, sizeof(int));
	if (flag == -1 || flag != sizeof(int)) {
		perror("read() failed");
		exit(1);
	}
	if (count1 != count2) {
		fprintf(stderr, "counts in data and index files do not match!\n");
		exit(1);
	}
	return -1;
}

int sortRecordsAscenRoll(int datafd, int indexfd){
	int flag;
	int count1;
	int count2;
	struct studentPrefix sPref;
	lseek(datafd,0,SEEK_SET);
	flag = read(datafd, &count1, sizeof(int));
	if (flag == -1 || flag != sizeof(int)) {
		perror("read() failed");
		exit(1);
	}
	lseek(indexfd,0,SEEK_SET);
	flag = read(indexfd, &count2, sizeof(int));
	if (flag == -1 || flag != sizeof(int)) {
		perror("read() failed");
		exit(1);
	}
	if (count1 != count2) {
		fprintf(stderr, "counts in data and index files do not match!\n");
		exit(1);
	}
	if(count1<=1){
		printf("No need to sort as count = %d\n", count1);
		return 0;
	}
	int rolls[count1 + 1];
	int offsets[count1 + 1];
	for(int i=1;i<=count1;i++){
		int offset;
		flag = lseek(indexfd,i*sizeof(int),SEEK_SET);
		if(flag==-1){
			perror("lseek() failed");
			exit(1);
		}
		flag = read(indexfd,&offset,sizeof(int));
		if(flag==-1 || flag!=sizeof(int)){
			perror("read() failed");
			exit(1);
		}
		offsets[i] = offset;
		if(offset==-1){
			continue;
		}
		flag = lseek(datafd,offset,SEEK_SET);
		if(flag==-1){
			perror("lseek() failed");
			exit(1);
		}
		flag = read(datafd,&sPref,sizeof(struct studentPrefix));
		if(flag==-1 || flag!=sizeof(struct studentPrefix)){
			perror("read() failed");
			exit(1);
		}
		if(sPref.roll == -1){
			rolls[i] = INT_MAX;
		} else {
			rolls[i] = sPref.roll;
		}

		//Bubble Sort
		for(int i=1;i<=count1-1;i++){
			for(int j=1;j<=count1-i;j++){
				if(rolls[j]>rolls[j+1]){
					int tempRoll = rolls[j];
					rolls[j] = rolls[j+1];
					rolls[j+1] = tempRoll;

					int tempOffset = offsets[j];
					offsets[j] = offsets[j+1];
					offsets[j+1] = tempOffset;
				}
			}
		}

		for(int i=1;i<=count1;i++){
			flag = lseek(indexfd,i*sizeof(int),SEEK_SET);
			if(flag==-1){
				perror("lseek() failed");
				exit(1);
			}
			flag = write(indexfd,&offsets[i],sizeof(int));
			if(flag==-1 || flag!=sizeof(int)){
				perror("write() failed");
				exit(1);
			}
		}
	}
	return 0;
}
