#!/usr/bin/env python3
# SQLi testing script
import argparse
import requests
from bs4 import BeautifulSoup as bs
from urllib.parse import urljoin
from pprint import pprint

# Start the session
s = requests.Session()
s.headers[
    "User-Agent"
] = "Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:89.0) Gecko/20100101 Firefox/89.0"


def get_all_forms(url: str):
    """
    Extracts and returns all forms from the provided url.
    ----------------------------
    Param:
        Str: url to test
    ----------------------------
    Return:
        bs4 object
    """
    soup = bs(s.get(url).content, "html.parser")

    return soup.find_all("form")


def get_form_details(form) -> dict:
    """
    Extract useful information from an HTML form.
    ---------------------------------------------
    Param:
        Object: form object from beautiful soup
    ---------------------------------------------
    Return:
        Dict: Form details
    """
    details = {}

    try:
        action = form.attrs.get("action").lower()
    except:
        action = None

    # Get Form method
    method = form.attrs.get("method", "get").lower()

    # Get input details from form
    inputs = []
    for input_tag in form.find_all("input"):
        input_type = input_tag.attrs.get("type", "text")
        input_name = input_tag.attrs.get("name")
        input_value = input_tag.attrs.get("value", "")
        inputs.append({"type": input_type, "name": input_name, "value": input_value})

    # Stores everything in a dictionary
    details["action"] = action
    details["method"] = method
    details["inputs"] = inputs

    return details


def vulnerable(response):
    """
    Function to determine if a webpage or form is vulnerable to SQLi
    ________________________________________________________________
    Param:
        response
    ----------------------------------------------------------------
    Return:
        bool: true or false based on test
    """
    errors = {
        "you have an error in your sql syntax;",
        "warning: mysql",
        # MSSSQL
        "unclosed quotation mark after the character string",
        # Oracle
        "quoted string not properly terminated",
    }

    for error in errors:
        if error in response.content.decode().lower():
            return True

    return False


def scan_sql_injection(url: str, file):
    """
    Function to conduct the SQLi test on a given webpage.
    -----------------------------------------------------
    Param:
        str: url
        str: test file containing SQLi tests
    ----------------------------------------------------
    Return:
        None
    """
    for t in tests:
        t.strip()
        new_url = f"{url}{t}"
        print("[+] Testing: {}".format(new_url))

        # make the http request
        res = s.get(new_url)
        if vulnerable(res):
            # SQLi found, no need to proceed further in testing
            # Do not extract forms
            print("[+] SQLi vulnerability found: {}".format(new_url))

            return

    # test HTML forms found
    forms = get_all_forms(url)
    print("[*] Detected {} forms on {}.".format(len(forms), url))

    for form in forms:
        form_details = get_form_details(form)

        for s in tests:
            data = {}
            if input_tag["value"] or input_tag["type"] == "hidden":
                # if value is hidden, use it in form body
                try:
                    data[input_tag["name"]] = input_tag["value"] + s
                except:
                    pass

            elif input_tag["type"] != "submit":
                # all except submit, use junk data w/ special character
                data[input_tag["name"]] = f"test{s}"

        # join the url and form action
        url = urljoin(url, form_details["action"])
        if form_details["method"] == "post":
            send = s.post(url, data=data)
        elif form_details["method"] == "get":
            send = s.post(url, params=data)

        # test if resulting page is vulnerable
        if vulnerable(send):
            print("[+] SQLi detected: {}".format(url))
            print("[+] Form:")
            pprint(form_details)
            break


if __name__ == "__main__":

    parser = argparse.ArgumentParser(
        prog="sqli_test.py",
        usage="%(prog)s -u <url> -f <test file>",
        description="A simple SQLi testing program for websites and forms",
    )
    parser.add_argument("-u", "--url", help="target url", required=True)
    parser.add_argument(
        "-f",
        "--file",
        dest="testfile",
        type=argparse.FileType("r"),
        help="file containing SQLi tests",
        required=True,
    )
    args = parser.parse_args()

    scan_sql_injection(url, testfile.readlines())
= args.testfile

    scan_sql_injection(url, testfile.readlines())
