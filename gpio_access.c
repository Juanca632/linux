#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdint.h>

#define GPIO_BASE 0xFF203000   // Adresse du registre GPIO connecté aux LED
#define MAP_SIZE 4096         // Taille de la page mémoire (4KB)

int main() {
    int fd;
    void *map_base;
    volatile uint32_t *gpio;

    // Ouvrir le fichier /dev/mem en lecture/écriture
    fd = open("/dev/mem", O_RDWR | O_SYNC);
    if (fd < 0) {
        perror("Erreur ouverture /dev/mem");
        return -1;
    }

    // Mapper la mémoire physique à une adresse virtuelle
    map_base = mmap(NULL, MAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, GPIO_BASE);
    if (map_base == MAP_FAILED) {
        perror("Erreur mmap");
        close(fd);
        return -1;
    }

    // Pointeur vers le registre GPIO
    gpio = (volatile uint32_t *)map_base;

    // Écrire une valeur dans le registre GPIO (exemple : allumer toutes les LEDs)
    *gpio = 0xFF;  // Met tous les bits à 1 (selon hardware)

    // Lire la valeur actuelle du registre GPIO
    uint32_t val = *gpio;
    printf("Valeur lue dans le registre GPIO : 0x%08X\n", val);

    // Démapper la mémoire et fermer le fichier
    munmap(map_base, MAP_SIZE);
    close(fd);

    return 0;
}
