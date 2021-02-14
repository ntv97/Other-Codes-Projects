#include<iostream>
#include<cmath>
#include<limits>
#include<time.h>
#include<stdlib.h>
#include<string>
#include<queue>
#include<deque>
#include<vector>
#include<list>

using namespace std;

double cur_time, q_delay, t_delay;

class frame {
public:
        frame(double tme, char tpe, int snder, int rcvr, int len) : time(tme), type(tpe), sender(snder), receiver(rcvr), length(len) {}
        double get_time() { return time; }
        char get_type() { return type;}
        void change_time(double serv_time) { time = serv_time; }
        void change_sender(int s) { sender=s; }
        void change_receiver(int r) { receiver = r; }
        void change_type(char t) { type = t; }
	void change_times_sent(int x) { times_sent = x; }
        int get_sender() { return sender; }
        int get_receiver() { return receiver; }
        int get_length() { return length; }
        int add_times_sent() { times_sent++; }
        int get_times_sent() { return times_sent; }
	double q_start_t;
private:
        double time;
        char type;
        int sender;
        int receiver;
        int length;
        int times_sent = 0;
};

bool operator<(frame f1, frame f2) {
        return f1.get_time() > f2.get_time();
}

class host {
public:
        host(int id_num) : id(id_num) {}
        int get_id() { return id; }
        double get_front_time() {
                frame f = q.top();
                return f.get_time();
        }
        void add_frame(double tme, char tpe, int s, int r, int len) {
                frame f{tme, tpe, s, r, len};
                q.push(f);
        }
        frame get_frame() {
                frame f = q.top();
                q.pop();
                return f;
        }
private:
        int id;
        std::priority_queue<frame> q;
};

bool compare(frame f1, frame f2) {
        return f1.get_time() < f2.get_time();
}

class FrameList {
public:
        FrameList() {}

        void insert(frame f) {
                l.push_front(f);
                if (l.size() > 1) {
                        l.sort(compare);
                }

        }
        void push_front(frame f) {
                l.push_front(f);
        }
	void change_top_time(double tme) { 
		frame &f = l.front();
		f.change_time(tme);
	}

        frame getFront() {
                frame f = l.front();
                l.pop_front();
                return f;
        }
	double top_time() {
		if(l.size()==0) {
		} else {
			frame f = l.front();
			return f.get_time();
		}
	}

private:
        list<frame> l;
};

class Queue {
public:
        Queue() {}
        void push_front(frame f) {
		if(f.get_times_sent()==0 || f.get_times_sent()==1) {
			f.q_start_t = cur_time;
		}
                qchannel.push(f);
        }
        frame get_frame() {
                frame f = qchannel.front();
                qchannel.pop();
                return f;
        }
        int get_size() { return qchannel.size(); }
	bool is_empty() { return qchannel.empty(); }
        bool is_idle() { return idle; }
        bool is_busy() { return !idle; }
        void change_idle(bool stat) { idle = stat; }
private:
        std::queue<frame> qchannel;
        int id = 0;
        bool idle = true;
};

double negative_exponentially_distributed_time(double rate) {
        double u;

        //u = uniform random distribution
        //u = drand48();
        u = rand() / (RAND_MAX + 1.0);

        return ((-1/rate)*log(1-u));
}

frame get_next_frame();
frame create_frame(char type);
void process_sending(frame f);
void process_receiving(frame f);
void add_frame_to_list();
void process_ack(frame f);
void calc_q_delay(frame f);
int create_random_id(int max, int exclude);
int get_backoff_value(int n);
int get_frame_length();

std::vector<host> host_v;
int linkcapacity = 10*1000000; //bps
double arrival_rate, service_rate = linkcapacity/1544, difs=0.0001*100, sifs=0.00005*100;
FrameList fl;
Queue q; //max capacity = 10 Mbps;
int hostnum, length, num_dropped, MAX_TIMES_SENT = 1, backoff,t=106, collision, tot_bytes, bytes_dropped;


int main() {
	double avg_throughput;
	double avg_delay;
	int host_id = std::numeric_limits<int>::infinity(), total_time = 100000/100;
        double min_time = std::numeric_limits<double>::infinity();
        std::cout << "Enter host number: ";
        std::cin >> hostnum;
	std::cout << "Enter arrival rate: ";
	std::cin >> arrival_rate;
        std::cout << "Enter T value: ";
        std::cin >> t;

        for(int i=0; i<hostnum; i++) {
                host h{i};
                h.add_frame(negative_exponentially_distributed_time(arrival_rate), 's', i, create_random_id(hostnum,i), get_frame_length());
                host_v.push_back(h);
                if(h.get_front_time() < min_time) {
                        host_id = i;
                        min_time = h.get_front_time();
                }
        }
        fl.insert(host_v[host_id].get_frame());

        for(int i = 0; i < total_time; i++) {
                frame f = fl.getFront();

                if (f.get_type() == 's') {
                        process_sending(f);
                }
                else if(f.get_type() == 'r') {
                        process_receiving(f);
                } else if(f.get_type() == 'a') {
                        process_ack(f);
                }
        }
	
	t_delay = tot_bytes*8.0/linkcapacity;
	avg_throughput = (double)tot_bytes/double(total_time); // in bytes
	avg_delay = (t_delay + q_delay)/tot_bytes;
	std::cout << arrival_rate << "   avg throughput: " << avg_throughput << "     avg network delay: " << avg_delay <<  std::endl;
}




int create_random_id(int max, int exclude) {
        int rand_id;
        do {
                rand_id = rand() % max;
        } while(rand_id == exclude);

        return rand_id;
}

void process_sending(frame f) {
	if(backoff && q.is_idle()) {
		cur_time += backoff;
		backoff = 0;
	} else {
		cur_time = f.get_time();
	}

        if (f.get_times_sent() > MAX_TIMES_SENT) {
                num_dropped++;
                bytes_dropped += f.get_length();
                return;
        }

	add_frame_to_list();
	frame nextframe = get_next_frame();

	if(cur_time > nextframe.get_time() || (!backoff && cur_time > nextframe.get_time())) {
		if(!backoff) {
			collision++;
			backoff = get_backoff_value(1);
			nextframe.add_times_sent();
			f.change_time(cur_time + negative_exponentially_distributed_time(arrival_rate));
			q.push_front(nextframe);
			fl.push_front(f);
			q.change_idle(false);
			return;
		}
	}
	
	cur_time += difs;
	f.change_time(cur_time + negative_exponentially_distributed_time(service_rate));
	f.change_sender(f.get_receiver());
	f.change_receiver(f.get_sender());
	f.change_type('r');

	q.push_front(nextframe);

	calc_q_delay(f);
	fl.push_front(f);
	f.add_times_sent();
	q.change_idle(false);
}

void process_receiving(frame f) {
	cur_time = f.get_time();

	add_frame_to_list();

	f.change_time(cur_time + negative_exponentially_distributed_time(service_rate));
	f.change_sender(f.get_receiver());
	f.change_receiver(f.get_sender());
	f.change_type('a');
	cur_time += sifs;
	fl.push_front(f);

	tot_bytes += f.get_length();

}

void process_ack(frame f) {
	frame nextframe = get_next_frame();
	cur_time = f.get_time();

	tot_bytes += f.get_length();
	add_frame_to_list();

        if(cur_time > nextframe.get_time() || (!backoff && cur_time > nextframe.get_time())) {
                if(!backoff) {
                        collision++;
			backoff = get_backoff_value(f.get_times_sent());
                        nextframe.add_times_sent();
			f.change_time(cur_time + negative_exponentially_distributed_time(arrival_rate));
			f.change_sender(f.get_receiver());
			f.change_receiver(f.get_sender());
			f.change_type('s');
			q.push_front(nextframe);
                        fl.push_front(f);
			return;
                }
	}
	t_delay += f.get_length()/linkcapacity;
	q.push_front(nextframe);
	tot_bytes += 64;
	q.change_idle(true);

}

int get_frame_length() {
        double u;
        u = rand() / (RAND_MAX + 1.0);
        u = ((-1/arrival_rate)*log(1-u));
        u = std::fmod(1544,u);
        return int(std::round(u));
}

int get_backoff_value(int n) {
        if(n==1) {
        	double val = ((double) rand() / (RAND_MAX));
        	val *= t;
        	return int(round(val));
	} else {
		int interval = n*t + 1;
		return rand()%interval;
	}
}

void add_frame_to_list() { 
	int host_id = std::numeric_limits<int>::infinity();
	double min_time = std::numeric_limits<double>::infinity();
        for(int i=0; i<hostnum; i++) {
                host_v[i].add_frame(cur_time + negative_exponentially_distributed_time(arrival_rate), 's', i, create_random_id(hostnum,i), get_frame_length());
                if(host_v[i].get_front_time() < min_time) {
                        host_id = i;
                        min_time = host_v[i].get_front_time();
                }
        }
	frame hostframe = host_v[host_id].get_frame();
        fl.insert(hostframe);
}

frame get_next_frame() {
	if(!q.is_empty()) {
		frame f = q.get_frame();
		return f;
	} else {
		frame f = fl.getFront();
		return f;
	}
}

void calc_q_delay(frame fr) {
	q_delay += cur_time - fr.q_start_t;	
}
