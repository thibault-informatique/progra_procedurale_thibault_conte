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
    typedef struct 
    {
        uint32_t address; // IPv4 (32bits) unsigned int qui fait exactement 32 bits       
    } Ipv4_t;

    // couple (ip, masque) à envisager? 
    typedef struct 
    {
        uint8_t bytes[16]; // IPv6 (128bits) soit 16 * 8 bits
    } Ipv6_t;



    /****************************
    ****** MACHINES RESEAUX *****
    *****************************/

    /*** ENUM ET STRUCT ***/

    typedef enum 
    {
        ROUTER,
        SWITCH,
        FIREWALL,
        SERVER,
        WORKSTATION,
        PRINTER,
        ACCESS_POINT,
        OTHER,
        UNKNOWN
    } Device_type;

    typedef enum 
    {
        STATUS_ONLINE,
        STATUS_OFFLINE,
        STATUS_MAINTENANCE,
        STATUS_FAILED,
        STATUS_UNKNOWN
        
    } Device_status;

    typedef struct 
    {
        char name[50];
        Device_type type;
        Ipv4_t ip;
        Ipv4_t subnet_mask;
        Device_status status;

    } Device;

    Return_crud createDevice(Device *device, const char name[], Device_type type, Ipv4_t ip, Ipv4_t subnet_mask, Device_status status);





  

    /****************************
    ******   PARC RESEAU   ******
    *****************************/

    typedef struct
    {
        Device *park;
       unsigned int nbOfDevice;        

    } NewtorkPark;
    
    bool initPark(Device Park[], int tabLength);
    
    /*** CRUD ***/

    typedef enum 
    {
        SUCCES,
        ERR_STR_LENGTH,
        ERR_INVALID_IP,
        ERR_INVALID_MASK
    } Return_crud;

    
    bool addDeviceToPark(Device park[], Device *device);   
    // read cherche un device dans le parc / le fichier display gère l'affichage de ce device
    // NULL si pas trouvé, pointeur sur le device si trouvé
    Device* readDevice(Device *device, int count, const char name[]);

    bool updateDevice(Device* device);
    bool deleteDevice(Device* device);

  

#endif