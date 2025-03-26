#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;

struct Nod {
	Masina info;
	struct Nod* urmator;
	struct Nod* precedent;
};
typedef struct Lista Lista;
typedef struct Nod Nod;


struct Lista {
	Nod* prim;
	Nod* ultim;
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
	strcpy_s(m1.model, strlen(aux) + 1, aux);
	aux = strtok(NULL, sep);
	m1.numeSofer = malloc(strlen(aux) + 1);
	strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);
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

void afisareListaMasini(Lista lista) {
	Nod* p = lista.prim;
	while (p) {
		afisareMasina(p->info);
		p = p->urmator;
	}
}

void adaugaMasinaInLista(Lista* lista, Masina masinaNoua) {
	Nod* p = (Nod*)malloc(sizeof(Nod));
	p->info = masinaNoua;
	p->urmator = NULL;
	p->precedent = lista->ultim;
	if (lista->ultim != NULL) {
		lista->ultim->urmator = p;
	}
	else {
		lista->prim = p;
	}
	lista->ultim = p;
}

void adaugaLaInceputInLista(Lista* lista, Masina masinaNoua) {

	Nod* p = (Nod*)malloc(sizeof(Nod));
	p->info = masinaNoua;
	p->urmator = lista->prim;
	p->precedent = NULL;
	if (lista->prim){
		lista->prim->precedent=p;
	}
	else {
		lista->ultim = p;
	}
	lista->prim = p;
}

Lista citireLDMasiniDinFisier(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	Lista lista;
	lista.prim = NULL;
	lista.ultim = NULL;
	while (!feof(f)) {
		adaugaLaInceputInLista(&lista, citireMasinaDinFisier(f));
	}
	fclose(f);
	return lista;
}

void afisareListaMasiniInvers(Lista lista) {
	Nod* p = lista.ultim;
	while (p) {
		afisareMasina(p->info);
		p = p->precedent;
	}
}

void dezalocareLDMasini(Lista* lista) {
	Nod* p = lista->prim;
	while (p->urmator!=NULL) {
		free(p->info.model);
		free(p->info.numeSofer);
		
		p = p->urmator;
		free(p->precedent);
	}
	free(p->info.model);
	free(p->info.numeSofer);
	free(p);
	lista->prim = NULL;
	lista->ultim = NULL;
}

float calculeazaPretMediu(Lista lista) {
	Nod* aux = lista.prim;
	float suma = 0, cnt = 0;
	while (aux) {
		suma += aux->info.pret;
		cnt++;
			aux = aux->urmator;
	}
	return suma;
}

int main() {
	Lista lista;
	lista = citireLDMasiniDinFisier("masini.txt");
	afisareListaMasini(lista);
	float pretMediu = calculeazaPretMediu(lista);
	printf("pret mediu: %.2f\n", pretMediu);
	dezalocareLDMasini(&lista);
	return 0;
}
