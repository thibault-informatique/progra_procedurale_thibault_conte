#include "network.h"

// TODO isValidIp, isValidMask, isPrivateIp 
bool isValidIp(Ipv4_t ip)
{
    return true;
}

bool isValidMask(Ipv4_t subnet_mask)
{
    return true;
}

// 10.0.0.0 à 10.255.255.255
// 172.16.0.0 à 172.31.255.255
// 192.168.0.0 à 192.168.255.255
bool isPrivateIp(Ipv4_t ip)
{
    return true;
}