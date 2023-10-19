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
 
    if (argc == 2) 
    { 
        int s; /* Per treballar amb el socket */ 
        struct sockaddr_in serv_adr, client_adr; 
        char buffer[MIDA_BUFFER]; 
        socklen_t mida; 
        int n, i; 
        int port; 
 
        /* Volem socket d'internet i no orientat a la connexio */ 
        s = socket(AF_INET, SOCK_DGRAM, 0); 
 
        /* Posem les dades del socket */ 
        serv_adr.sin_family = AF_INET; 
        serv_adr.sin_addr.s_addr = INADDR_ANY; 
        serv_adr.sin_port = htons(atoi(argv[1])); 
 
        /* Enllacem el socket */ 
        n = bind(s, (struct sockaddr *)&serv_adr, sizeof(serv_adr)); 
 
        if (n < 0) 
        { 
            printf("No s'ha pogut enllacar el socket\n"); 
        } 
        else 
        { 
            i = 0; 
            /* Servidor operatiu! */ 
            printf("Servidor operatiu al port %d!\n", atoi(argv[1])); 
 
            while (i < 5) /* Nomes rebre cinc paquets */ 
            { 
                recvfrom(s, buffer, MIDA_BUFFER, 0, (struct sockaddr *)&client_adr, &mida); 
                printf("Paquet rebut!\n"); 
                printf("%s\n", buffer); 
                i++; 
            } 
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

  