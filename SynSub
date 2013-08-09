/*
 * Subscriber.cpp
 *
 *  Created on: Aug 7, 2013
 *      Author: root
 */
#include <string>
#include "zhelpers.hpp"
using namespace std;

int main(int argc, char* argv[]) {

  zmq::context_t context(1);

	// First, connect our subscriber socket
	zmq::socket_t subscriber(context, ZMQ_SUB);
	subscriber.connect("tcp://114.214.163.182:5561");
	subscriber.setsockopt(ZMQ_SUBSCRIBE, "", 0);

	// Second, synchronize with publisher
	zmq::socket_t syncclient(context, ZMQ_REQ);
	syncclient.connect("tcp://114.214.163.182:5562");

	// -send a synchronization request
	s_send(syncclient, "");

	// - wait for synchronization reply
	s_recv(syncclient);

	// Third, get our updates and report how many we got
	long start = clock();
	int update_nbr = 0;
	while(1) {

		if(s_recv(subscriber).compare("END") == 0) {
			break;
		}
		update_nbr ++;
	}

	long end = clock();
	long subscribe_time = (long) (end -start) / CLOCKS_PER_SEC;
	cout << "subscribe time: " << subscribe_time << " seconds , " << "Received " << update_nbr << " updates" << endl;

	return 0;
}
