# --- Choix du firmware ---
FIRMWARE ?= blink

# --- Variables globales ---
MCU = atmega328p
F_CPU = 13000000
PORT = COM5
PROGRAMMER = usbasp

SRC = $(FIRMWARE)/main.c
BUILD_DIR = build
ELF = $(BUILD_DIR)/$(FIRMWARE).elf
HEX = $(BUILD_DIR)/$(FIRMWARE).hex
OBJ = $(BUILD_DIR)/main.o

# --- Règles principales ---

# Compilation
all: $(HEX)

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

$(OBJ): $(SRC) | $(BUILD_DIR)
	@echo "Compilation de $(SRC) en $(OBJ)..."
	avr-gcc -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os -c $(SRC) -o $(OBJ)

$(ELF): $(OBJ)
	@echo "Edition de lien -> $(ELF)..."
	avr-gcc -mmcu=$(MCU) -o $(ELF) $(OBJ)

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