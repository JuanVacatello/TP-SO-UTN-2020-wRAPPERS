# tp-2020-1c-wRAPPERS

cd

#INICIO DE COMMONS

if test -d /home/utnso/so-commons-library; then
    cd /home/utnso/so-commons-library/
    sudo make unistall
    cd ..
    sudo rm -r ./so-commons-library
fi

cd

git clone https://github.com/sisoputnfrba/so-commons-library.git
cd so-commons-library/
sudo make install

cd

#FIN DE COMMONS

#COPIO CARPETA TP

if test -d /home/utnso/Documentos/tp-2020-1c-wRAPPERS/; then
	sudo rm -r /home/utnso/Documentos/tp-2020-1c-wRAPPERS/
fi

mkdir Documentos

cd tp-2020-1c-wRAPPERS
git checkout prueba --
cd ..
cp -r tp-2020-1c-wRAPPERS/ /home/utnso/Documentos/tp-2020-1c-wRAPPERS

#FIN DE COPIAR CARPETA

cd

#INICIO DE GAMEBOY

cd Documentos/tp-2020-1c-wRAPPERS/GameBoy/

if test -e GameBoy.config; then
	rm GameBoy.config
fi

echo -e "IP_BROKER=127.0.0.1\nIP_TEAM=127.0.0.2\nIP_GAMECARD=127.0.0.4\nPUERTO_BROKER=4444\nPUERTO_TEAM=5555\nPUERTO_GAMECARD=7777\nLOG_FILE=/home/utnso/Documentos/tp-2020-1c-wRAPPERS/GameBoy/GameBoy.log\nPROCESS_ID=2808" >> GameBoy.config

cd Debug
make clean
make all

cd

#FIN DE GAMEBOY

#INICIO BROKER

#CREO LOS BROKERS

cd /home/utnso/Documentos/tp-2020-1c-wRAPPERS/

cp -r Broker/ Broker-CONSOLIDACION-LRU
cp -r Broker/ Broker-COMPACTACION-PD-FIFO
cp -r Broker/ Broker-COMPACTACION-PD-LRU
cp -r Broker/ Broker-BUDDY-SYSTEM-FIFO
cp -r Broker/ Broker-BUDDY-SYSTEM-LRU

#CONFIGURO BROKERS
cd
#Configuramos Broker consolidacion Particiones dinamicas FIFO

cd /home/utnso/Documentos/tp-2020-1c-wRAPPERS/Broker

if test -e Broker.config; then
	rm Broker.config
fi

echo -e "TAMANO_MEMORIA=64\n
TAMANO_MINIMO_PARTICION=4\n
ALGORITMO_MEMORIA=PARTICIONES\n
ALGORITMO_REEMPLAZO=FIFO\n
ALGORITMO_PARTICION_LIBRE=FF\n
FRECUENCIA_COMPACTACION=10\n
PATH_ARCHIVO_DUMP=/home/utnso/Documentos/tp-2020-1c-wRAPPERS/Broker/Broker.dump\n
LOG_FILE=/home/utnso/Documentos/tp-2020-1c-wRAPPERS/Broker/Broker.log\n
IP_BROKER=127.0.0.1\n
PUERTO_BROKER=4444\n">> Broker.config

cd Debug
make clean
make all

cd

#Configuro Broker consolidacion Particiones dinamicas -LRU

cd /home/utnso/Documentos/tp-2020-1c-wRAPPERS/Broker-CONSOLIDACION-LRU

if test -e Broker.config; then
	rm Broker.config
fi

echo -e "TAMANO_MEMORIA=64\n
TAMANO_MINIMO_PARTICION=4\n
ALGORITMO_MEMORIA=PARTICIONES\n
ALGORITMO_REEMPLAZO=LRU\n
ALGORITMO_PARTICION_LIBRE=FF\n
FRECUENCIA_COMPACTACION=10\n
PATH_ARCHIVO_DUMP=/home/utnso/Documentos/tp-2020-1c-wRAPPERS/Broker-CONSOLIDACION-LRU/Broker.dump\n
LOG_FILE=/home/utnso/Documentos/tp-2020-1c-wRAPPERS/Broker-CONSOLIDACION-LRU/Broker.log\n
IP_BROKER=127.0.0.1\n
PUERTO_BROKER=4444\n">> Broker.config

cd Debug
make clean
make all

cd

#Configuro Broker compactacion Particiones Dinamicas

cd /home/utnso/Documentos/tp-2020-1c-wRAPPERS/Broker-COMPACTACION-PD-FIFO/

if test -e Broker.config; then
	rm Broker.config
fi

echo -e "TAMANO_MEMORIA=64\n
TAMANO_MINIMO_PARTICION=4\n
ALGORITMO_MEMORIA=PARTICIONES\n
ALGORITMO_REEMPLAZO=FIFO\n
ALGORITMO_PARTICION_LIBRE=FF\n
FRECUENCIA_COMPACTACION=1\n
PATH_ARCHIVO_DUMP=/home/utnso/Documentos/tp-2020-1c-wRAPPERS/Broker-COMPACTACION-PD-FIFO/Broker.dump\n
LOG_FILE=/home/utnso/Documentos/tp-2020-1c-wRAPPERS/Broker-COMPACTACION-PD-FIFO/Broker.log\n
IP_BROKER=127.0.0.1\n
PUERTO_BROKER=4444\n">> Broker.config

cd Debug
make clean
make all

cd

cd /home/utnso/Documentos/tp-2020-1c-wRAPPERS/Broker-COMPACTACION-PD-LRU

if test -e Broker.config; then
	rm Broker.config
fi

echo -e "TAMANO_MEMORIA=64\n
TAMANO_MINIMO_PARTICION=4\n
ALGORITMO_MEMORIA=PARTICIONES\n
ALGORITMO_REEMPLAZO=LRU\n
ALGORITMO_PARTICION_LIBRE=FF\n
FRECUENCIA_COMPACTACION=1\n
PATH_ARCHIVO_DUMP=/home/utnso/Documentos/tp-2020-1c-wRAPPERS/Broker-COMPACTACION-PD-LRU/Broker.dump\n
LOG_FILE=/home/utnso/Documentos/tp-2020-1c-wRAPPERS/Broker-COMPACTACION-PD-LRU/Broker.log\n
IP_BROKER=127.0.0.1\n
PUERTO_BROKER=4444\n">> Broker.config

cd Debug
make clean
make all

cd

#Configuro Broker Buddy System

cd /home/utnso/Documentos/tp-2020-1c-wRAPPERS/Broker-BUDDY-SYSTEM-FIFO/

if test -e Broker.config; then
	rm Broker.config
fi

echo -e "TAMANO_MEMORIA=64\n
TAMANO_MINIMO_PARTICION=4\n
ALGORITMO_MEMORIA=BS\n
ALGORITMO_REEMPLAZO=FIFO\n
ALGORITMO_PARTICION_LIBRE=FF\n
FRECUENCIA_COMPACTACION=1\n
PATH_ARCHIVO_DUMP=/home/utnso/Documentos/tp-2020-1c-wRAPPERS/Broker-BUDDY-SYSTEM-FIFO/Broker.dump\n
LOG_FILE=/home/utnso/Documentos/tp-2020-1c-wRAPPERS/Broker-BUDDY-SYSTEM-FIFO/Broker.log\n
IP_BROKER=127.0.0.1\n
PUERTO_BROKER=4444\n">> Broker.config

cd Debug
make clean
make all

cd

cd /home/utnso/Documentos/tp-2020-1c-wRAPPERS/Broker-BUDDY-SYSTEM-LRU

if test -e Broker.config; then
	rm Broker.config
fi

echo -e "TAMANO_MEMORIA=64\n
TAMANO_MINIMO_PARTICION=4\n
ALGORITMO_MEMORIA=BS\n
ALGORITMO_REEMPLAZO=LRU\n
ALGORITMO_PARTICION_LIBRE=FF\n
FRECUENCIA_COMPACTACION=1\n
PATH_ARCHIVO_DUMP=/home/utnso/Documentos/tp-2020-1c-wRAPPERS/Broker-BUDDY-SYSTEM-LRU/Broker.dump\n
LOG_FILE=/home/utnso/Documentos/tp-2020-1c-wRAPPERS/Broker-BUDDY-SYSTEM-LRU/Broker.log\n
IP_BROKER=127.0.0.1\n
PUERTO_BROKER=4444\n">> Broker.config

cd Debug
make clean
make all

#FIN DE BROKER

cd