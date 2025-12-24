#include <cstdint>
#include <cstring>
#include <string>

using namespace std;

namespace REPS {
    namespace PacketDecoder {
        std::string DataToString(const uint8_t* data, uint32_t len) {
            if (!data || len == 0)
                return {};
            return std::string(reinterpret_cast<const char*>(data), len);
        }
    }
}
