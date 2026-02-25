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
/* Tehtävä L12, tiedoston nimi graafiTestit.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "graafiKirjasto.h"

void testLueGraafiTiedostosta() {
    FILE *tiedosto = fopen("testausgraafi.txt", "w");
    assert(tiedosto != NULL);

    fprintf(tiedosto, "Solmu1;Solmu2;Etaisyys\n");
    fprintf(tiedosto, "A;B;10\n");
    fprintf(tiedosto, "B;C;20\n");
    fclose(tiedosto);

    GRAAFI *graafi = NULL;
    lueGraafiTiedostosta("testausgraafi.txt", &graafi);

    // Tarkistaa tiedot
    assert(graafi != NULL);
    assert(strcmp(graafi->Solmu1, "B") == 0);
    assert(strcmp(graafi->Solmu2, "C") == 0);
    assert(graafi->etaisyys == 20);
    assert(graafi->seuraava != NULL);
    assert(strcmp(graafi->seuraava->Solmu1, "A") == 0);
    assert(strcmp(graafi->seuraava->Solmu2, "B") == 0);
    assert(graafi->seuraava->etaisyys == 10);
    assert(graafi->seuraava->seuraava == NULL);
    vapautaGraafi(&graafi);
    remove("testausgraafi.txt");
    printf("Graafin lukeminen tiedostosta onnistui!\n");
}

void testLisaaKaari(){
    GRAAFI *graafi = NULL;
    
    lisaaKaari(&graafi,"testi1","testi2",50);
    assert(graafi != NULL);
    assert(strcmp(graafi->Solmu1,"testi1") == 0);
    assert(strcmp(graafi->Solmu2,"testi2") == 0);
    assert(graafi->etaisyys == 50);
    vapautaGraafi(&graafi);

    printf("Kaaren lisäys onnistui!\n");
}

void testLisaaJaPaivita(){
    GRAAFI *graafi = NULL;
    
    lisaaKaari(&graafi,"testi1","testi2",50);
    assert(graafi != NULL);
    assert(strcmp(graafi->Solmu1,"testi1") == 0);
    assert(strcmp(graafi->Solmu2,"testi2") == 0);
    assert(graafi->etaisyys == 50);

    // lisätään toinen kaari ja tarkistetaan että se on oikea
    lisaaKaari(&graafi, "testi2", "testi3",60); 

    assert(graafi->seuraava != NULL);
    assert(strcmp(graafi->Solmu1,"testi2") == 0);
    assert(strcmp(graafi->Solmu2, "testi3") == 0);
    assert(graafi->etaisyys == 60);

    printf("Useamman kaaren lisäys onnistui!\n");

    vapautaGraafi(&graafi);
}

void testPoistaSolmu(){
    GRAAFI *graafi = NULL;
    
    lisaaKaari(&graafi,"testi1","testi2",50);
    lisaaKaari(&graafi,"testi2","testi3",50);
    lisaaKaari(&graafi,"testi3","testi4",50);

    poistaSolmuGraafista(&graafi, "testi2");

    GRAAFI *nykyinen = graafi; // tsekataan ettei poistettua solmua enää löydy
    while(nykyinen != NULL) {
        assert(strcmp(nykyinen->Solmu1,"testi2") != 0);
        assert(strcmp(nykyinen->Solmu2,"testi2") != 0);
        nykyinen = nykyinen->seuraava;
    }

    vapautaGraafi(&graafi);
    printf("solmun poistaminen graafista onnistui!\n");
}

void testEtsiLyhyinReittiJaTallennaTiedostoon() {
    GRAAFI *graafi = NULL;
    lisaaKaari(&graafi, "A", "B", 10);
    lisaaKaari(&graafi, "B", "C", 5);
    lisaaKaari(&graafi, "A", "C", 30);
    
    remove("lyhyin_reitti.txt");
    etsiLyhyinReittiJaTallennaTiedostoon(graafi, "A", "C", "lyhyin_reitti.txt");

    vapautaGraafi(&graafi);
    printf("Lyhin reitin löytäminen onnistui!\n");
}

void suorita_testit() {
    testLueGraafiTiedostosta();
    testLisaaKaari();
    testLisaaJaPaivita();
    testPoistaSolmu();
    testEtsiLyhyinReittiJaTallennaTiedostoon();
    printf("Kaikki testit läpäisty!\n");
}

int main() {
    suorita_testit();
    return 0;
}
