target:
	g++ -fPIC -c hello.cpp -o hello.o -I/usr/include/python2.7 
	g++ -shared -o hello.so hello.o -lpython2.7 -lboost_python
clean:
	rm -rf hello.o hello.so
