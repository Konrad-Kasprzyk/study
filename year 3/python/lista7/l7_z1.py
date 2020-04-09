import requests
import threading
import queue
import html.parser
import re
import bs4

class MyHTMLParser(html.parser.HTMLParser):
    links = list()

    def handle_starttag(self, tag, attrs):
        if tag == 'a':
            for (atr, val) in attrs:
                if atr == 'href':
                    self.links.append(val)



adres = "([a-zA-Z]+\.)*[a-zA-Z]+" 
automat = re.compile("https*://" + adres)
used_links = []
myparser = MyHTMLParser()


def crawl_thread(start_page, distance, action):
    pipe = queue.Queue()
    main_crawl_thread = threading.Thread(target=crawl, args=[start_page, distance, action, pipe])
    main_crawl_thread.start()
    while main_crawl_thread.is_alive() or not pipe.empty():
        try:
            # format (link, tresc)
            krotka = pipe.get(False)
            yield krotka
        except queue.Empty:
            pass
    print("\n\nkoncze")

# wywołuje funckje action i daje wynik do pipe  
def action_thread(link, action, pipe):
    res = action(link)
    pipe.put((link,res))


def crawl(start_page, distance, action, pipe):
    if distance == 0:
        return None
    threads = []
    r = requests.get(start_page)
    myparser.feed(r.text)
    # mam listę linków
    links_list = myparser.links
    for link in links_list:
        # Jeśli to jest link i wcześniej do niego nie weszliśmy
        if automat.match(link) and link not in used_links:
            # funckja action_thread będzie wykonana jako osobny wątek, dzięki temu funkcja action jest bez zmian
            threads.append(threading.Thread(target=action_thread, args=[link, action, pipe]))
            threads[-1].start()
            # naprawia powtarzające się linki z ukośnikiem i bez ukosnika na końcu
            if link[:-1] != "/":
                link+= "/"
            used_links.append(link)
            # rekurencyjne wywołania to też wątki
            threads.append(threading.Thread(target=crawl, args=[link, distance-1, action, pipe]))
            threads[-1].start()
    for thread in threads:
        thread.join()

# zwraca listę zdań z 'Python'
def lines_with_Python(x):
    r = requests.get(x)
    bs = bs4.BeautifulSoup(r.text, "html.parser")
    # wypisuje sam tekst bez znaczników w html
    sent = bs.get_text()
    # bierze linie i usuwa z nich białe znaki na początku i końcu
    split = (x.strip() for x in sent.splitlines())
    lista = list()
    for x in split:
        if "Python" in x:
            lista.append(x)
    return lista






for x, y in crawl_thread("http://www.ii.uni.wroc.pl/~marcinm/dyd/python/", 1, lines_with_Python):
    print("\n ----------------- \n")
    print("Url", x, "After action", y)