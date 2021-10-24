#!/usr/bin/env python3
# A sniffer to detect and log suspicious activity
# on the network

from scapy.all import *
from scapy.utils import PcapWriter
from datetime import *  #datetime, timedelta
import os, sys, signal

# Defines and runs a signal handler for ease of use.
def signal_handler(signal, frame):
    print("\nProgram exiting...")
    sys.exit(0)

signal.signal(signal.SIGINT, signal_handler)

winplat = ["win32", "win64"]
linux = ["linux", "linux2", "linux3"]
platform = sys.platform

if platform in winplat:
    print("Windows")
    now = datetime.now()
    stop = now + timedelta(seconds=120) # amount of time to run (min/hr)
    flushdns = os.system("ipconfig /flushdns") # flush windows DNS cache
    # os.system("pythonw.exe firewallrules.py") # auto implement new firewall rules 

elif platform in linux:
    print("Linux")
    now = datetime.now()
    stop = now + timedelta(seconds=120)
    flushdns = os.system("sudo /etc/init.d/networking restart")
    
    try:
        print("[*] Listening to traffic...")
        while datetime.now() < stop:
            #TCP SYN + SYNACK capture and DNS port 53 capture
            packets = sniff(filter="tcp[tcpflags] & (tcp-syn) !=0 or port 53",
                    session=IPSession, #defrag on-the-flow
                    count = 0, # 2 packets before continuing
                    prn = lambda x: x.summary()) # prints TCP SYNACK and DNS req/resp
            # Append to 'sniffed.pcap'
            pktdump1 = PcapWriter("sniffed.pcap", append=True, sync=True)
            pktdump1.write(packets)

            pcap = 'sniffed.pcap'
            pkts = rdpcap(pcap)
            UDP_ips = []
            TCP_ips = []

            # Add TCP dst packets  to list for comparison
            for p in pkts:
                if p.haslayer(TCP):
                    TCP_ips.append(p[IP].dst)
                # Loop for DNS parsing and recording entries
                if p.haslayer(UDP):
                    UDP_ips.append(p[IP].dst)
                    if p.haslayer(DNSRR):
                        a_count = p[DNS].ancount
                        i = a_count + 4 
                        arp = "arpa"
                        while i > 4:
                            if str(p[0][i].rdata)[0].isnumeric():
                                print(p[0][i].rdata)
                                UDP_ips.append(p[0][i].rdata)
                            elif p[0][i].rrname.decode().count("in-addr.arpa") > 0:
                                #print(packet[0][i].rrname.decode()
                                base = (p[0][i].rrname.decode())
                                chop = base[:-14]
                                work = chop.split('.')
                                final = work[3] + "." + work[2] + "." + work[1] + "." + work[0]
                                UDP_ips.append(final)
                                i -= 1
                in_t_not_u = list(set(TCP_ips) - set(UDP_ips))

            with open("suspicious.txt", 'w+') as f:
                for i in in_t_not_u:
                    f.write(str(i))
                    f.write("\n")
                f.close()
    except KeyboardInterrupt:
        print("Sniffer off...")
else:
    print("[!] Unknown system...")
