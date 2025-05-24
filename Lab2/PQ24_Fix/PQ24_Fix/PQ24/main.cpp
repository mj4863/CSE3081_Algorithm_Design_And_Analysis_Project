// 
// CSE3081-1/AIE3051-1 Design and Analysis of Algorithm
// (c) 2024 Soang University
//
// Example: Using min heap to manage clients with priority
// main.cpp
//

#include "clients_fix.h"

CLIENTS my_clients(65536);

void example_1() {
	my_clients.add_client(10037, 59, nullptr);
	my_clients.add_client(10128, 14, nullptr);
	my_clients.add_client(10055, 13, nullptr);
	my_clients.add_client(10355, 77, nullptr);
	my_clients.add_client(10152, 19, nullptr);
	my_clients.add_client(10015, 66, nullptr);
	my_clients.add_client(10111, 54, nullptr);
	my_clients.add_client(10125, 37, nullptr);
	my_clients.add_client(10512, 25, nullptr);
	my_clients.add_client(10001, 2, nullptr);

	my_clients.print_clients("example_1");
	my_clients.print_min_heap("example_1");
	my_clients.print_min_heap_into_file("result_mh_ex_1.txt");
	my_clients.print_clients_into_file("result_cl_ex_1.txt");
}

void example_2() {
	int client_ID, priority;
	CLIENT_DATA* client_data;

	my_clients.add_client(10037, 59, nullptr);
	my_clients.add_client(10128, 14, nullptr);
	my_clients.add_client(10055, 13, nullptr);
	my_clients.add_client(10355, 77, nullptr);
	my_clients.add_client(10152, 19, nullptr);
	my_clients.add_client(10015, 66, nullptr);
	my_clients.add_client(10111, 54, nullptr);
	my_clients.add_client(10125, 37, nullptr);
	my_clients.add_client(10512, 25, nullptr);
	my_clients.add_client(10001, 2, nullptr);
	client_ID = my_clients.delete_client(&priority, &client_data);
	client_ID = my_clients.delete_client(&priority, &client_data);
	client_ID = my_clients.delete_client(&priority, &client_data);

	my_clients.print_clients("example_2");
	my_clients.print_min_heap("example_2");
	my_clients.print_min_heap_into_file("result_mh_ex_2.txt");
	my_clients.print_clients_into_file("result_cl_ex_2.txt");
}

void example_3() {
	int client_ID, priority;
	CLIENT_DATA* client_data;

	my_clients.add_client(10037, 59, nullptr);
	my_clients.add_client(10128, 14, nullptr);
	my_clients.add_client(10055, 13, nullptr);
	my_clients.add_client(10355, 77, nullptr);
	my_clients.add_client(10152, 19, nullptr);
	my_clients.add_client(10015, 66, nullptr);
	my_clients.add_client(10111, 54, nullptr);
	my_clients.add_client(10125, 37, nullptr);
	my_clients.add_client(10512, 25, nullptr);
	my_clients.add_client(10001, 2, nullptr);
	client_ID = my_clients.delete_client(&priority, &client_data);
	client_ID = my_clients.delete_client(&priority, &client_data);
	client_ID = my_clients.delete_client(&priority, &client_data);

	my_clients.add_client(20125, 18, nullptr);
	my_clients.add_client(20537, 49, nullptr);
	my_clients.adjust_client_priority(10125, +35);
	my_clients.add_client(20299, 22, nullptr);
	my_clients.adjust_client_priority(20537, -40);

	my_clients.print_clients("example_3");
	my_clients.print_min_heap("example_3");
	my_clients.print_min_heap_into_file("result_mh_ex_3.txt");
	my_clients.print_clients_into_file("result_cl_ex_3.txt");
}

void example_4() {
	int client_ID, priority;
	CLIENT_DATA* client_data;

	my_clients.add_client(10037, 59, nullptr);
	my_clients.add_client(10128, 14, nullptr);
	my_clients.add_client(10055, 13, nullptr);
	my_clients.add_client(10355, 77, nullptr);
	my_clients.add_client(10152, 19, nullptr);
	my_clients.add_client(10015, 66, nullptr);
	my_clients.add_client(10111, 54, nullptr);
	my_clients.add_client(10125, 37, nullptr);
	my_clients.add_client(10512, 25, nullptr);
	my_clients.add_client(10001, 2, nullptr);
	client_ID = my_clients.delete_client(&priority, &client_data);
	client_ID = my_clients.delete_client(&priority, &client_data);
	client_ID = my_clients.delete_client(&priority, &client_data);

	my_clients.add_client(20125, 18, nullptr);
	my_clients.add_client(20537, 49, nullptr);
	my_clients.adjust_client_priority(10125, +35);
	my_clients.add_client(20299, 22, nullptr);
	my_clients.adjust_client_priority(20537, -40);

	client_ID = my_clients.delete_client(&priority, &client_data);
	my_clients.add_client(30071, 15, nullptr);
	my_clients.adjust_client_priority(10015, -10);
	my_clients.add_client(30913, 40, nullptr);
	my_clients.add_client(30448, 30, nullptr);
	my_clients.adjust_client_priority(10355, 20);
	client_ID = my_clients.delete_client(&priority, &client_data);
	my_clients.adjust_client_priority(20299, -20);
	my_clients.add_client(30001, 20, nullptr);
	my_clients.add_client(30031, 35, nullptr);
	my_clients.adjust_client_priority(30001, 50);

	my_clients.print_clients("example_4");
	my_clients.print_min_heap("example_4");
	my_clients.print_min_heap_into_file("result_mh_ex_4.txt");
	my_clients.print_clients_into_file("result_cl_ex_4.txt");
}

void example_5() {
	int client_ID, priority;
	CLIENT_DATA* client_data;

	my_clients.add_client(10000, 100, nullptr);
	my_clients.add_client(10001, 2200, nullptr);
	my_clients.add_client(10002, 300, nullptr);
	my_clients.add_client(10003, 2300, nullptr);
	my_clients.add_client(10004, 3600, nullptr);
	my_clients.add_client(10005, 3900, nullptr);
	my_clients.add_client(10006, 200, nullptr);
	my_clients.add_client(10007, 3700, nullptr);
	my_clients.add_client(10008, 0, nullptr);
	my_clients.add_client(10009, 3400, nullptr);
	my_clients.add_client(20000, 2000, nullptr);
	my_clients.add_client(20001, 1900, nullptr);
	my_clients.add_client(20002, 3500, nullptr);
	my_clients.add_client(20003, 2900, nullptr);
	my_clients.add_client(20004, 3800, nullptr);
	my_clients.add_client(20005, 2800, nullptr);
	my_clients.add_client(20006, 1000, nullptr);
	my_clients.add_client(20007, 3300, nullptr);
	my_clients.add_client(20008, 1500, nullptr);
	my_clients.add_client(20009, 600, nullptr);
	my_clients.add_client(30000, 2100, nullptr);
	my_clients.add_client(30001, 1400, nullptr);
	my_clients.add_client(30002, 2700, nullptr);
	my_clients.add_client(30003, 900, nullptr);
	my_clients.add_client(30004, 400, nullptr);
	my_clients.add_client(30005, 3200, nullptr);
	my_clients.add_client(30006, 2500, nullptr);
	my_clients.add_client(30007, 500, nullptr);
	my_clients.add_client(30008, 3100, nullptr);
	my_clients.add_client(30009, 1100, nullptr);
	my_clients.add_client(40000, 2400, nullptr);
	my_clients.add_client(40001, 1200, nullptr);
	my_clients.add_client(40002, 1300, nullptr);
	my_clients.add_client(40003, 1800, nullptr);
	my_clients.add_client(40004, 3000, nullptr);
	my_clients.add_client(40005, 2600, nullptr);
	my_clients.add_client(40006, 800, nullptr);
	my_clients.add_client(40007, 1700, nullptr);
	my_clients.add_client(40008, 1600, nullptr);
	my_clients.add_client(40009, 700, nullptr);
	client_ID = my_clients.delete_client(&priority, &client_data);
	client_ID = my_clients.delete_client(&priority, &client_data);
	client_ID = my_clients.delete_client(&priority, &client_data);
	client_ID = my_clients.delete_client(&priority, &client_data);
	client_ID = my_clients.delete_client(&priority, &client_data);
	client_ID = my_clients.delete_client(&priority, &client_data);
	client_ID = my_clients.delete_client(&priority, &client_data);
	client_ID = my_clients.delete_client(&priority, &client_data);
	client_ID = my_clients.delete_client(&priority, &client_data);
	client_ID = my_clients.delete_client(&priority, &client_data);
	my_clients.adjust_client_priority(30000, -550);
	my_clients.adjust_client_priority(20006, 2050);
	my_clients.adjust_client_priority(20002, -2250);
	my_clients.adjust_client_priority(20005, 450);
	my_clients.adjust_client_priority(30001, -550);
	client_ID = my_clients.delete_client(&priority, &client_data);
	my_clients.adjust_client_priority(20004, -3550);
	my_clients.add_client(50001, 1730, nullptr);
	my_clients.add_client(50002, 2230, nullptr);
	my_clients.add_client(50003, 1870, nullptr);
	my_clients.add_client(50004, 160, nullptr);
	client_ID = my_clients.delete_client(&priority, &client_data);
	client_ID = my_clients.delete_client(&priority, &client_data);
	my_clients.adjust_client_priority(10004, -2210);
	client_ID = my_clients.delete_client(&priority, &client_data);

	my_clients.print_clients("example_5");
	my_clients.print_min_heap("example_5");
	my_clients.print_min_heap_into_file("result_mh_ex_5.txt");
	my_clients.print_clients_into_file("result_cl_ex_5.txt");
}
int main() {
	example_1();

	my_clients.reset();
	example_2();

	my_clients.reset();
	example_3();

	my_clients.reset();
	example_4();

	my_clients.reset();
	example_5();

	return 0;
}