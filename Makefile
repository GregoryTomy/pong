# Compiler and Linker
CC = clang++

# The Target Binary Program
TARGET = pong

# Directories
BUILDDIR = ./build
SRCDIR = ./
LIBDIR = /opt/homebrew/Cellar/sfml/2.6.0/lib
INCDIR = /opt/homebrew/Cellar/sfml/2.6.0/include

# Compiler Flags
CFLAGS = -std=c++20 --debug
LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# Subsystem for compilation
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(BUILDDIR)/%.o)

# Rules for make
all: directories $(BUILDDIR)/$(TARGET)

directories:
	@mkdir -p $(BUILDDIR)

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

$(BUILDDIR)/$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -L$(LIBDIR) $(LIBS) -o $@

clean:
	@rm -rf $(BUILDDIR)

