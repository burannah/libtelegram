#include "libtelegram/libtelegram.h"

auto main()->int {
  std::string const token("229029247:AAHfNUvcGS_ttvvulZG3Qi4NmMrjebH8F6w");     // in practice you would probably read this from config file or database
  telegram::listener listener;                                                  // create a listener which will process incoming requests
  telegram::sender sender(token);                                               // create a sender with our token for outgoing messages
  listener.set_callback_message([&](boost::property_tree::ptree const &input){  // we set a callback for receiving messages, using a lambda for convenience
    std::string  const message_text(   input.get("text", ""));                  // message components are passed in boost property tree format
    std::string  const message_sender( input.get("from.first_name", "unknown")); // we specify a default fallback in case the property isn't found
    int_fast64_t const message_chat_id(input.get<int_fast64_t>("chat.id", -1)); // the return type can be deduced from the fallback's type, or specified manually
    sender.send_message(message_chat_id, message_sender + " sent \"" + message_text + "\" to chat id " + std::to_string(message_chat_id)); // send our reply from within the callback
  });
  listener.run();                                                               // launch the listener - this call blocks until the fastcgi server drops us
  return EXIT_SUCCESS;
};
