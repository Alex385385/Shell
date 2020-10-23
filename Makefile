main_compile : 
		gcc -o gladewin main.c -Wall `pkg-config --cflags --libs gtk+-3.0` -export-dynamic