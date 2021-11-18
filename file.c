#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define elecMin 10
#define condMin 5

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
		printf("** %d -> %s %s %s\n", i + 1, arr[i].fname, arr[i].lname, arr[i].cin);
	}
	printf("\n");
}

void printElects(struct electeur *arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		printf("** %d -> %s\n", i + 1, arr[i].cin);
	}
	printf("\n");
}

void main()
{
	int elecSize = 0, condSize = 0;
	struct electeur *electeurs;
	struct condidat *condidats;
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
	system("cls");
	printf("liste des electeurs:\n\n");
	printElects(electeurs, elecSize);
	printf("liste des condidats:\n\n");
	printConds(condidats, condSize);

	// tour 1
	int pass = 0, t = 0;
	struct condidat *nommT1;
	while (!t)
	{
		int tour1[elecSize], in = 0, idx = -1;
		while (in < elecSize)
		{
			printf("%s vote pour : ", electeurs[in].cin);
			scanf("%d", &idx);
			if (idx <= 0 || idx > condSize)
				printf("veuillez choisir un numero parmi ceux affiches a l'ecran\n");
			else
			{
				tour1[in] = idx - 1;
				in++;
			}
		}

		// for (int i = 0; i < elecSize; i++)
		// 	printf("%d ", tour1[i]);
		// printf("\n");

		int score[condSize][2];
		float pourc[condSize];
		for (int i = 0; i < condSize; i++)
		{
			score[i][0] = i;
			score[i][1] = 0;
			for (int j = 0; j < elecSize; j++)
			{
				// printf("tour1[%d] = %d || i = %d\n", j, tour1[j], i);
				if (i == tour1[j])
					score[i][1]++;
				// printf("%d -> %d\n", score[i][0], score[i][1]);
			}
		}
		// for (int i = 0; i < elecSize; i++)
		// 	printf("%d ", tour1[i]);
		// printf("\n");
		pass = 0;
		for (int i = 0; i < condSize; i++)
		{
			pourc[i] = (float)score[i][1] * 100 / elecSize;
			if (pourc[i] > (float)15.0)
				pass++;
			// printf("%s a %d votes (%.3f%%)\n", condidats[i].cin, score[i][1], pourc[i]);
		}
		in = 0;
		int diff = 0;
		while (diff == 0 && in < condSize - 1)
		{
			// printf("\npourc[%d] : %f| pourc[%d] : %f", in, pourc[in], in + 1, pourc[in + 1]);
			if (pourc[in] != pourc[in + 1])
			{
				diff = 1;
				break;
			}
			in++;
		}
		// printf("\ndiff = %d | in = %d | pass = %d\n", diff, in, pass);
		//system("clear");
		system("cls");
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
			t = 1;
		}
		else
		{
			printf("**le premier tour sera refait (les condidats ont le meme nombre de votes**\n\n");
			printConds(condidats, condSize);
			printf("\n");
		}
		for (int i = 0; i < condSize; i++)
		{
			printf("%s a %d votes (%.3f%%)\n", condidats[i].cin, score[i][1], pourc[i]);
		}
		printf("\n");
	}
	printf("liste des condidats nomines pour le deuxieme tour\n");
	printConds(nommT1, pass);
	//tour2
	struct condidat *nommT2;
	int condT2 = pass;
	t = pass = 0;
	while (!t)
	{
		int tour2[elecSize], idx, in = 0;
		while (in < elecSize)
		{
			printf("%s vote pour : ", electeurs[in].cin);
			scanf("%d", &idx);
			if (idx <= 0 || idx > condT2)
				printf("veuillez choisir un numero parmi ceux affiches a l'ecran\n");
			else
			{
				tour2[in] = idx - 1;
				in++;
			}
		}
		// for (int i = 0; i < elecSize; i++)
		// 	printf("%d ", tour2[i]);
		// printf("\n");
		int score[condT2][2];
		float pourc2[condT2];
		for (int i = 0; i < condT2; i++)
		{
			score[i][0] = i;
			score[i][1] = 0;
			for (int j = 0; j < elecSize; j++)
			{
				if (i == tour2[j])
					score[i][1]++;
			}
		}

		pass = 0;
		for (int i = 0; i < condT2; i++)
		{
			pourc2[i] = (float)score[i][1] * 100 / elecSize;
			if (pourc2[i] > (float)15.0)
				pass++;
			printf("%d has %d votes (%.3f%%)\n", score[i][0], score[i][1], pourc2[i]);
		}
		int diff = in = 0;
		while (diff == 0 && in < condT2 - 1)
		{
			if (pourc2[in] != pourc2[in + 1])
			{
				diff = 1;
				break;
			}
			in++;
		}
		//system("clear");
		system("cls");
		if (diff != 0)
		{
			nommT2 = (struct condidat *)malloc(condT2 * sizeof(struct condidat));
			int j = 0;
			for (int i = 0; i < condT2; i++)
			{
				if (pourc2[i] > (float)15.0)
				{
					strcpy(nommT2[j].fname, nommT1[i].fname);
					strcpy(nommT2[j].lname, nommT1[i].lname);
					strcpy(nommT2[j].cin, nommT1[i].cin);
					j++;
				}
			}
			t = 1;
		}
		else
		{
			printf("**le deuxieme tour sera refait (le condidats ont le meme nombre de votes**\n");
			printConds(nommT1, condT2);
			printf("\n");
		}
		for (int i = 0; i < condT2; i++)
		{
			printf("%s a %d votes (%.3f%%)\n", nommT2[i].cin, score[i][1], pourc2[i]);
		}
		printf("\n");
	}
	if (pass != 1)
	{
		//tour3
		printf("list des condidats nomines pour le troisieme tour\n");
		printConds(nommT2, pass);
		int condT3 = pass;
		t = pass = 0;
		while (!t)
		{
			int tour3[elecSize], idx, in = 0;
			while (in < elecSize)
			{
				printf("%s vote pour : ", electeurs[in].cin);
				scanf("%d", &idx);
				if (idx <= 0 || idx > condT3)
					printf("veuillez choisir un numero parmi ceux affiches a l'ecran\n");
				else
				{
					tour3[in] = idx - 1;
					in++;
				}
			}
			int score[condT3][2];
			float pourc3[condT3];
			for (int i = 0; i < condT3; i++)
			{
				score[i][0] = i;
				score[i][1] = 0;
				for (int j = 0; j < elecSize; j++)
				{
					if (i == tour3[j])
						score[i][1]++;
				}
			}
			pass = 0;
			for (int i = 0; i < condT3; i++)
			{
				pourc3[i] = (float)score[i][1] * 100 / elecSize;
				if (pourc3[i] > (float)15.0)
					pass++;
				// printf("%d has %d votes (%.3f%%)\n", score[i][0], score[i][1], pourc3[i]);
			}
			printf("\npourc\n");
			// for (int i = 0; i < condT3; i++)
			// {
			// 	printf("i = %d | pourc i = %.3f\n", i, pourc3[i]);
			// }
			int maxIdx = 0;
			for (int i = 1; i < condT3; i++)
			{
				if (pourc3[i] > pourc3[maxIdx])
					maxIdx = i;
			}
			printf("\nmaxid = %d\n", maxIdx);
			int found = 0, i = 0;
			while (!found && i < condT3)
			{
				printf("pourc[%d] %.3f | maxid %d | pourc[maxid] %.3f\n", i, pourc3[i], maxIdx, pourc3[maxIdx]);
				if (i != maxIdx && pourc3[i] == pourc3[maxIdx])
					found++;
				i++;
			}
			//system("clear");
			system("cls");
			for (int i = 0; i < condT3; i++)
			{
				printf("%s a %d votes (%.3f%%)\n", nommT2[i].cin, score[i][1], pourc3[i]);
			}
			printf("\n");
			if (found)
			{
				printf("**le troisieme tour sera refait (au moins deux conidat ont le meme nombre de votes**\n");
				printConds(nommT2, condT3);
				printf("\n");
			}
			else
			{
				printf("**le condidat elu a la presidence depuis le troisieme tour : \n\n");
				printf("%s\t%s\t%s\n\n", nommT2[maxIdx].fname, nommT2[maxIdx].lname, nommT2[maxIdx].cin);
				t = 1;
			}
		}
	}
	else
	{
		printf("**le condidat elu a la presidence depuis le deuxieme tour : \n");
		printf("%s\t%s\t%s", nommT2[0].fname, nommT2[0].lname, nommT2[0].cin);
	}
}
