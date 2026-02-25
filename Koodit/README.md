# CT60A2600-Tiimi13

Tietorakenteisiin ja algoritmeihin keskittyvä C-ohjelmointiprojekti LUT-yliopiston kurssille CT60A2600. README tiedosto generoitu openAI ChatGPT (malli 4o) tekoälytökalulla.

## Tiimi

- Antti Keronen (001855050)
- Severi Arpinen (000253077)
- Juuso Käyhkö (000493675)

## Tiedostot

| Tiedosto | Kuvaus |
|---------|--------|
| `main.c` | Pääohjelma, joka käyttää kaikkia kirjastoja |
| `linkitettyListaKirjasto.c/h` | Linkitetyn listan toteutus ja rajapinta |
| `linkitettyListaTestit.c` | Linkitetyn listan testejä |
| `binaariPuuKirjasto.c/h` | Binaaripuun toteutus ja rajapinta |
| `binaariPuuTestit.c` | Binaaripuun testejä |
| `graafiKirjasto.c/h` | Graafien käsittely (verkot, solmut, reunat) |
| `graafiTestit.c` | Graafikirjaston testejä |
| `Makefile` | Kääntämiseen käytettävät säännöt ja komennot |
| `*.txt` | Testi- ja syötetiedostoja (esim. `graafiData.txt`, `PuuData.txt`) |
| `.gitignore` | Gitin ohjeistus ohitettavista tiedostoista |

## Kääntäminen ja testaus

Käännä kaikki:

```make```

Aja pääohjelma:

```./projekti```

Testien ajaminen

```make test1``` (Linkitetty lista)

```make test2``` (Binääripuu)

```make test3``` (Graafi)

Siivoa käännösjäämät

```make clean```