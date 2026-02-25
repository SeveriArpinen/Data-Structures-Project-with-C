/*************************************************************************/
/* CT60A2600 Ohjelmakehitys C-kielellä
* Tiimi: 13
* Tekijä: Severi Arpinen, Antti Keronen, Juuso Käyhkö
* Opiskelijanumero: 000253077, 001855050, 000493675
* Päivämäärä: 01.04.2025
* Tämän ohjelman tekemisessä on käytetty kurssilla annettujen materiaalien
* ja ohjeiden lisäksi seuraavia lähteitä, työkaluja ja henkilöitä:
* Käytetyn aputyökalun nimi ja versio tai henkilön nimi: 
* Käytön tarkoitus:
* Yksityiskohtainen selvitys siitä, missä ohjelman osissa aputyökalua on
* käytetty ja miten, tai miten ko. henkilö on vaikuttanut ohjelmaan: Selitys yläpuolella
*/
/*************************************************************************/
/* Tehtävä L12, tiedoston nimi graafiKirjasto.c */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "graafiKirjasto.h"

void lisaaKaari(GRAAFI **alku, char *solmu1, char *solmu2, int etaisyys) {
    GRAAFI *uusSolmu = malloc(sizeof *uusSolmu);
        if (uusSolmu == NULL) {
            fprintf(stderr, "Virhe - Ei tarpeeksi muistia!\n");
            exit(0);
        }

        char *solmu1Kopio = malloc(strlen(solmu1) + 1);
        char *solmu2Kopio = malloc(strlen(solmu2) + 1);
        if (solmu1Kopio == NULL || solmu2Kopio == NULL) {
            fprintf(stderr, "Virhe - Ei tarpeeksi muistia!\n");
            free(uusSolmu);
            exit(0);
        }
        strcpy(solmu1Kopio, solmu1);
        strcpy(solmu2Kopio, solmu2);

        uusSolmu->Solmu1 = solmu1Kopio;
        uusSolmu->Solmu2 = solmu2Kopio;
        uusSolmu->etaisyys = etaisyys;

        uusSolmu->seuraava = *alku;
        *alku = uusSolmu;
}

void lueGraafiTiedostosta(const char *tiedostonNimi, GRAAFI **alku) {

    char rivi[256];
    char *solmu1, *solmu2, *pEtaisyys;
    int etaisyys;

    FILE *tiedosto = NULL;
    if((tiedosto = fopen(tiedostonNimi, "r"))== NULL){
        perror("Virhe tiedoston käsittelyssä.\n");
        exit(0);
    }

    // Ekan rivin lukeminen
    fgets(rivi, sizeof(rivi), tiedosto);

    while (fgets(rivi, sizeof(rivi), tiedosto) != NULL) {

        if ((solmu1 = strtok(rivi, ";")) == NULL) {
            printf("Merkkijonon %s pilkkominen epäonnistui, lopetetaan.\n", rivi);
            fclose(tiedosto);
            return;
        }

        if ((solmu2 = strtok(NULL, ";")) == NULL) {
            printf("Merkkijonon %s pilkkominen epäonnistui, lopetetaan.\n", rivi);
            fclose(tiedosto);
            return;
        }

        if ((pEtaisyys = strtok(NULL, ";")) == NULL) {
            printf("Merkkijonon %s pilkkominen epäonnistui, lopetetaan.\n", rivi);
            fclose(tiedosto);
            return;
        }

        etaisyys = atoi(pEtaisyys);
        lisaaKaari(alku, solmu1, solmu2, etaisyys);

    }
    fclose(tiedosto);
    return;
}

void lisaaJaPaivitaKaari(GRAAFI **alku) {
    char solmu1[256];
    char solmu2[256];
    int etaisyys;

    printf("Anna uusi tai päivitettävä kaari: (muodossa lähtösolmu;kohdesolmu;etäisyys)\n");
    if(scanf("%255[^;];%255[^;];%d", solmu1, solmu2, &etaisyys) != 3) {
        printf("Syöte oli virheellinen!\n");
        while ((getchar()) != '\n');
        return;
    };


    // Tarkistetaan ensin onko kyseinen kaari jo olemassa

    GRAAFI *nykyinen = *alku;

    while (nykyinen != NULL) {
        if((strcmp(nykyinen->Solmu1, solmu1) == 0 && strcmp(nykyinen->Solmu2, solmu2) == 0) 
        ||(strcmp(nykyinen->Solmu1, solmu2) == 0 && strcmp(nykyinen->Solmu2, solmu1) == 0)) { // kattellaan onko molemmat solmut samannimiset verrataan molemmat suunna A-B ja B-A.
            printf("Kaari löytyi, päivitetään sen etäisyys!\n");
            nykyinen->etaisyys = etaisyys;
            return;
        }
        nykyinen = nykyinen->seuraava;

    }
    // nyt jos kaarta ei ollu jo olemassa niin lisätään uusi:

    lisaaKaari(alku, solmu1, solmu2, etaisyys);
    return;
}

void poistaSolmuGraafista(GRAAFI **alku, char *poistettava) {
    if (*alku == NULL) {
        printf("Graafi on tyhjä, lisääthän arvoja ensin!\n");
        return;
    }

    GRAAFI *nykyinen = *alku;
    GRAAFI *edellinen = NULL;
    int poistettu = 0;

    while (nykyinen != NULL) {
        if (strcmp(nykyinen->Solmu1, poistettava) == 0 || strcmp(nykyinen->Solmu2, poistettava) == 0) {

            if (edellinen == NULL) {
                *alku = nykyinen->seuraava;
            } else {
                edellinen->seuraava = nykyinen->seuraava;
            }

            free(nykyinen->Solmu1);
            free(nykyinen->Solmu2);
            GRAAFI *poistetaan = nykyinen;
            nykyinen = nykyinen->seuraava;
            free(poistetaan);

            poistettu = 1;
            continue; // jatketaan silmukkaa, jos on lisää poistettavia
        }

        edellinen = nykyinen;
        nykyinen = nykyinen->seuraava;
    }

    if (poistettu) {
        printf("Solmu %s poistettu!\n", poistettava);
    } else {
        printf("Solmua %s ei löytynyt graafista.\n", poistettava);
    }

    return;
}

// NODEN MAARA JA NIMET
int nodenMaaraJaNimet(GRAAFI *alku, char *nodet[]) {
    int maara = 0;
    while (alku) {
        int loytyi1 = 0;
        int loytyi2 = 0;
        for (int i = 0; i < maara; i++) {
            if (strcmp(nodet[i], alku->Solmu1) == 0) loytyi1 = 1;
            if (strcmp(nodet[i], alku->Solmu2) == 0) loytyi2 = 1;
        }
        if (!loytyi1) nodet[maara++] = alku->Solmu1;
        if (!loytyi2) nodet[maara++] = alku->Solmu2;
        alku = alku->seuraava;
    }
    return maara;
}

// NODEN INDEXI NIMEN PERUSTEELLA
int nodenIndexi(char *nimi, char *nodet[], int nodeMaara) {
    // POISTAA LOPUSSA OLEVAT VÄLILYÖNNIT
    char puhdasNimi[100];
    strncpy(puhdasNimi, nimi, sizeof(puhdasNimi));
    puhdasNimi[strcspn(puhdasNimi, "\n")] = '\0';

    // ETSI NODEN INDEXI NIMEN PERUSTEELLA
    for (int i = 0; i < nodeMaara; i++) {
        if (strcmp(puhdasNimi, nodet[i]) == 0)
            return i;
    }
    return -1;
}

// TULOSTAA ETÄISYYDEN LAHTO JA MAALISOLMUSTA, JA -1 JOS REITTIÄ EI LÖYDY
// KÄYTTÄÄ DIJKSTRAN-ALGORITMIA
int etsiLyhyinReittiJaTallennaTiedostoon(GRAAFI *alku, char *lahto, char *loppu, char *tiedostonNimi) {
    char *nodet[100];
    int nodeMaara = nodenMaaraJaNimet(alku, nodet);

    int etaisyys[100];
    int kayty[100] = {0};

    // TULOSTA VARTEN
    int edeltajat[100];
    char tulos[500] = "";
    int polku[100];
    int pituus = 0;

    // ALUSTAA ETÄISYYSTAULUKON
    for (int i = 0; i < nodeMaara; i++) {
        edeltajat[i] = -1;
        etaisyys[i] = INT_MAX;
    }

    // ETSITÄÄN LAHTO JA MAALISOLMU
    int lahtoIndexi = nodenIndexi(lahto, nodet, nodeMaara);
    int loppuIndexi = nodenIndexi(loppu, nodet, nodeMaara);

    if (lahtoIndexi == -1 || loppuIndexi == -1) {
        printf("Lähtö tai maalisolmua ei löydy graafista.\n");
        return 0;
    } else {
        // ASETETAAN LAHTO SOLMUN ETÄISYYDEKSI 0
        etaisyys[lahtoIndexi] = 0;

        // DIJKSTRAN ALGORITMI
        // KÄY LÄPI KAIKKI SOLMUT
        for (int i = 0; i < nodeMaara; i++) {
            int pieninEtaisyysSolmuun = -1;
            int pieninEtaisyys = INT_MAX;

            // ETSI PIENIN ETÄISYYS SOLMUUN
            for (int j = 0; j < nodeMaara; j++) {
                if (!kayty[j] && etaisyys[j] < pieninEtaisyys) {
                    pieninEtaisyys = etaisyys[j];
                    pieninEtaisyysSolmuun = j;
                }
            }
            // EI LÖYTYNYT PIENINTÄ ETÄISYYTTÄ
            if (pieninEtaisyysSolmuun == -1) break;

            // MERKITÄÄN SOLMU KÄYTYNEEKSI
            kayty[pieninEtaisyysSolmuun] = 1;

            // KÄY LÄPI KAIKKI KAARET
            GRAAFI *ptr = alku;
            while (ptr) {
                int solmu1Indexi = nodenIndexi(ptr->Solmu1, nodet, nodeMaara);
                int solmu2Indexi = nodenIndexi(ptr->Solmu2, nodet, nodeMaara);

                if (solmu1Indexi == -1 || solmu2Indexi == -1) {
                    ptr = ptr->seuraava;
                    continue;
                }

                // KATSOO ONKO SOLMU 1 TAI 2 PIENIN ETÄISYYS SOLMUUN
                // JA KATSOO ONKO SE KÄYTYNYT
                // JA KATSOO ONKO ETÄISYYS PIENEMPI KUIN AIEMMIN

                if (pieninEtaisyysSolmuun == solmu1Indexi) {
                    if (!kayty[solmu2Indexi]) {
                        if (etaisyys[pieninEtaisyysSolmuun] + ptr->etaisyys < etaisyys[solmu2Indexi]) {
                            etaisyys[solmu2Indexi] = etaisyys[pieninEtaisyysSolmuun] + ptr->etaisyys;
                            edeltajat[solmu2Indexi] = pieninEtaisyysSolmuun;
                        }
                    }
                }
                if (pieninEtaisyysSolmuun == solmu2Indexi) {
                    if (!kayty[solmu1Indexi]) {
                        if (etaisyys[pieninEtaisyysSolmuun] + ptr->etaisyys < etaisyys[solmu1Indexi]) {
                            etaisyys[solmu1Indexi] = etaisyys[pieninEtaisyysSolmuun] + ptr->etaisyys;
                            edeltajat[solmu1Indexi] = pieninEtaisyysSolmuun;
                        }
                    }
                }
                ptr = ptr->seuraava;
            }
        }

        // LUO TULOS
        for (int at = loppuIndexi; at != -1; at = edeltajat[at]) {
            polku[pituus++] = at;
        }
        
        for (int i = pituus - 1; i >= 0; i--) {
            strcat(tulos, nodet[polku[i]]);
            if (i > 0) strcat(tulos, " -> ");
        }
        
        char loppuosa[50];
        sprintf(loppuosa, " = %d", etaisyys[loppuIndexi]);
        strcat(tulos, loppuosa);

        // TALLENNA TIEDOSTOON
        FILE *tiedosto = NULL;
        if((tiedosto = fopen(tiedostonNimi, "w"))==NULL){
            perror("Tiedoston käsittelyssä virhe\n");
            exit(0);


        }

        fprintf(tiedosto, "%s\n", tulos);
        fclose(tiedosto);
        return 1; // onnistui


    }
}

void tulostaGraafi(GRAAFI *alku) {
    if (alku == NULL) {
        printf("Graafi on tyhjä.\n");
    }

    GRAAFI *iteraattori = alku;
    while (iteraattori != NULL) {
        printf("%s - %s, etäisyys: %d\n", iteraattori->Solmu1, iteraattori->Solmu2, iteraattori->etaisyys);
        iteraattori = iteraattori->seuraava;

    }
}

void vapautaGraafi(GRAAFI **alku) {
    GRAAFI *vapaa = *alku;
    while (vapaa != NULL) {
        GRAAFI *nykynenSolmu = vapaa;
        vapaa = vapaa->seuraava;
        free(nykynenSolmu->Solmu1);
        free(nykynenSolmu->Solmu2);
        free(nykynenSolmu);
    }
    *alku = NULL; 
    return;
}
