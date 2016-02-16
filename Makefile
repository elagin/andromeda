all:
	g++ -g src/main.cpp src/api.cpp -o bin/main -std=c++11 -L/usr/local/lib/ -I/usr/include/mysql-connector-c++/ -lboost_system -lserved -luuid -lmysqlcppconn


