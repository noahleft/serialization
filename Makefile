
prog: *.cpp */*
	g++ -Idata -Iboost_serialization main.cpp -o $@

clean:
	rm prog
