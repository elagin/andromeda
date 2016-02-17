all:
	g++ -g src/main.cpp src/api.cpp -o bin/main -std=c++11 -L/usr/local/lib/ -I/usr/include/mysql-connector-c++/ -lboost_system -lserved -luuid -lmysqlcppconn -lsoci_core -lsoci_mysql -lsoci_odbc -ldl -lmysqlclient -I/usr/local/include/soci/mysql/ -I/usr/local/include/soci/ -I/usr/include/mysql


