all:
	g++ -g src/main.cpp src/api.cpp -o bin/main -std=c++11 -L/home/pavel/dev/cpp/served/lib/ -lboost_system -lserved -luuid
