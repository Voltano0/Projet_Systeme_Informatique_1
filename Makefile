make:
	mkdir -p temp
	#gcc  -o temp/Philosof Philosof.c -lpthread
	gcc  -o temp/WriterReader WriterReader.c -lpthread    
	gcc  -o temp/Producer_Consumer Producer_Consumer.c -lpthread    
clean:
	rm -f temp/*

test:
	make
	./experiment.sh > temp/output.csv
	python3 GraphMaker.py

# a .PHONY target forces make to execute the command even if the target already exists
# $(CC) -o  TestSystemC tests/TestSystemC.c -lcunit
.PHONY: clean tests
