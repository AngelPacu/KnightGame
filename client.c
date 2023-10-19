/* CLIENT */
/* Es tracta d'un exemple per als professors */
/* Als estudiants els posarem un esquelet */

/* Inclusio de fitxers .h habituals */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Inclusio de fitxers .h per als sockets */
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MIDA_BUFFER 1024

int main(int argc, char **argv)
{

    if (argc == 3)
    {

        int s; /* Per treballar amb el socket */
        struct sockaddr_in adr;
        char buffer[MIDA_BUFFER];
        int i;

        /* Volem socket d'internet i no orientat a la connexio */
        s = socket(AF_INET, SOCK_DGRAM, 0);

        adr.sin_family = AF_INET;
        adr.sin_port = htons(atoi(argv[2]));

        /* L'adreca de comunicacio sera la IP del servidor, es a dir el parametre */
        adr.sin_addr.s_addr = inet_addr(argv[1]);

        /* Generem 5 paquets i els enviem */
        for (i = 0; i < 5; i++)
        {
            buffer[0] = i + '0';
            buffer[1] = '\0';

            sendto(s, buffer, MIDA_BUFFER, 0, (struct sockaddr *)&adr, sizeof(adr));

            printf("Paquet enviat!\n");
        }

        /* Tanquem el socket */
        close(s);
    }

    else
    {
        printf("El nombre de paràmetres no és el correcte!\n");
    }

    return 0;
}