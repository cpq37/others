TARGET = VWTranslator
TARGET_DIR = 

ifeq ($(ARCH), arm)

else
LIBDIR = 
OBJ_OUTPUT_PATH = ./output/linux/x86

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

SRCDIR 	= ./src
SRCDIR	+= ./src/xml/dom
INCLUDE  	= $(foreach dir,$(SRCDIR), -I$(dir))

# **********************************************
# Source files to be compiled
# **********************************************
C_SRC_FILES = 	
C_OBJ_FILES = $(patsubst %.c, %.o, $(C_SRC_FILES))

CPP_SRC_FILES = $(foreach dir, $(SRCDIR), $(wildcard $(dir)/*.cpp))
CPP_OBJ_FILES = $(patsubst %.cpp, %.o, $(CPP_SRC_FILES))

OBJ_FILES = $(patsubst %.o, $(OBJ_OUTPUT_PATH)/%.o, $(C_OBJ_FILES) $(CPP_OBJ_FILES))

# **********************************************
# Rules
# **********************************************



test:$(CPP_OBJ_FILES) 
	$(CPP) -o $(TARGET) $(CPP_OBJ_FILES)  
	

print:
	@echo $(CPP_SRC_FILES)
	@echo $(CPP_OBJ_FILES) 

clean:
	rm $(CPP_OBJ_FILES) $(TARGET)








