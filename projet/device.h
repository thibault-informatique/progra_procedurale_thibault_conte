#ifndef DEVICE_H
    #define DEVICE_H

    #include <stdint.h> // types entiers à largeurs fixe (dont la taille en bits est garantie, indépendamment de la plateforme) / utile pour le réseau
    #include <stdbool.h>

    /*************************
    ****** ADRESSES IPv4 *****
    **************************/

    // créer une struct permet une sécurité de type => vérif compilateur possible lors des calculs réseaux
    // choix de valider les adresses par fct lors de la création/ modification des devices

    // utilité d'avoir un champ adresse valide dans la struct ipv4_t?  si récup adresses "sales" d'un inventaire 
    // ou si machine découverte sur le réseau dont l'adresse n'a pu être vérifiée
    typedef struct ipv4_t 
    {
        uint32_t address; // IPv4 (32bits) unsigned int qui fait exactement 32 bits       
    } ipv4_t;

    // couple (ip, masque) à envisager? 
    typedef struct ipv6_t 
    {
        uint8_t bytes[16]; // IPv6 (128bits) soit 16 * 8 bits
    } ipv6_t;



    /****************************
    ****** MACHINES RESEAUX *****
    *****************************/

    /*** ENUM ET STRUCT ***/

    typedef enum device_type 
    {
        ROUTER,
        SWITCH,
        FIREWALL,
        SERVER,
        WORKSTATION,
        PRINTER,
        ACCESS_POINT,
        OTHER
    } device_type;

    typedef enum device_status 
    {
        ONLINE,
        OFFLINE,
        MAINTENANCE,
        FAILED,
        UNKNOWN
        
    } device_status;

    typedef struct Device 
    {
        char name[50];
        enum device_type type;
        ipv4_t ip;
        ipv4_t subnet_mask;
        enum device_status status;

    } Device;

    /*** CRUD ***/

    enum return_crud 
    {
        SUCCES,
        ERR_STR_LENGTH
    };
    // conseil de créer le device puis l'ajouter afin de diminuer le nbre de para de la fct
    // TODO après cours double **
    enum return_crud addDevice(Device *device, char name[], device_type type, ipv4_t ip, ipv4_t subnet_mask, device_status status);
    Device* readDevice(Device* device);
    bool updateDevice(Device* device);
    bool deleteDevice(Device* device);


#endif