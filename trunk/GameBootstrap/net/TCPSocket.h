#ifndef _TCPSOCKET_H_
#define _TCPSOCKET_H_
#define MAX_COLA 20
#define MAX_BUFFER_READ 50

#include <string>

using namespace std;

namespace net
{
class TCPSocket
{
public:
	TCPSocket();
	virtual ~TCPSocket(void);

	/* Le indica al socket cual será la dirección donde escuchará las nuevas conexiones */
	void doBind(int port);

	/* Le indica al sistema operativo que el socket debe empezar a recibir conexiones entrantes
	 * El parámetro que recibe es para indicar que tamaño máximo tendrá la cola de conexiones entrantes */
	void doListen(int connectionQueueSize);

	/* Conecta al socket con la dirección indicada y el puerto indicado */
	void doConnect(const string& ip , int port);

	/* Le indica al socket que debe dejar de emitir y recibir datos */
	void doShutDown(void);

	/* Cierra el socket */
	void doClose(void);

	/* Acepta una nueva conexion desde la cola de conexiones */
	TCPSocket* doAccept(void);

	/* Envia la cantidad de bytes indicada por longitud a partir de la posicion indicada por data */
	void doSend(char* data, int length);

	/* Envia el contenido de la cadena de strings */	 	 	
	void doSend(string buffer);

	/* Recibe la cantidad de bytes indicada por la longitud y lo guarda a partir de la posicion indicada.
	   No retorna hasta que se reciben todos los bytes especificados en "longitud" */
	void doReceive(char* data, int length);

	/* Envia un entero */
	void doSend(int number);

	/* Recibe un entero*/
	int doReceive(void);

	/* Lee todos los bytes enviados por el socket hasta que se recibe la cadena de control especificada en "controlchar".
	   No retorna hasta que se recibe la cadena de control (sin incluirla).
	   El buffer "data" es inicializado en la funcion y debe ser liberado por el usuario */
	void doReceive(char* &data, string controlchar);
	
	/* Lee hasta recibir la cadena de control
	   Devuelve el contenido como un string (sin incluir cadena de control) */
	string doReceive(string controlchar);
protected:
	unsigned int descriptor;
	bool creado;
};
};
#endif
