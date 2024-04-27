#include "Server.hpp"
#include "Exception.hpp"
#include "Utils.hpp"
#include "Client.hpp"

#include "Room.hpp"
#include <string>
#include <iostream>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/select.h>
#include "Define.hpp"
#include <fcntl.h>

void Server::initSocket()
{
	this->_socket = socket(AF_INET, SOCK_STREAM, 0); // Create socket 0 for macos and IPPROTO_IP for linux ipv4 protokolüne göre soket oluşturur tcp için SOCK_STREAM udp için SOCK_DGRAM
	if (_socket < 0)
	{
		throw Exception("Socket creation failed");
	}
	else
	{
		std::cout << "Socket created successfully!    "; 
		Utils::printTime();
	}
	int dumb = 1;
	//SO_REUSEADDR sunucu kapatıldıktan sonra hemen aynı adres ve portu kullanarak tekrar başlatılmasına izin verir.
	//Bu fonksiyon, soketin farklı seçeneklerini (options) belirterek, bu seçeneklerin değerlerini değiştirmenizi sağlar
	if (setsockopt(this->_socket, SOL_SOCKET, SO_REUSEADDR, &dumb, sizeof(int)) < 0)
	{
		throw Exception("Socket option failed");
	}
	else
	{
		std::cout << "Socket option set successfully! ";
		Utils::printTime() ;
	}
	//(file control)
	//Blok olmayan mod, dosya veya soket işlemlerinin bloklamadan gerçekleştirilmesini sağlar.
	// Yani, bir işlem hemen tamamlanamazsa, beklemek yerine hemen dönüş yapılır
	if (fcntl(this->_socket, F_SETFL, O_NONBLOCK) < 0)
	{
		throw Exception("Socket fcntl failed on Server");
	}
	else
	{
		std::cout << "Socket fcntl set successfully!  ";
		Utils::printTime();
	}
//struct sockaddr_in
//// IPv4 adresleri ve bağlantı noktaları için kullanılan yapı
/* struct sockaddr_in {
    short            sin_family;   // Adres ailesi, genellikle AF_INET
    unsigned short   sin_port;     // Bağlantı noktası, network byte order'da
    struct in_addr   sin_addr;     // IPv4 adresi
    char             sin_zero[8];  // Padding, sıfırlanmalı
}; */
// soket fonksiyonları genellikle struct sockaddr türü ile çalışır.
	memset(&address, 0, sizeof(address));
	address.sin_family = AF_INET;		 
	address.sin_addr.s_addr = INADDR_ANY;//INADDR_ANY, herhangi bir ağ arabirimine bağlanmak için kullanılan bir özel bir IP adresidir.
	// Bu, soketin tüm yerel IP adreslerinden gelen bağlantıları kabul edeceğini belirtir.
	address.sin_port = htons(this->port);

	if (::bind(this->_socket, (struct sockaddr *)&address, sizeof(address)) < 0)//bind fonksiyonu, bir soketi belirli bir IP adresi ve port numarasıyla ilişkilendirir. 
	{
		throw Exception("Socket bind failed");
	}
	else
	{
		std::cout << "Socket binded successfully!     ";
		Utils::printTime();
	}

	//listen fonksiyonu çağrılarak bu soketin bağlantıları kabul etmeye hazır hale getirilir.
	// Bu şekilde, sunucu soketi gelen bağlantıları bekleyebilir ve kabul edebilir
	//Bu değer, aynı anda kabul edilebilecek bağlantı sayısını temsil eder.
	if (listen(this->_socket, SOMAXCONN) < 0)
	{
		throw Exception("Socket listen failed");
	}
	else
	{
		std::cout << "Socket listening successfully!  ";
		Utils::printTime() ;
	 }
}