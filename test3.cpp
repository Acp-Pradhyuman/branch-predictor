#include "pin.H"
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>

std::ofstream outFile;  // Don't open the file globally, open it in Fini

// To store branch history (a simple sliding window)
std::vector<int> branchHistory;
const size_t historyLength = 20; // Set the history length (e.g., 4)

// Record branch address, branch outcome, and history
VOID RecordBranch(ADDRINT branchAddress, BOOL taken) {
    // Record branch address and branch outcome
    outFile << "Branch Address: " << std::hex << branchAddress << ", Taken: " << taken << std::endl;

    // Update branch history (sliding window approach)
    branchHistory.push_back(taken);
    if (branchHistory.size() > historyLength) {
        branchHistory.erase(branchHistory.begin());  // Maintain history length
    }

    // Print branch history
    outFile << "Branch History: ";
    for (size_t i = 0; i < branchHistory.size(); ++i) {
        outFile << branchHistory[i] << " ";
    }
    outFile << std::endl;
}

VOID Instruction(INS ins, VOID *v) {
    // Check if the instruction is a branch
    if (INS_IsBranch(ins)) {
        // Add instrumentation to track both taken and not-taken branches
        INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)RecordBranch,
                       IARG_INST_PTR, IARG_BRANCH_TAKEN, IARG_END);
    }
}

// Open the output file when the program finishes
VOID Fini(INT32 code, VOID *v) {
    outFile.close();  // Close the output file at the end
    std::cerr << "Instrumentation complete. Exiting program." << std::endl;
}

INT32 Usage() {
    std::cerr << "This tool profiles branches and records history" << std::endl;
    return -1;
}

// Main entry point of the program
int main(int argc, char *argv[]) {
    // Initialize PIN
    if (PIN_Init(argc, argv)) {
        return Usage();
    }

    // Open the output file for writing at the beginning of the program
    outFile.open("branch_data.out", std::ios::out);
    if (!outFile.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return -1;
    }

    // Register instruction callback to handle branches
    INS_AddInstrumentFunction(Instruction, nullptr);

    // Register Fini function to close the output file
    PIN_AddFiniFunction(Fini, nullptr);

    // Start the program (this will not return until the program terminates)
    PIN_StartProgram();

    return 0;
}