/*************************************************************************/
/* CT60A2600 Ohjelmakehitys C-kielellä
* Tiimi: 13
* Tekijä: Severi Arpinen, Antti Keronen, Juuso Käyhkö
* Opiskelijanumero: 000253077, 001855050, 000493675
* Päivämäärä: 09.03.2025
* Tämän ohjelman tekemisessä on käytetty kurssilla annettujen materiaalien
* ja ohjeiden lisäksi seuraavia lähteitä, työkaluja ja henkilöitä:
* https://www.geeksforgeeks.org/bubble-sort-algorithm/
* https://www.geeksforgeeks.org/insertion-sort-algorithm/
* Käytetyn aputyökalun nimi ja versio tai henkilön nimi
* Käytön tarkoitus:
* Bubblesort ja insertion sort algoritmin oppiminen ja ymmärtäminen, kuinka sen voi implementoida
* meidän projektiin
* Yksityiskohtainen selvitys siitä, missä ohjelman osissa aputyökalua on
* käytetty ja miten, tai miten ko. henkilö on vaikuttanut ohjelmaan:
* Algoritmien ymmärtäminen vaadittiin ohjelman kirjoittamiseen.
*/
/*************************************************************************/
/* Tehtävä L10, tiedoston nimi linkitettyListakirjasto.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "linkitettyListaKirjasto.h"



Node *lisaaNode(Node *listanHead, char *nimi, int maara) { // lisää listaan uuden noden
    Node *uusi = (Node *)malloc(sizeof(Node));
    if (!uusi) {
        printf("Muistin varaus epäonnistui.\n");
        return listanHead;
    }

    strcpy(uusi->nimi, nimi);
    uusi->maara = maara;
    uusi->seuraava = NULL;
    uusi->edellinen = NULL;

    if (listanHead == NULL) {
        return uusi;
    }

    Node *pointer = listanHead;
    while (pointer->seuraava != NULL) {
        pointer = pointer->seuraava;
    }
    pointer->seuraava = uusi;
    uusi->edellinen = pointer;
    return listanHead;
}

Node *lueTiedosto(Node *listanHead, char *tiedostonimi) { // tämä funktio hoitaa tiedostojen lukemisen, hyväksyy vain rivit jotka ovat muodossa nimi;määrä
    FILE *tiedosto = fopen(tiedostonimi, "r");
    if (!tiedosto) {
        printf("Tiedoston avaaminen epäonnistui.\n");
        return listanHead;
    }

    char rivi[100];
    char *pNimi, *pMaara;
    int maara;

    // EKAN RIVIN LUKEMINEN, TIEDOSTOT ALKAA OTSIKKORIVILLÄ, tsekataan onko se olemassa ettei lueta tyhjää tiedostoa
    if(fgets(rivi, 100, tiedosto) == NULL) {
        printf("Yritit lukea tyhjän tiedoston!\n");
        return listanHead;
    }

    while (fgets(rivi, 100, tiedosto) != NULL) {
        if ((pNimi = strtok(rivi, ",")) == NULL) {
            printf("Merkkijonon %s pilkkominen epäonnistui, lopetetaan.\n", rivi);
            printf("Tiedoston tulee olla muodossa nimi;määrä\n");
            exit(0);
        }

        if ((pMaara = strtok(NULL, ",")) == NULL) {
            printf("Merkkijonon %s pilkkominen epäonnistui, lopetetaan.\n", rivi);
            printf("Tiedoston tulee olla muodossa nimi;määrä\n");
            exit(0);
        }

        maara = atoi(pMaara);
        listanHead = lisaaNode(listanHead, pNimi, maara);
    }
    fclose(tiedosto);
    return listanHead;
}

void tulostaLista(Node *listanHead) {
    while (listanHead != NULL) {
        printf("%s, %d\n", listanHead->nimi, listanHead->maara);
        listanHead = listanHead->seuraava;
    }

    return;
}

void tallennaTiedostoon(Node *listanHead, char *tiedostonimi) { // tallentaa tulokset tiedostoon etuperin
    FILE *tiedosto = fopen(tiedostonimi, "w");
    if (!tiedosto) {
        printf("Tiedoston avaaminen epäonnistui.\n");
        return;
    }

    while (listanHead != NULL) {
        fprintf(tiedosto, "%s,%d\n", listanHead->nimi, listanHead->maara);
        listanHead = listanHead->seuraava;
    }

    fclose(tiedosto);

    return;
}

void tallennaTiedostoonTakaperin(Node *listanTail, char *tiedostonimi) { // tallentaa tulokset tiedostoon takaperin
    FILE *tiedosto = fopen(tiedostonimi, "w");
    if (!tiedosto) {
        printf("Tiedoston avaaminen epäonnistui.\n");
        return;
    }

    while (listanTail != NULL) {
        fprintf(tiedosto, "%s,%d\n", listanTail->nimi, listanTail->maara);
        listanTail = listanTail->edellinen;
    }

    fclose(tiedosto);
    return;
}

Node *tyhjenna(Node *listanHead) { // tyhjentää listan
    Node *ptr = listanHead;
    while (ptr != NULL) {
        listanHead = ptr->seuraava;
        free(ptr);
        ptr = listanHead;
    }
    listanHead = NULL;
    return listanHead;
}


// TÄSTÄ ALKAA L09 MODUULIT

// BUBBLE SORT, VALINTAAN 6), SEVERI JA ANTTI

// laskee kuinka monta on yhteensä
int nodejaYhteensa(Node *listanHead) {
    int yhteensa = 0;
    Node *nykyinen = listanHead;
    while(nykyinen != NULL) {
        yhteensa++;
        nykyinen = nykyinen->seuraava;
    }
    return yhteensa;
}

void vaihdaNodet(Node *eka, Node *toka) { //eka ja toka on nodet joita vertaillaan
    int tempMaara;
    char tempNimi[100];
    tempMaara = eka->maara;

    strcpy(tempNimi,eka->nimi);
    eka->maara = toka->maara;
    strcpy(eka->nimi, toka->nimi);
    toka->maara = tempMaara;
    strcpy(toka->nimi, tempNimi);

    return;
}

void kuplaLajittelu(Node *listanHead) {
    // Kuplalajittelu eli bubble sort
    // Lajittelu laskevasti
    int i, j, n;
    int vaihdettu;
    Node *nykyinen;
    Node *seuraava;

    n = nodejaYhteensa(listanHead);

    for (i = 0; i < n - 1; i++) {
        vaihdettu = 0;
        nykyinen = listanHead;
        seuraava = nykyinen->seuraava;

        for (j = 0; j < n - i - 1; j++) {
            // Verrataan määrää
            if (nykyinen->maara < seuraava->maara) {
                vaihdaNodet(nykyinen, seuraava);
                vaihdettu = 1;
            }
            // jos määrä sama
            else if (nykyinen->maara == seuraava->maara) {
                if (strcmp(nykyinen->nimi, seuraava->nimi) < 0) {
                    vaihdaNodet(nykyinen, seuraava);
                    vaihdettu = 1;
                }
            }
            nykyinen = seuraava;
            seuraava = seuraava->seuraava;
        }

        if (vaihdettu == 0) {
            break;
        }
    }

    return;
}

// SELECTION SORT ELI VALINTALAJITTELU, LAJITTELU NOUSEVASTI, VALINTAAN 5 VALIKOSSA, JUUSO
void valintaLajittelu(Node* listanHead) {
    Node* nykyinen = listanHead;

    while (nykyinen != NULL) {
        Node* temp = nykyinen;
        Node* seuraava = nykyinen->seuraava;

        // ETSI PIENIN ALKIO JÄLJELLÄ OLEVASTA LISTASTA
        while (seuraava != NULL) {
            if (seuraava->maara < temp->maara) {
                temp = seuraava;
            } else if (seuraava->maara == temp->maara) {
                 if (strcmp(seuraava->nimi, temp->nimi) < 0) {
                    temp = seuraava;
                 }
            }
            seuraava = seuraava->seuraava;
        }

        // VAIHDA PAIKKOJA JOS TARVII
        if (temp != nykyinen) {
            vaihdaNodet(nykyinen, temp);
        }

        nykyinen = nykyinen->seuraava;
    }

    return;
}

// INSERTION SORT ELI LISÄYSLAJITTELU, LAJITTELU NOUSEVASTI, VALINTAAN 7 VALIKOSSA, JUUSO
void lisaysLajittelu(Node* listanHead) {
    if (listanHead == NULL) {
        return;
    }
    Node* nykyinen = listanHead->seuraava;

    while (nykyinen != NULL) {
        Node* verrattava = listanHead;

        while (verrattava != nykyinen) {
            if (nykyinen->maara < verrattava->maara ||
               (nykyinen->maara == verrattava->maara &&
                strcmp(nykyinen->nimi, verrattava->nimi) < 0)) {

                // VAIHDA NYKYINEN JA VERRATTAVA JOS NYKYINEN KUULUU ETEEN
                vaihdaNodet(nykyinen, verrattava);
            }

            verrattava = verrattava->seuraava;
        }

        nykyinen = nykyinen->seuraava;
    }

    return;
}
