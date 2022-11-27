make:
	#gcc  -o bin/Philosof Philosof.c -lpthread
	gcc  -o bin/WriterReader WriterReader.c -lpthread    
	gcc  -o bin/Producter_Consumer Producter_Consumer.c -lpthread    
clean:
	rm -f bin/*

tests:


# a .PHONY target forces make to execute the command even if the target already exists
# $(CC) -o  TestSystemC tests/TestSystemC.c -lcunit
.PHONY: clean tests
