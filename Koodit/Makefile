# /*************************************************************************/
# /* CT60A2600 Ohjelmakehitys C-kielellä
# * Tiimi: 13
# * Tekijä: Antti Keronen
# * Opiskelijanumero:001855050
# * Päivämäärä: 09.03.2025
# * Tämän ohjelman tekemisessä on käytetty kurssilla annettujen materiaalien
# * ja ohjeiden lisäksi seuraavia lähteitä, työkaluja ja henkilöitä:
# * Käytetyn aputyökalun nimi ja versio tai henkilön nimi
# * Käytön tarkoitus
# * Yksityiskohtainen selvitys siitä, missä ohjelman osissa aputyökalua on
# * käytetty ja miten, tai miten ko. henkilö on vaikuttanut ohjelmaan
# */
# /*************************************************************************/
# /* Tehtävä L10, tiedoston nimi Makefile */

projekti: main.o linkitettyListaKirjasto.o binaariPuuKirjasto.o graafiKirjasto.o
	gcc -o projekti main.o linkitettyListaKirjasto.o binaariPuuKirjasto.o graafiKirjasto.o

main.o: main.c linkitettyListaKirjasto.h binaariPuuKirjasto.h graafiKirjasto.h
	gcc -c main.c -std=c99 -pedantic -Wall

linkitettyListaKirjasto.o: linkitettyListaKirjasto.c linkitettyListaKirjasto.h
	gcc -c linkitettyListaKirjasto.c -std=c99 -pedantic -Wall

binaariPuuKirjasto.o: binaariPuuKirjasto.c binaariPuuKirjasto.h
	gcc -c binaariPuuKirjasto.c -std=c99 -pedantic -Wall

graafiKirjasto.o: graafiKirjasto.c graafiKirjasto.h
	gcc -c graafiKirjasto.c -std=c99 -pedantic -Wall

#LINKLISTAN TESTIT
test1: linkitettyListaTestit.o linkitettyListaKirjasto.o
	gcc -o test_linkitettyLista linkitettyListaTestit.o linkitettyListaKirjasto.o
	./test_linkitettyLista

linkitettyListaTestit.o: linkitettyListaTestit.c linkitettyListaKirjasto.h
	gcc -c linkitettyListaTestit.c -std=c99 -pedantic -Wall

#BINÄÄRIPUU TESTIT
test2: binaariPuuTestit.o binaariPuuKirjasto.o
	gcc -o test_binaariPuu binaariPuuTestit.o binaariPuuKirjasto.o
	./test_binaariPuu

binaariPuuTestit.o: binaariPuuTestit.c binaariPuuKirjasto.h
	gcc -c binaariPuuTestit.c -std=c99 -pedantic -Wall

#GRAAFI TESTIT
test3: graafiTestit.o graafiKirjasto.o
	gcc -o test_graafi graafiTestit.o graafiKirjasto.o
	./test_graafi

graafiTestit.o: graafiTestit.c graafiKirjasto.h
	gcc -c graafiTestit.c -std=c99 -pedantic -Wall

clean:
	rm -f *.o projekti test_linkitettyLista test_binaariPuu test_graafi output.txt