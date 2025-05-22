//#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//trebuie sa folositi fisierul masini.txt
//sau va creati un alt fisier cu alte date

struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;

//1.
// structuri necesare
//dorim stocarea unui graf intr-o lista de liste
//astfel avem nod ListaPrincipala si NodListaSecundara


typedef struct NodListaPrincipala NodListaPrincipala;
typedef struct NodListaSecundara NodListaSecundara;

struct  NodListaPrincipala {
	NodListaPrincipala* next;
	NodListaPrincipala* vecini;
	Masina info;
};

struct NodListaSecundara {
	NodListaPrincipala* info;
	NodListaSecundara* next;
};

Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Masina m1;
	aux = strtok(buffer, sep);
	m1.id = atoi(aux);
	m1.nrUsi = atoi(strtok(NULL, sep));
	m1.pret = atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	m1.model = malloc(strlen(aux) + 1);
	strcpy(m1.model,  aux);

	aux = strtok(NULL, sep);
	m1.numeSofer = malloc(strlen(aux) + 1);
	strcpy(m1.numeSofer, aux);

	m1.serie = *strtok(NULL, sep);
	return m1;
}

void afisareMasina(Masina masina) {
	printf("Id: %d\n", masina.id);
	printf("Nr. usi : %d\n", masina.nrUsi);
	printf("Pret: %.2f\n", masina.pret);
	printf("Model: %s\n", masina.model);
	printf("Nume sofer: %s\n", masina.numeSofer);
	printf("Serie: %c\n\n", masina.serie);
}

//2.
//functii de inserare in liste
//si in principala si in secundara
NodListaPrincipala* inserareListaPrincipala(NodListaPrincipala* cap, Masina info) {
	NodListaPrincipala* nou=(NodListaPrincipala*)malloc(sizeof(NodListaPrincipala));
	nou->info=info;
	nou->vecini=NULL;
	nou->next=NULL;

//inseram la sfarsit
	if(!cap) {
		return nou;
	}

	NodListaPrincipala* p=cap;
	while (p->next)p=cap;
	p->next=nou;
	return cap;
};

NodListaSecundara* inserareListaSecundara(NodListaSecundara* cap, NodListaPrincipala* info) {
	NodListaSecundara* nou=(NodListaSecundara*)malloc(sizeof(NodListaSecundara));
	nou->info=info;
	nou->next=NULL;

//inseram la inceput
	if (cap) {
		nou->next=cap;
		cap=nou;
		return cap;
	}
};

//3.
//functie de cautarea in lista principala dupa ID
void* cautaNodDupaID(NodListaPrincipala* listaPrincipala, int id) {
	while(listaPrincipala && listaPrincipala->info.id != id) {
		listaPrincipala=listaPrincipala->next;
	}
	return listaPrincipala;
}

//4.
//inserare muchie
void inserareMuchie(NodListaPrincipala* listaPrincipala, int idStart, int idStop) {
		NodListaPrincipala* nodStart=cautaNodDupaID(listaPrincipala, idStart);
		NodListaPrincipala* nodStop = cautaNodDupaID(listaPrincipala, idStop);
		if (nodStart && nodStop) {
			nodStart->vecini=inserareListaSecundara(nodStart->vecini, nodStop);
			nodStop->vecini=inserareListaSecundara(nodStop->vecini, nodStart);
		}
}


void* citireNoduriMasiniDinFisier(const char* numeFisier) {
	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
	//prin apelul repetat al functiei citireMasinaDinFisier()
	//ATENTIE - la final inchidem fisierul/stream-ul

	NodListaPrincipala* listaPrincipala=NULL;
	FILE* f= fopen(numeFisier, "r");
	while (!feof(f)) {
		inserareListaPrincipala(listaPrincipala, citireMasinaDinFisier(f));
	}
	fclose(f);
	return listaPrincipala;
}

void citireMuchiiDinFisier(NodListaPrincipala* listaPrincipala,const char* numeFisier ) {
	//functia primeste numele fisierului, il deschide si citeste
	//toate id-urile de start si stop pentru fiecare muchie
	//ATENTIE - la final inchidem fisierul/stream-ul

	FILE* f = fopen(numeFisier, "r");
	while (!feof(f)) {
		int idstart;
		int idStop;
		fscanf(f, "%d %d", &idstart, &idStop );
		inserareMuchie(listaPrincipala, idstart, idStop);
	}
	fclose(f);
}

void stergeListaSecundara(NodListaSecundara** cap) {
	NodListaSecundara* aux=(*cap)->next;
	while ((*cap)) {
		aux=(*cap)->next;
		free(*cap);
		(*cap)=aux;
	}
}

void dezalocareNoduriGraf(NodListaPrincipala** listaPrincipala) {
	//sunt dezalocate toate masinile din graf
	//si toate nodurile celor doua liste

	NodListaPrincipala* aux;
	while (*listaPrincipala) {
		aux=(*listaPrincipala)->next;
		stergeListaSecundara((*listaPrincipala)->vecini);
		if (listaPrincipala) {
			free((*listaPrincipala)->info.model);
		}
		if (listaPrincipala) {
			free((*listaPrincipala)->info.numeSofer);
		}
		free(*listaPrincipala);
		*listaPrincipala=aux;

	}


}

int main() {

	NodListaPrincipala* graf= citireNoduriMasiniDinFisier("masini.txt") ;
	citireMuchiiDinFisier(graf, "muchii.txt");
	dezalocareNoduriGraf(&graf);
	return 0;
}
