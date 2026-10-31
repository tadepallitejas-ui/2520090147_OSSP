CC = gcc
CFLAGS = -g -O0 -Wall -Wextra

BIN = bin
SRC = src
FIXED = fixed

.PHONY: all clean dirs

all: dirs $(BIN)/buggy_app $(BIN)/crash_demo $(BIN)/debug_runner \
     $(BIN)/buggy_app_fixed $(BIN)/crash_demo_fixed

dirs:
	mkdir -p $(BIN) reports

$(BIN)/buggy_app: $(SRC)/buggy_app.c
	$(CC) $(CFLAGS) -o $@ $<

$(BIN)/crash_demo: $(SRC)/crash_demo.c
	$(CC) $(CFLAGS) -o $@ $<

$(BIN)/debug_runner: $(SRC)/debug_runner.c
	$(CC) $(CFLAGS) -o $@ $<

$(BIN)/buggy_app_fixed: $(FIXED)/buggy_app_fixed.c
	$(CC) $(CFLAGS) -o $@ $<

$(BIN)/crash_demo_fixed: $(FIXED)/crash_demo_fixed.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -rf $(BIN) reports/*.txt reports/*.log
