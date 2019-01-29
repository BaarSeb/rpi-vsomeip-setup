#include <iomanip>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>

#include <vsomeip/vsomeip.hpp>
#include "../../../../nlohmann/json.hpp"

#define SAMPLE_SERVICE_ID 0x0003
#define SAMPLE_INSTANCE_ID 0x0020
#define SAMPLE_METHOD_ID 0x0200

using json = nlohmann::json;

std::shared_ptr<vsomeip::application> app;

void on_message(const std::shared_ptr<vsomeip::message> &_request) {

  // Create a response based upon the request
  std::shared_ptr<vsomeip::message> resp = vsomeip::runtime::get()->create_response(_request);

  // Read in the json file and add timestamp
  std::ifstream s("/etc/service_lights_msg.json");
  json j;
  s >> j;
  auto t = std::time(nullptr);
  auto tm = *std::localtime(&t);

  std::ostringstream oss;
  oss << std::put_time(&tm, "%d-%m-%Y %H-%M-%S");
  auto time = oss.str();


  j["timestamp"] = time;
  int x = rand() % 100;
  int y = rand() % 100;

  j["lights"]["head_light"]["x_position"] = x;
  j["lights"]["head_light"]["y_position"] = y;
  j["lights"]["rear_light"]["x_position"] = x;
  j["lights"]["rear_light"]["y_position"] = y;

  // Construct string to send back
  std::string str = j.dump();

  str += "\0";

  // Create a payload which will be sent back to the client
  std::shared_ptr<vsomeip::payload> resp_pl = vsomeip::runtime::get()->create_payload();
  std::vector<vsomeip::byte_t> pl_data(str.begin(), str.end());
  resp_pl->set_data(pl_data);
  resp->set_payload(resp_pl);

  // Send the response back
  app->send(resp, true);
}

int main() {

   app = vsomeip::runtime::get()->create_application("service-lights");
   app->init();
   app->register_message_handler(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID, SAMPLE_METHOD_ID, on_message);
   app->offer_service(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID);
   app->start();
}
