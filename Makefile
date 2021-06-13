
prog: *.cpp */*
	g++ -Idata -Iboost_serialization main.cpp -o $@ -lboost_serialization

clean:
	rm prog
