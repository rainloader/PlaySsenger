##-----------------
## PATHS
##-----------------

HOME		= `pwd`
COMMON = $(HOME)/common
SERVER = $(HOME)/server
TEST = $(HOME)/test


## RULES
common_mod :
	@echo "----------------------------"
	@echo "Building Common files..."
	@echo "----------------------------"
	@cd $(COMMON); make
	@echo "Common files Building Complete"
	@echo "----------------------------"
	@make server_mod

server_mod :
	@echo "----------------------------"
	@echo "Building Server..."
	@echo "----------------------------"
	@cd $(SERVER); make
	@echo "Server Building Complete"
	@echo "----------------------------"
	@make test_mod

test_mod :
	@echo "----------------------------"
	@echo "Building Test..."
	@echo "----------------------------"
	@cd $(TEST); make
	@echo "Test Building Complete"
	@echo "----------------------------"

clean:
	@cd $(COMMON); make clean
	@cd $(SERVER); make clean
	@cd $(TEST); make clean
	@echo "Clean"
