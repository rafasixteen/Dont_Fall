#pragma once

constexpr int DEFAULT_COLOR = 0;
constexpr int CMD_RED = 91;
constexpr int CMD_GREEN = 92;
constexpr int CMD_YELLOW = 93;
constexpr int CMD_BLUE = 94;
constexpr int CMD_PINK = 95;
constexpr int CMD_LIGHT_BLUE = 96;
constexpr int CMD_WHITE = 97;

#define location (std::string(__FILE__) + ":" + std::to_string(__LINE__))

#define COLOR_INFO(msg, color) std::cout << "\x1B[" << color << "m" << msg << "\x1B[0m" << std::endl

#define INFO(msg) std::cout << "\x1B[" << CMD_GREEN << "m" << msg << "\x1B[0m" << std::endl

#define WARNING(msg) std::cout << "\x1B[" << CMD_YELLOW << "m" << msg << " " << location << "\x1B[0m" << std::endl

#define ERROR(msg)                                                                          \
{                                                                                           \
    std::cout << "\x1B[" << CMD_RED << "m" << msg << " " << location << "\x1B[0m" << std::endl; \
    __debugbreak();                                                                         \
}                                                                                           \

#define LINE() std::cout << std::endl

#define CHECK(result) if (VkResult resultValue = (result); resultValue != VK_SUCCESS) ERROR("Vulkan call failed with error code "<<resultValue)