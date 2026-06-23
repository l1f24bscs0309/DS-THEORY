// ============================================================
// Task 5 — Word-level Huffman Coding using Hashtable<string>
//
// Pipeline:
//  1. Read words from "text.txt" → store in `text`  (with dupes)
//  2. Build `strings`  — unique words only
//  3. Build `frequencies` — word → count  (stored as "word:count")
//  4. Build `codes`       — word → binary code (sorted by freq desc)
//  5. Compress: replace every word in `text` with its code
//  6. Decompress: replace every code in `text` back with the word
//
// All hashtables use AVLTree chaining (see Hashtable.h).
// ============================================================


// IMPORTANT NOTE:
// I have used algorithm and iomanip libraries in this file.
// HERE IS THE JUSTIFICATION WHY I USED THEM:
//
// for iomanip: I used this library to format the output of the frequency table and the codes table. It allows me to set the width of the columns and align the text properly, making the output more readable.
//
//for algorithm: I used this library to sort the frequency table and the codes table. It provides the sort function, which allows me to sort the vectors of pairs based on the frequency or code values, making it easier to display the data in a meaningful way.

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Node.h"
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;


#include "MyStack.h"
#include "AVLTree.h"
#include "Hashtable.h"


// Collect all values from a Hashtable<string> into a vector
// Uses iterative inorder over each AVL bucket
vector<string> collectAll(const Hashtable<string> &ht, int cap) {
    vector<string> out;
    // We expose via forEach (template method in Hashtable)
    ht.forEach([&](const string &s){ out.push_back(s); });
    return out;
}

// Parse "word:count" frequency entry
pair<string,int> parseFreq(const string &entry) {
    size_t pos = entry.rfind(':');
    string word = entry.substr(0, pos);
    int cnt     = stoi(entry.substr(pos + 1));
    return {word, cnt};
}

// Build binary string from integer index (0 → "0", 1 → "1", 2 → "10" …)
string toBinary(int n) {
    if (n == 0) return "0";
    string bits;
    while (n > 0) {
        bits = (char)('0' + (n & 1)) + bits;
        n >>= 1;
    }
    return bits;
}

int main() {
    const int CAP = 101;

    // ── 1. Read words from text.txt ─────────────────────────
    Hashtable<string> text(CAP);
    vector<string> wordOrder; // preserves original word sequence

    ifstream fin("text.txt");
    if (!fin) {
        cerr << "Cannot open 'text.txt'.\n";
        return 1;
    }

    string word;
    while (fin >> word) {
        // strip punctuation from ends
        while (!word.empty() && !isalnum(word.front())) word.erase(word.begin());
        while (!word.empty() && !isalnum(word.back()))  word.pop_back();
        if (word.empty()) continue;

        // lowercase
        for (char &c : word) c = (char)tolower(c);

        text.insert(word);        // with duplicates (count tracked externally)
        wordOrder.push_back(word);
    }
    fin.close();

    cout << "Words read from text.txt: " << wordOrder.size() << "\n\n";

    // ── 2. Build `strings` — unique words ───────────────────
    Hashtable<string> strings(CAP);
    for (const string &w : wordOrder) {
        if (strings.search(w).empty()) // not yet inserted
            strings.insert(w);
    }

    // ── 3. Build `frequencies` — "word:count" entries ───────
    // We store each unique word's count as  "word:count"
    Hashtable<string> frequencies(CAP);

    vector<string> uniqueWords = collectAll(strings, CAP);

    // Count occurrences
    for (const string &uw : uniqueWords) {
        int cnt = 0;
        for (const string &w : wordOrder)
            if (w == uw) cnt++;
        frequencies.insert(uw + ":" + to_string(cnt));
    }

    // ── 4. Build `codes` — assign binary codes ───────────────
    // Sort by frequency descending so the most frequent word → "0"
    vector<pair<string,int>> freqVec;
    vector<string> freqEntries = collectAll(frequencies, CAP);
    for (const string &e : freqEntries)
        freqVec.push_back(parseFreq(e));

    sort(freqVec.begin(), freqVec.end(),
         [](const pair<string,int> &a, const pair<string,int> &b){
             return a.second > b.second; // descending
         });

    // `codes` stores "word:binarycode"
    Hashtable<string> codes(CAP);
    for (int i = 0; i < (int)freqVec.size(); i++)
        codes.insert(freqVec[i].first + ":" + toBinary(i));

    // Build lookup map (word → code) for compression
    // We parse from the codes hashtable
    vector<string> codeEntries = collectAll(codes, CAP);

    // Helper lambda: find code for a word
    auto getCode = [&](const string &w) -> string {
        for (const string &e : codeEntries) {
            size_t pos = e.rfind(':');
            if (e.substr(0, pos) == w)
                return e.substr(pos + 1);
        }
        return w; // fallback
    };

    // Helper lambda: find word for a code
    auto getWord = [&](const string &code) -> string {
        for (const string &e : codeEntries) {
            size_t pos = e.rfind(':');
            if (e.substr(pos + 1) == code)
                return e.substr(0, pos);
        }
        return code; // fallback
    };

    // ── 5. Compression ────────────────────────────────────────
    // Replace each word in wordOrder with its binary code
    Hashtable<string> compressed(CAP);
    string compressedStr;
    for (const string &w : wordOrder) {
        string c = getCode(w);
        compressed.insert(c);
        compressedStr += c + " ";
    }

    // ── 6. Decompression ──────────────────────────────────────
    string decompressedStr;
    istringstream iss(compressedStr);
    string token;
    while (iss >> token) {
        decompressedStr += getWord(token) + " ";
    }

    // ── Output ────────────────────────────────────────────────
    cout << "=== Unique words and their Huffman codes ===\n";
    cout << left << setw(20) << "Word"
                 << setw(10) << "Freq"
                 << setw(15) << "Code" << "\n";
    cout << string(45, '-') << "\n";
    for (auto &p : freqVec) {
        cout << left << setw(20) << p.first
                     << setw(10) << p.second
                     << setw(15) << getCode(p.first) << "\n";
    }

    cout << "\n=== Compressed text ===\n" << compressedStr << "\n";
    cout << "\n=== Decompressed text ===\n" << decompressedStr << "\n";

    // Verify round-trip
    string original, rebuilt;
    for (const string &w : wordOrder) original += w + " ";
    bool ok = (original == decompressedStr);
    cout << "\nRound-trip check: " << (ok ? "PASSED" : "FAILED") << "\n";

    return 0;
}
