
#		## BENELKADI Safouane El-Amine ##
#		## Groupe-1 Projet TP Reseau   ##
#		## L3 Informatique 2019/2020   ##



# 			FTP serveur et client




## Comment installer:

```
1- cd vers le dossier du projet
2- make
3- executer avec           ./ftpcli
   executer avec           ./ftpserv

4- Possibilité d'effacer les fichiers executable avec 'make clean'
```




## Commands implementer:

* Utiliser le username : 'Anonymous'
* ls cd pwd get put quit
* lls lcd lpwd





## Fonctionnement:

#/**** Commande 100% Fonctionelle, pour de meilleur test placez le serveur et client dans deux Dossiers différents.             ****/#

* Les ports doivent etre similaire dans les deux interface client/   serveurs, 

* Le nom d'utilisateur est 'Anonymous' pour permettre la connexion au serveur,

* Dans le but d'avoir des packets legers et une conversation client/serveur controlé et optimales; Une fois connecter, la communication entre client/serveur est restreinte a quelques choix selon les commandes, toutes autre messages ne sera pas envoyé au serveurs et géré par le client lui meme qui demandera a l'utilisateur de choisir parmie une liste restreinte.

* Choix conversation Client/Serveur possible :
       | 1- GET | 2- PUT | 3- PWD | 4- LS  | 5- CD  | 6- QUIT |

* Autre choix conversation avec la machine locale du client :
       | 10- LPWD | 11- LLS | 12- LCD |







## Choix technique:

* Vu que le serveur FTP doit pouvoir localisé son interlocuteur pour lui renvoyer ses fichiers et doit pouvoir connaitre les capacité de la machine client pour gérer et controlé les flux afin d'optimiser la connection et d'éviter d'inonder la machine client avec des packets qui seront perdus. >> Cela implique L'utilisation du protocole de message TCP.


* En utilisant le TCP il est possible de construire un FTP qui transfert les fichiers entre serveur/client et d'autre informations permettant de localiser les fichiers existant sur le serveur ou la machine client et de naviguer dans les repertoire serveur ou client, Une question qui se pose est est-ce que la méthode PUSH ou la méthode par défaut est meilleur pour le fonctionne du FTP ? Reponse : La methode par defaut de TCP, qui fait en sorte d'attendre que les packets soit assez large pour les envoyé en respectant une certaine proportion entre l'entete du segment TCP et la taille des données ce qui rends l'échange optimale. Car les principaux objectifs du FTP est bien le transfert de fichier et donc l'optimalité est bien necessaire.


* Afin de pouvoir répliquer les commande Linux sur le project FTP, l'utilisation de la fonction system est un bon choix afin d'interroger le système linux au lieu de réimplémenter sur le projet des fonctions déjà existante sur le système d'exploitation sur lequel le projet vas opéré, le résultat des commandes seront bufférisé et envoyer au client par communication TCP, se dernier vas faire la lecture des donnés une fois les packets reçus.



* La meme technique est utilisé sur les commande qui opèrent sur la machine locale du client, en interogeant le système d'exploitation de la machine du client, mais sans passé par la communication TCP avec le serveur.



```
Grace a ce projet j'ai pu nourrir mes connaissance ainsi qu'exploré d'autres maniere de voir les notions acquise pendant se module tel que l'utilité du modele OSI et sa structuration en couches hiérarchique  dans le developpement de nouveau protocol réseau, comme l'utilisation de IP par TCP et de TCP par FTP.
```


#		## BENELKADI Safouane El-Amine ##
#		## Groupe-1 Projet TP Reseau   ##
#		## L3 Informatique 2019/2020   ##




