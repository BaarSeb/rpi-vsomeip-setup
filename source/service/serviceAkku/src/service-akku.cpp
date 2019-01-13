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

void on_message(const std::shared_ptr<vsomeip::message> &_request) {

  // Create a response based upon the request
  std::shared_ptr<vsomeip::message> resp = vsomeip::runtime::get()->create_response(_request);

  // Read in the json file and add timestamp
  std::ifstream s("/etc/service_akku_msg.json");
  json j;
  s >> j;
  auto t = std::time(nullptr);
  auto tm = *std::localtime(&t);

  std::ostringstream oss;
  oss << std::put_time(&tm, "%d-%m-%Y %H-%M-%S");
  auto time = oss.str();

  j["timestamp"] = time;

  // Construct string to send back
  std::string str = j.dump();

  // Create a payload which will be sent back to the client
  std::shared_ptr<vsomeip::payload> resp_pl = vsomeip::runtime::get()->create_payload();
  std::vector<vsomeip::byte_t> pl_data(str.begin(), str.end());
  resp_pl->set_data(pl_data);
  resp->set_payload(resp_pl);

  // Send the response back
  app->send(resp, true);
}

void run(){
	while(1){
		// Read in the json file and add timestamp
		std::ifstream s("/etc/service_akku_msg.json");
		json j;
		s >> j;
		auto t = std::time(nullptr);
		auto tm = *std::localtime(&t);

		std::ostringstream oss;
		oss << std::put_time(&tm, "%d-%m-%Y %H-%M-%S");
		auto time = oss.str();

		j["timestamp"] = time;

		// Construct string to notify
		std::string str = j.dump();

		std::shared_ptr<vsomeip::payload> payload = vsomeip::runtime::get()->create_payload();
		std::vector<vsomeip::byte_t> pl_data(str.begin(), str.end());
		payload->set_data(pl_data);

		std::set<vsomeip::eventgroup_t> its_groups;
		its_groups.insert(SAMPLE_EVENTGROUP_ID);

		app->notify(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID, SAMPLE_EVENT_ID, payload);

	    std::this_thread::sleep_for(std::chrono::seconds (5));
	}
}

int main() {
   std::set<vsomeip::eventgroup_t> its_groups;
   its_groups.insert(SAMPLE_EVENTGROUP_ID);

   app = vsomeip::runtime::get()->create_application("service-akku");
   app->init();
   app->register_message_handler(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID, SAMPLE_METHOD_ID, on_message);
   app->offer_service(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID);
   app->offer_event(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID, SAMPLE_EVENT_ID, its_groups, true);
   std::thread sender(run);
   app->start();
}
