_CRT_SECURE_NO_WARNINGS;
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Bovina {
	char* rasa[50];
	char* origine[50];
	int sperantaDeViata;
	float greutate;
};
struct Nod {
	 Bovina info;
	 Nod* urmator;
};
struct HashTable {
	int size;
	Nod** v;
};
typedef struct Bovina Bovina;
typedef struct Nod Nod;
typedef struct HashTable HashTable;

HashTable adaugareInHashTable(HashTable ht, Bovina b) {
}

void adaugaBovineInLista(Nod* v, Bovina b) {
	if (v == NULL) {
		return;
	}
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = b;
	nou->urmator = NULL;
	while (v->urmator != NULL) {
		v = v->urmator;
	}
	v->urmator = nou;
}

void afisareListaBovine(Nod* v) {
	while (v != NULL) {
		afisareBovine(v->info);
		v = v->urmator;
	}
}

Bovina citireBovineDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	char* aux;
	Bovina b;
	fgets(buffer, sizeof(buffer), file);
	 aux = strtok(buffer, sep);
	 b.rasa = malloc(strlen(aux) + 1);
	 strcpy_s(b.rasa, strlen(aux) + 1, aux);
	 aux = strtok(NULL, sep);
	 b.origine = malloc(strlen(aux) + 1);
	 strcpy_s(b.origine, strlen(aux) + 1, aux);
	 b.greutate = atoi(strtok(NULL, sep));
	 b.sperantaDeViata = atoi(strtok(NULL, sep));
	 return b;
}
// Bovina initializare(char rasa[], char origine[], int sperantaDeViata, float greutate) {
//	struct Bovina b;
//	strcpy_s(b.rasa, sizeof(b.rasa), rasa);
//	strcpy_s(b.origine, sizeof(b.origine), origine);
//	b.sperantaDeViata = sperantaDeViata;
//	b.greutate = greutate;
//
//	return b;
//}

void modificaOrigine( Bovina* b, char origineNoua[]) {
	if(origineNoua != NULL)
		strcpy_s(b->origine, sizeof(b->origine), origineNoua);
}

void afisareBovine( Bovina b) {
	printf("Rasa: %s\nOrigine: %s\nSperanta de viata: %d\nGreutate: %5.2f\n\n\n\n", b.rasa, b.origine, b.sperantaDeViata, b.greutate);
}

void cantitateComestibila( Bovina b) {
	float cantitate = 0.5 * b.greutate;
	printf("Cantitatea comestibila este de %5.2f kg\n", cantitate);
}
HashTable initializeHashTable(int dim) {
	HashTable ht;
	ht.size = dim;
	ht.v = (Nod**)malloc(dim * sizeof(Nod*));
	for (int i = 0; i < dim; i++) {
		ht.v[i] = NULL;
	}
	return ht;
}
int calculeazaHash(const char* origine, int dim) {
	int suma = 0;
	if (dim == 0) {
		return 0;
	}
	for (int i = 0; i < strlen(origine); i++) {
		suma += origine[i];
	}
	return suma % dim;
}
void insereazaBovinaInHashTable(HashTable ht, Bovina b) {
	int poz = calculeazaHash(b.origine, ht.size);
	if (ht.v[poz] == NULL) {
		ht.v[poz] = (Nod*)malloc(sizeof(Nod));
		ht.v[poz]->info = b;
		ht.v[poz]->urmator = NULL;
	}
	else {
		Nod* nou = (Nod*)malloc(sizeof(Nod));
		nou->info = b;
		nou->urmator = ht.v[poz];
		ht.v[poz] = nou;
	}

}

void filtreazaGreutate( Bovina* b, int n) {
	float greutateMaxima;
	printf("Introduceti greutatea maxima: ");
	scanf_s("%f", &greutateMaxima);
	for (int i = 0; i < n; i++) {
		if (b[i].greutate <= greutateMaxima) {
			afisare(b[i]);
		}
	}
}


int conditieGreutate( Bovina b, float greutateMaxima) {
	return b.greutate > greutateMaxima;
}

void greutateGresita( Bovina* b, int n,  Bovina** vectorNou, int* m, float greutateMaxima) {
	*m = 0;
	*vectorNou = (struct Bovina*)malloc(n * sizeof(struct Bovina));
	if (*vectorNou == NULL) {
		printf("Eroare la alocarea memoriei");
		return;
	}

	for (int i = 0; i < n; i++) {
		if (!conditieGreutate(b[i], greutateMaxima)) {
			(*vectorNou)[*m] = b[i];
			(*m)++;
		}
	}

	*vectorNou = ( Bovina*)realloc(*vectorNou, (*m) * sizeof( Bovina));
	if (*vectorNou == NULL && *m > 0) {
		printf("Eroare la realocarea memoriei");
	}
}


void citireDeLaTastatura( Bovina* b) {
	printf("Rasa: ");
	gets_s(b->rasa, sizeof(b->rasa));
	printf("Origine: ");
	gets_s(b->origine, sizeof(b->origine));
	printf("Speranta de viata: ");
	scanf_s("%d", &b->sperantaDeViata);
	printf("Greutate: ");
	scanf_s("%f", &b->greutate);
}

int main() {
	/* Bovina b = initializare("Holstein", "Olanda", 20, 500);
	afisare(b);
	modificaOrigine(&b, "Germania");
	afisare(b);

	Bovina* vaci = (Bovina*)malloc(5 * sizeof(Bovina));
	if (vaci == NULL) {
		printf("Eroare la alocarea memoriei");
		return 1;
	}

	for (int i = 0; i < 5; i++) {
		vaci[i] = initializare("Rasa", "Origine", 10, 300);
		afisare(vaci[i]);
	}

	cantitateComestibila(b);
	free(vaci);*/
	return 0;
}
