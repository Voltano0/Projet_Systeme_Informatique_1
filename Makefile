make:
	mkdir -p temp
	mkdir -p logs
	gcc  -o temp/Philosof src/Philosof.c -lpthread
	gcc  -o temp/WriterReader src/WriterReader.c -lpthread    
	gcc  -o temp/Producer_Consumer src/Producer_Consumer.c -lpthread    
	gcc  -o temp/Perftest src/test_and_set.c -lpthread
	gcc  -o temp/Perftest2 src/test_and_test_and_set.c -lpthread
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
