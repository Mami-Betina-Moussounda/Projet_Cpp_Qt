#ifndef CONFIGURATION_H
#define CONFIGURATION_H


#include <stdint.h>
#include <string>

namespace cfig
{



    struct ClientConfig
    {

        static const int32_t tabSize= 3;
        static const uint8_t MsgId = 1U;
        static const uint8_t tempMsgPosition = 1U;
        static const uint8_t timeMsgPosition = 2U;
        static constexpr double precisionData=0.01;
        static const int32_t minRangeServerPort= 5000U;
        static const int32_t maxRangeServerPort= 65535U;
    };

    struct GraphConfig
    {

        static const int32_t quantityDataDisplay=20U;

        static const int32_t minSizeGraphX=1300U;
        static const int32_t minSizeGraphY=600U;
        static const int32_t markerSize=10U;

        static const int32_t minRangeY=1U;
        static const int32_t maxRangeY=1U;

        static const int32_t minRangeX=1U;
        static const int32_t maxRangeX=0U;




    };



}


#endif // CONFIGURATION_H
