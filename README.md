# RabbitMQWithCPP

# PART I - START THE RABBITMQ SERVER
1. Install Erlang from Erlang.org/downloads
2. Install rabbit mq server
3. Enable management plugin
    Run in CMD or BASH (In folder: C:\Program Files\RabbitMQ Server\rabbitmq_server-4.2.0\sbin)
        rabbitmq-plugins.bat enable rabbitmq_management
4. you should be able to access the rabbitmq management portal: http://localhost:15672/
    username: guest
    password: guest

# PART II - SimpleAmqpClient to communicate to RabbitMQ Server
SimpleAmqpClient needs boost and rabbitmq-c libraries to build
1. Create rabbitmq-c as follows -
    1. Git clone this repo: https://github.com/alanxz/rabbitmq-c.git
    2. Now, Prerequisites
        a. Have Cmake installed, Visual Studio installed (so that we have cl.exe)
    3. Open the repo in VS code
    4. Cmake .
        It might give error related to SSL. You can get around this by 
        cmake . -DBUILD_SHARED_LIBS=ON -DBUILD_STATIC_LIBS=ON -DBUILD_TESTS=OFF -DENABLE_SSL_SUPPORT=OFF
        (This tells cmake to build without encryption)
    5. Cmake --build .
    It should create rabbitmq.4.dll at RABBITMQC_LIB

    These are the RabbitMQ C client libraries:
        • rabbitmq.4.dll → runtime DLL
        • rabbitmq.4.lib → import library for linking
        • librabbitmq.4.lib → sometimes the static variant, depending on build options

2. Install Boost - Download prebuild boost windows binaries (.exe file) from https://www.boost.org/users/download/
    ○ You might have to build the chrono and other libraries as well by following
        § Let's say you have downloaded and installed boost and it produces: C:\local\boost_1_89_0
        § Start developer command prompt for VS
        § cd C:\local\boost_1_89_0
        § bootstrap.bat
        § b2 --build-type=complete --with-chrono --with-system --with-thread variant=release address-model=64
    These steps will resolve your dependency issue with boost
        
3. Create SimpleAmqpClient libraries
    This is a wrapper around rabbitmq-c
    We need librabbitmq.4.dll and the include directory to build SimpleAmqpClient

    1. Clone the repo for SimpleAmqpClient from: https://github.com/alanxz/SimpleAmqpClient.git
    2. Open the folder in VS code and mkdir build
    3. Run following cmake command to configure the build
        cmake .. -DRabbitmqc_LIBRARY="C:\work\projects\cppprojects\rabbitmq-c\librabbitmq\Debug\rabbitmq.4.lib" -DRabbitmqc_INCLUDE_DIR="C:\work\projects\cppprojects\rabbitmq-c\include" -DENABLE_SSL_SUPPORT=OFF

        ○ This configures the rabbitmq-c library and include paths. And also turns SSL encryption off.
    4. Cmake --build .
        • This will output following important files:
            ○ SimpleAmqpClient.7.dll
            ○ SimpleAmqpClient.7.lib
            ○ SimpleAmqpClient.7.pdb
            ○ SimpleAmqpClient.7.exp
        
# PART III - Create sender.exe and receiver.exe and communicate via SimpleAmqpClient
This requires, 
    SimpleAmqpClient.7.lib to statically build
    SimpleAmqpClient.7.dll to be copied near the executable
    rabbitmq.4.dll to be copied near the executable
    boost dlls to be copied near the executable
    boost library includes.
