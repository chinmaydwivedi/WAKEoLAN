#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <ctype.h>

void parse_mac_address(const char *mac_str, unsigned char *mac) {
    int values[6];
    if (sscanf(mac_str, "%x:%x:%x:%x:%x:%x", 
               &values[0], &values[1], &values[2], 
               &values[3], &values[4], &values[5]) != 6) {
        fprintf(stderr, "Invalid MAC address format.\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < 6; i++) {
        mac[i] = (unsigned char)values[i];
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <MAC Address> <Broadcast IP>\n", argv[0]);
        return EXIT_FAILURE;
    }

    unsigned char toSend[102], mac[6];
    struct sockaddr_in udpClient, udpServer;
    int broadcast = 1;

    // Parse MAC Address
    parse_mac_address(argv[1], mac);

    // UDP Socket creation
    int udpSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (udpSocket < 0) {
        perror("Socket creation failed");
        return EXIT_FAILURE;
    }

    // Enable Broadcast
    if (setsockopt(udpSocket, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast)) == -1) {
        perror("setsockopt (SO_BROADCAST)");
        return EXIT_FAILURE;
    }

    udpClient.sin_family = AF_INET;
    udpClient.sin_addr.s_addr = INADDR_ANY;
    udpClient.sin_port = 0;

    // Bind the socket
    if (bind(udpSocket, (struct sockaddr *)&udpClient, sizeof(udpClient)) < 0) {
        perror("Socket binding failed");
        return EXIT_FAILURE;
    }

    // Prepare the magic packet
    for (int i = 0; i < 6; i++)
        toSend[i] = 0xFF;
    for (int i = 1; i <= 16; i++)
        memcpy(&toSend[i * 6], mac, 6);

    // Configure UDP server
    udpServer.sin_family = AF_INET;
    udpServer.sin_addr.s_addr = inet_addr(argv[2]);
    udpServer.sin_port = htons(9);

    // Send the magic packet
    if (sendto(udpSocket, toSend, sizeof(toSend), 0, (struct sockaddr *)&udpServer, sizeof(udpServer)) < 0) {
        perror("sendto failed");
        return EXIT_FAILURE;
    }

    printf("Magic packet sent to %s via %s\n", argv[1], argv[2]);
    return 0;
}
