
include Makefile.top


MODULE     = dvat

CFLAGS = -I$(INCDIR)/ \
        -I/usr/local/include/\
        -I/usr/include/\
	-Iinclude/\

CFLAGS += -g -ggdb -fPIC


LDFLAGS = \
	-L/usr/local/lib\

SOURCES = \
	Image.cpp\
	Sobel.cpp\
	Video.cpp\
	PSNR.cpp\
	SSIM.cpp\
	PWSSIM.cpp\
    main.cpp


.SUFFIXES: .cpp .o .h

include Makefile.build

default: all
