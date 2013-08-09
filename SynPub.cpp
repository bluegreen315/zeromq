#include <string>
#include "zhelpers.hpp"
using namespace std;

//we wait for 10 subscribers
#define SUBSCRIBERS_EXPECTED 10

int main() {
  zmq::context_t context(1);

	//  Socket to talk to clients
	zmq::socket_t publisher(context, ZMQ_PUB);
	publisher.bind("tcp://*:5561");

	//  Socket to receive singals
	zmq::socket_t syncservice(context, ZMQ_REP);
	syncservice.bind("tcp://*:5562");

	//  Get synchronization from subscribers
	int subscribers = 0;
	while(subscribers < SUBSCRIBERS_EXPECTED) {
		//   -wait for synchronization request
		s_recv(syncservice);
		//   -sent synchronization reply
		s_send(syncservice, "");

		subscribers ++;
	}

	//Prepare data
	int message_size = 2000;
	string data ;
	for(int i = 0; i < (message_size / 10); i ++) {
		data.append("AAAAAAAAAA");
	}

	long start = clock();
	//  Now broadcast exactly 1M updates followed by END
	int total_count = 1000;

	int update_nbr;
	for(update_nbr = 0; update_nbr < total_count; update_nbr++) {
		s_send(publisher, data);
//		cout << "Sent " << (update_nbr + 1) << " updates" << endl;
	}
	s_send(publisher, "END");

	long end = clock();
	double time = (double)(end - start) / CLOCKS_PER_SEC;
	cout << "Publish Time : " << time << " seconds" << endl;
//	cout << "Total_Sent " << (update_nbr + 1) << " updates" << endl;

	sleep(1);                  // Give 0MQ time to flush output
	return 0;
}
