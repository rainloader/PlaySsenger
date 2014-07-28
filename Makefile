##-----------------
## PATHS
##-----------------

HOME		= `pwd`
COMMON = $(HOME)/common
SERVER = $(HOME)/server
CLIENT = $(HOME)/client
TEST = $(HOME)/test


## RULES

all : common_mod server_mod client_mod test_mod

common_mod :
	@echo "*****************************************************************"
	@echo "Building Common files..."
	@echo "----------------------------"
	@cd $(COMMON); make
	@echo "----------------------------"
	@echo "Common files Building Complete"

server_mod :
	@echo "*****************************************************************"
	@echo "Building Server..."
	@echo "----------------------------"
	@cd $(SERVER); make
	@echo "----------------------------"
	@echo "Server Building Complete"

client_mod :
	@echo "*****************************************************************"
	@echo "Building Client..."
	@echo "----------------------------"
	@cd $(CLIENT); make
	@echo "----------------------------"
	@echo "Client Building Complete"

test_mod :
	@echo "*****************************************************************"
	@echo "Building Test..."
	@echo "----------------------------"
	@cd $(TEST); make
	@echo "----------------------------"
	@echo "Test Building Complete"

clean:
	@cd $(COMMON); make clean
	@cd $(SERVER); make clean
	@cd $(CLIENT); make clean
	@cd $(TEST); make clean
	@echo "Clean"
