include ../../test.mk

TEST_SOL:=test.sol

tests: gen-output cmp-output

gen-output:
	@$(SOLC) $(TEST_SOL)
	@mv $(TEST_SOL) output
	@mv $(TEST_SOL).orig $(TEST_SOL)
