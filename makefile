make:
	g++ main.cpp -std=c++11 -Wall
run:
	./a.out adwCommands.txt sampleCommands.txt > results.txt 
clean:
	rm a.out results.txt
