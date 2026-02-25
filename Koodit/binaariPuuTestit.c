/*************************************************************************/
/* CT60A2600 Ohjelmakehitys C-kielellä
* Tiimi: 13
* Tekijä: Severi Arpinen, Antti Keronen, Juuso Käyhkö
* Opiskelijanumero: 000253077, 001855050, 000493675
* Päivämäärä: 19.03.2025
* Tämän ohjelman tekemisessä on käytetty kurssilla annettujen materiaalien
* ja ohjeiden lisäksi seuraavia lähteitä, työkaluja ja henkilöitä:
* Käytetyn aputyökalun nimi ja versio tai henkilön nimi
* Käytön tarkoitus
* Yksityiskohtainen selvitys siitä, missä ohjelman osissa aputyökalua on
* käytetty ja miten, tai miten ko. henkilö on vaikuttanut ohjelmaan
*/
/*************************************************************************/
/* Tehtävä L10, tiedoston nimi binaariPuuTestit.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "binaariPuuKirjasto.h"

// APU FUNKTIO TARKISTAMAAN PUUN JÄRJESTYKSEN
void jarjestyksessaTesti(TreeNode* juuriNode, int* arr, int* index) {
    if (juuriNode != NULL) {
        jarjestyksessaTesti(juuriNode->vasenNode, arr, index);
        assert(juuriNode->maara == arr[*index]);
        (*index)++;
        jarjestyksessaTesti(juuriNode->oikeaNode, arr, index);
    }
}

// LISÄÄ NODEJA
void testi_lisaaNode() {
    TreeNode* juuri = NULL;

    juuri = lisaaNodePuuhun(juuri, "Juuso", 5);
    juuri = lisaaNodePuuhun(juuri, "Antti", 3);
    juuri = lisaaNodePuuhun(juuri, "Severi", 7);

    int expected[] = {3, 5, 7};
    int index = 0;
    jarjestyksessaTesti(juuri, expected, &index);
}

// APUFUNKTIO TARKISTAMAAN JOS NODE ON OLEMASSA
int nodeOlemmassa(TreeNode* juuriNode, char* nimi, int maara) {
    if (juuriNode == NULL) return 0;
    if (juuriNode->maara == maara && strcmp(juuriNode->nimi, nimi) == 0)
        return 1;
    return nodeOlemmassa(juuriNode->vasenNode, nimi, maara) || nodeOlemmassa(juuriNode->oikeaNode, nimi, maara);
}

// TESTAA JOS NODE(T) ON OLEMASSA
void testi_nodeOlemassa() {
    TreeNode* juuri = NULL;
    juuri = lisaaNodePuuhun(juuri, "Juuso", 5);
    juuri = lisaaNodePuuhun(juuri, "Antti", 3);
    juuri = lisaaNodePuuhun(juuri, "Severi", 7);

    assert(nodeOlemmassa(juuri, "Juuso", 5) == 1);
    assert(nodeOlemmassa(juuri, "Antti", 3) == 1);
    assert(nodeOlemmassa(juuri, "Severi", 7) == 1);
    assert(nodeOlemmassa(juuri, "Unknown", 10) == 0);
}

void testi_jononToiminnot() {
    Jono* jono = luoJono();
    assert(onkoJonoTyhja(jono) == 1);

    TreeNode node1 = {"A", 1, PUNAINEN, NULL, NULL};
    TreeNode node2 = {"B", 2, PUNAINEN, NULL, NULL};

    lisaaJonoon(jono, &node1);
    lisaaJonoon(jono, &node2);
    assert(onkoJonoTyhja(jono) == 0);
    
    assert(poistaJonosta(jono) == &node1);
    assert(poistaJonosta(jono) == &node2);
    assert(onkoJonoTyhja(jono) == 1);
    
    vapautaJono(jono);
}

// TESTAA LEVEYDENSUUNTAINEN
void testi_leveydensuuntainenHaku() {
    TreeNode* juuri = NULL;
    juuri = lisaaNodePuuhun(juuri, "Juuso", 5);
    juuri = lisaaNodePuuhun(juuri, "Antti", 3);
    juuri = lisaaNodePuuhun(juuri, "Severi", 7);
    suoritaLeveydensuuntainenHaku(juuri, "Antti", "testidata/testi.txt");
    suoritaLeveydensuuntainenHaku(juuri, "Tuntematon", "testidata/testi.txt");
    tyhjennaPuu(juuri);
}

// SYVYYSHAKU TESTI
void testi_syvyyshaku(){
    TreeNode *juuri = NULL;
    juuri = lisaaNodePuuhun(juuri, "Juuso", 5);
    juuri = lisaaNodePuuhun(juuri, "Antti", 3);
    juuri = lisaaNodePuuhun(juuri, "Severi", 7);
    suoritaSyvyyshaku(juuri, 5, "testidata/testi_syvyys.txt");
    suoritaSyvyyshaku(juuri,3,"testidata/testi_syvyys2.txt");
    tyhjennaPuu(juuri);
}

// TESTAA TASAPAINOTUS
// APUFUNKTIO TARKISTAMAAN ONKO PUU TASAPAINOSSA
int tarkistaTasapaino(TreeNode* juuriNode) {
    if (juuriNode == NULL) return 0;

    int vasenKorkeus = tarkistaTasapaino(juuriNode->vasenNode);
    if (vasenKorkeus == -1) return -1;

    int oikeaKorkeus = tarkistaTasapaino(juuriNode->oikeaNode);
    if (oikeaKorkeus == -1) return -1;

    if (abs(vasenKorkeus - oikeaKorkeus) > 1) return -1;

    return 1 + (vasenKorkeus > oikeaKorkeus ? vasenKorkeus : oikeaKorkeus);
}

// TESTIFUNKTIO TASAPAINOLLE
void testi_puuTasapainossa() {
    TreeNode* juuri = NULL;
    juuri = lisaaNodePuuhun(juuri, "Juuso", 5);
    juuri = lisaaNodePuuhun(juuri, "Antti", 3);
    juuri = lisaaNodePuuhun(juuri, "Severi", 7);

    // ON TASAPAINOSSA
    assert(tarkistaTasapaino(juuri) != -1);

    // TEE PUUSTA TARKOITUKSELLITESTI EPÄTASAPAINOINEN
    juuri = lisaaNodePuuhunIlmanTasapainoitusta(juuri, "Zorro", 8);
    juuri = lisaaNodePuuhunIlmanTasapainoitusta(juuri, "Xavier", 9);

    // EI PITÄISI OLLA TASAPAINOSSA
    assert(tarkistaTasapaino(juuri) == -1);

    tyhjennaPuu(juuri);
}

void testi_poisto() {
    TreeNode *juuri = NULL;
    juuri = lisaaNodePuuhun(juuri, "Antti", 50);
    juuri = lisaaNodePuuhun(juuri, "Juuso", 30);
    juuri = lisaaNodePuuhun(juuri, "Severi", 70);
    
    assert(etsiPoistettavaSolmu(juuri, 50, NULL) != NULL);
    suoritaPoisto(&juuri, 50, NULL);
    assert(etsiPoistettavaSolmu(juuri, 50, NULL) == NULL);
}

void testi_binaarihaku() {
    TreeNode* juuri = NULL;
    juuri = lisaaNodePuuhun(juuri, "Antti", 50);
    juuri = lisaaNodePuuhun(juuri, "Juuso", 30);
    juuri = lisaaNodePuuhun(juuri, "Severi", 70);

    assert(binaarihaku(juuri,50) != NULL);
    assert(binaarihaku(juuri,30) != NULL);
    assert(binaarihaku(juuri,70) != NULL);

    // arvo jota ei löydy

    assert(binaarihaku(juuri,999) == NULL);


    tyhjennaPuu(juuri);

}

void testi_duplikaattiMaara() {
    TreeNode *juuri = NULL;
    juuri = lisaaNodePuuhun(juuri, "Juuso", 10);
    juuri = lisaaNodePuuhun(juuri, "Antti", 10);
    juuri = lisaaNodePuuhun(juuri, "Severi", 10);

    assert(nodeOlemmassa(juuri, "Juuso", 10));
    assert(nodeOlemmassa(juuri, "Antti", 10));
    assert(nodeOlemmassa(juuri, "Severi", 10));

    tyhjennaPuu(juuri);
}

void testi_binaarihaku_tyhja() {
    TreeNode* juuri = NULL;
    assert(binaarihaku(juuri,999) == NULL);
    // pitäis tulla aina null, ihan sama mikä numero
}

void testi_tiedostonLukuJaKirjoitus() {
    TreeNode* juuri = NULL;
    juuri = lueTiedostoPuuhun(juuri, "testidata/testi_puu.txt");
    kirjoitaPuuTiedostoon(juuri, "testidata/testi_puu_output.txt");

    FILE *in = fopen("testidata/testi_puu.txt", "r");
    FILE *out = fopen("testidata/testi_puu_output.txt", "r");
    assert(in && out);

    char riviIn[100], riviOut[100];
    fgets(riviIn, 100, in); // OHITA OTSIKKO
    // VERTAILLAAN RIVEJÄ MOLEMMISSA TIEDOSTOISSA
    while (fgets(riviIn, 100, in) && fgets(riviOut, 100, out)) {
        // VAIHDA ; -> , TIEDOSTOSSA
        for (int i = 0; riviOut[i]; i++) {
            if (riviOut[i] == ',') {
                riviOut[i] = ';';
            }
        }
        assert(strcmp(riviIn, riviOut) == 0);
    }

    fclose(in);
    fclose(out);
    tyhjennaPuu(juuri);
}

void testi_virhetapaukset() {
    // NULL PUU
    assert(nodeOlemmassa(NULL, "Ei", 123) == 0);
    assert(binaarihaku(NULL, 123) == NULL);
    suoritaSyvyyshaku(NULL, 123, "testidata/tyhja.txt"); // EI PITÄISI KAATUA

    TreeNode* juuri = NULL;
    juuri = lueTiedostoPuuhun(juuri, "testidata/ei_ole.txt"); // EI PITÄISI KAATUA
    tyhjennaPuu(juuri);
}

void suorita_testit() {
    testi_lisaaNode();
    testi_nodeOlemassa();
    testi_jononToiminnot();
    testi_leveydensuuntainenHaku();
    testi_syvyyshaku();
    testi_puuTasapainossa();
    testi_poisto();
    testi_binaarihaku();
    testi_duplikaattiMaara();
    testi_binaarihaku_tyhja();
    testi_tiedostonLukuJaKirjoitus();
    testi_virhetapaukset();
    printf("Kaikki binääripuu testit läpäisty!\n");
}

int main() {
    suorita_testit();
    return 0;
}

