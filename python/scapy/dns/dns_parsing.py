#!/usr/bin/env python3
# Parsing data from DNS
from scapy.all import *
import sys, re

# Main function to parse DNS
def extract_ips_from_packet(pkt):
    packet_dict = {}
    query_name = pkt[DNS].qd.qname.decode()

    # For 'A' Records
    if pkt[DNS].qd.qtype == 1:
        for x in range(pkt[DNS].ancount):
            # Skip NONE rdata - we want an IP address, not a domain
            if re.match('^\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}$', str(pkt[DNS].an[x].rdata)) == None:
                continue

            # Create a temp dict, IP = Key, Value = [record name, query name]
            temp = {pkt[DNS].an[x].rdata:[
                pkt[DNS].an[x].rrname.decode(),
                query_name
            ]}
            packet_dict.update(temp)

        for x in range(pkt[DNS].arcount):
            if re.match('^\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}$', str(pkt[DNS].ar[x].rdata)) == None:
                continue
            temp = {pkt[DNS].ar[x].rdata:[
                pkt[DNS].ar[x].rrname.decode(),
                query_name
            ]}
            packet_dict.update(temp)

    # For SRV Requests
    if pkt[DNS].qd.qtype == 33:
        for x in range(pkt[DNS].arcount):
            if re.match('^\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}$', str(pkt[DNS].ar[x].rdata)) == None:
                continue
            temp = {pkt[DNS].ar[x].rdata:[
                pkt[DNS].ar[x].rrname.decode(),
                query_name
            ]}
            packet_dict.update(temp)

    return packet_dict
    
# Filter out non-DNS
def build_dns_dict(pcap):
    dns_dict = {}
    print("[+] Working through the packets now...")
    for pkt in pcap:
        if (DNS in pkt) and (pkt[DNS].qr == 1):
            dns_dict.update(extract_ips_from_packet(pkt))
    
    return dns_dict
    
# The main....bring in the pcap
if __name__ == '__main__':
    pcap_fn = sys.argv[1]
    pcap = rdpcap(pcap_fn)
    print("[+] Loading pcap....")

    dns_dict = build_dns_dict(pcap)

    with open('domains.txt', 'w') as file:
        for ip in dns_dict:
            file.write(ip + '\n' + '    Domains: ' + dns_dict[ip][0].rstrip('.') + '\n' + '             ' + dns_dict[ip][1].rstrip('.') + '\n\n')   
    file.close()
