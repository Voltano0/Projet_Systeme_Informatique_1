# Project 1 Multi-threaded programming and evaluation of performance.

We had to implement 3 simple multi-threaded algorithms and test their performance on a 32 core machine. Thoses algorithms are : Dining Philosophers, 
WriterReader and ProducerConsumer. After that, we had to implement test-and-set and test-and-test-and-set algorithms in inline assembly. 
Create a custom semaphore with those spinlock and rewrite the 3 algorithms with the custom semaphore.

## Structure of the code
- `headers/` contains our custom lock and semaphore.
- `logs/` contains the output of the valgrind execution.
- `Soumission_Studsrv/` contains the output of our code on the 32 core machine.
- `src/` contains all the C files.
- `temp/` contains all the output of our code.
- `experiments.sh/` is the bash script to evaluate the perfomances.
- `GraphMaker.py/` is the python script to plot the outputs.
- `Makefile/` is the script to comppile and run the code.
- `README.md/` contains all the usefull informations for the project.
## How to run the code.
 
```bash
$ make : 
```
Compile all the files in src and make the folders for valgrinds logs and the output.