objects = main \
  prog11 prog12 prog13 prog14 prog15 \
  prog21 prog22 trans \
  prog31 prog32 mycopy \
  prog71 prog72 prog73 \
  list list2 list3

all: $(objects)

$(objects): %: %.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(objects)