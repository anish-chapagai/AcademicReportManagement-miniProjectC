#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <math.h>

//COLOUR DEFINITIONS
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define RESET   "\x1b[0m"

FILE *fptr;
void about();
void editRec();
void deleteRecord();
void makeUpper(char []);
void add();
void showFrame();
void divCalculation();
void percentCalculation();
char menu();
void show();
void tabulate();
void writeData();

char sub[6][15]={"PHYSICS","DRAWING","APPLIED","MATHS","PROGRAMMING","ELECTRICAL"};
int delRoll,stat;

struct  person{
	char name[20];
	char depart[4],pas;
	char div[6];
	int roll;
	float perc;
	int marks[6];	//physics,drawing,applied,maths,programming,electrical
}p;
int main(){
	start:
	switch(menu()){
		case '1':
		add();
		writeData();	//writes above information to a file
		break;
		
		case '2':
			editRec();
			fclose(fptr);
		break;
		
		case '3':
		deleteRecord();
		break;
		
		case '4':
		show();
		fclose(fptr);
		printf(YELLOW"\nPress any key to return to main menu..."RESET);
		getch();
		break;
		
		case '5':
		tabulate();
		break;
		
		case '6':
		about();
		break;
		
		case '7':
		printf(GREEN"\n\n\n\n\n\n\t\t\t\t\tThank you for using the program...\n\n\n"RESET);
		exit(0);
		break;
		
		default:
		system("cls");
		printf(RED"\a\n\n\n\t\t\tInvalid Choice....\n\t\t\t\tEnter Valid Choice..."RESET);;
		Sleep(1000);
		break;
	}
	goto start;
}

//add function
void add(){
	int i=0;
	p.perc=0;
	system("cls");
	printf(YELLOW"Enter name: ");
	scanf("%s",p.name);	//name
	
	makeUpper(p.name);
	
	printf("Enter Roll number: ");
	scanf("%d",&p.roll);	//roll

	printf("Enter Department: ");	//depart
	scanf("%s",p.depart);
	i=0;
	makeUpper(p.depart);
	
	printf("Enter marks of:\n");
	
	for(i=0;i<6;i++){
	printf("\t%s: ",sub[i]);		//takes makes of 6 subjects
	scanf("%d",&p.marks[i]);
	}
	fflush(stdin);

	percentCalculation();

	divCalculation();

	system("cls");
}

//menu function
char menu(){
	system("cls");
		printf(BLUE" \t-----------------------------------------------------------\n");
		printf("\t|\t\t    WRC RESULT SHEET                      |\n");
		printf("\t-----------------------------------------------------------\n");
		printf("\t|   1) ADD NEW RECORD\t        | 2) EDIT EXISTING RECORD |\n");
		printf("\t-----------------------------------------------------------\n");
		printf("\t|   3) DELETE EXISTING RECORD\t| 4) SHOW EXISTING RECORD |\n");
		printf("\t-----------------------------------------------------------");
		printf("\n\t|   5) TABULATE DATA            |  6) About developer     |");
		printf("\n\t-----------------------------------------------------------");
		printf("\n\t|   7) Exit Program  |");
		printf("\n\t----------------------");
		printf(" \n==>");
		return(getch());
}

//show function
void show(){
	int i,rol,j;
	char nam[20];
	//checks for existence of record...if not returns to menu
	if(fopen("studentProfile.txt","r")==NULL){
		printf(RED"\a\n\n\t\t\tNo record...Add record first..."RESET);
		Sleep(1000);
		return;
	}
	
	//I_DONT_KNOW_WHAT_THESE_IMMEDIATE_TWO_LINES_DO_BUT_THEY_SEEM_TO_SOLVE_THE_PROBLEM
	fptr = fopen("StudentProfile.txt","a+");
	fclose(fptr);
	
	fopen("studentProfile.txt","a+");
	rewind(fptr);
	choose:
	system("cls");
	printf(YELLOW"Search options:\n\t1) By name\n\t2) By roll number\n\t==>");
	scanf("%d",&i);
		if (i==2){
		system("cls");
		printf("Enter the Roll number of the student: ");
		scanf("%d",&rol);
		system("cls");
		fseek(fptr,0,SEEK_SET);//cursor to initial position
		while(fread(&p,sizeof(p),1,fptr) || getc(fptr)!=EOF){
			if (p.roll==rol){
				delRoll = rol; //saves info for deletion
				system("cls");
				stat=1;		
				showFrame();
				break;
			}
		}
		if(stat == 0){
			printf(RED"\n\n\n\t\t\t\t\t\aNo record with Roll number: %d"RESET,rol);
			Sleep(1000);
			return;
			}
		}
		else if (i==1){
			system("cls");
			printf("Enter the name of the student: ");
			scanf("%s",nam);
			makeUpper(nam);
			fseek(fptr,0,SEEK_SET);//cursor to initial position
			system("cls");
			while(fread(&p,sizeof(p),1,fptr) || getc(fptr)!=EOF){
				if (strcmp(nam,p.name)==0){
					delRoll = p.roll;	//saves info for deletion
					showFrame();
					stat=1;			//FUNCTION TO SHOW THE RESPECTIVE DETAILS
					break;
				}
			}
		if(stat ==0){
			printf("\n\n\n\t\t\t\t\t\aNo record with name:  %s",nam);
			Sleep(1000);
			return;
		}
	}
	else{
		system("cls");
		printf("\a\n\n\t\t\t\tInvalid  Option...");
		fflush(stdin);
		Sleep(1000);
		goto choose;
	}
}

void tabulate(){
	fptr=fopen("studentProfile.txt","r");
	if(fptr==NULL){
		printf(RED"\n\t\t\t\t\aNo profile to show....Add some records first"RESET);
		Sleep(1000);
		return;
	}
	system("cls");
	printf(BLUE"****************************************************************************************************************************");
	printf("\n|\t\t\t\t\t\tSTUDENT RECORD\t\t\t\t\t                           |");
	printf("\n|**************************************************************************************************************************|");
	//printf("\n\t\t|Name: %s\t\t\tRoll no.: %d\t\t\tDepartment: %s");
	//printf("\n\t\t********************************************************************************************************");
	printf("\n|Student Name| Roll No. |\t\t\tMarks\t\t\t            |   Percentage   |   Division   |Status|");
	printf("\n|***********************************************************************************|****************|**************|******|");
	printf("\n|\t     |          |Physics | Drawing | Programming | Applied | Basic-E | Maths|                |              |      |");
	printf("\n|            |          |***********************************************************|                |              |      |");
	
	fseek(fptr,0,SEEK_SET);		//SETS CURSOR TO INITIAL POSITION
	while(fread(&p,sizeof(p),1,fptr) || getc(fptr)!=EOF){
		printf("\n|%12s|%8d  |%7d | %7d | %11d | %7d | %7d | %5d|   %11.2f  |   %7s    |  %c   |",p.name,p.roll,p.marks[0],p.marks[1],p.marks[2],p.marks[3],p.marks[4],p.marks[5],p.perc,p.div,p.pas);
		printf("\n|**************************************************************************************************************************|");
	}
	fclose(fptr);
	getch();
}

void divCalculation(){
	int j;
	p.pas='P';
	//CHECKING IF STUDENT HAS FAILED ANYONE OF THE SUBJECTS
	for(j=0;j<6;j++){
		if(p.marks[j] < 40){

			strcpy(p.div,"FAILED");
			p.pas='F';
			break;
		}
	}
		//SETTING DIVISION AND STATUS
		switch((int)ceil(p.perc/10)){
			case (10||9):
			strcpy(p.div,"DIST");
			break;
			case 8:
			strcpy(p.div,"SECOND");
			break;
			case 7:
			strcpy(p.div,"THIRD");
			break;
			case 6:
			strcpy(p.div,"FOURTH");
			break;
			case 5:
			strcpy(p.div,"FIFTH");
			break;
			default:
			if(p.perc==40){
			strcpy(p.div,"PASSED");
			}
			else{
				strcpy(p.div,"FAILED");
				p.pas='F';
			}
			break;
	}
}
void showFrame(){
	int j;
			printf(BLUE"\t\t\t\t --------------\n");
			printf("\t\t\t\t|STUDENT STATUS|\n");
			printf("\t-------------------------------------------------------------\n");
			printf("\t|Name:%16s     |  Roll: %3d\t|  Department: %s  |\n",p.name,p.roll,p.depart);
			printf("\t-------------------------------------------------------------");
			printf("\n\n\t\t--------------------------------------");
			printf("\n\t\t|  Subjects\t\t   |   Marks |");
			printf("\n\t\t--------------------------------------");
			
			for ( j = 0; j < 6; j++){
			printf("\n\t\t|  %s \t",sub[j]);
			printf("\t   |  %d     |",p.marks[j]);
			printf("\n\t\t--------------------------------------");
			}

			printf("\n\t\t---------------------------");
			printf("\n\t\t|  PERCENTAGE:    |  %.2f%     |\n",p.perc);
			printf("\t\t---------------------------\n");
			printf("\t\t|  DIVISION:      | %6s| ",p.div);
			printf("\n\t\t---------------------------\n"RESET);
}
void makeUpper(char target[]){			//makes strings uppercase
	int j=0;
		while(target[j]!='\0'){
			target[j]=toupper(target[j]);
			j++;
		}
}
void deleteRecord(){
	int j;
	FILE *fptr1;
	char ch;
	system("cls");
	printf(RED"DELETE OPTIONS: \n\t1)Delete Specific Record\t2)Delete all record\t==>");
	if(getch() == '2'){
		system("cls");
		if(remove("studentProfile.txt")==0){	
		printf(GREEN"\t\t\tDeleted Successfully"RESET);
		}
		else{
			printf("\t\t\tDeletion error....Cannot delete file"RESET);
			Sleep(1000);
		}
		return;
	}
	show();
	printf("%d",stat);
	getch();
	if(stat == 0){
		return;
	}			
	fclose(fptr);

	babe:
	printf(RED"\n\nDo you want to delete this record?(Y/N)\n==>"RESET);
	fflush(stdin);
	ch=getch();
	system("cls");
	if(toupper(ch) == 'N'){
		printf(GREEN"\n\n\t\t\t\tDeletion Cancelled"RESET);
		Sleep(1000);
		return;
	}
	else if (toupper(ch) == 'Y'){
		fptr =fopen("studentProfile.txt","r+");
		fptr1=fopen("temp.txt","w");
		rewind(fptr);
		while(fread(&p,sizeof(p),1,fptr) || fgetc(fptr)!=EOF){		//copies all the contents of original file except the record to be deleted to another file
			if(p.roll!=delRoll){
				fwrite(&p,sizeof(p),1,fptr1);
			}
		}
		fclose(fptr1);
		fclose(fptr);
		
		fptr =fopen("studentProfile.txt","w");
		fptr1=fopen("temp.txt","r+");
		rewind(fptr1);
		while(fread(&p,sizeof(p),1,fptr1) || fgetc(fptr1)!=EOF){		//copies the updated data to original file...I didnt just removed the orig
				fwrite(&p,sizeof(p),1,fptr);							//file and renamed the temp to studentProfile because it didnt operate
		}
	fclose(fptr1);
	fclose(fptr);
	printf(GREEN"\n\n\n\t\t\t\t\tDELETION SUCCESSFUL......"RESET);
	Sleep(1000);
	}
	else{
		printf(RED"\n\n\n\t\t\t\t\t/aEnter valid option...."RED);
		Sleep(1000);
		system("cls");
		goto babe;
	}
}

void editRec(){
	int cursorVal,j,tempRol,tempMarks[6];
	char tempName[20],tempDepart[3];
	show();

	if(stat == 0)
		return;
	cursorVal= ftell(fptr); //records the cursor position of the record
	fclose(fptr);
	
	fptr=fopen("studentProfile.txt","r+");
	
	darlin:
	printf(YELLOW"\n\t\t\t\t\tEdit options:\n");
	printf("\t\t1) Edit name\t2)Edit Roll\t\t3)Edit Department\n\t\t4)Edit Marks\t5)Edit Whole Record\t6)Exit Editing\n==>");
	switch(getch()){
		case '1':
			printf("Enter New Name: ");
			scanf("%s",tempName);
			makeUpper(tempName);
			strcpy(p.name,tempName);
			break;
		case '2':
			printf("Enter new Roll: ");
			scanf("%d",&tempRol);
			p.roll=tempRol;
			break;
		case '3':
			printf("Enter department: ");
			scanf("%s",tempDepart);
			strcpy(p.depart,tempDepart);
			break;
		case '4':
		printf("Enter marks of: \n");
			for(j=0;j<6;j++){
			printf("\t%s: ",sub[j]);		//takes marks of resp subject
			scanf("%d",&tempMarks[j]);
			p.marks[j]=tempMarks[j];
			}
			percentCalculation();
			divCalculation();
			break;
		case '5':
			add();
			break;
		case '6':
		fclose(fptr);
		return;
			break;

		default:
			printf(RED"\a\n\n\t\t\t\tEnter Valid option"RESET);
			goto darlin;
			break;
	}
	//fseek(fptr,-cursorVal,SEEK_CUR);	//sets sursor to initial position of current structure
	fwrite(&p,sizeof(p),1,fptr);		//overwrites the previous structure with updated one
	stat=0; 
	system("cls");
	printf(GREEN"\n\n\n\t\t\tEDITING SUCCESSFUL...."RESET);  //sets the availibility reference variable to initial state.. if its not changed then it will allow options for edit even if the record doesbt match
	Sleep(1000);
	system("cls");
	goto darlin;
}
void writeData(){
	if(fopen("studentProfile.txt","r+b")==NULL){
	fptr = fopen("studentProfile.txt","w+b");
	fclose(fptr);
	printf("NO FILE");}
	//WRITES
	fptr=fopen("studentProfile.txt","a+");
	fwrite(&p,sizeof(p),1,fptr);
	fclose(fptr);
	system("cls");
	printf(GREEN"\t\tProfile Added Successfully..."RESET);
	Sleep(1000);
}
void percentCalculation(){
	int j;
	p.perc=0;
	//percent calculation
		for(j=0;j<6;j++){
			p.perc += p.marks[j];
		}
		p.perc = p.perc/6;
}

//UNDER CONSTRUCTION
void about(){							//contains little animation although its not     
	char ch, lang1[8]={"About Us"};
	int j,k=0,l=0,m;
	system("cls");
		for(j=0;j<=40;j++){
			printf(BLUE"*");
			Sleep(30);
			while(l<8 && j ==20){
				printf(YELLOW"%c",lang1[l]);
				Sleep(100);
				l++;
				}
			}
			
		char lan[]={"\nDeveloped by: Anish Chapagai\nRoll No: 4\nDepartment: BCT\nYear: I/I\nDeveloped in: Approximately 1 day\n"};
		for(l=0;lan[l]!='\0';l++){
			if(lan[l]=='\n'){
				printf(BLUE"\n");
				for(j=1;j<=(l-m);j++){
					printf("*");
					Sleep(50);
				}
				m=l;
			}
			printf(YELLOW"%c",lan[l]);
			Sleep(40);
		}
		//creates a voice file
		//voice script is a vbs script only works for windows machines
		//i didn't do error handling when it's being used by other machines except windows
		if((fptr=fopen("voice.vbs","r"))==NULL){
			char lang[]={"Set Sapi = Wscript.CreateObject(\"SAPI.SpVoice\")\ndim str\nSapi.speak \"Redirecting to his blog for more information in 10 seconds\""};
			fptr=fopen("voice.vbs","w");
			fwrite(&lang,sizeof(lang),1,fptr);
			fclose(fptr);
		}
		printf(RED"\nRedirecting to his blog for more information in: ");
		system("voice.vbs");
		k=0;
		for(j=10;j>=0;j--){
			printf("%4d",j);
			Beep(1000,500);
			Sleep(500);
		}
		system("explorer https://www.anishchapagai.com.np");
		printf(GREEN"\nPress any key to return to main menu....");
		getch();
	}
