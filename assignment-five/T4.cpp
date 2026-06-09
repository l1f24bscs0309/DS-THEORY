// SPRING 2026 DATA STRUCTURES SECTION D20 ASSIGNMENT
// Name of Student: MUHAMMAD IKRAM UL HAQ
// Registration of Student: L1F24BSCS0309

#include <iostream>
using namespace std;
#include "Node.h"
#include "BinaryTree.h"
#include "BinarySearchTree.h"
#include "BlockChainNode.h"
#include "KeyNode.h"
#include "BlockChain.h"

/*
PROBLEM DESCRIPTION:
Simulate a basic Blockchain structure that stores coins with associated keys and passwords.
The blockchain supports the following operations:
1. Add a new coin with a coin ID, amount, key ID, and password
2. Display all coins in descending order
3. Search for a coin by its key ID
4. Verify the integrity of the blockchain (checks that all blocks are in sync)
5. Delete a coin by its key ID

SOLUTION:

addCoin
--------
1. Create a new blockchain node with the provided coin ID, amount, key ID, and password
2. Append the node to the blockchain in the appropriate position
3. The coin's key is stored in a separate key structure linked to the block

displayDescending
------------------
1. Traverse the blockchain from the last block to the first
2. Print each block's details (coin ID, amount, key ID) in descending order

searchByKey
------------
1. Traverse the blockchain nodes
2. Compare each node's key ID with the given key
3. Return true if a match is found, false otherwise

verify
-------
1. Check that the blockchain's internal state is consistent
2. Returns true if all blocks are properly linked and synced, false otherwise

deleteByKey
------------
1. Search the blockchain for a node matching the given key ID
2. If found, remove the node and relink adjacent blocks
3. If not found, print a not-found message and do nothing

##################################################################

Main demonstrates:
- Adding 3 coins to the blockchain
- Displaying all coins in descending order
- Searching for existing and non-existing keys
- Verifying blockchain integrity before and after deletion
- Deleting coins by key (including keys that do not exist)
- Re-adding a coin after deletion and confirming search results
*/

/********* MAIN FUNCTION *********/

int main() {
    Blockchain bc;

    // --- Add coins to the blockchain ---
    // Each call adds a block with coin ID, amount, key ID, and password
    bc.addCoin("A1B2C3",  100.5,  "K9X2M1", "pass123");
    bc.addCoin("D4E5F6",  250.0,  "K3R7N5", "pass456");
    bc.addCoin("G7H8I9",  75.25,  "K1A4Z8", "pass789");

    // --- Display all coins in descending order ---
    bc.displayDescending();

    // --- Search for keys: one that exists and one that does not ---
    cout << "Search K3R7N5 (exists)   : " << (bc.searchByKey("K3R7N5") ? "Found"     : "Not Found") << "\n";
    cout << "Search K0X0X0 (absent)   : " << (bc.searchByKey("K0X0X0") ? "Found"     : "Not Found") << "\n";

    // --- Verify blockchain integrity before any deletions ---
    cout << "Verify (all synced)      : " << (bc.verify() ? "Valid" : "Invalid") << "\n\n";

    // --- Delete coins by key ---
    // K3R7N5 exists and will be removed
    bc.deleteByKey("K3R7N5");
    // K8B3L6 does not exist — deletion should be handled gracefully
    bc.deleteByKey("K8B3L6");
    // K0X0X0 does not exist — deletion should be handled gracefully
    bc.deleteByKey("K0X0X0");

    // --- Display chain again after deletions ---
    bc.displayDescending();

    // --- Verify blockchain integrity after deletion ---
    cout << "Verify (post-delete)     : " << (bc.verify() ? "Valid" : "Invalid") << "\n\n";

    // --- Re-add a coin with the same data as the first coin ---
    bc.addCoin("A1B2C3", 100.5, "K9X2M1", "pass123");

    // --- Confirm deleted key is gone and re-added key is present ---
    cout << "Search K3R7N5 (deleted)  : " << (bc.searchByKey("K3R7N5") ? "Found" : "Not Found") << "\n";
    cout << "Search K9X2M1 (exists)   : " << (bc.searchByKey("K9X2M1") ? "Found" : "Not Found") << "\n";

    return 0;
}
