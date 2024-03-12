NAME = main
SRCDIR = ./source

RAYLIB = ./libs/raylib-5.0_win64_mingw-w64
CFILES := $(wildcard $(SRCDIR)/*.c)

LINUX_CC = gcc
LINUX_OBJDIR = ./objects/linux
LINUX_OFILES = $(patsubst $(SRCDIR)/%.c, $(LINUX_OBJDIR)/%.o, $(CFILES))
LINUX_RAYFLAGS = -lraylib -lm -L./libs -lcollisions3D

OFLAGS = -O0
CFLAGS = -Wall -g -I$(SRCDIR) $(OFLAGS)

all: linux
	@echo "\033[1;33m ~> Compiling for linux"

linux: $(NAME)

$(NAME): $(LINUX_OFILES)
	$(LINUX_CC) -o $(NAME) $^ $(LINUX_RAYFLAGS)

$(LINUX_OBJDIR)/%.o:$(SRCDIR)/%.c
	$(LINUX_CC) $(CFLAGS) -c -o $@ $<

clean:
	@echo "\033[1;31m ~> Cleaning objects files and executables\033[1;0m"
	-rm $(LINUX_OBJDIR)/*.o main