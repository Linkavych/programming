#!/usr/bin/env python3
# Parse TCP data from pcaps

from scapy.all import *
import sys

pktcap = rdpcap(sys.argv[1])

tcp_pkts = []

# Sort out the TCP traffic and create a pcap
for pkt in pktcap:
    if pkt.haslayer(TCP):
        tcp_pkts.append(pkt)

print(len(tcp_pkts))
