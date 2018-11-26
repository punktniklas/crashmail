AR = ar -ru
RM = rm -f
STRIP = strip
INSTALL = install

CPPFLAGS = -DPLATFORM_LINUX -D__LINUX__ -I$(PWD) $(OPTCPPFLAGS)
CFLAGS = -Wall -Werror
# Silence warnings about insecure tmpnam()
CFLAGS += -Wno-deprecated-declarations

