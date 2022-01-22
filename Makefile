#CROSS = arm-linux-gnueabihf-

MAKE = make

CC = $(CROSS)gcc
LD = $(CROSS)ld
STRIP = $(CROSS)strip

ROOT_DIR = $(CURDIR)
MBEDTLS = $(ROOT_DIR)/mbedtls

CFLAGS = -fPIC -DHAVE_CONFIG_H -D_U_="__attribute__((unused))" -O2
LDFLAGS =

INCLUDES = -I$(MBEDTLS)/include
LIBS = $(MBEDTLS)/library/libmbedx509.a $(MBEDTLS)/library/libmbedtls.a $(MBEDTLS)/library/libmbedcrypto.a -lm

SOURCES = main.c https.c cJSON.c

OBJS = $(SOURCES:.c=.o)

INSTALL_PATH += /usr/local/bin

.SUFFIXES:.c .o

all: wxmsg

mbedtls_make:
	@for dir in $(MBEDTLS); do \
		$(MAKE) -C $$dir ; \
		if [ $$? != 0 ]; then exit 1; fi; \
	done

wxmsg: mbedtls_make $(OBJS)
	@echo Linking: $@ ....
	$(CC) -o $@ $(OBJS) $(LDFLAGS) $(LIBS)
#	$(STRIP) -s $@

.c.o:
	@echo Compiling: $< ....
	$(CC) -c $(CFLAGS) $(INCLUDES) -o $@ $<

clean:
	rm -f https_client *.o

mbedtls_clean:
	@for dir in $(MBEDTLS); do \
		$(MAKE) -C $$dir clean; \
		if [ $$? != 0 ]; then exit 1; fi; \
	done

install:
	cp wxmsg $(INSTALL_PATH)/wxmsg