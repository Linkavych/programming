#!/usr/bin/env python3
# An ARP monitor tool using scapy
from scapy.all import *

def arp_display(pkt):
    if pkt[ARP].op == 1: #who-has request
        return f"Request: {pkt[ARP].psrc} is asking about {pkt[ARP].pdst}"
    if pkt[ARP].op == 2: # is-at request
        return f"**Response: {pkt[ARP].hwsrc} has address {pkt[ARP].psrc}"

sniff(prn=arp_display, filter="arp", count=10, store=0)
