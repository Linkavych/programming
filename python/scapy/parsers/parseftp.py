#!/usr/bin/env python3
# Simple FTP pcap parsing
from scapy.all import *
import sys

pkts = rdpcap(sys.argv[1])

pkt_info = [] 
creds = []

def parse_ftp(pkts):
    for pkt in pkts:
        try:
            if pkt.haslayer(Raw):
                pkt_info.append(pkt[Raw].load.decode())
        except Exception as e:
            pass

def grab_cred_ftp(pkt_info):
    for pkt in pkt_info:
        for x in pkt_info.split():
            if 'USER' in x:
                print(x)



parse_ftp(pkts)
print(pkt_info)
