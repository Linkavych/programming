#!/usr/bin/env python3
from scapy.all import *

pkts = PcapReader('2020-11-13-traffic-analysis-exercise.pcap')
udp_pkts = []

for pkt in pkts:
    if pkt.haslayer(UDP):
        udp_pkts.append(pkt)

print(len(udp_pkts))

def udp_parse(udp_pkts):
    conversations = [] 
    for pkt in udp_pkts:
        src = pkt[IP].src
        dst = pkt[IP].dst
        sport = pkt[UDP].sport
        dport = pkt[UDP].dport
        conversations.append(f"Source: {src}:{sport}, Destination: {dst}:{dport}")

    udp_conversations = open('UDP_Conversations.txt', 'w+')
    for item in set(conversations):
        udp_conversations.write(item + '\n')
    udp_conversations.close()

udp_parse(udp_pkts)
