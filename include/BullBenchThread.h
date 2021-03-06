#ifndef BULLBENCH_BULLBENCHTHREAD_H
#define BULLBENCH_BULLBENCHTHREAD_H

#include <sys/socket.h>
#include <queue>

#include "Thread.h"
#include "Settings.h"

class BullBenchThread : public Thread {
    public:
        BullBenchThread(Settings& settings, std::queue<std::string>& requestQueue) 
            : _settings(settings), _requestQueue(requestQueue) {}
        ~BullBenchThread() {}
        
        void run(); 
    private :
       inline int _getSocket() {
            int sock;
            sock = socket(AF_INET, SOCK_STREAM, 0);
            if (sock < 0) {
                return -1;
            }
            if (connect(sock, (struct sockaddr *)&(_settings.ad), sizeof(_settings.ad)) < 0) {
                return -1;
            }
            return sock;
        }

        void buildRequest(char* request,std::string& uri); 
        
        Settings& _settings;
        std::queue<std::string>& _requestQueue;
};
// end class BullBenchThread
#endif
