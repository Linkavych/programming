#!/usr/bin/env python3
# Reporting on basic security web headers
import argparse
import requests
import socket
import sys

# Open a file containing a list of URLs
# return a list of URLs

def usage():
    '''
    Simple usage function
    '''
    print("USAGE: python3 web_headers.py -u <url> | -i <file>")

def open_file(url_list):
    '''
    Opens a file containing a list of URLs
    Returns the list
    '''
    with open(url_list, 'r', encoding='utf-8') as fd:
        for line in fd.readlines():
            line = line.strip()
            urls.append(line)
    return urls


def check_headers(url):
    '''
    Checks the header returns fro the provided URL.
    Params:
        URL - string
    Return:
        Header values - string/bool
    '''
    r = requests.get(url)
    host = url.split('/')[2]
    ip_addr = socket.gethostbyname(host)

    print(f'[+] Testing: {url}...')
    print(f'[+] IP Address: {ip_addr}')

    # Header checks here
    if 'Server' in r.headers:
        print(f'[+] Server: {r.headers["Server"]}')
    if 'https' in url:
        if 'Strict-Transport-Security' not in r.headers:
            print(f'[!] {url}: Missing "Strict-Transport-Security" header!')
    if 'Content-Security-Policy' not in r.headers:
        print(f'[!] {url}: Missing "Content-Security-Policy" header!')
    if 'X-Frame-Options' not in r.headers:
        print(f'[!] {url}: Missing "X-Frame-Options" header!')

    print("\n")



if __name__ == "__main__":

    urls = list()

    parser = argparse.ArgumentParser(
        description="Testing web headers for security features. Supply either a single URL, or file with a list of URLs for testing."
    )
    parser.add_argument(
        "--url", help="single url to test", required=False, action='store'
    )
    parser.add_argument(
        "--infile", help="list of domains to test", required=False, action='store'
    )
    args = parser.parse_args()

    if args.url is None and args.infile is None:
        usage()
    elif args.url is not None:
        urls.append(args.url)
    elif args.infile is not None:
        urls = open_file(args.infile)

    for url in urls:
        try:
            check_headers(url)
        except requests.exceptions.RequestException as e:
            print(f'[!!] Connection error on: {url}!')