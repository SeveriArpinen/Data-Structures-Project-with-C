/*************************************************************************/
/* CT60A2600 Ohjelmakehitys C-kielellä
* Tiimi: 13
* Tekijä: Antti Keronen, Juuso Käyhkö
* Opiskelijanumero: 001855050, 000493675
* Päivämäärä: 09.03.2025
* Tämän ohjelman tekemisessä on käytetty kurssilla annettujen materiaalien
* ja ohjeiden lisäksi seuraavia lähteitä, työkaluja ja henkilöitä:
* Käytetyn aputyökalun nimi ja versio tai henkilön nimi
* Käytön tarkoitus
* Yksityiskohtainen selvitys siitä, missä ohjelman osissa aputyökalua on
* käytetty ja miten, tai miten ko. henkilö on vaikuttanut ohjelmaan
*/
/*************************************************************************/
/* Tehtävä L10, tiedoston nimi linkitettyListakirjasto.h*/

#ifndef L08T1KIRJASTO_H
#define L08T1KIRJASTO_H

typedef struct Node {
    char nimi[100];
    int maara;
    struct Node *seuraava;
    struct Node *edellinen;
} Node;

Node *lisaaNode(Node *listanHead, char *nimi, int maara);
Node *lueTiedosto(Node *listanHead, char *tiedostonimi);
void tulostaLista(Node *listanHead);
void tallennaTiedostoon(Node *listanHead, char *tiedostonimi);
void tallennaTiedostoonTakaperin(Node *listanTail, char *tiedostonimi);
Node *tyhjenna(Node *listanHead);
int nodejaYhteensa(Node *listanHead);
void vaihdaNodet(Node *eka, Node *toka);
void kuplaLajittelu(Node *listanHead);
void valintaLajittelu(Node *listanHead);
void lisaysLajittelu(Node *listanHead);

#endif


