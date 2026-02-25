/*************************************************************************/
/* CT60A2600 Ohjelmakehitys C-kielellä
* Tiimi: 13
* Tekijä: Severi Arpinen, Antti Keronen, Juuso Käyhkö
* Opiskelijanumero: 000253077, 001855050, 000493675
* Päivämäärä: 09.03.2025
* Tämän ohjelman tekemisessä on käytetty kurssilla annettujen materiaalien
* ja ohjeiden lisäksi seuraavia lähteitä, työkaluja ja henkilöitä:
* Käytetyn aputyökalun nimi ja versio tai henkilön nimi
* Käytön tarkoitus
* Yksityiskohtainen selvitys siitä, missä ohjelman osissa aputyökalua on
* käytetty ja miten, tai miten ko. henkilö on vaikuttanut ohjelmaan
*/
/*************************************************************************/
/* Tehtävä L10, tiedoston nimi main.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkitettyListaKirjasto.h"
#include "binaariPuuKirjasto.h"
#include "graafiKirjasto.h"

int paaValikko(void) {
    int valinta;
    printf("Valitse tietorakenne:\n");
    printf("1) Linkitetty lista\n");
    printf("2) Binääripuu\n");
    printf("3) Graafi\n");
    printf("0) Lopeta\n");
    printf("Anna valintasi: ");
    scanf("%d", &valinta);
    getchar();

    return valinta;
}

int linkitettyListaValikko(void) {
    int valinta;
    printf("Valitse haluamasi toiminto (linkitetty lista):\n");
    printf("1) Lue tiedosto\n");
    printf("2) Tallenna lista etuperin\n");
    printf("3) Tallenna lista takaperin\n");
    printf("4) Tyhjennä lista\n");
    printf("5) Järjestä nousevaan järjestykseen (selection sort)\n");
    printf("6) Järjestä laskevaan järjestykseen\n");
    printf("7) Järjestä nousevaan järjestykseen (insertion sort)\n");
    printf("0) Takaisin\n");
    printf("Anna valintasi: \n");
    scanf("%d", &valinta);
    getchar();

    return valinta;
}

int binaariPuuValikko(void) {
    int valinta;
    printf("Valitse haluamasi toiminto (binääripuu):\n");
    printf("1) Lue tiedosto\n");
    printf("2) Kirjoita puun arvot tiedostoon\n");
    printf("3) Syvyyshaku\n");
    printf("4) Leveyshaku\n");
    printf("5) Binääripuuhaku\n");
    printf("6) Poista solmu\n");
    printf("7) Tulosta puumaisemmassa muodossa\n");
    printf("8) Tyhjennä puu\n");
    printf("0) Takaisin\n");
    printf("Anna valintasi: ");
    scanf("%d", &valinta);
    getchar();

    return valinta;
}

int graafiValikko(void) {
    int valinta;
    printf("Valitse haluamasi toiminto (graafi):\n");
    printf("1) Lue tiedosto\n");
    printf("2) Lisää/päivitä kaari\n");
    printf("3) Poista solmu\n");
    printf("4) Etsi lyhin reitti\n");
    printf("5) Tulosta graafi\n");
    printf("6) Tyhjennä graafi\n");
    printf("0) Takaisin\n");
    printf("Anna valintasi: ");
    scanf("%d", &valinta);
    getchar();
    return valinta;
}

int main(void) {
    int paaValinta;
    int linkitettyListaValinta;
    int binaariPuuValinta;
    int graafiValinta;
    //Graafi
    GRAAFI *graafi = NULL;
    char poistettava[100];
    char tiedostonimi[100];
    
    // LINKITETTY LISTA
    Node *lista = NULL;
    Node *listanTail = NULL;
    //binääri puu
    TreeNode *juuri = NULL;
    int etsittavaArvo;
    int binaariHakuArvo;

    // Graafi
    char lyhyinReittiTiedostonNimi[100] = "";

    do {
        paaValinta = paaValikko();

        if (paaValinta == 1) {
            do {
                // LINKITETTY LISTA
                linkitettyListaValinta = linkitettyListaValikko();

                if (linkitettyListaValinta == 1) {
                    lista = tyhjenna(lista);
                    printf("Anna luettavan tiedoston nimi: ");
                    scanf("%99s", tiedostonimi);
                    lista = lueTiedosto(lista, tiedostonimi);
                    printf("\n");
        
                } else if (linkitettyListaValinta == 2) {
                    if (lista == NULL) {
                        printf("Luethan tiedoston ensin!\n");
                        printf("\n");
                        continue;
                    }
                    printf("Anna kirjoitettavan tiedoston nimi: ");
                    scanf("%99s", tiedostonimi);
                    tallennaTiedostoon(lista, tiedostonimi);
                    printf("\n");
        
                } else if (linkitettyListaValinta == 3) {
                    if (lista == NULL) {
                        printf("Luethan tiedoston ensin!\n");
                        printf("\n");
                        continue;
                    }
                    printf("Anna kirjoitettavan tiedoston nimi: ");
                    scanf("%99s", tiedostonimi);
        
                    listanTail = lista;
                    while(listanTail->seuraava != NULL) {
                        listanTail = listanTail->seuraava;
                    }
        
                    tallennaTiedostoonTakaperin(listanTail, tiedostonimi);
                    printf("\n");
        
                } else if (linkitettyListaValinta == 4) {
                    if (lista == NULL) {
                        printf("Lista on jo tyhjä!\n");
                        printf("\n");
                        continue;
                    }
        
                    lista = tyhjenna(lista);
                    printf("Lista tyhjennetty.\n");
        
                    printf("\n");
                
        
                } else if (linkitettyListaValinta == 5){
                    // NOUSEVAAN JÄRJESTYKSEEN (SELECTION SORT)
                    if (lista == NULL) {
                        printf("Luethan tiedoston ensin!\n");
                        printf("\n");
                        continue;
                    }
        
                    valintaLajittelu(lista);
                    printf("Lista lajiteltu nousevaan järjestykseen.\n");
                    printf("\n");
                } else if (linkitettyListaValinta == 6){
                    // LASKEVAAN JÄRJESTYKSEEN
                    if (lista == NULL) {
                        printf("Luethan tiedoston ensin!\n");
                        printf("\n");
                        continue;
                    }
        
                    kuplaLajittelu(lista);
                    printf("Lista lajiteltu laskevaan järjestykseen.\n");
                    printf("\n");
                    
        
                } else if (linkitettyListaValinta == 7){
                    // NOUSEVAAN JÄRJESTYKSEEN (INSERTION SORT)
                    if (lista == NULL) {
                        printf("Luethan tiedoston ensin!\n");
                        printf("\n");
                        continue;
                    }
        
                    lisaysLajittelu(lista);
                    printf("Lista lajiteltu nousevaan järjestykseen.\n");
                    printf("\n");
                } else if (linkitettyListaValinta == 0) {
                    printf("Lopetetaan.\n");
                    printf("\n");
                } else {
                    printf("Tuntematon valinta, yritä uudestaan.\n");
                    printf("\n");
                }
                
            } while (linkitettyListaValinta != 0);
        } else if (paaValinta == 2) {
            do {
                // BINÄÄRIPUU
                binaariPuuValinta = binaariPuuValikko();

                if (binaariPuuValinta == 1) {
                    printf("Anna luettavan tiedoston nimi: ");
                    scanf("%99s", tiedostonimi);
                    juuri = lueTiedostoPuuhun(juuri,tiedostonimi);
                    printf("Tiedosto luettu.\n");
                    printf("\n");

                } else if (binaariPuuValinta == 2) {
                    if (juuri == NULL) {
                        printf("Puu on tyhjä, luethan tiedoston ensin.\n");
                        printf("\n");
                        continue;
                    }

                    printf("Anna kirjoitettavan tiedoston nimi: ");
                    scanf("%99s",tiedostonimi);
                    kirjoitaPuuTiedostoon(juuri, tiedostonimi); 
                    printf("\n");
                
                } else if (binaariPuuValinta == 3) {
                    if (juuri == NULL) {
                        printf("Puu on tyhjä, luethan tiedoston ensin.\n");
                        printf("\n");
                        continue;
                    }

                    printf("Anna etsittävä arvo: ");
                    scanf("%d",&etsittavaArvo);
                    printf("Anna kirjoitettavan tiedoston nimi: ");
                    scanf("%99s", tiedostonimi);
                    suoritaSyvyyshaku(juuri, etsittavaArvo, tiedostonimi);
                    printf("\n");

                } else if (binaariPuuValinta == 4) {
                    if (juuri == NULL) {
                        printf("Puu on tyhjä, luethan tiedoston ensin.\n\n");
                        continue;
                    }
                
                    char etsittava[100];
                    printf("Anna etsittävä arvo: ");
                    scanf("%99s", etsittava);
                
                    printf("Anna kirjoitettavan tiedoston nimi: ");
                    scanf("%99s", tiedostonimi);
                
                    suoritaLeveydensuuntainenHaku(juuri, etsittava, tiedostonimi);


                } else if (binaariPuuValinta == 5){
                    if (juuri == NULL) {
                        printf("Puu on tyhjä, luethan tiedoston ensin.\n\n");
                        continue;
                    }
                    printf("Anna etsittävä lukumäärä: ");
                    scanf("%d",&binaariHakuArvo);
                    binaarihaku(juuri, binaariHakuArvo);

                } else if (binaariPuuValinta == 6) {
                    if (juuri == NULL) {
                        printf("Puu on tyhjä, ei poistettavia solmuja.\n");
                    } else {
                        char syote[50];
                        int maara = 0;
                        char nimi[50];
                
                        printf("Anna poistettava arvo: ");
                        scanf("%s", syote);
                
                        if (sscanf(syote, "%d", &maara) == 1) {
                            // Etsi määrällä
                            TreeNode *solmu = etsiPoistettavaSolmu(juuri, maara, NULL);
                            if (solmu == NULL) {
                                printf("Arvoa %d ei löytynyt puusta.\n", maara);
                            } else {
                                printf("Poistetaan arvoa %s, %d...", solmu->nimi, solmu->maara);
                                suoritaPoisto(&juuri, maara, NULL);
                            }
                        } else {
                            strcpy(nimi, syote);
                            TreeNode *solmu = etsiPoistettavaSolmu(juuri, 0, nimi);
                            //etsi nimellä
                            if (solmu == NULL) {
                                printf("Nimeä %s ei löytynyt puusta.\n", nimi);
                                printf("\n");
                            } else {
                                printf("Poistetaan arvoa %s, %d...", nimi, solmu->maara);
                                suoritaPoisto(&juuri, 0, nimi);
                            }
                        }
                    }
                } else if (binaariPuuValinta == 7) {
                    if (juuri == NULL) {
                        printf("Puu on tyhjä, luethan tiedoston ensin.\n\n");
                        continue;
                    }

                    printf("Binääripuu tulostetaan:\n");
                    tulostaPuu(juuri, 0);
                    printf("\n");            
                } else if (binaariPuuValinta == 8) {  
                    if (juuri == NULL) {
                        printf("Puu on jo tyhjä.\n\n");
                        continue;
                    }
                    tyhjennaPuu(juuri);
                    juuri = NULL;
                    printf("Puu tyhjennetty.\n\n");

                } else if (binaariPuuValinta == 0) {
                    printf("Palataan päävalikkoon.\n\n");
                } else {
                    printf("Tuntematon valinta, yritä uudestaan.\n\n");
                }
            } while (binaariPuuValinta != 0);
        } else if (paaValinta == 3) {
            do {
                graafiValinta = graafiValikko();

                if (graafiValinta == 1) {
                    
                    char tiedostonNimi[256];
                    printf("Anna tiedoston nimi: ");
                    scanf("%s", tiedostonNimi);
                    lueGraafiTiedostosta(tiedostonNimi, &graafi);

                
                } else if (graafiValinta == 2) {
                    lisaaJaPaivitaKaari(&graafi);
                
                } else if (graafiValinta == 3) {
                    printf("Anna poistettavan solmun nimi: ");
                    scanf("%s",poistettava);
                    poistaSolmuGraafista(&graafi,poistettava);
             
                } else if (graafiValinta == 4) {
                    if (graafi == NULL) {
                        printf("Graafi on tyhjä!\n");
                        printf("\n");
                        continue;
                    }

                    char lahtoSolmu[100] = "";
                    char loppuSolmu[100] = "";
                    
                    // JOS TIEDOSTON NIMEÄ EI OLE ANNETTU
                    if (strlen(lyhyinReittiTiedostonNimi) == 0) {
                        printf("Mihin tiedostoon lyhyin reitti tallennetaan? ");
                        scanf("%s", lyhyinReittiTiedostonNimi);
                    }
                    
                    printf("Aloitus: ");
                    scanf("%s",lahtoSolmu);
                    printf("Lopetus: ");
                    scanf("%s",loppuSolmu);

                    
                    if (etsiLyhyinReittiJaTallennaTiedostoon(graafi, lahtoSolmu, loppuSolmu, lyhyinReittiTiedostonNimi)) {
                        printf("Lyhin reitti tallennettu tiedostoon %s\n", lyhyinReittiTiedostonNimi);
                    }
                } else if (graafiValinta == 5) {
                    if (graafi == NULL) {
                        printf("Graafi on tyhjä!\n");
                        printf("\n");
                        continue;
                    }
                    tulostaGraafi(graafi);
                
                } else if (graafiValinta == 6) {
                    vapautaGraafi(&graafi);
                    printf("Graafi tyhjennetty!\n");

                } else if (graafiValinta == 0) {
                    printf("Palataan päävalikkoon.\n\n");
                } else {
                    printf("Tuntematon valinta, yritä uudestaan.\n\n");
                }

                printf("\n");
            } while (graafiValinta != 0);
        }
    } while (paaValinta != 0);

    lista = tyhjenna(lista);
    tyhjennaPuu(juuri);
    vapautaGraafi(&graafi);

    printf("Kiitos ohjelman käytöstä.\n");

    return 0;
}
