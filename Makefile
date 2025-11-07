# --- Variables globales ---
MCU = atmega328p
F_CPU = 13000000
PORT = /dev/ttyACM0
PROGRAMMER = usbasp

# Main selection
MAIN ?= led_driver_main.c

# Directory structure
BUILD_DIR = build
MAIN_DIR = main_s

# Source files
MAIN_FILE = $(MAIN_DIR)/$(MAIN)
# Compile only library/source files from the src/ directory (avoid other folders that contain their own mains)
SRCS = $(wildcard src/*.c)

# Object files
OBJS = $(SRCS:%.c=$(BUILD_DIR)/%.o)
MAIN_OBJ = $(BUILD_DIR)/$(MAIN_DIR)/$(MAIN:.c=.o)

# Output files
TARGET = $(basename $(MAIN))
ELF = $(BUILD_DIR)/$(TARGET).elf
HEX = $(BUILD_DIR)/$(TARGET).hex

# Compiler flags
CFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os
CFLAGS += -I.

# --- Règles principales ---

# Compilation
all: $(HEX)

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(dir $(OBJS))
	@mkdir -p $(dir $(MAIN_OBJ))

$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	@echo "Compilation de $< en $@..."
	avr-gcc $(CFLAGS) -c $< -o $@

$(ELF): $(OBJS) $(MAIN_OBJ)
	@echo "Edition de lien -> $(ELF)..."
	avr-gcc $(CFLAGS) $(OBJS) $(MAIN_OBJ) -o $(ELF)

$(HEX): $(ELF)
	@echo "Conversion en HEX -> $(HEX)..."
	avr-objcopy -O ihex -R .eeprom $(ELF) $(HEX)
	@echo "Compilation terminée : $(HEX)"



# Téléversement
install: $(HEX)
	@echo "Téléversement du programme sur la carte..."
	avrdude -v -p $(MCU) -c $(PROGRAMMER) -P $(PORT) -b $(F_CPU) -U flash:w:$(HEX):i
	@echo "Téléversement terminé !"

# Nettoyage
clean:
	@echo "Nettoyage du dossier $(BUILD_DIR)..."
	-@rm -rf $(BUILD_DIR) 2>/dev/null || rmdir /s /q $(BUILD_DIR)
	@echo "Fichiers générés supprimés"

# Cibles symboliques
.PHONY: all install clean