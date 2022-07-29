#!/bin/bash
#lukee tiedoston
cat midsummer_nights_dream.txt | 
# muuttaa kaikki ei-alphanumeeriset merkit ja korvaa ne "\n":llä eli muuttaa sanojen välissä olevat välit rivinvaihdoiksi.
tr -cs "[:alnum:]" "\n"| 
# muuttaa kaikki isot kirjaimet pieniksi
tr "[:upper:]" "[:lower:]" |
# järjestää
sort | 
# Laskee kuinka monta kertaa sanat esiintyvät
uniq -c |
# järjestää numerot reverse järjestyksessä
sort -nr | 
# näyttää rivinumeron
cat -n | 
# lukee 10 ensimmäistä riviä
head -n 10
