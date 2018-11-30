#include <iomanip>
#include <iostream>
#include <sstream>

#include <vsomeip/vsomeip.hpp>

#define SAMPLE_SERVICE_ID 0x0004
#define SAMPLE_INSTANCE_ID 0x0020
#define SAMPLE_METHOD_ID 0x0200

std::shared_ptr<vsomeip::application> app;
int i = 0;

void on_message(const std::shared_ptr<vsomeip::message> &_request) {

  // Create a response based upon the request
  std::shared_ptr<vsomeip::message> resp = vsomeip::runtime::get()->create_response(_request);

  // Construct string to send back
  std::string str("{\r\n  \"timestamp\": \"\",\r\n  \"cells\": {\r\n    \"cell1status\": \"charging\",\r\n    \"cell2status\": \"charging\",\r\n    \"cell3status\": \"charging\"\r\n  },\r\n  \"voltage\": \"11.9V\",\r\n  \"location\": \"49\u00B000'12.2\\\"N 12\u00B005'44.3\\\"E\"\r\n}");

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
