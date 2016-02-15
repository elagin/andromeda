#ifndef API_H
#define API_H

#include <iostream>
#include <cstring>
#include <string>

using namespace std;

class Api
{
public:
	Api();
	string login(string name, string pass);

private:
	string newUUID();
};

#endif // API_H
