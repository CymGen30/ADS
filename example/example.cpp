#include "AdsLibOOI.h"
#include "AdsDevice.h"
#include <array>
#include <iostream>

void runAdsClientExample(std::ostream& out)
{
    static const AmsNetId remoteNetId { 192, 168, 0, 231, 1, 1 };
    static const char remoteIpV4[] = "ads-server";

    out << __FUNCTION__ << "():\n";

    AdsDevice route {remoteIpV4, remoteNetId, 851};

    // Write and read values
    uint8_t valueToWrite = 0x99;
    AdsVariable<uint8_t> simpleVar {route, "MAIN.byByte[0]"};
    simpleVar = valueToWrite;
    out << "Wrote " << (uint32_t)valueToWrite << " to MAIN.byByte and read " << (uint32_t)simpleVar << " back\n";

    // Write and read values by index group/offset
    AdsVariable<uint8_t> simpleVarIndex {route, 0x4020, 0};
    simpleVarIndex = valueToWrite;
    out << "Wrote " << (uint32_t)valueToWrite << " to MAIN.byByte and read " << (uint32_t)simpleVarIndex <<
        " back\n";

    // Write and read arrays
    static const std::array<uint8_t, 4> arrayToWrite = { 1, 2, 3, 4 };
    AdsVariable<std::array<uint8_t, 4> > arrayVar {route, "MAIN.byByte"};
    arrayVar = arrayToWrite;
    std::array<uint8_t, 4> readArray = arrayVar;
    out << "Wrote array with first value " << (uint32_t)arrayToWrite[0] << " and last value " <<
    (uint32_t)arrayToWrite[3] << "\n";
    out << "Read back array with first value " << (uint32_t)readArray[0] << " and last value " <<
    (uint32_t)readArray[3] << "\n";

    // Write and read arrays by index group/offset
    static const std::array<uint8_t, 4> arrayOfZeros = {0, 0, 0, 0};
    AdsVariable<std::array<uint8_t, 4> > arrayVarIndex {route, 0x4020, 0};
    arrayVarIndex = arrayOfZeros;
    std::array<uint8_t, 4> readArrayIndex = arrayVarIndex;
    out << "Wrote array with first value " << (uint32_t)arrayToWrite[0] << " and last value " <<
    (uint32_t)arrayToWrite[3] << "\n";
    out << "Read back array with first value " << (uint32_t)readArrayIndex[0] << " and last value " <<
    (uint32_t)readArrayIndex[3] << "\n";

    // Read device info
    const auto deviceInfo = route.GetDeviceInfo();
    const auto version = deviceInfo.version;
    out << "Read device info from device " << deviceInfo.name << ". Version is " <<
    (uint32_t)version.version << "." << (uint32_t)version.revision << "." <<
    (uint32_t)version.build << "\n";

    const auto state = route.GetState();
    out << "AdsState: " << std::dec << (uint16_t)state.ads << " DeviceState: " << (uint16_t)state.device << '\n';
}

int main()
{
    try {
        runAdsClientExample(std::cout);
    } catch (const AdsException& ex) {
        std::cout << "Error: " << ex.errorCode << "\n";
        std::cout << "AdsException message: " << ex.what() << "\n";
    } catch (const std::runtime_error& ex) {
        std::cout << ex.what() << '\n';
    }

    std::cout << "Hit ENTER to continue\n";
    std::cin.ignore();
}
