#ifndef CONFIGURATION_H
#define CONFIGURATION_H


#include <stdint.h>

namespace cfig
{



    struct TcpIpServerConfig
    {

        static const int32_t serverPort= 5000;
    };

    struct ThpSupervisorConfig
    {

        static const int32_t timerFrequence= 1000;
    };



}


#endif // CONFIGURATION_H
