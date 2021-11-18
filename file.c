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

void printConds(struct condidat *arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		printf("%d -> %s %s %s\n", i, arr[i].fname, arr[i].lname, arr[i].cin);
	}
}

void printElects(struct electeur *arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		printf("%d -> %s\n", i + 1, arr[i].cin);
	}
}

void main()
{
	int elecSize = 0, condSize = 0;
	struct electeur *electeurs;
	struct condidat *condidats;
	//system("clear");
	while (elecSize < elecMin)
	{
		printf("entrer le nombre des electeurs : ");
		scanf("%d", &elecSize);
		if (elecSize < elecMin)
			printf("le nombre des electeurs doit etre au moins 10\n");
		else
		{
			electeurs = (struct electeur *)malloc(elecSize * sizeof(struct electeur));
			for (int i = 0; i < elecSize; i++)
			{
				printf("entrer cin %d : ", i + 1);
				scanf("%s", &electeurs[i].cin);
			}
		}
	}
	while (condSize < condMin)
	{
		printf("entrer le nombre des cindidats : ");
		scanf("%d", &condSize);
		if (condSize < condMin)
			printf("le nombre des condidats doit etre au moins 5\n");
		else
		{
			condidats = (struct condidat *)malloc(condSize * sizeof(struct condidat));
			for (int i = 0; i < condSize; i++)
			{
				printf("entrer prenom %d : ", i + 1);
				scanf("%s", &condidats[i].fname);
				printf("entrer nom %d : ", i + 1);
				scanf("%s", &condidats[i].lname);
				printf("entrer cin %d : ", i + 1);
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
	int pass = 0, t1 = 0;
	struct condidat *nommT1;
	while (!t1)
	{
		int tour1[elecSize], in = 0, idx = -1;
		while (in < elecSize)
		{
			printf("%s vote pour : ", electeurs[in].cin);
			scanf("%d", &idx);
			if (idx < 0 || idx >= condSize)
				printf("veuillez choisir un numero parmi ceux affiches a l'ecran\n");
			else
			{
				tour1[in] = idx;
				in++;
			}
		}

		for (int i = 0; i < elecSize; i++)
			printf("%d ", tour1[i]);
		printf("\n");

		int score[condSize][2];
		float pourc[condSize];
		for (int i = 0; i < condSize; i++)
		{
			score[i][0] = i;
			score[i][1] = 0;
			for (int j = 0; j < elecSize; j++)
			{
				printf("tour1[%d] = %d || i = %d\n", j, tour1[j], i);
				if (i == tour1[j])
					score[i][1]++;
				printf("%d -> %d\n", score[i][0], score[i][1]);
			}
			printf("\n");
		}
		for (int i = 0; i < elecSize; i++)
			printf("%d ", tour1[i]);
		printf("\n");
		pass = 0;
		for (int i = 0; i < condSize; i++)
		{
			pourc[i] = (float)score[i][1] * 100 / elecSize;
			if (pourc[i] > 15.0)
				pass++;
			printf("%d has %d votes (%.3f%%)\n", score[i][0], score[i][1], pourc[i]);
		}
		in = 0;
		int diff = 0;
		while (diff == 0 && in < condSize - 1)
		{
			printf("\npourc[%d] : %f| pourc[%d] : %f", in, pourc[in], in + 1, pourc[in + 1]);
			if (pourc[in] != pourc[in + 1])
			{
				printf("\n***diff****\n");
				diff = 1;
				break;
			}
			in++;
		}
		printf("\ndiff = %d | in = %d | pass = %d\n", diff, in, pass);
		if (diff != 0)
		{
			nommT1 = (struct condidat *)malloc(pass * sizeof(struct condidat));
			int j = 0;
			for (int i = 0; i < condSize; i++)
			{
				if (pourc[i] > (float)15.0)
				{
					strcpy(nommT1[j].fname, condidats[i].fname);
					strcpy(nommT1[j].lname, condidats[i].lname);
					strcpy(nommT1[j].cin, condidats[i].cin);
					j++;
				}
			}
			t1 = 1;
		}
		else
			printf("**le premier tour sera refait (les condidats ont le meme nombre de votes**\n");
	}
	printf("liste des condidats nommines pour le deuxieme tour\n");
	printConds(nommT1, pass);
}
