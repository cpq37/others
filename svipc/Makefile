TARGET = libsvipc

ifeq ($(ARCH), arm)
LIBDIR = ./lib/$(ARCH)

export CC                               = arm-linux-gnueabihf-gcc -march=armv7-a -marm -mthumb-interwork -mfloat-abi=hard -mfpu=neon -mtune=cortex-a15 \
	--sysroot=$(SVP_SYSTEM_SDK_PATH)/sysroots/cortexa15t2hf-vfp-neon-oe-linux-gnueabi
export CPP                              = arm-linux-gnueabihf-g++ -march=armv7-a -marm -mthumb-interwork -mfloat-abi=hard -mfpu=neon -mtune=cortex-a15 \
	--sysroot=$(SVP_SYSTEM_SDK_PATH)/sysroots/cortexa15t2hf-vfp-neon-oe-linux-gnueabi
export AR                               = arm-linux-gnueabihf-ar
export LD                               = arm-linux-gnueabihf-ld
export STRIP                    = arm-linux-gnueabihf-strip

export CFLAGS                   = -I$(SVP_SYSTEM_SDK_PATH)/sysroots/cortexa15t2hf-vfp-neon-oe-linux-gnueabi/include/c++/4.7.3 \
	-I$(SVP_SYSTEM_SDK_PATH)/sysroots/cortexa15t2hf-vfp-neon-oe-linux-gnueabi/include/c++/4.7.3/arm-linux-gnueabihf/arm-linux-gnueabi \
	-fstack-protector -O2 -pipe -feliminate-unused-debug-types -fPIC -D__LINUX__ -D__linux__
export CPPFLAGS                 = -I$(SVP_SYSTEM_SDK_PATH)/sysroots/cortexa15t2hf-vfp-neon-oe-linux-gnueabi/include/c++/4.7.3 \
	-I$(SVP_SYSTEM_SDK_PATH)/sysroots/cortexa15t2hf-vfp-neon-oe-linux-gnueabi/include/c++/4.7.3/arm-linux-gnueabihf/arm-linux-gnueabi \
	-fstack-protector -O2 -pipe -fPIC -D__LINUX__ -D__linux__
export LD_LIB_PATH              = -L./ -L$(SVP_LIB_PATH)
export LDFLAGS_SHARE    = -shared \
	-L$(SVP_SYSTEM_SDK_PATH)/sysroots/cortexa15t2hf-vfp-neon-oe-linux-gnueabi/usr/lib \
	-Wl,-rpath-link,$(SVP_SYSTEM_SDK_PATH)/sysroots/cortexa15t2hf-vfp-neon-oe-linux-gnueabi/usr/lib \
	-Wl,-O1 -Wl,--hash-style=gnu
export LDFLAGS                  = -L$(SVP_SYSTEM_SDK_PATH)/sysroots/cortexa15t2hf-vfp-neon-oe-linux-gnueabi/usr/lib \
	-Wl,-rpath-link,$(SVP_SYSTEM_SDK_PATH)/sysroots/cortexa15t2hf-vfp-neon-oe-linux-gnueabi/usr/lib \
	-Wl,-O1 -Wl,--hash-style=gnu
else
LIBDIR = ./lib/x86

export CC                       = gcc
export CPP                      = g++
export AR                       = ar
export LD                       = ld
export STRIP                    = strip

#export CFLAGS                   = -pipe -fPIC -O3 -D__LINUX__ -D__linux__ -DSVP_SIMULATOR -Wl,-O3
#export CPPFLAGS                 = -pipe -fPIC -O3 -D__LINUX__ -D__linux__ -DSVP_SIMULATOR -Wl,-O3
export LD_LIB_PATH              += -L./ -L$(SVP_LIB_PATH)
export LDFLAGS_SHARE    = -shared -Wl,-O3
export LDFLAGS                  = -Wl,-O3
export ARFLAGS                  =
endif

SRCDIR = ./src
INCDIR = ./include
INCLUDE      = $(foreach dir,$(INCDIR), -I$(dir))
# **********************************************
# Source files to be compiled
# **********************************************
SRC_FILES = $(foreach dir, $(SRCDIR), $(wildcard $(dir)/*.c)) 
SRC_FILES += $(foreach dir, $(SRCDIR), $(wildcard $(dir)/*.cpp))

OBJ_TEMP_FILE = $(patsubst %.cpp, %.o, $(SRC_FILES))
OBJ_FILE = $(patsubst %.c, %.o, $(OBJ_TEMP_FILE))

OBJ_FILES = *.o


# **********************************************
# Rules
# **********************************************
all: $(OBJ_FILES) testServer

$(OBJ_FILES): $(OBJ_FILE)
	$(AR) cr $(TARGET).a  $(OBJ_FILE)
	$(CPP) $(OBJ_FILE) -shared -o $(TARGET).so
	cp -f $(TARGET).* $(LIBDIR)
	cp $(SRCDIR)/*.h  $(INCDIR)/

test:
	$(CPP) -o test test.cpp $(CPPFLAGS) -I./include  -L$(LIBDIR) -lsvipc -lpthread
testServer:
	$(CC) -o testService testService.c $(CFLAGS) 
testClient:
	$(CC) -o testClient ./src/testClient.c ./src/IPC_Message.c $(CFLAGS)
print:
	@echo $(CPPFLAGS)
	@echo $(ARCH)
	@echo $(LIBDIR)
	@echo $(SRCDIR)
	@echo $(SRC_FILES)
	@echo $(OBJ_FILE)
	@echo $(INCLUDE)

clean:
	rm $(OBJ_FILE) $(TARGET).* $(LIBDIR)/$(TARGET).* test testService

