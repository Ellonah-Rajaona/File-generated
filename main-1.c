#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

    // LECTURE FICHIER "int.csv"
    FILE *csv = fopen("int.csv", "r");

    // CREATION DY FICHIER "tableau.html"
    FILE *html = fopen("tableau.html", "w");

    // VERIFICATION OUVERTURE
    if (csv == NULL || html == NULL) {
        printf("Erreur lors de l'ouverture des fichiers\n");
        return 1;
    }

    char ligne[1024];
    int premiere_ligne = 1;

    // ---------- HTML ----------
    fprintf(html, "<!DOCTYPE html>\n");
    fprintf(html, "<html>\n");


    fprintf(html, "<head>\n");
    fprintf(html, "<meta charset=\"UTF-8\">\n");
    fprintf(html, "<title>Tableau</title>\n");
    fprintf(html, "</head>\n");


    fprintf(html, "<body>\n");
    fprintf(html, "<h2>Tableau des donnees genere via le langage C</h2>\n");

    fprintf(html, "<table>\n");

    // ---------- Lecture CSV ----------
    while (fgets(ligne, sizeof(ligne), csv)) {

        // Si c'est la première ligne → en-tête
        if (premiere_ligne) {
            fprintf(html, "<thead>\n<tr>");
        } else {
            fprintf(html, "<tr>");
        }

        // Découpage
        char *t = strtok(ligne, ";");

        while (t != NULL) {

            // Supprimer le \n
            t[strcspn(t, "\n")] = 0;

            // Si en-tête <th>, sinon <td>
            if (premiere_ligne) {
                fprintf(html, "<th>%s</th>", t);
            } else {
                fprintf(html, "<td>%s</td>", t);
            }

            t = strtok(NULL, ";");
        }

        // Fermer ligne
        fprintf(html, "</tr>\n");

        // Fermer thead après première ligne
        if (premiere_ligne) {
            fprintf(html, "</thead>\n<tbody>\n");
            premiere_ligne = 0;
        }
    }

    // ---------- Fin HTML ----------
    fprintf(html, "</tbody>\n");
    fprintf(html, "</table>\n");

    fprintf(html, "</body>\n");
    fprintf(html, "</html>");

    // Fermer fichiers
    fclose(csv);
    fclose(html);

    printf("Fichier tableau.html genere avec succes !\n");

    return 0;
}
