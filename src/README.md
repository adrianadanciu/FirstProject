# Manager de portofoliu Gigiquant

Acest proiect se imparte in patru parti: calcularea indicatorul Sharpe ratio, calcularea oportunitatilor de arbitraj, optimizarea portofoliului prin diversificare si calcularea tiparelor de tranzitie intre preturi folosind lanturile Markov.

## Rularea programului

Programul contine un fisier central de rulare (main.c), care, pe baza fisierul de intrare dat, ruleaza automat task-ul corect.

## Sharpe ratio

Prima parte a proiectul utilizeaza liste simplu inlantuite pentru a calcula acest indicatorul, folosindu-se, de asemenea, de formula S = (randamentul mediu - randamentul fara risc) / volatilitate

## Arbitraj

Se folosesc trei stive si o coada pentru a compara valorile preturilor in fiecare zi. In cazul in care, pe o zi, preturile a doua orase sunt egale, iar cel de al treilea difera, exista oportunitate de arbitraj, care este stocata ulterior in coada

## Diversificarea portofoliului

Se stocheaza actiunile intr-un arbore binar si se cauta opusul acestuia, daca exista. Regula de stocare este ca stanga oricarui nod reprezinta o scadere a valorii, iar dreapta o crestere a acesteia.

## Lanturi Markov

Se calculeaza starea fiecarui pret dat, urmata de matricea de tranzitie, in care se afla probabiliteta de a se trece din starea i in starea j. Cu ajutorul acesteia, se calculeaza probabilitatea de a se ajunge dintr-un pret initial intr-un pret final, in fiecare zi, pe o perioada de k zile data.