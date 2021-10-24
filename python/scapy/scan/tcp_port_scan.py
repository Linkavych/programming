#!/usr/bin/env python3
# a TCP port scanner based on scapy

import random
from scapy.all import *

# Define end host and TCP port range
host = '192.168.88.22'
port_range = [22, 23, 80, 139, 443, 445, 3389]

# Send a SYN with random src port for each dst port
for dst_port in port_range:
    src_port = random.randint(1025, 65534)
    resp = sr1(
        IP(dst=host)/TCP(sport=src_port, dport=dst_port, flags='S'), timeout=1,
        verbose=0,
    )
    
    if resp is None:
        print(f"[-] {host}:{dst_port} is filtered (silently dropped).")

    elif (resp.haslayer(TCP)):
        if (resp.getlayer(TCP).flags == 0x12):
            # send a gratuitous reset to close the connection
            send_rst = sr(
                IP(dst=host)/TCP(sport=src_port, dport=dst_port, flags='R'),
                timeout=1, verbose=0,
            )
            print(f"[+] {host}:{dst_port} is open.")
    
        elif (resp.getlayer(TCP).flags == 0x14):
            print(f"[-] {host}:{dst_port} is closed.")

    elif (resp.haslayer(ICMP)):
        if (
            int(resp.getlayer(ICMP).type) == 3 and
            int(resp.getlayer(ICMP).code) in [1, 2, 3, 9, 10, 13]
        ):
            print(f"[-] {host}:{dst_port} is filtered (silently dropped).")
