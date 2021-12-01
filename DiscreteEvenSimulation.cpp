#include <iostream>
#include <queue>
#include <cmath>
#include <list>
#include <string>
#include <climits>
#include <stdlib.h>
#include <time.h>

using namespace std;

class packet {
public:
	packet(double st) : service_time(st) {}
	double get_service_time() {
		return service_time;
	}

private:
	double service_time;
};

class event {
public:
	event(double time, char t) : start(time), type(t) {}
	double start_time() {
		return start;
	}
	char get_type() {
		return type;
	}

private:
	double start;
	char type;
};

bool compare(event e1, event e2) {
	return e1.start_time() < e2.start_time();
}

class MyGEL {
public:
	MyGEL() {}

	void insert(event e) {
		l.push_front(e);
		if (l.size() > 1) {
			l.sort(compare);
		}

	}

	event getFront() {
		event e = l.front();
		l.pop_front();
		return e;
	}
private:
	list<event> l;
};

double negative_exponenetially_distributed_time(double rate);
double pareto_distribution(double rate);
void process_arrival(event currEvent, double arrival_rate, double service_rate);
void process_departure(event currEvent);

//___________________________________________________________________________________

int length, num_dropped;
unsigned int MAXBUFFER;
double cur_time, busy_time, total_area;
std::queue<packet> q;
MyGEL *gel = new MyGEL();
bool isBusy = false;

int main() {
	length=0;
    num_dropped=0;
	cur_time=0;
    busy_time=0;
    total_area=0;
    MAXBUFFER = UINT_MAX;
	double arrival_rate=0.1, service_rate=1;

	//event *cur_event=new event(pareto_distribution(arrival_rate), 'a');
	event *cur_event=new event(negative_exponenetially_distributed_time(arrival_rate), 'a');
	gel->insert(*cur_event);

	for(int i = 0; i < 100000; i++){
	//1. get the first event from the GEL;
		event e = gel->getFront();

        //cout << e.get_type() << ' ' << e.start_time() << "\n";
	//2. If the event is an arrival then process-arrival-event;
	//3. Otherwise it must be a departure event and hence process-
		if (e.get_type() == 'a') {
			process_arrival(e, arrival_rate, service_rate);
		} else {
			process_departure(e);
		}
	}

	//output_statistics
    cout << "Mean queue length: " << total_area / cur_time << "\n";
	cout << "Fraction of time server is busy: " << busy_time / cur_time << "\n";
	cout << "Number of packets dropped: " << num_dropped;
}

double negative_exponenetially_distributed_time(double rate) {
	double u;

	//u = uniform random distribution
	//u = drand48();
	u = rand() / (RAND_MAX + 1.0);

	return ((-1/rate)*log(1-u));
}

double pareto_distribution(double rate){
    //equation from https://math.stackexchange.com/questions/1777367/how-to-generate-a-random-number-from-a-pareto-distribution
    double Xm = 0.01;
    return Xm * exp(negative_exponenetially_distributed_time(rate));
}

//adds new packet to queue and new event to GEL
void process_arrival(event currEvent, double arrival_rate, double service_rate)
{
    //updateStats for mean queue-length and server busy time
    double interval = isBusy * (currEvent.start_time() - cur_time);
    busy_time += interval;
    total_area += interval * length;
    isBusy = true;

    cur_time = currEvent.start_time();

    //schedule next event
    //double timeNextArrival = cur_time + pareto_distribution(arrival_rate);
    double timeNextArrival = cur_time + negative_exponenetially_distributed_time(arrival_rate);
    double packetServiceTime = negative_exponenetially_distributed_time(service_rate);
    packet *p1 = new packet(packetServiceTime);
    event *nextArrival = new event(timeNextArrival, 'a');
    gel->insert(*nextArrival);

    //processing
    if(length == 0)
    {
        event *d = new event(cur_time + p1->get_service_time(), 'd');
        gel->insert(*d);
    }

    //if elements already in queue
    else
    {
        //if not at max capacity
        if(length - 1 < MAXBUFFER)
        {
            q.push(*p1);
        }
        //if at max capacity, must drop this packet
        else
        {
            num_dropped++;
            length--; // length stays the same, so decrement now because it will increment at the end of the function
        }
    }
    length++;
}

void process_departure(event currEvent)
{
    //updateStats for mean queue-length and server busy time
    double interval = isBusy * (currEvent.start_time() - cur_time);
    busy_time += interval;
    total_area += interval * length;
    cur_time = currEvent.start_time();

    length--;

    //no packets in queue to depart
    if(length == 0)
    {
        isBusy = false;
        return;
    }

    //if there are packets in the queue, then have the first packet depart
    packet p1 = q.front();
    q.pop();
    event *d = new event(cur_time + p1.get_service_time(), 'd');
    gel->insert(*d);
}
