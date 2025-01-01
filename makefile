# Nom de l'exécutable final
TARGET = chess

# Répertoires
SRC_DIR = src
INC_DIR = include
BUILD_DIR = build
Autosave_Dir= Save/AutoSave

# Extensions
SRC_EXT = c
OBJ_EXT = o

# Commandes et options du compilateur
CC = gcc
CFLAGS = -Wall -Wextra -I$(INC_DIR) -g

# Recherche des fichiers source et création des fichiers objets
SRCS = $(wildcard $(SRC_DIR)/*.$(SRC_EXT))
OBJS = $(patsubst $(SRC_DIR)/%.$(SRC_EXT), $(BUILD_DIR)/%.$(OBJ_EXT), $(SRCS))

# Règle par défaut
all: $(TARGET) $(Autosave_Dir)

# Compilation de l'exécutable final
$(TARGET): $(OBJS)
	@echo "[LINK] Création de l'exécutable $(TARGET)"
	$(CC) $(CFLAGS) -o $@ $^

# Compilation des fichiers objets
$(BUILD_DIR)/%.$(OBJ_EXT): $(SRC_DIR)/%.$(SRC_EXT) | $(BUILD_DIR)
	@echo "[CC] Compilation de $<"
	$(CC) $(CFLAGS) -c $< -o $@

# Création du répertoire build s'il n'existe pas
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)
#creation de Autosave si il n'existe pas
$(Autosave_Dir):
	@mkdir -p $(Autosave_Dir)

# Nettoyage
clean:
	@echo "[CLEAN] Suppression des fichiers compilés"
	rm -rf $(BUILD_DIR) $(TARGET)

# Phonies
.PHONY: all clean
