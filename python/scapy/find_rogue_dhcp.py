#!/usr/bin/env python3
# Find a rogue DHCP server in the network
from scapy.all import *

fam, hw = get_if_raw_hwaddr(conf.iface)

# Callback for receiving DHCP pkts
def dhcp_call(pkt):
    if DHCP in pkt and pkt[DHCP].options[0][1] == 2:
        print(f"DHCP offer received from IP: {pkt[IP].src}, MAC: {pkt[Ether].src}")

# Build the DHCP request
dhcp_req = (
        Ether(dst="ff:ff:ff:ff:ff:ff")/
        IP(src="0.0.0.0", dst="255.255.255.255")/
        UDP(sport=68, dport=67)/
        BOOTP(chaddr=hw)/
        DHCP(options=[("message-type","discover"), "end"])
        )

# Send the DHCP reques on the line
sendp(dhcp_req)

# sniff for DHCP packets
sniff(prn=dhcp_call, store=0)


