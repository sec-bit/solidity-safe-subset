pragma solidity ^0.4.16;

contract ArrayContract {
    uint[2**20] m_aLotOfIntegers;
    bool[2][] m_pairsOfFlags;
    bytes m_byteData;

    function byteArrays(bytes data) public {
        for(var x : data) {
	    x = byte(8);
	}
    }
}
