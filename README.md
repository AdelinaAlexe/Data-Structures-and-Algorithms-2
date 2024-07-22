Tema2 - Structuri si de date si Algoritmi
Alexe Adelina Maria - 312CC

In implementarea cerintelor, am folosit urmatoarele functii:

Functia initT:
Initializeaza arborele si aloca memoria pentru campurile aferente din
structura.
Pentru campul value am alocat dinamic un sir de caractere, chiar daca la
inceput
in acesta se retine decat un singur caracter, pentru a avea posibilitatea de
memorare a unui intreg sufix ulterior.

Functia charToIndex:
Atribuie fiecarui caracter indicele corespunzator din vectorul de succesori.
Caracterului '$' ii este asociata pozitia 0, iar caracterelor din alfabet de 
la 'a' la 'z', pozitiile 1-26.

Functia insertChild:
Creeaza un nou nod pentru un caracter, folosind functia initT.

Functia insertWord:
Adauga un intreg cuvant in arbore, caracter cu caracter, folosind functia de
mai sus.

Functia heightT:
Calculeaza inaltimea maxima a arborelui.

Functia printLevel:
Afiseaza toate caracterele care se afla la un anumit nivel din arbore
( afiseaza pe nivel ).

Functia printT:
Afiseaza intreg arborele, pe nivele, folosind functia de mai sus.

Functia leavesT:
Numara cate frunze exista in arbore, adica cate caractere '$', pentru ca
acestea se afla la finalul
oricarui sufix, adica la finalul oricarei ramuri.

Functia kSufix:
Numara cate sufixe de lungime k exista, numarand caracter cu caracter pana la
lungimea k, coborand
nivel cu nivel in arbore pana ajunge la caracterul terminal '$'.

Functia nrDesc:
Numara cati descendenti directi are un nod.

Functia maxDesc:
Calculeaza numarul maxim de descenti directi pe care ii poate avea un nod,
folosind
functia de mai sus.

Functia findWord:
Verifica existenta unui anumit sufix in arbore, caracter cu caracter.

Functia uniqChild:
Verifica daca un nod are un singur nod "copil", si daca da, il returneaza

Functia decreaseLevel:
Decrementeaza nivelele nodurilor de la un anumit nod in jos.

Functia concatT:
In aceasta functie am verificat pentru fiecare nod daca are un singur
descendent direct
folosind functia de mai sus. In caz pozitiv, am concatenat valorile celor
doua noduri
si am atribuit rezultatul valorii nodului copil. Am facut legatura cu intre
nodul parinte
nodului curent si nodul copil si am eliberat memoria pentru nodul curent si
campurile
aferente.

Functia freeT:
Elibereaza memoria pentru intreg arborele corespunzator.

In functia main:
Am deschis fisierele in functie de pozitia la care se afla numele lor in
vectorul de 
argumente in linia de comanda.

Am citit din fisier in functie de cerinta data ca argument in linia de comada
si am 
apelat functiile corespunzatoare.

Am eliberat memoria pentru arbore si toate celelalte variabile folosite.
