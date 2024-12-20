/**
 * @file utils.c
 * @brief Implementazione delle funzioni di utilità per la stampa di testo colorato
 *        e la visualizzazione dei menu per la generazione di password.
 *
 * Questo file fornisce funzioni di utilità che includono:
 *  - Gestione dei codici colore ANSI per l'output nel terminale.
 *  - Visualizzazione dei menu di generazione password e delle informazioni di aiuto.
 *
 * @version 1.1.0
 * @date 2024-12-20
 * @author Michele Camassa
 */

#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include "utils.h"

/* - - - - - - - - - - - - - - - - - COLORI - - - - - - - - - - - - - - - - - */

/**
 * @brief Restituisce il codice di escape ANSI per il colore specificato.
 *
 * Questa funzione mappa un valore di enumerazione `textColor` al corrispondente
 * codice di escape ANSI per l'output del colore nel terminale.
 *
 * @param[in] color Il colore da utilizzare, come specificato nell'enum `textColor`.
 * @return Una stringa contenente il codice di escape ANSI per il colore.
 *         Se l'input è invalido, restituisce il codice di reset `RESET`.
 */
const char *generate_ansi_color_code(textColor color) {
    switch(color) {
		case BLACK: 	return "\033[30m";
		case RED:		return "\033[31m";
		case GREEN:		return "\033[32m";
		case YELLOW:	return "\033[33m";
		case BLUE:		return "\033[34m";
		case MAGENTA:	return "\033[35m";
		case CYAN: 		return "\033[36m";
		case WHITE: 	return "\033[37m";
		case RESET: 	return "\033[0m";
		default: 		return "\033[0m";
	}
}

/**
 * @brief Stampa una stringa nel colore specificato.
 *
 * Questa funzione avvolge il testo fornito nei codici di escape ANSI per il colore
 * desiderato e lo stampa nel terminale. Il colore viene resettato al termine della stampa.
 *
 * @param[in] text Il testo da stampare. Deve essere una stringa valida terminata da NULL.
 * @param[in] color Il colore da applicare, come specificato nell'enum `textColor`.
 *
 * @pre `text` non deve essere NULL.
 * @post Il testo viene visualizzato nel terminale con il colore specificato.
 */
void print_with_color(const char *text, textColor color) {
	if (text == NULL) return;
    printf("%s%s%s", generate_ansi_color_code(color), text, generate_ansi_color_code(RESET));
}

/* - - - - - - - - - - - - - - - - FINE COLORI - - - - - - - - - - - - - - - - */

/* - - - - - - - - - - - - - - - - - MENU DI AIUTO PER LA PASSWORD - - - - - - - - - - - - */

/**
 * @brief Visualizza il menu di aiuto per il generatore di password.
 *
 * Questo menu fornisce una guida dettagliata sui comandi disponibili per la generazione della password,
 * inclusi le opzioni di lunghezza e tipo.
 */
void show_help_menu() {
	const char *help_text =
		"\nMenu di Aiuto del Generatore di Password\n"
		"Comandi:\n"
		" h        : mostra questo menu di aiuto\n"
		" n LENGTH : genera password numerica (solo numeri)\n"
		" a LENGTH : genera password alfabetica (solo lettere minuscole)\n"
		" m LENGTH : genera password mista (lettere minuscole e numeri)\n"
		" s LENGTH : genera password sicura (lettere maiuscole, lettere minuscole, numeri, simboli)\n"
		" u LENGTH : genera password sicura senza ambiguità (senza caratteri simili)\n"
		" q        : esci dall'applicazione\n\n"
		" La lunghezza (LENGTH) deve essere tra 6 e 32 caratteri\n\n"
		" Caratteri ambigui esclusi nell'opzione 'u':\n"
		" 0 O o (zero e lettera O)\n"
		" 1 l I i (uno e lettere l, I)\n"
		" 2 Z z (due e lettera Z)\n"
		" 5 S s (cinque e lettera S)\n"
		" 8 B (otto e lettera B)\n"
		"\nSe la lunghezza non è presente, viene utilizzato un valore predefinito: 8\n\n";
	print_with_color(help_text,CYAN);
}

/**
 * @brief Visualizza il menu principale del generatore di password.
 *
 * Questo menu invita l'utente a scegliere il tipo e la lunghezza della password
 * da generare, con spiegazioni per ogni tipo.
 */
void show_password_menu() {
	const char *menu_text =
		"Inserisci il tipo di password e la sua lunghezza (tra 6 e 32):\n"
		"  n: password numerica (solo numeri)\n"
		"  a: password alfabetica (solo lettere minuscole)\n"
		"  m: password mista (lettere minuscole e numeri)\n"
		"  s: password sicura (lettere maiuscole, lettere minuscole, numeri e simboli)\n"
		"  u: password sicura senza ambiguità (senza caratteri simili)\n"
		"  h: menu di aiuto\n"
		"  q: esci dall'applicazione\n"
		"? ";
	print_with_color(menu_text, YELLOW);
}

/* - - - - - - - - - - - FINE MENU DI AIUTO PER LA PASSWORD - - - - - - - - - - - - */
