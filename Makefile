
prog: *.cpp
	g++ main.cpp -o $@

clean:
	rm prog