#pragma once

#include "swift_net.h"
#include <arpa/inet.h>
#include <tuple>
#include "../../main.hpp"

namespace utils::net {
    in_addr get_public_ip();
    in_addr get_private_ip();
}
