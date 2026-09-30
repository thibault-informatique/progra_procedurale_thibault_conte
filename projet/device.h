#ifndef DEVICE_H
    #define DEVICE_H

    #include <stdint.h> // types entiers à largeurs fixe (dont la taille en bits est garantie, indépendamment de la plateforme) / utile pour le réseau
    #include <stdbool.h>

    enum device_type {
        ROUTER,
        SWITCH,
        FIREWALL,
        SERVER,
        WORKSTATION,
        PRINTER,
        ACCESS_POINT,
        OTHER
    };

    enum device_status {
        ONLINE,
        OFFLINE,
        MAINTENANCE,
        FAILED,
        UNKNOWN
        
    };


    typedef union ipv4_t {
        uint32_t address; // IPv4 address in dotted decimal notation
        uint8_t bytes[4]; // IPv4 address as 4 bytes
    } ipv4_t;

    typedef union ipv6_t {
        uint8_t bytes[16]; // IPv6 address as 16 bytes
    } ipv6_t;

    typedef struct Device {
        char name[50];
        enum device_type type;
        ipv4_t ip;
        ipv4_t subnet_mask;
        enum device_status status;

    } Device;

#endif