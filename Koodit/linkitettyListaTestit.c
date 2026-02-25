/*************************************************************************/
/* CT60A2600 Ohjelmakehitys C-kielellä
* Tiimi: 13
* Tekijä: Severi Arpinen, Antti Keronen, Juuso Käyhkö
* Opiskelijanumero: 000253077, 001855050, 000493675
* Päivämäärä:
* Tämän ohjelman tekemisessä on käytetty kurssilla annettujen materiaalien
* ja ohjeiden lisäksi seuraavia lähteitä, työkaluja ja henkilöitä:
* Käytetyn aputyökalun nimi ja versio tai henkilön nimi
* Käytön tarkoitus
* Yksityiskohtainen selvitys siitä, missä ohjelman osissa aputyökalua on
* käytetty ja miten, tai miten ko. henkilö on vaikuttanut ohjelmaan
*/
/*************************************************************************/
/* Tehtävä L10, tiedoston nimi linkitettyListaTestit.c */

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "linkitettyListaKirjasto.h"


void testi_lisaaNode() {
    Node *testNode = NULL;
    testNode = lisaaNode(testNode, "Testi", 5);
    assert(testNode != NULL);
    assert(strcmp(testNode->nimi, "Testi") == 0);
    assert(testNode->maara == 5);
    testNode = tyhjenna(testNode);
}


void testi_lueTiedosto() {
    Node *testNode = NULL;
    testNode = lueTiedosto(testNode, "testidata/LListaTestiTiedosto.txt");
    assert(testNode != NULL);
    testNode = tyhjenna(testNode);
}


void testi_tallennaTiedostoon() {
    Node *testNode = NULL;
    testNode = lisaaNode(testNode, "Testi", 10);
    tallennaTiedostoon(testNode, "output.txt");
    testNode = tyhjenna(testNode);
}

void testi_tallennaTiedostoonTakaperin() {
    Node *testNode = NULL;
    testNode = lisaaNode(testNode, "eka", 1);
    testNode = lisaaNode(testNode, "toka", 2);
    testNode = lisaaNode(testNode, "kolmas", 3);

    Node *tail = testNode;
    while (tail->seuraava != NULL) {
        tail = tail->seuraava;
    }

    tallennaTiedostoonTakaperin(tail, "testidata/testinimet.txt");
    testNode = tyhjenna(testNode);
}


void testi_kuplaLajitteluLaskevaJärjestys() {
    Node *testNode = NULL;
    testNode = lisaaNode(testNode, "eka", 5);
    testNode = lisaaNode(testNode, "toka", 8);
    testNode = lisaaNode(testNode, "kolmas", 3);
    testNode = lisaaNode(testNode, "neljäs", 8);
    testNode = lisaaNode(testNode, "viides", 7);
    kuplaLajittelu(testNode);

    Node *nykyinen = testNode;
    assert(nykyinen != NULL);
    while (nykyinen != NULL && nykyinen->seuraava != NULL) {
        assert(nykyinen->maara >= nykyinen->seuraava->maara);
        if (nykyinen->maara == nykyinen->seuraava->maara) {
            assert(strcmp(nykyinen->nimi, nykyinen->seuraava->nimi) > 0);
        }
        nykyinen = nykyinen->seuraava;
    }

    testNode = tyhjenna(testNode);
}


void testi_kuplaLajitteluTyhjaLista() {
    Node *testNode = NULL;
    kuplaLajittelu(testNode);
    assert(testNode == NULL);
}


void testi_kuplaLajitteluYksiItemi() {
    Node *testNode = NULL;
    testNode = lisaaNode(testNode, "eka", 5);
    kuplaLajittelu(testNode);
    assert(testNode != NULL);
    assert(testNode->maara == 5);
    assert(strcmp(testNode->nimi, "eka") == 0);
    testNode = tyhjenna(testNode);
}


void testi_lisäysLajitteluNousevaJärjestys() {
    Node *testNode = NULL;
    testNode = lisaaNode(testNode, "eka", 5);
    testNode = lisaaNode(testNode, "toka", 8);
    testNode = lisaaNode(testNode, "kolmas", 3);
    testNode = lisaaNode(testNode, "neljäs", 8);
    testNode = lisaaNode(testNode, "viides", 7);
    lisaysLajittelu(testNode);

    Node *nykyinen = testNode;
    assert(nykyinen != NULL);
    while (nykyinen != NULL && nykyinen->seuraava != NULL) {
        assert(nykyinen->maara <= nykyinen->seuraava->maara);
        if (nykyinen->maara == nykyinen->seuraava->maara) {
            assert(strcmp(nykyinen->nimi, nykyinen->seuraava->nimi) <= 0);
        }
        nykyinen = nykyinen->seuraava;
    }

    testNode = tyhjenna(testNode);
}


void testi_lisäysLajitteluTyhjaLista() {
    Node *testNode = NULL;
    lisaysLajittelu(testNode);
    assert(testNode == NULL);
}


void testi_lisäysLajitteluYksiItemi() {
    Node *testNode = NULL;
    testNode = lisaaNode(testNode, "eka", 5);
    lisaysLajittelu(testNode);
    assert(testNode != NULL);
    assert(testNode->maara == 5);
    assert(strcmp(testNode->nimi, "eka") == 0);
    testNode = tyhjenna(testNode);
}


void suorita_testit() {
    testi_lisaaNode();
    testi_lueTiedosto();
    testi_tallennaTiedostoon();
    testi_tallennaTiedostoonTakaperin();
    testi_kuplaLajitteluLaskevaJärjestys();
    testi_kuplaLajitteluTyhjaLista();
    testi_kuplaLajitteluYksiItemi();
    testi_lisäysLajitteluNousevaJärjestys();
    testi_lisäysLajitteluTyhjaLista();
    testi_lisäysLajitteluYksiItemi();
    printf("Kaikki testit läpäisty!\n");
}

int main() {
    suorita_testit();
    return 0;
}
