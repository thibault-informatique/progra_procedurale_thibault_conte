#ifndef DEVICE_H
    #define DEVICE_H

    #include <stdint.h> // types entiers à largeurs fixe (dont la taille en bits est garantie, indépendamment de la plateforme) / utile pour le réseau
    #include <stdbool.h>

    #include "constants.h"

    /*************************
    ****** ADRESSES IPv4 *****
    **************************/

    // TODO: fct calcul reseau + fct calcul prefixe "human readable" en /... 

    // créer une struct permet une sécurité de type => vérif compilateur possible lors des calculs réseaux
    // choix de valider les adresses par fct lors de la création/ modification des devices

    // utilité d'avoir un champ adresse valide dans la struct Ipv4?  si récup adresses "sales" d'un inventaire 
    // ou si machine découverte sur le réseau dont l'adresse n'a pu être vérifiée

    // struct IPv4 en 32 bits imposés (uint32_t std)
    // utilité : gateway, dns, broadcast,... (sans masque ou préfixe)
    typedef struct 
    {
        uint32_t address; // IPv4 (32bits) unsigned int qui fait exactement 32 bits       
    } Ipv4;    
    
    /*
    typedef struct 
    {
        uint8_t bytes[16]; // IPv6 (128bits) soit 16 * 8 bits
    } Ipv6;
    */


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
        Ipv4 ipAddress;
        Ipv4 subnet_mask;
        Device_status status;

    } Device;

    typedef struct 
    {
        Device device[PARK_LENGTH];
        int nbOfDevice;
        int maxParkLength;
    } Park;
    


 
    /*** CRUD ***/

    typedef enum 
    {
        SUCCES,
        ERR_STR_LENGTH,
        ERR_INVALID_IP,
        ERR_INVALID_MASK
    } Return_crud;

    // TODO après cours double **
    Return_crud initDevice(Device *device, const char name[], Device_type type, Ipv4 ip, Ipv4 mask, Device_status status);



    /****************************
    ******       PARK       *****
    *****************************/
    bool initPark(Device Park[], int tabLength);

    // CRUD
    Return_crud addDevice(Device park[], int count);
    Device* findDevice(Device park[], int count, const char name[]);
    bool updateDevice(Device* device);
    bool removeDevice(Device* device);
    // si device trouvé => retourne un pointeur sur le device | NULL sinon
   
   

#endif