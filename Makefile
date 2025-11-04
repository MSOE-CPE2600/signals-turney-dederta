CC=gcc
CFLAGS=-Wall

EXECUTABLES=signal_alarm signal_sigaction signal_segfault send_signal recv_signal serve_tennis recv_tennis

SOURCES=$(addsuffix .c,$(EXECUTABLES))
OBJECTS=$(SOURCES:.c=.o)


all: $(EXECUTABLES)

# build each from its own .c file
%: %.c
	$(CC) $(CFLAGS) $< -o $@

# generate dependency files
%.o: %.c
	$(CC) $(CFLAGS) $< -o $@
	$(CC) -MM $< > $*.d

-include $(OBJECTS:.o=.d)

clean:
	rm -rf $(OBJECTS) $(EXECUTABLES) *.d