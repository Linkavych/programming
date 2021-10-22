#!/usr/bin/env python3
# Geolocation and ownership of a given IP address or network
# This time using an API and requests
import requests
import sys
import json
import ipaddress
from pprint import pprint

API_KEY = ''

def usage():
    print("Usage: ./ip_geo.py <api_key_file> <ip file> <output_file>")
    exit(1)

def lookup(ip_addr, API_KEY):
    '''
    Requests an ip lookup from  app.geolocation.io
    Params:
        ip_addr - a single ip address
        API_KEY - api key for website
    Return:
        name - owner of ip address
        country - country code
    '''
    payload = {'apiKey': API_KEY, 'ip': ip_addr, 'fields': 'organization,country_code3'}
    r = requests.get('https://api.ipgeolocation.io/ipgeo', params=payload)

    data = r.json()
#    pprint(data)
    country = data['country_code3']
    name = data['organization']

    return name, country


def main(infile, outfile):
    '''
    Main function for program to verify ownership and geolocation
    of a given IP address or range.

    Params:
        infile - a file with a list of IP addresses, or CIDR ranges
    Returns:
        outfile - new file list ip, owner, and country code
    '''
    ip_info = []
    ip_list2 = []

    with open(infile, 'r') as f:
        ips = f.readlines()

    for ip in ips:
        ip = ip.strip()
        try:
            ip_addr = ipaddress.ip_address(ip)
        except ValueError:
            print("[!] IP: {} is not a valid IP.".format(ip))

            try:
                ip_list2 = [str(ip1) for ip1 in ipaddress.ip_network(ip, strict=False)]
                for ip2 in ip_list2:
                    ip2 = ip2.strip()

                    name, country = lookup(ip2, API_KEY)
                    ip_info.append((name, country, ip2))
            except ValueError:
                print("[!] Not a valid IP range: {}".format(ip2))
                continue
            continue

        name, country = lookup(ip_addr, API_KEY)
        ip_info.append((name, country, ip_addr))

    with open(outfile, 'w') as fd:
        for item in ip_info:
            fd.write('Owner: {}, Country: {}, IP: {}\n'.format(item[0], item[1], item[2]))

    print("[+] File written to: {}".format(outfile))


if __name__ == '__main__':

    if len(sys.argv) != 4:
        usage()
    else:
        with open(sys.argv[1], 'r') as fd:
            API_KEY = fd.readline()
            API_KEY = API_KEY.strip()

        infile = sys.argv[2]
        outfile = sys.argv[3]

        main(infile, outfile)
