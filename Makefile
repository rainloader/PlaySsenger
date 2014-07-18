##-----------------
## PATHS
##-----------------

HOME		= `pwd`
SERVER = $(HOME)/server
TEST = $(HOME)/test


## RULES
server_mod :
	@echo "----------------------------"
	@echo "Building Server..."
	@echo "----------------------------"
	@cd $(SERVER); make
	@echo "Server Building Complete"
	@echo "----------------------------"

test_mod :
	@echo "----------------------------"
	@echo "Building Test..."
	@echo "----------------------------"
	@cd $(TEST); make
	@echo "Test Building Complete"
	@echo "----------------------------"

clean:
	@echo "Clean"
