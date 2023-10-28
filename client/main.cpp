#include <iostream>
#include <fstream>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

void sendFTPRequest(tcp::socket& socket, const std::string& filename) {
    std::string request = filename + "\n";

    boost::asio::write(socket, boost::asio::buffer(request));

    std::ifstream file(filename, std::ios::binary);
    if (file) {
        file.seekg(0, std::ios::end);
        size_t fileSize = file.tellg();
        file.seekg(0, std::ios::beg);

        std::vector<char> buffer(fileSize);
        file.read(buffer.data(), fileSize);

        boost::asio::write(socket, boost::asio::buffer(buffer));
    }
}

int main() {
    boost::asio::io_service ioService;

    tcp::socket socket(ioService);
    tcp::resolver resolver(ioService);

    boost::asio::connect(socket, resolver.resolve({"localhost", "12345"}));

    std::string filename = "example_file.txt";
    sendFTPRequest(socket, filename);

    std::cout << "File sent successfully." << std::endl;

    return 0;
}
