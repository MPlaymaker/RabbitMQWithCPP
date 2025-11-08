#include <iostream>
#include <thread>
#include <chrono>
#include <SimpleAmqpClient/SimpleAmqpClient.h>

using namespace std;

int main()
{
    // ✅ Set up connection options
    AmqpClient::Channel::OpenOpts opts;
    opts.host = "localhost";                                                // RabbitMQ broker
    opts.port = 5672;                                                       // default port
    opts.auth = AmqpClient::Channel::OpenOpts::BasicAuth{"guest", "guest"}; // default credentials

    // ✅ Create the channel
    auto channel = AmqpClient::Channel::Open(opts);

    std::string queue_name = "test_queue";

    // ✅ Declare the queue (durable = true)
    channel->DeclareQueue(queue_name, false, true, false, false);

    int i = 1;
    while (true)
    {
        std::string message = "Hello " + std::to_string(i++);
        channel->BasicPublish("", queue_name, AmqpClient::BasicMessage::Create(message));
        cout << "Sent message: " << message << endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}
