#include <string>
#include <cstring>
#include <cstdint>

using namespace std;

namespace REPS {
    namespace PacketDecoder {
        std::string DataToString(const uint8_t* data, uint32_t len);
    }
}
