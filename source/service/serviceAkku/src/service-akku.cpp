#include <iomanip>
#include <iostream>
#include <sstream>
#include <fstream>
#include <chrono>
#include <thread>

#include <vsomeip/vsomeip.hpp>
#include "../../../../nlohmann/json.hpp"

#define SAMPLE_SERVICE_ID 0x1234
#define SAMPLE_INSTANCE_ID 0x5678
#define SAMPLE_METHOD_ID 0x0421
#define SAMPLE_EVENT_ID 0x3333
#define SAMPLE_EVENTGROUP_ID 0x4444

std::shared_ptr<vsomeip::application> app;

using json = nlohmann::json;

void run(){
	std::set<vsomeip::eventgroup_t> its_groups;
	its_groups.insert(SAMPLE_EVENTGROUP_ID);

	short cell_status [5] = {1, 1, 1, 1, 1};

	std::shared_ptr<vsomeip::payload> payload = vsomeip::runtime::get()->create_payload();
	std::vector<vsomeip::byte_t> pl_data;

	int rnd;
	while(1){
		for (int n = 0; n < 5; n++){
			rnd = rand() % 5;
			cell_status[n] = (cell_status[n] + rnd) % 100;
			pl_data.push_back(cell_status[n]);
		}

		payload->set_data(pl_data);
		pl_data.clear();


		app->notify(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID, SAMPLE_EVENT_ID, payload);

	    std::this_thread::sleep_for(std::chrono::seconds (5));
	}
}

int main() {
   std::set<vsomeip::eventgroup_t> its_groups;
   its_groups.insert(SAMPLE_EVENTGROUP_ID);

   app = vsomeip::runtime::get()->create_application("service-akku");
   app->init();
   app->offer_service(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID);
   app->offer_event(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID, SAMPLE_EVENT_ID, its_groups, false);
   std::thread sender(run);
   app->start();
}
