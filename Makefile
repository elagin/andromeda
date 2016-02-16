all:
	g++ -g src/main.cpp src/api.cpp -o bin/main -std=c++11 -L/home/pavel/dev/cpp/served/lib/ -L/usr/local/lib/ -I/usr/include/mysql-connector-c++-1.1.4/ -lboost_system -lserved -luuid -lmysqlcppconn


