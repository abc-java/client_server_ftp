#include <iostream>
#include <fstream>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

void handleFTPRequest(tcp::socket& socket) {
    boost::asio::streambuf buffer;
    boost::asio::read_until(socket, buffer, "\n");

    std::istream requestStream(&buffer);
    std::string filename;
    std::getline(requestStream, filename);

    std::ofstream file(filename, std::ios::binary);

    boost::system::error_code error;
    size_t bytesRead = 0;
    do {
        bytesRead = boost::asio::read(socket, buffer, boost::asio::transfer_at_least(1), error);
        if (!error) {
            std::ostreambuf_iterator<char> fileIterator(file);
            std::copy(boost::asio::buffers_begin(buffer.data()),
                      boost::asio::buffers_end(buffer.data()),
                      fileIterator);
        }
    } while (bytesRead > 0);

    if (error != boost::asio::error::eof) {
        throw boost::system::system_error(error);
    }

    std::cout << "File received and saved successfully." << std::endl;
}

int main() {
    boost::asio::io_service ioService;
    tcp::acceptor acceptor(ioService, tcp::endpoint(tcp::v4(), 12345));

    while (true) {
        tcp::socket socket(ioService);
        acceptor.accept(socket);

        handleFTPRequest(socket);
    }

    return 0;
}