pragma solidity ^0.4.16;

contract ArrayContract {
    uint[2**20] m_aLotOfIntegers;
    bool[2][] m_pairsOfFlags;
    bytes m_byteData;

    function byteArrays(bytes data) public {
	for(var x : data){
	    x = byte(8);
	    for(var y : m_byteData){
	        y = byte(7);
	    }
	    for(var z : m_pairsOfFlags){
	        z[0] = true;
	    }
	    for(var j : m_pairsOfFlags[1]){
	        j = true;
	    }
	    for(uint8 i = 0; i < 10; i++) {
		i;
	    }
	}
    }
}
