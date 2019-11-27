#define mdp "Anonymous"
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
     
#include<sys/stat.h>
     
#include<sys/sendfile.h>
     
#include<fcntl.h>
     
    int main(int argc,char *argv[])
    {

      struct sockaddr_in server;
      struct stat obj;
      int sock,c,PORT;
      int choice;
      char buf[100], command[5], filename[20], *f,sec[20];
      int k, size, status;
      int filehandle;
      printf("\033[1;33mVeuillez inserer le port du serveur FTP pour se connecter : ");

      scanf("%d",&PORT); 
      while((strcmp(sec, mdp))!=0){
	printf("\033[1;33mNom d'utilisateur : (Ecrire 'Anonymous')\n");
	scanf("%s",&sec);
      }
      sock = socket(AF_INET, SOCK_STREAM, 0);
      if(sock == -1)
        {
          printf("\033[1;33mEchec de creation de socket");
          exit(1);
        }
      server.sin_family = AF_INET;
      server.sin_port = htons(PORT);
      server.sin_addr.s_addr = inet_addr("127.0.0.1");
      k = connect(sock,(struct sockaddr*)&server, sizeof(server));
      if(k == -1)
        {
          printf("\033[1;33mErreur de connection");
          exit(1);
        }
      printf("\t\033[1;31m_________________________________________________________\n");
      printf("\t\033[1;31m*********************************************************\n");
      printf("\t\033[1;31m       C O N N E X I O N          E T A B L I E          \n");
      printf("\t\033[1;31m            Bienvenue sur le serveur FTP de              \n");
      printf("\t\033[1;35m              BENELKADI Safouane El-Amine                \n");
      printf("\t\033[1;31m*********************************************************\n");
      printf("\t\033[1;31m_________________________________________________________\n");
      int i = 1;
      while(1)
        {
          
          printf("\033[1;32mInteragissez avec le serveur FTP en selectionnant un numero de commande:\n\t | 1- GET | 2- PUT | 3- PWD | 4- LS  | 5- CD  | 6- QUIT | \n");
	  printf("______________________________________________________________________________\n");
	  printf("\033[1;32mInteragissez avec votre machine locale en selectionnant un numero de commande:\n\t | 10- LPWD | 11- LLS | 12- LCD | \n \033[1;34mVotre Num de commande :  \033[1;36m");
          scanf("%d", &choice);
          switch(choice)
    	{
    	case 1:
    	  printf("\033[1;36mEntrez le nom du fichier: ");
    	  scanf("%s", filename);
    	  strcpy(buf, "get ");
    	  strcat(buf, filename);
    	  send(sock, buf, 100, 0);
    	  recv(sock, &size, sizeof(int), 0);
    	  if(!size)
    	    {
    	      printf("\033[1;36mAucun fichier de se nom sur le repertoire en cours.\n\n");
    	    break;
    	    }
    	  f = malloc(size);
    	  recv(sock, f, size, 0);
    	  while(1)
    	    {
    	      filehandle = open(filename, O_CREAT | O_EXCL | O_WRONLY, 0666);
    	      if(filehandle == -1)
    		{
    		  sprintf(filename + strlen(filename), "%d", i);
    		}
    	      else break;
    	    }
    	  write(filehandle, f, size, 0);
    	  close(filehandle);
    	  strcpy(buf, "cat ");
    	  strcat(buf, filename);
    	  system(buf);
    	  break;
    	case 2:
    	  printf("\033[1;36mEntrez le nom du fichier que vous souhaitiez transfere vers le serveur FTP : ");
              scanf("%s", filename);
    	  filehandle = open(filename, O_RDONLY);
              if(filehandle == -1)
                {
                  printf("\033[1;36mPas de fichier portant se nom sur la machine locale\n\n");
                  break;
                }
              strcpy(buf, "put ");
    	  strcat(buf, filename);
    	  send(sock, buf, 100, 0);
    	  stat(filename, &obj);
    	  size = obj.st_size;
    	  send(sock, &size, sizeof(int), 0);
    	  sendfile(sock, filehandle, NULL, size);
    	  recv(sock, &status, sizeof(int), 0);
    	  if(status)
    	    printf("\033[1;36mFichier transfere avec succes\n");
    	  else
    	    printf("\033[1;36mEchec du transfer du fichier\n");
    	  break;
    	case 3:
    	  strcpy(buf, "pwd");
    	  send(sock, buf, 100, 0);
    	  recv(sock, buf, 100, 0);
    	  printf("\033[1;36mLe chemin du repertoire actuel est :\n\t %s\n", buf);
    	  break;
    	case 4:
    	  strcpy(buf, "ls");
              send(sock, buf, 100, 0);
    	  recv(sock, &size, sizeof(int), 0);
              f = malloc(size);
              recv(sock, f, size, 0);
    	  filehandle = creat("temp.txt", O_WRONLY);
    	  write(filehandle, f, size, 0);
    	  close(filehandle);
              printf("\033[1;36mLa liste des fichier sur le repertoire actuel est :\n");
    	  system("cat temp.txt");
    	  break;
    	case 5:
    	  strcpy(buf, "cd ");
    	  printf("\033[1;36mEntrez le chemin que vous voulez vous y deplacer: ");
    	  scanf("%s", buf + 3);
              send(sock, buf, 100, 0);
    	  recv(sock, &status, sizeof(int), 0);
              if(status)
                printf("\033[1;36mRepertoire actuel changer avec succes.\n");
              else
                printf("\033[1;36mEchec lors du changement du repertoire actuel.\n");
              break;
    	case 6:
    	  strcpy(buf, "quit");
              send(sock, buf, 100, 0);
              recv(sock, &status, 100, 0);
    	  if(status)
    	    {
    	      printf("\033[1;36mServeur a ferme\nSortie..\n");
    	      exit(0);
    	    }
    	    printf("\033[1;36mEchec de la fermeture de la connection\n");
	case 10:
    	  system("pwd>temp.txt");
    	  i = 0;
              FILE*f = fopen("temp.txt","r");
              while(!feof(f))
                buf[i++] = fgetc(f);
              buf[i-1] = '\0';
    	  fclose(f);
		
              printf("\033[1;36mLe chemin du repertoire local de la machine client est :\n\t %s\n", buf);
    	break;
	case 11:
    	  system("ls >temps.txt");
    	  
              printf("\033[1;36mLa liste des fichier sur le repertoire Local est :\n");
    	  system("cat temps.txt");
    	break;
	case 12:
	  strcpy(buf, "cd ");
    	  printf("\033[1;36mEntrez le chemin que vous voulez vous y deplacer: ");
    	  scanf("%s", buf + 3);
    	  if(chdir(buf+3) == 0)
    	    c = 1;
    	  else
    	    c = 0;
            if(c)
                printf("\033[1;36mRepertoire actuel changer avec succes.\n");
              else
                printf("\033[1;36mEchec lors du changement du repertoire actuel.\n");
    	break;
	default:
	printf("\033[1;36m\t*** Pour optimiser les transaction Client/Serveur FTP,\n\tvous etes restreint a utiliser des packet de petite taille \n\tVeuillez choisir parmis les entiers representant des  commandes \n\tafin d'envoyer le packet au serveur FTP ***\n");
	break;
    	}
        }
    }
