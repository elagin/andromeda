#include <iostream>
#include <cstring>
#include <string>
#include <served/served.hpp>
#include "api.h"

using namespace std;

//login?name=demo&pass=demo
//getVehiclesByUser?name=demo&sessionID=2b0ad2d8-2ad0-4650-930b-6ce8f17a7f1f
//{"data":"ok","err":{"code":"success"},"meta":{"sessionID":"2b0ad2d8-2ad0-4650-930b-6ce8f17a7f1f"}}

Api api;

int main(int argc, char const* argv[]) {
	// Create a multiplexer for handling requests
	served::multiplexer mux;

	// register middleware / plugin
	mux.use_before([](served::response & res, const served::request & req) {
		std::cout << "request: " << req.url().URI() << std::endl;
	});

	mux.use_after([](served::response & res, const served::request & req) {
		res.set_header("Access-Control-Allow-Credentials","true");
		res.set_header("Access-Control-Allow-Origin", "*");
		res.set_header("Access-Control-Allow-Headers","Content-Type,SessionID,SOAPAction");
		res.set_header("Access-Control-Expose-Headers", "SessionID");

	});

	// GET /hello
	mux.handle("/hello")
			.get([](served::response & res, const served::request & req) {
		// iterate all query params
		for ( const auto & query_param : req.query ) {
			res << "Key: " << query_param.first << ", Value: " << query_param.second << "\n";
		}
		// get a specific param value, returns an empty string if it doesn't exist.
		res << "test: " << req.query["test"] << "\n";
	});

	// GET /login
	mux.handle("/login")
			.get([](served::response & res, const served::request & req) {

		// check headers for the correct content type
//		if ( req.header("content-type") != "application/x-www-form-urlencoded" )
//		{
//			// return 400 bad request if the content type is wrong for this example.
//			served::response::stock_reply(400, res);
//		}
//		else
		{

			string name = req.query["name"];
			string pass = req.query["pass"];
			if(!name.empty() && !pass.empty()) {
				//res << "Login: "<< name << "\n";
				//res << "Password: "<< pass << "\n";
				res << api.login(name, pass);
			} else {
				res << "few parameters";
			}
		}
	});

	// Create the server and run with 10 handler threads.
	served::net::server server("127.0.0.1", "8081", mux);
	server.run(10);

	return (EXIT_SUCCESS);
}
