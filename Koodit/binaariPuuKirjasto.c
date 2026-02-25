/*************************************************************************/
/* CT60A2600 Ohjelmakehitys C-kielellä
* Tiimi: 13
* Tekijä: Severi Arpinen, Antti Keronen, Juuso Käyhkö
* Opiskelijanumero: 000253077, 001855050, 000493675
* Päivämäärä: 19.03.2025
* Tämän ohjelman tekemisessä on käytetty kurssilla annettujen materiaalien
* ja ohjeiden lisäksi seuraavia lähteitä, työkaluja ja henkilöitä:
* https://www.geeksforgeeks.org/preorder-tree-traversal-of-binary-tree-in-c/
* https://www.geeksforgeeks.org/binary-search-tree-set-1-search-and-insertion/?ref=shm
* https://www.geeksforgeeks.org/c-program-for-breadth-first-search-or-bfs-for-a-graph/?ref=next_article_top
* https://www.geeksforgeeks.org/deletion-in-binary-search-tree/
* https://www.geeksforgeeks.org/binary-search-tree-set-1-search-and-insertion/
* Käytetyn aputyökalun nimi ja versio tai henkilön nimi: 
* Käytön tarkoitus:
* kohdan 2) läpikäynnin ymmärtäminen ja soveltaminen omaan ohjelmaan
* kohdan 4 leveyshaun ymmärtäminen
* binääripuun noden poisto ja tasapainotus siinä yhteydessä
* Yksityiskohtainen selvitys siitä, missä ohjelman osissa aputyökalua on
* käytetty ja miten, tai miten ko. henkilö on vaikuttanut ohjelmaan: Selitys yläpuolella
*/
/*************************************************************************/
/* Tehtävä L10, tiedoston nimi binaariPuuKirjasto.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "binaariPuuKirjasto.h"

/////////////////////// APU FUNKTIOITA ///////////////////////

// ONKO NODE PUNAINEN
int onPunainen(TreeNode* node) {
    return node != NULL && node->vari == PUNAINEN;
}

// PALAUTTAA 1 JOS JONO ON TYHJÄ
int onkoJonoTyhja(Jono *jono) {
    return (jono->etu == NULL);
}

// VAPAUTTAA JONON
void vapautaJono(Jono *jono) {
    while (!onkoJonoTyhja(jono)) {
        poistaJonosta(jono); // Poistaa solmun ja vapauttaa muistin
    }
    free(jono); // Vapautetaan itse jono
}

// TULOSTAA PUUN NÄTISTI
void tulostaPuu(TreeNode* juuri, int syvyys) {
    if (juuri != NULL) {
        tulostaPuu(juuri->oikeaNode, syvyys + 1);  
        for (int i = 0; i < syvyys; i++) {
            printf("            ");
        }
        printf("%s %d\n", juuri->nimi, juuri->maara); 
        tulostaPuu(juuri->vasenNode, syvyys + 1);
    }
}

// KIRJOITA PUU, REKURSIIVINEN
void kirjoitaPuu(TreeNode *juuri, FILE *tiedosto) {
    if (juuri == NULL) {
        return;
    }
     
    // KIRJOITETAAN TIEDOSTOON
    fprintf(tiedosto, "%s,%d\n", juuri->nimi, juuri->maara);

    // REKURSIIVINEN KUTSU VASEMPAAAN JA OIKEAAN PUUHUN
    kirjoitaPuu(juuri->vasenNode, tiedosto);

    kirjoitaPuu(juuri->oikeaNode, tiedosto);

    return;
}

// KIRJOITA PUU TIEDOSTOON
void kirjoitaPuuTiedostoon(TreeNode *juuri, char *tiedostonimi) {
    FILE *tiedosto = fopen(tiedostonimi, "w");
    if (!tiedosto) {
        printf("Tiedoston avaaminen epäonnistui.\n");
        return;
    }

    // kutsuu kirjoittavaa ohjelmaa
    kirjoitaPuu(juuri, tiedosto);

    fclose(tiedosto);

    return;
}

// SYVYYSHAKU, REKURSIIVINEN
int syvyyshaku(TreeNode *juuri, int etsittava, FILE *tiedosto) {
    // Funktio kattoo löytyykö arvo tästä kohdasta, jos ei niin kutsuu vasenta ja oikeeta nodea
    // ja tallentaa kaikki läpikäydyt nodet tiedosttoon
    if (juuri == NULL) {
        return 0;
    }

    fprintf(tiedosto, "%s,%d\n", juuri->nimi, juuri->maara);
    if (juuri->maara == etsittava) {
        return 1; // jos löytyy niin palautetaan aina ykköne, jos ei niin 0
    }

    // rekursiiviset kutsut vasempaan ja oikeaan puuhun, katotaan löytyykö niistäkään
    if (syvyyshaku(juuri->vasenNode, etsittava, tiedosto) == 1) {
        return 1;
    }

    if (syvyyshaku(juuri->oikeaNode, etsittava, tiedosto) == 1) {
        return 1;
    }

    // jos ei löydy niin palautellaan 0

    return 0;
}

// SUORITA SYVYYSHAKU (ELI AVAA TIEDOSTO JA KUTSU syvyyshaku() FUNKTIO)
void suoritaSyvyyshaku(TreeNode *juuri, int etsittava, char *tiedostonimi) {
    int loytyi; // jos tää saa arvon 1, niin on löytynyt arvo, jos ei niin saa arvon 0

    FILE *tiedosto = fopen(tiedostonimi, "w");
    if (!tiedosto) {
        printf("Tiedoston avaaminen epäonnistui.\n");
        return;
    }

    // kutsuu syvyyshakua
    loytyi = syvyyshaku(juuri, etsittava, tiedosto); 

    if (loytyi == 1) {
        printf("Puussa on arvo '%d'.\n", etsittava);
    } else if (loytyi == 0) {
        printf("Puussa ei ole arvoa '%d'.\n", etsittava);
    }

    fclose(tiedosto);

    return;
}

// UUSI SOLMU JONOON
void lisaaJonoon(Jono *jono, TreeNode *solmu) {
    JonoSolmu *uusi = (JonoSolmu*)malloc(sizeof(JonoSolmu));
    uusi->solmu = solmu;
    uusi->seuraava = NULL;
    
    if (jono->taka == NULL) {
        jono->etu = jono->taka = uusi;
        return;
    }
    
    jono->taka->seuraava = uusi;
    jono->taka = uusi;
}

// TYHJENNÄ PUU, REKURSIIVINEN
void tyhjennaPuu(TreeNode *juuri) {
    if (juuri == NULL) {
        return;
    }

    tyhjennaPuu(juuri->vasenNode);
    tyhjennaPuu(juuri->oikeaNode);

    free(juuri);
}

// POISTA SOLMU PUUSTA ARVON PERUSTEELLA
void suoritaPoisto(TreeNode **juuri, int etsittavaArvo, const char *etsiNimi) {
    TreeNode *poistettavaSolmu = etsiPoistettavaSolmu(*juuri, etsittavaArvo, etsiNimi);
    if (poistettavaSolmu != NULL) {
        *juuri = poistaSolmu(*juuri, poistettavaSolmu);
        printf("Poisto suoritettu.\n");
        printf("\n");
    } else {
        printf("Solmua ei löytynyt puusta.\n");
        printf("\n");
    }
}

// Breadth-first search (BFS)
void suoritaLeveydensuuntainenHaku(TreeNode *juuri, char *etsittava, char *tiedostonimi){
    if (juuri == NULL) {
        printf("Puu on tyhjä.\n");
        return;
    }

    FILE *tiedosto = NULL;
    if ((tiedosto = fopen(tiedostonimi, "w")) == NULL) {
        perror("Virhe tiedoston avaamisessa");
        exit(0);
    }

    Jono *jono = luoJono();
    lisaaJonoon(jono, juuri);
    int loytyi = 0;

    while (!onkoJonoTyhja(jono)) {
        TreeNode *nykyinen = poistaJonosta(jono);
        fprintf(tiedosto, "%s,%d\n", nykyinen->nimi, nykyinen->maara);

        // Tarkista löytyykö
        if (strcmp(nykyinen->nimi, etsittava) == 0) {
            printf("Puussa on arvo '%s %d'.\n", nykyinen->nimi, nykyinen->maara);
            printf("\n");
            loytyi = 1;
            break;  // Poistu jos arvo löytyy
        }

        // Lisää solmut jonoon, jos olemassa
        if (nykyinen->vasenNode) lisaaJonoon(jono, nykyinen->vasenNode);
        if (nykyinen->oikeaNode) lisaaJonoon(jono, nykyinen->oikeaNode);
    }

    fclose(tiedosto);
    vapautaJono(jono);

    // Jos arvo ei löytyny
    if (!loytyi) {
        printf("Puussa ei ole arvoa '%s'.\n", etsittava);
        printf("\n");
    }
}

/////////////////////// APU FUNKTIOT LOPPU ///////////////////////

// UUSI NODE
TreeNode* uusiNode(char *nimi, int maara) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    if (!node) {
        printf("Muistin varaus epäonnistui.\n");
        return NULL;
    }

    strcpy(node->nimi, nimi);
    node->maara = maara;
    node->vari = PUNAINEN;
    node->vasenNode = node->oikeaNode = NULL;
    return node;
}

// NODEN KIERTO VASEMMALLE
TreeNode* kiertoVasemmalle(TreeNode* node) {
    TreeNode* oikeaLapsiNode = node->oikeaNode;
    node->oikeaNode = oikeaLapsiNode->vasenNode;
    oikeaLapsiNode->vasenNode = node;
    oikeaLapsiNode->vari = node->vari;
    node->vari = PUNAINEN;
    return oikeaLapsiNode;
}

// NODEN KIERTO OIKEALLE
TreeNode* kiertoOikealle(TreeNode* node) {
    TreeNode* vasenLapsiNode = node->vasenNode;
    node->vasenNode = vasenLapsiNode->oikeaNode;
    vasenLapsiNode->oikeaNode = node;
    vasenLapsiNode->vari = node->vari;
    node->vari = PUNAINEN;
    return vasenLapsiNode;
}

// TASAPAINOTA PUU
TreeNode* tasapainota(TreeNode* node) {
    if (onPunainen(node->oikeaNode) && !onPunainen(node->vasenNode))
        node = kiertoVasemmalle(node);

    if (onPunainen(node->vasenNode) && onPunainen(node->vasenNode->vasenNode))
        node = kiertoOikealle(node);

    if (onPunainen(node->vasenNode) && onPunainen(node->oikeaNode)) {
        node->vari = PUNAINEN;
        node->vasenNode->vari = MUSTA;
        node->oikeaNode->vari = MUSTA;
    }

    return node;
}

// LISÄÄ NODE PUUHUN
TreeNode* lisaaNodePuuhun(TreeNode* juuriNode, char *nimi, int maara) {
    if (juuriNode == NULL) {
        return uusiNode(nimi, maara);
    }

    if (maara < juuriNode->maara) {
        juuriNode->vasenNode = lisaaNodePuuhun(juuriNode->vasenNode, nimi, maara);
    }
    else if (maara > juuriNode->maara) {
        juuriNode->oikeaNode = lisaaNodePuuhun(juuriNode->oikeaNode, nimi, maara);
    } else {
        // MÄÄRÄT SAMAT, VERTAA NIMIÄ AAKKORSJÄESTYKSESSÄ
        if (strcmp(nimi, juuriNode->nimi) < 0)
            juuriNode->vasenNode = lisaaNodePuuhun(juuriNode->vasenNode, nimi, maara);
        else
            juuriNode->oikeaNode = lisaaNodePuuhun(juuriNode->oikeaNode, nimi, maara);
    }

    return tasapainota(juuriNode);
}

// LISÄÄ NODE PUUHUN ILMAN TASAPAINOITUSTA (TESTEJÄ VARTEN)
TreeNode* lisaaNodePuuhunIlmanTasapainoitusta(TreeNode* juuriNode, char *nimi, int maara) {
    if (juuriNode == NULL) {
        return uusiNode(nimi, maara);
    }
    if (maara < juuriNode->maara) {
        juuriNode->vasenNode = lisaaNodePuuhunIlmanTasapainoitusta(juuriNode->vasenNode, nimi, maara);
    } else if (maara > juuriNode->maara) {
        juuriNode->oikeaNode = lisaaNodePuuhunIlmanTasapainoitusta(juuriNode->oikeaNode, nimi, maara);
    } else {
        if (strcmp(nimi, juuriNode->nimi) < 0) {
            juuriNode->vasenNode = lisaaNodePuuhunIlmanTasapainoitusta(juuriNode->vasenNode, nimi, maara);
        } else {
            juuriNode->oikeaNode = lisaaNodePuuhunIlmanTasapainoitusta(juuriNode->oikeaNode, nimi, maara);
        }
    }

    return juuriNode;
}

// LISÄÄ JA PALAUTA PUUN JUURI
TreeNode* lisaaJaPalautaJuuri(TreeNode* juuri, char *nimi, int maara) {
    juuri = lisaaNodePuuhun(juuri, nimi, maara);
    juuri->vari = MUSTA;
    return juuri;
}

// TIEDOSTON LUKU
TreeNode *lueTiedostoPuuhun(TreeNode *juuri, char *tiedostonimi) {
    FILE *tiedosto = fopen(tiedostonimi, "r");
    if (!tiedosto) {
        printf("Tiedoston avaaminen epäonnistui.\n");
        return juuri;
    }

    char rivi[100];
    char *pNimi, *pMaara;
    int maara;

    // EKAN RIVIN LUKEMINEN
    fgets(rivi, 100, tiedosto);

    while (fgets(rivi, 100, tiedosto) != NULL) {
        if ((pNimi = strtok(rivi, ";")) == NULL) {
            printf("Merkkijonon %s pilkkominen epäonnistui, lopetetaan.\n", rivi);
            exit(0);
        }

        if ((pMaara = strtok(NULL, ";")) == NULL) {
            printf("Merkkijonon %s pilkkominen epäonnistui, lopetetaan.\n", rivi);
            exit(0);
        }

        maara = atoi(pMaara);
        juuri = lisaaJaPalautaJuuri(juuri, pNimi, maara);
    }
    fclose(tiedosto);
    return juuri;
}

// LUO UUSI JONO
Jono* luoJono() {
    Jono *j = (Jono*)malloc(sizeof(Jono));
    j->etu = j->taka = NULL;
    return j;
}

// Poista solmu jonosta
TreeNode* poistaJonosta(Jono *jono) {
    if (jono->etu == NULL) {
        return NULL;
    }

    JonoSolmu *vanha = jono->etu;
    TreeNode *solmu = vanha->solmu;
    jono->etu = jono->etu->seuraava;

    if (jono->etu == NULL) {
        jono->taka = NULL;
    }

    free(vanha);
    return solmu;
}

// Tässä ny L11 poisto homma, teen sen ny tähä tiedostoo ku se kuuluu tähän samaa valikkoo
TreeNode* etsiPoistettavaSolmu(TreeNode *juuri, int etsittavaArvo, const char *etsiNimi) {
    if (juuri == NULL) {
        return NULL;  // jos tyhjä
    }
    // Onko solmun arvo tai nimi oikea
    if (juuri->maara == etsittavaArvo || (etsiNimi != NULL && strcmp(juuri->nimi, etsiNimi) == 0)) {
        return juuri;  // Löyty
    }

    // kutsut vasempaan ja oikeaan puuhun
    TreeNode *vasen = etsiPoistettavaSolmu(juuri->vasenNode, etsittavaArvo, etsiNimi);
    if (vasen != NULL) {
        return vasen;
    }
    return etsiPoistettavaSolmu(juuri->oikeaNode, etsittavaArvo, etsiNimi);
}

// Poistetaan solmu puusta
TreeNode* poistaSolmu(TreeNode *juuri, TreeNode *solmuPoistettavaksi) {
    if (juuri == NULL) {
        return NULL;
    }

    if (juuri == solmuPoistettavaksi) {
        TreeNode *temp = NULL;

        // Jos solmu ei lehtisolmu
        if (juuri->vasenNode == NULL) {
            temp = juuri->oikeaNode;
            free(juuri);
            return temp;
        } else if (juuri->oikeaNode == NULL) {
            temp = juuri->vasenNode;
            free(juuri);
            return temp;
        }

        // Jos solmulla kaks lasta
        temp = etsiPieninSolmu(juuri->oikeaNode);
        juuri->maara = temp->maara;
        strcpy(juuri->nimi, temp->nimi);
        juuri->oikeaNode = poistaSolmu(juuri->oikeaNode, temp);

        return juuri;
    }

    // Etitään puussa oikee paikka
    if (solmuPoistettavaksi->maara < juuri->maara) {
        juuri->vasenNode = poistaSolmu(juuri->vasenNode, solmuPoistettavaksi);
    } else if (solmuPoistettavaksi->maara > juuri->maara) {
        juuri->oikeaNode = poistaSolmu(juuri->oikeaNode, solmuPoistettavaksi);
    }
    return juuri;
}

// ETSI PIENIN SOLMU
TreeNode* etsiPieninSolmu(TreeNode *juuri) {
    while (juuri != NULL && juuri->vasenNode != NULL) {
        juuri = juuri->vasenNode;  // Etitää vasurista pienin solmu.
    }
    return juuri;
}

// binäärihaku, käytetään tässä rekursiota niin on perhanan tehokasta
TreeNode* binaarihaku(TreeNode* juuri, int etsittava){
    if (juuri == NULL) {
        printf("Arvoa %d ei löydy!\n",etsittava);
        return NULL;
    }

    if (juuri->maara == etsittava) {
        printf("Löydettiin arvo %d, nimi on %s\n",etsittava, juuri->nimi);
        return juuri;
    }
    
    if (juuri->maara < etsittava) {
        juuri = juuri->oikeaNode;
        return (binaarihaku(juuri, etsittava));

    } else {
        juuri = juuri->vasenNode;
        return(binaarihaku(juuri, etsittava)); 
    }

    return NULL;
}