#include <iostream>
#include <thread>
#include <chrono>
#include <SimpleAmqpClient/SimpleAmqpClient.h>

using namespace std;

int main()
{
    try
    {
        AmqpClient::Channel::OpenOpts opts;
        opts.host = "localhost";   // ✅ set host
        opts.port = 5672;          // optional, default 5672
        opts.auth = AmqpClient::Channel::OpenOpts::BasicAuth{"guest", "guest"};  // ✅ credentials
        auto channel = AmqpClient::Channel::Open(opts);  // ✅ now correct

        channel->DeclareQueue("test_queue", false, true, false, false);
        std::cout << "Waiting for messages..." << std::endl;

        while (true)
        {
            AmqpClient::Envelope::ptr_t envelope;
            bool got_message = channel->BasicGet(envelope, "test_queue", false);
            if (got_message)
            {
                std::string body = envelope->Message()->Body();
                std::cout << "Received: " << body << std::endl;
            }
            else
            {
                std::cout << "No message available" << std::endl;
            }

            // ✅ Explicit manual acknowledgment
            channel->BasicAck(envelope);
            
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Caught exception: " << e.what() << std::endl;
    }
}
