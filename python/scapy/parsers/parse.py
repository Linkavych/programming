#!/usr/bin/env python3
# Pcap parsing
# Quickly pull unique IP addresses and communication streams form a PCAP

from scapy.all import *
import sys

traffic_capture = rdpcap(sys.argv[1])
output_filename = sys.argv[2]

udp_pkts = []
tcp_pkts = []

# Sort packets into lists based on TCP/UDP
for pkt in traffic_capture:
    if pkt.haslayer(TCP):
        tcp_pkts.append(pkt)

for pkt in traffic_capture:
    if pkt.haslayer(UDP):
        udp_pkts.append(pkt)

print(len(tcp_pkts))
print(len(udp_pkts))


# Creating a unique list of IP addresses from the pcap
def unique_ips(traffic_capture):
    unique_ips = []
    try:
        for pkt in traffic_capture:
            src = pkt[IP].src
            dst = pkt[IP].dst
            unique_ips.append(src)
            unique_ips.append(dst)
    except:
        pass

    ip_list = open(output_filename + "_ips.txt", "w+")
    for ip in set(unique_ips):
        ip_list.write("Host: " + ip + '\n')
    ip_list.close()

#    for i in set(unique_ips):
#        print(f"Host IP: {i}\n")

# Caputuring TCP conversations between systems
def TCP_conversations(tcp_pkts):
    conversations = []
    try:
        for pkt in tcp_pkts:
            try:
                src = pkt[IP].src
                dst = pkt[IP].dst
                sport = pkt[TCP].sport
                dport = pkt[TCP].dport
                conversations.append(f"Source IP: {src}:{sport}, Destination IP: {dst}:{dport}")
            except:
                pass
    except:
        pass

    conversation_list = open(output_filename + "_TCP_conversations.txt", "w+")
    for item in set(conversations):
        conversation_list.write(item + '\n')
    conversation_list.close()

#    for item in set(conversations):
#        print(item)

# Capture any UDP conversations between systems
def UDP_conversations(udp_pkts): # This function is not working yet! FIX
    conversations = []
    try:
        for pkt in udp_pkts:
            try:
                src = pkt[IP].src
                dst = pkt[IP].dst
                sport = pkt[UDP].sport
                dport = pkt[UDP].dport
                conversations.append(f"Source IP: {src}:{sport}, Destination IP: {dst}:{dport}")
            except:
                pass
    except:
        pass

    conversations_list = open(output_filename + "_UDP_conversations.txt", "w+")
    for item in set(conversations):
        conversations_list.append(item + '\n')
    conversations_list.close()

# Separates HTTP traffic and writes to a new pcap
def web_pcap(traffic_capture):
    web_chat = []
    try:
        for pkt in traffic_capture:
            try:
                if pkt[TCP].dport == 80:
                    web_chat.append(pkt)
                elif pkt[TCP].dport == 443:
                    web_chat.append(pkt)
                elif pkt[TCP].sport == 80:
                    web_chat.append(pkt)
                elif pkt[TCP].sport == 443:
                    web_chat.append(pkt)
            except:
                pass
    except:
        pass

    wrpcap(output_filename + "_web_traffic.pcap", web_chat)

if __name__ == '__main__':
    unique_ips(traffic_capture)
    TCP_conversations(traffic_capture)
    web_pcap(traffic_capture)
