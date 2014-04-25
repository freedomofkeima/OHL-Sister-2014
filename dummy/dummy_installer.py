from time import sleep


with open("dummy/files.txt", "r") as file:
	for line in file:
		filepart = line.rsplit('.', 1)
		
		print "Installing {0}".format(filepart[0])
		sleep(0.01)
		
print
print "Done."