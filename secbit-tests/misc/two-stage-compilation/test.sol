pragma solidity ^0.4.0;

contract Test {
	function at(address _addr) public pure returns (bool) {
		if(_addr == 0)
			return true;
		return false;
	}
}
