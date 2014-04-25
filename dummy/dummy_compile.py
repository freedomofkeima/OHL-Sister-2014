from time import sleep
from random import uniform

flags = "-Iincludes -Llibs -lwinafx -lappxt -lbgmi -lhdmi -lgdi32 -lglut32 -lsnd32 -lx86_64 -lardax -lwmd32 -lcrt64"

i = 0
k = 0
nk = uniform(0,100)

with open("dummy/files.txt", "r") as file:
	for line in file:
		filepart = line.rsplit('.', 1)
		compiler = "gcc" if filepart[1] == "c" else "g++"
		
		if i % 50 == 0:
			print "\t{0} -c {1} {2}".format(compiler, line, flags)

		i+=1
		
		print "\t[CC] {0}.o".format(filepart[0])
		
		if k >= nk:
			k = 0
			nk = uniform(0,100)
			sleep(0.5)
		else:
			k+=1
			sleep(0.01)
			
print
print "Integrating modules..."
sleep(1.5)
print "Done."