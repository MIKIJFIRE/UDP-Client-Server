Secondo esonero di Laboratorio - Reti di Calcolatori (ITPS A-L) a.a. '24-25 🎅 🎄 🎁
Progettare ed implementare un'applicazione UDP client/server, dove il server è un generatore di password che risponde alle richieste del client nel seguente modo:

Il client usa una socket UDP per inviare datagrammi al server all'indirizzo passwdgen.uniba.it (sulla porta da voi stabilita).

Quando il server riceve un datagramma da un client, visualizza sullo standard output l'indirizzo e il numero di porta del mittente, scrivendo "New request from from xxx.xxx.xxx.xxx:yyyyy".

Il client legge il tipo di password da generare dallo standard input usando i caratteri:

n: password numerica (solo cifre)
a: password alfabetica (solo lettere minuscole)
m: password mista (lettere minuscole e numeri)
s: password sicura (lettere maiuscole, minuscole, numeri e simboli)
u: password sicura senza caratteri ambigui
h: visualizza il seguente menu di aiuto
 Password Generator Help Menu
 Commands:
 h        : show this help menu
 n LENGTH : generate numeric password (digits only)
 a LENGTH : generate alphabetic password (lowercase letters)
 m LENGTH : generate mixed password (lowercase letters and numbers)
 s LENGTH : generate secure password (uppercase, lowercase, numbers, symbols)
 u LENGTH : generate unambiguous secure password (no similar-looking characters)
 q        : quit application

 LENGTH must be between 6 and 32 characters

 Ambiguous characters excluded in 'u' option:
 0 O o (zero and letters O)
 1 l I i (one and letters l, I)
 2 Z z (two and letter Z)
 5 S s (five and letter S)
 8 B (eight and letter B)
seguito dalla lunghezza desiderata (es. n 8 per una password numerica di 8 caratteri).

Il server, ricevuto il datagramma dal client, genera la password secondo i criteri richiesti e la invia al client in un nuovo datagramma UDP (es. 45237891).

Il client rimane in attesa di ricevere il datagramma di risposta dal server contenente la password generata e la visualizza sullo standard output.

Il client legge dallo standard input la successiva richiesta di generazione.

Se invece di una richiesta valida è inserito il carattere q, il client termina qui il suo processo; altrimenti, torna al punto 3.

Il server non termina mai il suo processo.

REQUISITI DI PROGETTO
Il protocollo applicativo condiviso fra client e server deve essere specificato tramite file header .h.
Creare le funzioni di generazione utilizzando i seguenti nomi: generate_numeric(), generate_alpha(), generate_mixed(), generate_secure(), e generate_unambiguous() .
La lettura da riga di comando è effettuata in una singola lettura (ossia n 8[invio], non n[invio]8[invio]).
Il client e il server devono potersi avviare senza parametri passati da riga di comando, ossia usando un indirizzo ip, nome del server, e numero di porta di default predefiniti.
La lunghezza minima della password deve essere 6 caratteri e la massima 32.
Codice e commenti dovranno essere scritti in inglese.
Il codice deve essere portabile, pertanto non potete usare librerie che sono supportate, per es., su Windows e non su MacOS/Linux o viceversa.
Il client e server devono essere creati come progetti Eclipse separati.
REQUISITI DI CONSEGNA
Se non si usa un repository GitHub, il link dovrà puntare a un archivio in formato .zip (non sono ammessi altri formati di archivio quali .rar o .7z).
L'archivio o il repository GitHub dovranno contenere esclusivamente il client e del progetto server come progetti Eclipse separati (cioè ciascuno contenente i propri file .project e .cproject, oltre che il codice).
Il link da utilizzare per la consegna dovrà essere accessibile pubblicamente, senza password nè richieste di condivisione.
NOTE
La consegna deve avvenire entro le 23.59 del giorno 22 dicembre attraverso questo form.
Non è necessario prenotarsi, tutti gli studenti che hanno superato la prova TCP sono automaticamente ammessi al secondo esonero.
L'elenco degli ammessi sarà pubblicato a tempo debito su questo indirizzo.
Gli studenti che avranno superato anche la seconda prova pratica di laboratorio potranno sostenere direttamente la prova di esame scritta, previa prenotazione su ESSE3 con indicazione nel campo note di aver già superato la prova di laboratorio attraverso gli esoneri durante il corso.
L'esonero per la prova di laboratorio sarà valido fino all'inizio del successivo insegnamento di Reti di Calcolatori per l'a.a. 25/26.
