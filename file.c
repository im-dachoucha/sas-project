#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define elecMin 2
#define condMin 2

// typedef struct condidat
// {
// 	char* fname;
// 	char* lname;
// 	char* cin;
// } Cond ;

struct condidat
{
	char fname[100];
	char lname[100];
	char cin[8];
};
// typedef struct electeur
// {
// 	char* cin;
// } Elect ;
struct electeur
{
	char cin[8];
};

//int checkElec(Elect* arr, int size, char* cin){
	//for(int i = 0; i < size; i++){
		//if(strcmp(arr[i].cin, cin) == 0) return 1;
	//}
	//return 0;
//}

void printConds(struct condidat* arr, int size){
	for(int i = 0; i < size; i++){
		printf("%d -> %s %s %s\n", i, arr[i].fname, arr[i].lname, arr[i].cin);
	}
}

void printElects(struct electeur* arr, int size){
	for(int i = 0; i < size; i++){
		printf("%d -> %s\n", i+1, arr[i].cin);
	}
}

void main(){
	int elecSize=0, condSize=0;
	struct electeur* electeurs;
	struct condidat* condidats;
  //system("clear");
	while(elecSize < elecMin){
		printf("entrer le nombre des electeurs : ");
		scanf("%d", &elecSize);
		if(elecSize < elecMin) printf("le nombre des electeurs doit etre au moins 10\n");
		else{
			electeurs = (struct electeur*)malloc(elecSize * sizeof(struct electeur));
			for(int i = 0; i < elecSize; i++){
				printf("entrer cin %d : ", i+1);
				scanf("%s", &electeurs[i].cin);
			}
		}
	}
	while(condSize < condMin){
		printf("entrer le nombre des cindidats : ");
		scanf("%d", &condSize);
		if(condSize < condMin) printf("le nombre des condidats doit etre au moins 5\n");
		else{
			condidats = (struct condidat*)malloc(condSize * sizeof(struct condidat));
			for(int i = 0; i < condSize; i++){
				printf("entrer prenom %d : ", i+1);
				scanf("%s", &condidats[i].fname);
				printf("entrer nom %d : ", i+1);
				scanf("%s", &condidats[i].lname);
				printf("entrer cin %d : ", i+1);
				scanf("%s", &condidats[i].cin);
			}
		}
	}
  //system("clear");
  printf("liste des electeurs:\n");
	printElects(electeurs, elecSize);
  printf("liste des condidats:\n");
	printConds(condidats, condSize);
	// tour 1
  int tour1[elecSize], in=0, idx=-1;
  while(in < elecSize){
    printf("%s vote pour : ", electeurs[in].cin);
    scanf("%d", &idx); 
    if(idx < 0 || idx >= condSize) printf("veuillez choisir un numero parmi ceux affiches a l'ecran\n");
    else {tour1[in] = idx; in++;}
  }
  
  for(int i = 0; i < elecSize; i++) printf("%d ", tour1[i]);
  printf("\n");

  //int score[condSize][2];
  //for(int i = 0; i < condSize; i++){
    //score[i][0] = i;
    //score[i][1] = 0;
    //for(int j = 0; j < elecSize; j++){
      //if(tour1[j] == i) score[i][1]++;
    //}
  //}

  int score[condSize][2];
  for(int i = 0; i < condSize; i++){
    score[i][0] = i;
    score[i][1] = 0;
    for(int j = 0; j < elecSize; j++){
      printf("tour1[%d] = %d || i = %d\n", j, tour1[j], i);
      if(i == tour1[j]) score[i][1]++;
      printf("%d -> %d\n", score[i][0], score[i][1]);
    }
    printf("\n");
  }
  for(int i = 0; i < elecSize; i++) printf("%d ", tour1[i]);
  printf("\n");
  for(int i = 0; i < condSize; i++) printf("%d has %d votes (%.3f%%)\n", score[i][0], score[i][1], (float)score[i][1]*100/elecSize);

}
