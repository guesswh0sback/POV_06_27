# --- Choix du firmware ---
FIRMWARE ?= hall_effect

# --- Variables globales ---
MCU = atmega328p
F_CPU = 13000000
PORT = /dev/ttyACM0
PROGRAMMER = usbasp

# Source and object files
SRCS = $(wildcard $(FIRMWARE)/*.c)
BUILD_DIR = build
OBJS = $(patsubst $(FIRMWARE)/%.c,$(BUILD_DIR)/$(FIRMWARE)/%.o,$(SRCS))

# Output files
ELF = $(BUILD_DIR)/$(FIRMWARE).elf
HEX = $(BUILD_DIR)/$(FIRMWARE).hex

# Compiler flags
CFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os
CFLAGS += -I$(FIRMWARE)


# --- Règles principales ---

# Compilation
all: $(HEX)

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/$(FIRMWARE)/%.o: $(FIRMWARE)/%.c | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	@echo "Compilation de $< en $@..."
	avr-gcc $(CFLAGS) -c $< -o $@

$(ELF): $(OBJS)
	@echo "Edition de lien -> $(ELF)..."
	avr-gcc $(CFLAGS) $(OBJS) -o $(ELF)

$(HEX): $(ELF)
	@echo "Conversion en HEX -> $(HEX)..."
	avr-objcopy -O ihex -R .eeprom $(ELF) $(HEX)
	@echo "Compilation terminée : $(HEX)"



# Téléversement
install: $(HEX)
	@echo "Téléversement de $(FIRMWARE) sur la carte..."
	avrdude -v -p $(MCU) -c $(PROGRAMMER) -P $(PORT) -b $(F_CPU) -U flash:w:$(HEX):i
	@echo "Téléversement terminé !"

# Nettoyage
clean:
	@echo "Nettoyage du dossier $(BUILD_DIR)..."
	-@rm -rf $(BUILD_DIR) 2>/dev/null || rmdir /s /q $(BUILD_DIR)
	@echo "Fichiers générés supprimés"

# Cibles symboliques
.PHONY: all install clean