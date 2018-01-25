SOURCES = main.cpp Displays/CPU_Display.cpp Displays/GENERALINFORMATION_Display.cpp Displays/MEMORY_Display.cpp Displays/NETWORK_Display.cpp Displays/PONEY_Display.cpp Displays/TIME_Display.cpp

SOURCES += main.hpp Modules/CpuModule.cpp Modules/HostnameModule.cpp Modules/NetworkModule.cpp Modules/hostname_infos.cpp Modules/DateTimeModule.cpp Modules/MemoryModule.cpp Modules/SysnameModule.cpp

TARGET = ft_gkrellm
TEMPLATE = app
HEADERS = Displays/CPU_Display.hpp Displays/GENERALINFORMATION_Display.hpp Displays/MEMORY_Display.hpp Displays/NETWORK_Display.hpp Displays/PONEY_Display.hpp Displays/TIME_Display.hpp
CFLAGS -= -Wall -Werror -Wextra
QT += widgets charts
CONFIG += qt warn_on release

CXXFLAGS += -Wall -Wextra -Werror

LIBS += -L/usr/include -lncurses

# --------------------------- make rules
fclean.depends = clean
fclean.commands = rm -rf $(TARGET)
QMAKE_EXTRA_TARGETS += fclean

re.depends = fclean all
QMAKE_EXTRA_TARGETS += re