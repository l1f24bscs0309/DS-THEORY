#include <iostream>
using namespace std;
#include "Node.h"
#include "BinaryTree.h"
#include "BinarySearchTree.h"
#include "BlockChainNode.h"
#include "KeyNode.h"
#include "BlockChain.h"
    
int main() {
    Blockchain bc;

    // ── 1. Add coins ─────────────────────────────────────────────
    cout << "=== Adding Coins ===\n";
    bc.addCoin("A1B2C3",  100.5,  "K9X2M1", "pass123");
    bc.addCoin("D4E5F6",  250.0,  "K3R7N5", "pass456");
    bc.addCoin("G7H8I9",  75.25,  "K1A4Z8", "pass789");
    bc.addCoin("J1K2L3",  500.0,  "K6T9Q2", "pass321");
    bc.addCoin("M4N5O6",  180.75, "K2W5P7", "pass654");
    bc.addCoin("P7Q8R9",  320.0,  "K8B3L6", "pass987");
    cout << "\n";

    // ── 2. Display descending ─────────────────────────────────────
    cout << "=== Display Descending ===\n";
    bc.displayDescending();
    cout << "\n";

    // ── 3. Search by key ──────────────────────────────────────────
    cout << "=== Search by Key ===\n";
    cout << "Search K3R7N5 (exists)   : " << (bc.searchByKey("K3R7N5") ? "Found"     : "Not Found") << "\n";
    cout << "Search K1A4Z8 (exists)   : " << (bc.searchByKey("K1A4Z8") ? "Found"     : "Not Found") << "\n";
    cout << "Search K0X0X0 (absent)   : " << (bc.searchByKey("K0X0X0") ? "Found"     : "Not Found") << "\n";
    cout << "\n";

    // ── 4. Verify ─────────────────────────────────────────────────
    // cout << "=== Verify Chain ===\n";
    // cout << "Verify (all synced)      : " << (bc.verify() ? "Valid" : "Invalid") << "\n\n";

    // ── 5. Delete by key ──────────────────────────────────────────
    cout << "=== Delete by Key ===\n";
    cout << "Deleting K3R7N5...\n";
    bc.deleteByKey("K3R7N5");
    cout << "Deleting K8B3L6...\n";
    bc.deleteByKey("K8B3L6");
    cout << "Deleting K0X0X0 (absent): ";
    bc.deleteByKey("K0X0X0");
    cout << "\n";

    // ── 6. Display after deletion ─────────────────────────────────
    cout << "=== Display After Deletion ===\n";
    bc.displayDescending();
    cout << "\n";

    // ── 7. Verify after deletion ──────────────────────────────────
    cout << "=== Verify After Deletion ===\n";
    // cout << "Verify (post-delete)     : " << (bc.verify() ? "Valid" : "Invalid") << "\n\n";

    // ── 8. Duplicate add ──────────────────────────────────────────
    cout << "=== Duplicate Add ===\n";
    cout << "Adding duplicate K9X2M1: ";
    bc.addCoin("A1B2C3", 100.5, "K9X2M1", "pass123");
    cout << "\n";

    // ── 9. Search after deletion ──────────────────────────────────
    cout << "=== Search After Deletion ===\n";
    cout << "Search K3R7N5 (deleted)  : " << (bc.searchByKey("K3R7N5") ? "Found" : "Not Found") << "\n";
    cout << "Search K9X2M1 (exists)   : " << (bc.searchByKey("K9X2M1") ? "Found" : "Not Found") << "\n";

    return 0;
}
