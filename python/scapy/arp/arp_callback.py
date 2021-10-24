#!/usr/bin/env python3
# A simple ARP monitor with scapy
from scapy.all import*

def arp_callback(pkt):
    if ARP in pkt and pkt[ARP].op in (1,2): # who has or is at
        return pkt.sprintf("%ARP.hwsrc% %ARP.psrc%")

sniff(prn=arp_callback, filter="arp", store=0)
