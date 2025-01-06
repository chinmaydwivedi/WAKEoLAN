# LANoWake

This is a simple C program that sends a Wake-on-LAN (WoL) magic packet to remotely power on a PC over the internet or a local network. The program utilizes the UDP protocol to send the magic packet to the target device's broadcast address.

---

## Features
- Sends a WoL magic packet to wake up a target PC.
- Accepts MAC address and broadcast IP as input parameters.
- Includes error handling for invalid inputs and socket operations.

---

## Requirements

### Target PC (The PC to be woken up):
1. **WoL Support**: Ensure the PC supports Wake-on-LAN. This is usually enabled in the BIOS/UEFI settings.
   - Enable settings like "Wake on LAN" or "Power on by PCI-E."
2. **Network Adapter Configuration**:
   - Windows:
     - Go to `Device Manager` > Network Adapter Properties > Power Management.
     - Enable "Allow this device to wake the computer" and "Only allow a magic packet to wake the computer."
   - Linux:
     - Use `ethtool` to enable WoL:
       ```bash
       sudo ethtool -s <network_interface> wol g
       ```

### Sending PC (The PC running this program):
1. A C compiler (e.g., GCC).
2. The program must be on the same network or able to reach the target PC's broadcast address.

---

## Installation
1. Clone or download this repository.
2. Navigate to the directory containing the source code.

---

## Compilation
Compile the program using GCC:
```bash
gcc -o lano_wake lano_wake.c
```

---

## Usage
Run the program with the following syntax:
```bash
./lano_wake <MAC Address> <Broadcast IP>
```

### Parameters:
- `<MAC Address>`: The MAC address of the target PC in the format `xx:xx:xx:xx:xx:xx`.
- `<Broadcast IP>`: The broadcast address of the target PC's network (e.g., `192.168.1.255`).

### Example:
```bash
./lano_wake ab:cd:ef:12:34:56 192.168.1.255
```

---

## Testing
1. **Verify Requirements**:
   - Ensure the target PC is configured for WoL.
   - Obtain the target PC's MAC address and broadcast address.

2. **Run the Program**:
   - Compile and execute the program as shown above.

3. **Monitor with Wireshark (Optional)**:
   - Use Wireshark to capture UDP packets on port 9 and verify the magic packet is being sent.

4. **Put the Target PC to Sleep/Standby**:
   - Shut down or put the target PC into standby/hibernation mode.

5. **Send the Magic Packet**:
   - Run the program to wake up the target PC.

---

## Troubleshooting
1. **Target PC Doesn’t Wake Up**:
   - Ensure WoL is enabled in BIOS/UEFI and OS settings.
   - Verify the MAC address and broadcast IP are correct.
   - Check firewalls and ensure UDP traffic on port 9 is allowed.

2. **Verify Magic Packet**:
   - Use Wireshark to confirm the magic packet is reaching the target PC.

3. **Network Configuration**:
   - Ensure the sending PC and target PC are on the same subnet or that the broadcast address is reachable.

---

## License
This project is open-source and available under the MIT License.

---

## Acknowledgments
This project was developed as part of an effort to explore networking and remote management using the Wake-on-LAN protocol.

