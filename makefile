CC = arm-linux-gnueabihf-gcc
CFLAGS = -Wall -Wextra -std=c99 -D _POSIX_C_SOURCE=200809L 
LDFLAGS = -lrt
# TARGET = light_sampler_target 
TARGET = dht_test_target
INSTALL_DIR = ~/cmpt433/public/

.PHONY: all install clean

all: $(TARGET)

$(TARGET): bbb_dht_read.c bbb_mmio.c common_dht_read.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ -lpthread

install: $(TARGET)
	cp $(TARGET) $(INSTALL_DIR)

clean:
	rm -f $(TARGET)