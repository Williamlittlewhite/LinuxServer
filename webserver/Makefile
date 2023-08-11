app:http_conn.o main.o
	g++ -c main.cpp -o main.o
	g++ main.o http_conn.o -o app -pthread
http_conn.o: ./http_conn/http_conn.cpp
	g++ -c http_conn/http_conn.cpp -o http_conn.o
main.o: main.cpp
	g++ -c main.cpp -o main.o

.PHONY:clean
#./PHONY 来显示的指名一个目标是伪目标，有两个作用一个是改善性能，另外一个是来避免冲突。  
#如果没有./PHONY且有一个叫clean的文件 make clean将一直是最新 无法删除目标 

clean:
	rm *.o