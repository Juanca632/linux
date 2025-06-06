# Compte Rendu – TP Linux Embarqué

## Auteurs : Harnoufi Rayan - Restrepo Juan


---

## 1. Prise en main

### 1.1 Préparation de la carte SD
Nous avons commencé par télécharger l’image `VEEK_MT2S_LXDE.img`. Ensuite, nous l’avons flashée sur la carte SD à l’aide de la commande `dd`, en prenant soin de bien repérer le bon périphérique pour éviter toute erreur.

### 1.2 Démarrage
Une fois la carte prête, nous l’avons insérée dans la carte VEEK-MT2S. Le système Linux s’est lancé correctement et l’interface graphique s’est affichée à l’écran.

---

## 1.3 Connexion au système

### 1.3.1 Liaison série
Nous avons utilisé `minicom` pour établir une liaison série via le port USB mini-B. Après avoir configuré le bon port et le bon débit (115200 bauds), nous avons pu nous connecter avec le compte `root`, sans mot de passe.

### 1.3.2 Extension du système de fichiers
Nous avons vérifié l’espace disponible sur la carte avec `df -h`, puis lancé les scripts `expand_rootfs.sh` et `resize2fs_once` pour utiliser toute la capacité de la carte SD. Après redémarrage, l’espace disque était bien étendu.

### 1.3.3 Configuration réseau
Nous avons connecté la carte au réseau avec un câble Ethernet. Ensuite, nous avons modifié le fichier `/etc/network/interfaces` pour activer le DHCP. Après redémarrage, la carte a obtenu une adresse IP, que nous avons utilisée pour établir une connexion SSH depuis notre PC.

---

## 1.4 Découverte de la cible

### 1.4.1 Exploration système
Nous avons exploré les fichiers système dans `/proc` et `/sys/class`, notamment pour obtenir des informations sur le processeur et les périphériques comme les LEDs.

### 1.4.2 Compilation croisée
Une machine virtuelle Linux nous a permis de compiler notre programme "Hello World" avec `arm-linux-gnueabihf-gcc`. La compilation s’est déroulée sans erreur.

### 1.4.3 Hello World
Le fichier binaire compilé a été transféré sur la carte avec `scp`, puis exécuté via SSH. Le programme a bien affiché le message attendu.

### 1.4.4 Contrôle des LEDs
Nous avons testé l’allumage manuel d’une LED avec la commande :
```bash
echo "1" > /sys/class/leds/fpga_led1/brightness
```
Ce test a confirmé l’accès correct au matériel via le système de fichiers.

### 1.4.5 Chenillard
Nous avons ensuite développé un petit programme C réalisant un chenillard. Il utilise une boucle pour allumer les LEDs les unes après les autres, avec un délai entre chaque changement.

---

## 2. Modules noyau

### 2.1 Accès direct aux registres
Pour tester l’accès direct au matériel, nous avons utilisé `mmap()` pour accéder à l’adresse `0xFF203000` correspondant aux LEDs. Cette méthode fonctionne, mais elle contourne certaines protections du système.

### 2.2 Compilation d’un module noyau
Nous avons installé les paquets nécessaires pour compiler des modules noyau dans la VM. Ensuite, nous avons compilé un module simple (`hello.c`) à l’aide d’un Makefile. Le chargement et le déchargement du module avec `insmod` et `rmmod` ont été validés, et les messages dans `dmesg` ont confirmé son bon fonctionnement.

### 2.3 CrossCompilation de modules noyau

#### 2.3.0 Récupération du noyau Terasic
Nous avons cloné le dépôt GitHub contenant les sources du noyau `linux-socfpga` et nous avons utilisé le commit exact (`6b20a29`) correspondant à celui présent sur la carte, pour assurer la compatibilité.

#### 2.3.1 Préparation de la compilation
Nous avons installé les outils nécessaires à la compilation croisée (`crossbuild-essential-armhf`, `binutils-multiarch`) et nous avons repéré le chemin du compilateur avec `whereis arm-linux-gnueabihf-gcc`.

---

## Fin de l’étape actuelle
La configuration du noyau est prête. Nous allons pouvoir passer à la compilation de modules personnalisés pour la carte, avec les commandes `make prepare` et `make scripts`.

