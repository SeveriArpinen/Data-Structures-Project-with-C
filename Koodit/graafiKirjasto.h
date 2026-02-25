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
/* Tehtävä L12, tiedoston nimi graafiKirjasto.h */

#ifndef GRAAFIKIRJASTO_H
#define GRAAFIKIRJASTO_H

typedef struct GRAAFI {
    char *Solmu1;
    char *Solmu2;
    int etaisyys;
    struct GRAAFI *seuraava;
} GRAAFI;

void lisaaKaari(GRAAFI **alku, char *solmu1, char *solmu2, int etaisyys);
void lueGraafiTiedostosta(const char *tiedostonNimi, GRAAFI **alku);
int etsiLyhyinReittiJaTallennaTiedostoon(GRAAFI *alku, char *lahto, char *loppu, char *tiedostonNimi);
void tulostaGraafi(GRAAFI *alku);
void vapautaGraafi(GRAAFI **alku);
void lisaaJaPaivitaKaari(GRAAFI **alku);
void poistaSolmuGraafista(GRAAFI **alku, char *poistettava);

#endif





