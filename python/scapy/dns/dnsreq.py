#!/usr/bin/env python3
# simple DNS request and response witrh scapy
from scapy.all import *

dns_req = IP(dst="8.8.8.8")/UDP(dport=53)/DNS(rd=1, qd=DNSQR(qname='www.nytimes.com'))
answer = sr1(dns_req, verbose=0)

print(answer[DNS].summary())
