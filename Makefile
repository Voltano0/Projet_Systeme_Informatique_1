make:
	mkdir -p temp
	mkdir -p logs
	gcc  -o temp/Philosof Philosof.c -lpthread
	gcc  -o temp/WriterReader WriterReader.c -lpthread    
	gcc  -o temp/Producer_Consumer Producer_Consumer.c -lpthread    
	gcc  -o temp/Perftest perftest.c -lpthread
clean:
	rm -f temp/*
	rm -f logs/*
test:
	make
	./experiments.sh > temp/output.csv
	python3 GraphMaker.py
testMemory:
	make
	valgrind --log-file="logs/Philosof_valgrind.log" --leak-check=yes temp/Philosof 2

# a .PHONY target forces make to execute the command even if the target already exists
# $(CC) -o  TestSystemC tests/TestSystemC.c -lcunit
.PHONY: clean tests
