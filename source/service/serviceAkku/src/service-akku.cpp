#include <iomanip>
#include <iostream>
#include <sstream>

#include <vsomeip/vsomeip.hpp>

#define SAMPLE_SERVICE_ID 0x0003
#define SAMPLE_INSTANCE_ID 0x0010
#define SAMPLE_METHOD_ID 0x0100

std::shared_ptr<vsomeip::application> app;
int i = 0;

void on_message(const std::shared_ptr<vsomeip::message> &_request) {

  // Create a response based upon the request
  std::shared_ptr<vsomeip::message> resp = vsomeip::runtime::get()->create_response(_request);

  // Read in the json file and add timestamp
  std::ifstream i("service_akku_msg.json"),
  json j;
  i >> j;
  j["timestamp"] = std::chrono::system_clock::now()

  // Construct string to send back
  std::string str = j.dump();

  // Create a payload which will be sent back to the client
  std::shared_ptr<vsomeip::payload> resp_pl = vsomeip::runtime::get()->create_payload();
  std::vector<vsomeip::byte_t> pl_data(str.begin(), str.end());
  resp_pl->set_data(pl_data);
  resp->set_payload(resp_pl);

  // Send the response back
  app->send(resp, true);
  i++;
}

int main() {

   app = vsomeip::runtime::get()->create_application("World");
   app->init();
   app->register_message_handler(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID, SAMPLE_METHOD_ID, on_message);
   app->offer_service(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID);
   app->start();
}
