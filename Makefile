make:
	mkdir -p temp
	mkdir -p logs
	gcc  -o temp/Philosof src/Philosof.c -lpthread
	gcc  -o temp/WriterReader src/WriterReader.c -lpthread    
	gcc  -o temp/Producer_Consumer src/Producer_Consumer.c -lpthread       
	gcc  -o temp/Perftest src/test_and_set.c -lpthread
	gcc  -o temp/Perftest2 src/test_and_test_and_set.c -lpthread
	gcc  -o temp/Philosof_AC src/Philosof_AC.c -lpthread
	gcc  -o temp/WriterReader_AC src/WriterReader_AC.c -lpthread 
	gcc  -o temp/Producer_Consumer_AC src/Producer_Consumer_AC.c -lpthread 
clean:
	rm -f temp/* 
	rm -f logs/* 
test:
	make
	./experiments.sh > temp/output.csv
	python3 GraphMaker.py

testMem:
	make
	valgrind --log-file="logs/Philosof_valgrind.log" --leak-check=yes temp/Philosof 2
	valgrind --log-file="logs/Philosof_AC_valgrind.log" --leak-check=yes temp/Philosof_AC 2
	valgrind --log-file="logs/WriterReader_valgrind.log" --leak-check=yes temp/WriterReader 2 2
	valgrind --log-file="logs/WriterReader_AC_valgrind.log" --leak-check=yes temp/WriterReader_AC 2 2
	valgrind --log-file="logs/test_and_set_valgrind.log" --leak-check=yes temp/Perftest 2
	valgrind --log-file="logs/test_and_test_and_set_valgrind.log" --leak-check=yes temp/Perftest2 2
	valgrind --log-file="logs/Producer_Consumer_valgrind.log" --leak-check=yes temp/Producer_Consumer 2 2
zip:
	make clean
	zip -r ../Projet.zip . -x "*.git*" "*.vscode*"

# a .PHONY target forces make to execute the command even if the target already exists
.PHONY: clean tests
