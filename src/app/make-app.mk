APP_DIR = $(SRC_DIR)/app

include $(SRC_DIR)/shared/make-shared.mk

# Modules
APP_SRC_C += $(APP_DIR)/app.c \
			 $(SHARED_SRC_C)

APP_SRC_S += $(SHARED_SRC_S)

APPLICATION_INC += $(SHARED_INC)

APP_LINKER_SCRIPT = $(APP_DIR)/linker.ld

