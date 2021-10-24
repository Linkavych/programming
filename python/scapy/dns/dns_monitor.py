#!/usr/bin/env python3
# A simple DNS monitoring program

from scapy.all import *
import signal, sys

# Allow for gracefule exit with C-c
def signal_handler(signal, frame):
    print("\n[+] Exiting program...")
    sys.exit(0)
signal.signal(signal.SIGINT, signal_handler)

# Function to find DNS packets and print them to screen
def find_dns(pkt):
    try:
        if pkt.haslayer(DNSRR):
            print(f"Source: {pkt[IP].src}, Destination: {pkt[IP].dst}\n"
                   f"Domain: {pkt[DNSRR].rrname.decode()}, IP: {pkt[DNSRR].rdata}\n")
    except:
        pass

sniff(prn=find_dns, store=0)

