
prog: *.cpp data/*
	g++ -Idata main.cpp -o $@

clean:
	rm prog