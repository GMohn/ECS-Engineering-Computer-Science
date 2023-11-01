import time
start_time = time.time()
def concat():
	l  = []
	for i in range (1000):
		l = l + [i]

def append():
	l = []
	for i in range (1000):
		l.append(i)
print("--- %s seconds ---" % (time.time() - start_time))