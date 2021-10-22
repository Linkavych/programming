#!/usr/bin/env python3
# Verify the ownership and geolocation of the provided IP addresses.
# Output should be clean and organized.
# Should read addresses from a file containing both single addresses, and CIDR ranges
import sys
import ipaddress
from ipwhois import IPWhois


def usage():
    print("Usage: ./ip_whois.py <ip file> <outfile>")
    exit(1)

def lookup(ip_addr):
    '''
    Conduct the actual lookup of the ip address with whois
    Params:
        ip_addr - an IP address
    Return:
        Owner and geolocation
    '''
    ip_obj = IPWhois(ip_addr)

    info = ip_obj.lookup_rdap(depth=1)

    country = info["asn_country_code"]
    name = info["network"]['name']

    return name, country

def main(filename, output_file):

    '''
    Main function for the program
    Param:
        filename - name of file to be read
    Return:
        new file - with IP address - Country - Owner
    '''
    info = []
    ip_list = []
    with open(filename, 'r') as f:
        ips = f.readlines()

    for ip in ips:
        ip = ip.strip()
        try:
            ip_addr = ipaddress.ip_address(ip)
        except ValueError:
            print("[!] IP: {} is not valid.".format(ip))
            try:
                ip_list = [str(ip_a) for ip_a in ipaddress.ip_network(ip, strict=False)]
                for ip2 in ip_list:
                    ip2 = ip2.strip()

                    name, country = lookup(ip2)
                    info.append((ip2, name, country))
            except ValueError:
                print("[!] Not a valid IP range: {}".format(ip))
                continue
            continue

        name, country = lookup(ip_addr)
        info.append((ip_addr, name, country))

    with open(output_file, 'a') as fd:
        for item in info:
            fd.write('Owner: {}, Country: {}, IP: {}\n'.format(item[1], item[2], item[0]))

    print("[+] File located at: {}".format(output_file))

if __name__ == '__main__':
    if len(sys.argv) != 3:
        usage()
    else:
        filename = sys.argv[1]
        output_file = sys.argv[2]

    main(filename, output_file)




