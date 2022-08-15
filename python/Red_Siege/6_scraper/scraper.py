import requests
from urllib.parse import urlparse, urljoin
from bs4 import BeautifulSoup
import colorama
import string

from rich.console import Console
from rich.table import Table

# init the colorama module
colorama.init()

GREEN = colorama.Fore.GREEN
GRAY = colorama.Fore.LIGHTBLACK_EX
RESET = colorama.Fore.RESET
YELLOW = colorama.Fore.YELLOW

# initialize the set of links (unique links)
internal_urls = set()
external_urls = set()

total_urls_visited = 0
WORDS = []


def is_valid(url):
    """
    Checks whether `url` is a valid URL.
    """
    parsed = urlparse(url)
    return bool(parsed.netloc) and bool(parsed.scheme)


def get_all_website_links(url):
    """
    Returns all URLs that is found on `url` in which it belongs to the same website
    """
    # all URLs of `url`
    urls = set()
    soup = BeautifulSoup(requests.get(url).content, "html.parser")
    for a_tag in soup.findAll("a"):
        href = a_tag.attrs.get("href")
        if href == "" or href is None:
            # href empty tag
            continue
        # join the URL if it's relative (not absolute link)
        href = urljoin(url, href)
        parsed_href = urlparse(href)
        # remove URL GET parameters, URL fragments, etc.
        href = parsed_href.scheme + "://" + parsed_href.netloc + parsed_href.path
        if not is_valid(href):
            # not a valid URL
            continue
        if href in internal_urls:
            # already in the set
            continue
        if domain_name not in href:
            # external link
            if href not in external_urls:
                print(f"{GRAY}[!] External link: {href}{RESET}")
                external_urls.add(href)
            continue
        print(f"{GREEN}[*] Internal link: {href}{RESET}")
        urls.add(href)
        internal_urls.add(href)
    return urls


def crawl(url, max_urls=30):
    """
    Crawls a web page and extracts all links.
    You'll find all links in `external_urls` and `internal_urls` global set variables.
    params:
        max_urls (int): number of max urls to crawl, default is 30.
    """
    global total_urls_visited
    total_urls_visited += 1
    print(f"{YELLOW}[*] Crawling: {url}{RESET}")
    links = get_all_website_links(url)
    for link in links:
        if total_urls_visited > max_urls:
            break
        crawl(link, max_urls=max_urls)


def get_words(link):
    try:
        soup = BeautifulSoup(requests.get(link).text, "html.parser")
        for stuff in soup.find_all("p"):
            content = stuff.text
            words = content.lower().split()

            for word in words:
                if len(word) > 4:
                    if "http://" in word:
                        continue
                    elif "https://" in word:
                        continue
                    word = word.translate(str.maketrans("", "", string.punctuation))
                    WORDS.append(word)
    except:
        pass


def make_table():
    table = Table(title="Frequency of Words")

    table.add_column("Word", justify="center", style="blue")
    table.add_column("Frequency", justify="center", style="red")

    return table


if __name__ == "__main__":
    import argparse

    parser = argparse.ArgumentParser(description="Link Extractor Tool with Python")
    parser.add_argument("url", help="The URL to extract links from.")
    parser.add_argument(
        "-m",
        "--max-urls",
        help="Number of max URLs to crawl, default is 30.",
        default=30,
        type=int,
    )

    args = parser.parse_args()
    url = args.url
    max_urls = args.max_urls
    console = Console()
    # domain name of the URL without the protocol
    domain_name = urlparse(url).netloc
    crawl(url, max_urls=max_urls)

    print("[+] Total Internal links:", len(internal_urls))
    print("[+] Total External links:", len(external_urls))
    print("[+] Total URLs:", len(external_urls) + len(internal_urls))
    print("[+] Total crawled URLs:", max_urls)

    with open("internal_urls.txt", "w") as f:
        for link in internal_urls:
            f.write(link)

    for link in internal_urls:
        get_words(link)

    table = make_table()

    words = [i for i in WORDS if len(i) > 4]
    new_words = []
    for word in words:
        new_words.append((word, words.count(word)))
    new_words = set(sorted(new_words, key=lambda tup: tup[1], reverse=True))

    for item in list(new_words):
        table.add_row(item[0], str(item[1]))

    console.print(table)
