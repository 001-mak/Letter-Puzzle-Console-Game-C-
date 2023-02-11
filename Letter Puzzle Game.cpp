//Letter puzzle game using DataStructures "STACK" concepts
#include<iostream>
#include <windows.h>
#include <time.h>
#include <cstdlib>
using namespace std;

	struct tube{
		char lvlArr[4]={' ', ' ', ' ', ' '};
		int top=-1;
	}tubeObj[10];

//GLOBAL VARIABLES
int moves=0;
char elements[5]={'A', 'B', 'C', 'D', 'E'};
int frequency[5]={0,0,0,0,0};
int homeScreenOption=0;
int bucketComplete=0;
int levelCheckFlag=0;
int level=1;
int totalBuckets=5;
int pushes=1;
int option;

//FUNCTIONS
void gameBeep();
void splashScreen();
void homeScreen();
void boarder();
void startGame();
void afterLevelCompletes();
void updateVariables();
void displayBucket();
void gameBoard();
char generateElement();
void populateTube();
void yourMove();
void push(char element, int index);
char pop( int index );
void loadingBar();
void setCursor(int x, int y);
void checkLevelComplete();
void instructions();

//MAIN FUNCTION
int main(){
	splashScreen();
	homeScreen();
	srand(time(NULL));

}


//DISPLAY FUNCTION
void displayBucket(){
	for(int i=3; i>=0; i--){
		for(int j=0; j<totalBuckets; j++){
			cout<<"\t";
			cout<<"| "<<tubeObj[j].lvlArr[i]<<" |";
		}
		cout<<"\n";
	}
	for(int i=0; i<totalBuckets ;i++){
		cout<<"\t";cout<<"-----";
	}
	cout<<"\n";
	for(int i=0; i<totalBuckets ;i++){
		cout<<"\t";cout<<" "<<"("<<i+1<<")"<<" ";
	}
}
//GAME BOARD FUNCTION
void gameBoard(){

	cout<<"\n\n\t***********************************\n\t***********LETTER PUZZLE***********\n\n"<<"\tMoves:"<<moves<<"\tLevel:"<<level<<"\n\n\n";
		displayBucket();
	}
char generateElement(){
	int randi = rand() % (totalBuckets-2);
	char randElement= elements[randi];
	frequency[randi]++;
	if(frequency[randi] < 5){
		return randElement;
	}
	else{
		generateElement();
	}
}

//POPULATE TUBE
void populateTube(){

	for(int i=0; i<totalBuckets-2; i++){
		for(int j=0;j<4;j++){
			 push(generateElement(),i);
		}
	}
}

//YOUR MOVE INPUTS
void yourMove(){
	int from=0, to=0;
	cout<<"\n\n\tYOUR MOVE" <<"\n"<<"\tEnter Bucket Numbers\n";
	cout<<"\tFrom Bucket:";
	cin>>from;
	cout<<"\tTo Bucket:";
	cin>>to;
	
	if(from==to){
		cout<<"\nInvalid Move";
		yourMove();
	}
	else if(from<1 || from>totalBuckets ){
		cout<<"\nInvalid Move";
		yourMove();
	}

	else if(to<1 || to>totalBuckets ){
		cout<<"\nInvalid Move";
		yourMove();
	}

	else if(tubeObj[from-1].top<0){
		Beep(523,500);
		cout<<"\nBucket is Empty";
		yourMove();
	}

	else if( tubeObj[to-1].top > 2 ){
		Beep(123,500);
		cout<<"\nBucket is Full\n";
		yourMove();
	}
	else{
		pushes=1;
		if( tubeObj[from-1].lvlArr[tubeObj[from-1].top-1] == tubeObj[from-1].lvlArr[tubeObj[from-1].top]){
			if(tubeObj[to-1].top < 2){
				pushes++;
			}
			if( tubeObj[from-1].lvlArr[tubeObj[from-1].top-2] == tubeObj[from-1].lvlArr[tubeObj[from-1].top]){
				if(tubeObj[to-1].top < 3){
					pushes++;
				}
		}
		}
		
		for(int i=0;i<pushes;i++){
			Beep(423,300);
			push( pop(from-1) , to-1);
		}
			moves++;
	}

//else{
//	Beep(423,300);
//	push( pop(from-1) , to-1);
//}
}

//PUSH FUNCTION
void push(char element, int index){
	if( tubeObj[index].top > 3 ){
		Beep(523,500);
		cout<<"\nBucket is Full\n";
		yourMove();
	}
	else{
		tubeObj[index].top++;
		tubeObj[index].lvlArr[tubeObj[index].top]= element;
	}
}

//POP FUNCTION
char pop( int index ){
	char popedelement;
	if(tubeObj[index].top<0){
		Beep(523,500);
		cout<<"\nBucket is Empty";
		yourMove();
	}
	else{
		popedelement=tubeObj[index].lvlArr[tubeObj[index].top];
		tubeObj[index].lvlArr[tubeObj[index].top]= ' ';
		tubeObj[index].top--;
		return popedelement;
	}
}

//SET CURSOR
void setCursor(int x, int y){
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

//LOADING BAR
void loadingBar(){
	setCursor(50,22);
    cout<<"LOADING";
	for(int i =2; i<102; i++){
		setCursor(i,23);
            cout<<"|";
            Sleep(20);
		}

	setCursor(0,0);
}

//CHECK IF LEVEL IS COMPLETED
void checkLevelComplete(){
	bucketComplete=0;
	for(int i=0; i<10; i++){
		if(tubeObj[i].lvlArr[0]==tubeObj[i].lvlArr[1]){
			if(tubeObj[i].lvlArr[1]==tubeObj[i].lvlArr[2]){
				if(tubeObj[i].lvlArr[2]==tubeObj[i].lvlArr[3]){
					bucketComplete++;
				}
			}

		}
	}
	if(bucketComplete==10){
		levelCheckFlag=1;
		system("CLS");
		gameBoard();
		gameBeep();
		Sleep(1500);
		system("CLS");
		level++;
		afterLevelCompletes();
	}
}

//SPLASH SCREEN
void splashScreen(){
	boarder();
	setCursor(50,9);
	cout<<"|B| |C|";
	setCursor(50,7);
	cout<<"  |A|   ";
	setCursor(47,11);
	cout<<"LETTER PUZZLE";
	Sleep(30);
	loadingBar();
	gameBeep();
	system("CLS");
}

//HOME SCREEN
void homeScreen(){
		  boarder();
		setCursor(43,7);
		cout<<"LETTER PUZZLE";

		setCursor(40,10);
		cout<<"Press 1. START GAME";

		setCursor(40,12);
		cout<<"Press 2. INSTRUCTIONS";

		setCursor(40,14);
		cout<<"Press 3. QUIT GAME";
		setCursor(40,16);
		cin>>homeScreenOption;
	if(homeScreenOption==1){
		startGame();
		}
	if(homeScreenOption==2){
		instructions();
	}

	if(homeScreenOption==3){
		return ;
	}
	else{
		system("CLS");
		homeScreen();
	}
}

//GAME BOARD BORDER
void boarder(){
	for(int i=0; i<104;i++){
	    	setCursor(i,0);
	    	cout<<".";
	    	setCursor(i,25);
	    	cout<<".";
		}

		for(int i=0; i<26;i++){
	    	setCursor(0,i);
	    	cout<<".";
	    	setCursor(103,i);
	    	cout<<".";
		}
}

void gameBeep(){
  Beep(294,300);  Beep(294,300); Beep(370,300);  Beep(494,300);
  Beep(370,300);  Beep(440,800);
}

//START GAME FUNCTION
void startGame(){
//	 srand(time(NULL));
		populateTube();

		levelCheckFlag=0;
		bucketComplete=0;
		while(levelCheckFlag!=1){
			system("CLS");
			gameBoard();
			yourMove();
			checkLevelComplete();
		}
}

void afterLevelCompletes(){

	boarder();
	setCursor(45,8);
	cout<< "LEVEL "<<level-1<<" COMPLETED!";
	setCursor(50,10);
	cout<<"MOVES: "<<moves;
	setCursor(29,14);
	cout<< "Press 1 for Next Level\t\tPress 2 for Home ";
	cin>>option;
	if(option==1){
		updateVariables();
		loadingBar();
		startGame();
	}
	if(option==2){
        loadingBar();
		main();
	}
	else{
		afterLevelCompletes();
	}
}

void updateVariables(){
	for (int i=0;i<5;i++){
		frequency[i]=0;
	}
	for(int i=0; i<totalBuckets;i++){
		tubeObj[i].top=-1;
		for(int j=0; j<4;j++){
			tubeObj[i].lvlArr[j]= ' ';
		}
	}
	if(level>1 && level<3){
	totalBuckets=6;
	}
	else if(level>5){
		totalBuckets=7;
	}
	moves=0;
}

void instructions(){
    system("CLS");
    int option;
    boarder();
    setCursor(25,10);
    cout<<"INSTRUCTIONS";
    setCursor(5,12);
    cout<<"1. THERE ARE 5 TO 7 BUCKETS FILLED WITH LETTTER FROM A-E";
    setCursor(5,13);
    cout<<"2. YOU HAVE TO FILL EACH BUCKET WITH SIMILAR LETTERS";
    setCursor(5,14);
    cout<<"3. ENTER THE BUCKET NUMBER FROM WHICH YOU WANT TO MOVE THE LETTER";
    setCursor(5,15);
    cout<<"4. ENTER THE BUCKET NUMBER TO WHICH YOU WANT TO AADD THE LETTER";
    setCursor(5,17);
    cout<<"PRESS 1 FOR HOME SCREEN  ";

    while(option!=1){
      cin>>option;
    }
    if(option==1){
        system("CLS");
        homeScreen();
    }
}
