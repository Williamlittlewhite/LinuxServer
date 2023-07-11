app:http_conn.o main.o
	g++ -c main.cpp -o main.o
	g++ main.o http_conn.o -o app -pthread
http_conn.o: ./http_conn/http_conn.cpp
	g++ -c http_conn/http_conn.cpp -o http_conn.o
main.o: main.cpp
	g++ -c main.cpp -o main.o 