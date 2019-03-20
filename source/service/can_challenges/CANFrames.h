// SPDX-License-Identifier: GPL-3.0
/*
 * Copyright (c) 2014-2019 Nils Weiss
 */

#pragma once

#include "Can.h"
#include <cstddef>
#include <stdint.h>

namespace app
{
typedef struct
{
  uint32_t StdId;  /*!< Specifies the standard identifier.
                        This parameter can be a value between 0 to 0x7FF. */

  uint32_t ExtId;  /*!< Specifies the extended identifier.
                        This parameter can be a value between 0 to 0x1FFFFFFF. */

  uint8_t IDE;     /*!< Specifies the type of identifier for the message that
                        will be transmitted. This parameter can be a value
                        of @ref CAN_identifier_type */

  uint8_t RTR;     /*!< Specifies the type of frame for the message that will
                        be transmitted. This parameter can be a value of
                        @ref CAN_remote_transmission_request */

  uint8_t DLC;     /*!< Specifies the length of the frame that will be
                        transmitted. This parameter can be a value between
                        0 to 8 */

  uint8_t Data[8]; /*!< Contains the data to be transmitted. It ranges from 0
                        to 0xFF. */
} CanTxMsg;

struct msg :
    CanTxMsg {
    enum class type : uint32_t {
        tempomat = 0x143,
        ignition = 0x23,
        start = 0x453,
        speed = 0x3c9,
        fuelLevel = 0x210,
        oilLevel = 0x116,
        engineTemperature = 0x156,
        engineRPM = 0x3ff,
        malfunction = 0x4ac
    };

    void setType(const msg::type t);
    msg::type getType(void) const;
    void setData(const uint32_t data);
    uint32_t getData(void) const;
};
}
