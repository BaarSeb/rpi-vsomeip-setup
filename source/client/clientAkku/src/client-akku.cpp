#include <iomanip>
#include <iostream>
#include <sstream>
#include <chrono>

#include <condition_variable>
#include <thread>

#include <vsomeip/vsomeip.hpp>

#define SAMPLE_SERVICE_ID 0x1234
#define SAMPLE_INSTANCE_ID 0x5678
#define SAMPLE_METHOD_ID 0x0421
#define SAMPLE_EVENT_ID 0x3333
#define SAMPLE_EVENTGROUP_ID 0x4444

std::shared_ptr< vsomeip::application > app;
std::mutex mutex;
std::condition_variable condition;

//void run() {
//  std::unique_lock<std::mutex> its_lock(mutex);
//  condition.wait(its_lock);
//
//  std::shared_ptr< vsomeip::message > request;
//  request = vsomeip::runtime::get()->create_request();
//  request->set_service(SAMPLE_SERVICE_ID);
//  request->set_instance(SAMPLE_INSTANCE_ID);
//  request->set_method(SAMPLE_METHOD_ID);
//
//  std::shared_ptr< vsomeip::payload > its_payload = vsomeip::runtime::get()->create_payload();
//  std::vector< vsomeip::byte_t > its_payload_data;
//  for(vsomeip::byte_t i=0; i<10; i++) {
//	  its_payload_data.push_back(i % 256);
//  }
//  while(1){
//    std::cout << "Sending akku request" << std::endl;
//    its_payload->set_data(its_payload_data);
//    request->set_payload(its_payload);
//
//    app->send(request, true);
//    std::this_thread::sleep_for(std::chrono::seconds (5));
//  }
//}


void run() {
  std::unique_lock<std::mutex> its_lock(mutex);
  condition.wait(its_lock);

  std::set<vsomeip::eventgroup_t> its_groups;
  its_groups.insert(SAMPLE_EVENTGROUP_ID);
  app->request_event(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID, SAMPLE_EVENT_ID, its_groups, false);
  app->subscribe(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID, SAMPLE_EVENTGROUP_ID);
}

void on_message(const std::shared_ptr<vsomeip::message> &_response) {
  std::stringstream ss;
  std::shared_ptr<vsomeip::payload> pl = _response->get_payload();

	  for(short i = 0; i < pl->get_length(); i++){
	  ss << "cell " << i << ":" << (int) pl->get_data()[i] << "\n";
  }
  std::cout << ss.str() << std::endl;

//  std::vector<short> resp = reinterpret_cast<short>(pl->get_data());
//  std::cout << "Received: " << resp << std::endl;
}

void on_availability(vsomeip::service_t _service, vsomeip::instance_t _instance, bool _is_available) {
    std::cout << "CLIENT: Service ["
            << std::setw(4) << std::setfill('0') << std::hex << _service << "." << _instance
            << "] is "
            << (_is_available ? "available." : "NOT available.")
            << std::endl;
    condition.notify_one();
}

void on_state(vsomeip::state_type_e _state) {
    if (_state == vsomeip::state_type_e::ST_REGISTERED) {
        app->request_service(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID);
    }
}

int main() {
    app = vsomeip::runtime::get()->create_application("client-akku");
    app->init();
    app->register_availability_handler(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID, on_availability);
    app->request_service(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID);
//    app->register_state_handler(std::bind(on_state, this, std::placeholders::_1));
    app->register_message_handler(vsomeip::ANY_SERVICE, vsomeip::ANY_INSTANCE, vsomeip::ANY_METHOD, on_message);
    std::thread sender(run);
    app->start();
}
