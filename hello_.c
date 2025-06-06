#include <linux/init.h>     // Initialisation et nettoyage du module
#include <linux/module.h>   // Support des modules noyau
#include <linux/kernel.h>   // Fonctions du noyau (printk, etc.)

MODULE_LICENSE("GPL");               // Licence du module
MODULE_AUTHOR("Ton Nom");            // Auteur du module
MODULE_DESCRIPTION("Un module noyau simple Hello World"); // Description
MODULE_VERSION("0.1");               // Version du module

// Fonction appelée au chargement du module
static int __init mon_module_init(void) {
    printk(KERN_INFO "Bonjour le monde !\n"); // Affiche dans le log du noyau
    return 0;                                // Succès du chargement
}

// Fonction appelée à la décharge du module
static void __exit mon_module_exit(void) {
    printk(KERN_INFO "Au revoir le monde !\n"); // Message de sortie
}

module_init(mon_module_init); // Macro pour définir la fonction d'init
module_exit(mon_module_exit); // Macro pour définir la fonction de sortie
