import queue
import time
import threading


def stop(pipe,event):
    #while not event.is_set() or not pipe.empty():
    while not event.is_set() or not pipe.empty():
        try:
            print(pipe.get(False))
        except queue.Empty:
            pass
    print("koncze")

pipeline = queue.Queue()


pipeline.put(20)
pipeline.put(30)

event = threading.Event()

threading.Thread(target=stop, args=(pipeline,event)).start()


time.sleep(1)
event.set()


kr = (1, 2)

with kr as (x, y):
    print(x, y)















