cmd_drivers/char/built-in.a :=  rm -f drivers/char/built-in.a; llvm-ar rcSTPD drivers/char/built-in.a drivers/char/mem.o drivers/char/random.o drivers/char/misc.o drivers/char/hw_random/built-in.a drivers/char/agp/built-in.a drivers/char/adsprpc.o drivers/char/adsprpc_compat.o drivers/char/diag/built-in.a drivers/char/okl4_pipe.o drivers/char/vservices_serial.o drivers/char/vs_serial_client.o drivers/char/vs_serial_server.o
