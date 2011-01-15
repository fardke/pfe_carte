= Projet de fin d'étude =
=========================

Pour exécuter ces programme il faut avoir intaller libbluetooth-dev.
Pour la compilation il faut installer cmake.

Compilation
-----------

Créer un répertoire build à la racine du projet
 
 # mkdir build
 # cd build

Créer les makefiles nécessaire à la compilation

 # cmake .. -G"Unix Makefiles"

Lancer la compilation

 # make

Exécution
---------

Lancer la synchronisation sur le client:

# cd main
# ./synchroCarte

Lancer la synchronisation sur le serveur:

# cd main
# ./synchroServeur

La synchronisation doit créer sur le client un fichier config contenant l adresse du serveur

Sur le serveur lancer la réception des messages:

# cd main
# ./recvMsg

Sur la carte lancez un envoi de message

# cd main
# ./sendMsg

Si tout c est bien déroulé vous devriez voir sur le serveur Salut.
