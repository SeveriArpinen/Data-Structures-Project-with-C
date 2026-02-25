/*************************************************************************/
/* CT60A2600 Ohjelmakehitys C-kielellä
* Tiimi: 13
* Tekijä: Antti Keronen, Juuso Käyhkö
* Opiskelijanumero: 001855050, 000493675
* Päivämäärä: 19.03.2025
* Tämän ohjelman tekemisessä on käytetty kurssilla annettujen materiaalien
* ja ohjeiden lisäksi seuraavia lähteitä, työkaluja ja henkilöitä:
* Käytetyn aputyökalun nimi ja versio tai henkilön nimi
* Käytön tarkoitus
* Yksityiskohtainen selvitys siitä, missä ohjelman osissa aputyökalua on
* käytetty ja miten, tai miten ko. henkilö on vaikuttanut ohjelmaan
*/
/*************************************************************************/
/* Tehtävä L10, tiedoston nimi binaariPuuKirjasto.h*/

#ifndef BINAARIPUUKIRJASTO_H
#define BINAARIPUUKIRJASTO_H

# define PUNAINEN 0
# define MUSTA 1

typedef struct TreeNode {
    char nimi[100];
    int maara;
    int vari; //  PUNAINEN = 0, MUSTA = 1
    struct TreeNode* vasenNode;
    struct TreeNode* oikeaNode;
} TreeNode;

// Jonon solmu
typedef struct JonoSolmu {
    TreeNode *solmu;
    struct JonoSolmu *seuraava;
} JonoSolmu;

// Jonorakenne
typedef struct {
    JonoSolmu *etu, *taka;
} Jono;

TreeNode *lisaaNodePuuhun(TreeNode *juuriNode, char* nimi, int maara);
TreeNode *lisaaNodePuuhunIlmanTasapainoitusta(TreeNode *juuriNode, char* nimi, int maara);
TreeNode *lueTiedostoPuuhun(TreeNode *juuri, char *tiedostonimi);
void kirjoitaPuuTiedostoon(TreeNode *juuri, char *tiedostonimi);
void suoritaSyvyyshaku(TreeNode *juuri, int etsittava, char *tiedostonimi);
void suoritaLeveydensuuntainenHaku(TreeNode *juuri, char *etsittava, char *tiedostonimi);
void tyhjennaPuu(TreeNode *juuri);
void tulostaPuu(TreeNode *juuri, int taso);
TreeNode* etsiPoistettavaSolmu(TreeNode *juuri, int etsittavaArvo, const char *etsiNimi);
TreeNode* etsiPieninSolmu(TreeNode *juuri);
TreeNode* binaarihaku(TreeNode* juuri, int etsittava);
TreeNode* poistaSolmu(TreeNode *juuri, TreeNode *solmuPoistettavaksi);
void suoritaPoisto(TreeNode **juuri, int etsittavaArvo, const char *etsiNimi);


//Jono
Jono* luoJono();
void lisaaJonoon(Jono *jono, TreeNode *solmu);
TreeNode* poistaJonosta(Jono *jono);
int onkoJonoTyhja(Jono *jono);
void vapautaJono(Jono *jono);



#endif
