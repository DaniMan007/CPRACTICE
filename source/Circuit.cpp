#include "Resistor.h"
#include "Circuit.h"
#include "CurrentSource.h"
#include "VoltageSource.h"
#include "iostream"
#include "iomanip" // For formatting matrix output
#include "cmath"
#include "algorithm" // For std::swap

// Building the constructor and the destructor
Circuit::Circuit() {};
Circuit::~Circuit() {
    for(int i = 0; i < nodes.size(); i++) {
        delete nodes[i];
    };

    for(int j = 0; j < components.size(); j++) {
        delete components[j];
    };
};

// Building the circuit
void Circuit::addNode(Node* node) {
    nodes.push_back(node);
};
void Circuit::addComponent(Component* component) {
    components.push_back(component);
};

// Calculation Functions
void Circuit::buildAdmittanceMatrix() {
    std::cout << "\n--- Building The Y Matrix ---\n";

    int numNodes = nodes.size(); // Includes Ground (Node 0)
    
    // 1. Count how many Voltage Sources exist so we know how many extra rows/cols to add
    int numVSources = 0;
    for (int i = 0; i < components.size(); i++) {
        if (dynamic_cast<VoltageSource*>(components[i]) != nullptr) {
            numVSources++;
        }
    }

    // 2. Size the MNA Matrix and Right-Hand-Side Vector
    int matrixSize = numNodes + numVSources;
    Y_Matrix.assign(matrixSize, std::vector<float>(matrixSize, 0.0));
    I_Matrix.assign(matrixSize, 0.0);

    // Extra rows/columns for Voltage Sources start right after the last Node ID
    int vIndex = numNodes; 

    // 3. Stamp every component using the VIP Bouncer
    for (int i = 0; i < components.size(); i++) {
        Component* comp = components[i];

        Resistor* res = dynamic_cast<Resistor*>(comp);
        CurrentSource* cSrc = dynamic_cast<CurrentSource*>(comp);
        VoltageSource* vSrc = dynamic_cast<VoltageSource*>(comp);

        // --- CASE 1: RESISTOR ---
        if (res != nullptr) {
            int n1 = res->get01()->getId();
            int n2 = res->get02()->getId();
            double g = res->getConductance();

            if (n1 != 0) Y_Matrix.at(n1).at(n1) += g;
            if (n2 != 0) Y_Matrix.at(n2).at(n2) += g;

            if (n1 != 0 && n2 != 0) {
                Y_Matrix.at(n1).at(n2) -= g;
                Y_Matrix.at(n2).at(n1) -= g;
            }
        }
        // --- CASE 2: CURRENT SOURCE (n1 -> n2) ---
        else if (cSrc != nullptr) {
            int n1 = cSrc->get01()->getId(); // Current leaves n1 (-)
            int n2 = cSrc->get02()->getId(); // Current enters n2 (+)
            double i_val = cSrc->getCurrent();  // Note: Ensure this matches your getter name (e.g., getValue())

            if (n1 != 0) I_Matrix.at(n1) -= i_val;
            if (n2 != 0) I_Matrix.at(n2) += i_val;
        }
        // --- CASE 3: VOLTAGE SOURCE (n1 is '-', n2 is '+') ---
        else if (vSrc != nullptr) {
            int n_neg = vSrc->get01()->getId();
            int n_pos = vSrc->get02()->getId();
            double v_val = vSrc->getVoltage(); // Note: Ensure this matches your getter name (e.g., getValue())

            // Link the Voltage Source current variable (vIndex) to the nodes
            if (n_pos != 0) {
                Y_Matrix.at(n_pos).at(vIndex) += 1.0;
                Y_Matrix.at(vIndex).at(n_pos) += 1.0;
            }
            if (n_neg != 0) {
                Y_Matrix.at(n_neg).at(vIndex) -= 1.0;
                Y_Matrix.at(vIndex).at(n_neg) -= 1.0;
            }

            // Enforce V_pos - V_neg = v_val
            I_Matrix.at(vIndex) = v_val;
            vIndex++;
        }
    }

    // To verify the matrix
    for(int row = 1; row < numNodes; row++) {
        for(int column = 1; column < numNodes; column++) {
            std::cout << std::setw(20) << Y_Matrix.at(row).at(column);
        }
        std::cout << "\n";
    };
};

void Circuit::buildImpedanceMatrix() {
    std::cout << "\n--- Building The Z Matrix ---\n";

    int nodesNum = nodes.size();
    
    //Creating a N x N matrix filled with zeros using vectors; This is the standard way of creating dynamic arrays, matrices.
    
    // Ensure a local matrix is available if a member isn't defined
    Z_Matrix.assign(nodesNum, std::vector<float>(nodesNum, 0.0));

    // The Stamping Algorithm
    for(int k = 0; k < components.size(); k++) {
        Component* compName = components[k];

        // THE VIP BOUNCER
        // This is the part where we check if the component is a current source or not, if it is then we skip it because we can't use the nodal analysis method for voltage sources
        if(compName->getName()[0] == 'I') continue;

        // Getting the node ID's
        int n01 = compName->get01()->getId();
        int n02 = compName->get02()->getId();

        // Getting the resistance
        float r = compName->getResistance();

        // This is the c++ version of the nodal analysis rule: Add resistances to the diagonal entries and subtract them from no-diagonal entries
        if (n01 != 0) Z_Matrix.at(n01).at(n01) += r;
        if (n02 != 0) Z_Matrix.at(n02).at(n02) += r;

        if(n01 != 0.0 && n02 != 0.0) {
            Z_Matrix.at(n01).at(n02) -= r;
            Z_Matrix.at(n02).at(n01) -= r;      
        };
    };

    // To verify the matrix
    for(int row = 1; row < nodesNum; row++) {
        for(int column = 1; column < nodesNum; column++) {
            std::cout << std::setw(20) << Z_Matrix.at(row).at(column);
        }
        std::cout << "\n";
    };

};

void Circuit::findNodeVoltage() {
    std::cout << "\n1st Gaussian Elimination Operation\n";
    
    // Total active unknowns = (Active Nodes) + (Voltage Source Currents)
    int n = Y_Matrix.size() - 1; 

    // ==========================================
    // PHASE 1: FORWARD ELIMINATION + PARTIAL PIVOTING
    // ==========================================
    for (int k = 1; k <= n; k++) {
        
        // Partial Pivoting: Find the row with the largest value in column k
        // (Mandatory for MNA because Voltage Source rows start with 0 on the diagonal!)
        int maxRow = k;
        for (int i = k + 1; i <= n; i++) {
            if (std::abs(Y_Matrix.at(i).at(k)) > std::abs(Y_Matrix.at(maxRow).at(k))) {
                maxRow = i;
            }
        }

        // Swap rows in both Y_Matrix and I_Vector if a better pivot was found
        if (maxRow != k) {
            std::swap(Y_Matrix.at(k), Y_Matrix.at(maxRow));
            std::swap(I_Matrix.at(k), I_Matrix.at(maxRow));
        }

        // Safety check for floating/unsolvable circuits
        if (std::abs(Y_Matrix.at(k).at(k)) < 1e-12) {
            std::cout << "\n[FATAL MATH ERROR] Singular Matrix detected at row " << k << "!\n";
            return;
        }

        // Standard Gaussian Elimination below the pivot
        for (int i = k + 1; i <= n; i++) {
            double factor = Y_Matrix.at(i).at(k) / Y_Matrix.at(k).at(k);
            
            for (int j = k; j <= n; j++) {
                Y_Matrix.at(i).at(j) -= factor * Y_Matrix.at(k).at(j);
            }
            I_Matrix.at(i) -= factor * I_Matrix.at(k);
        }
    }

    // ==========================================
    // PHASE 2: BACK SUBSTITUTION
    // ==========================================
    solution.assign(n + 1, 0.0);

    for (int i = n; i >= 1; i--) {
        solution[i] = I_Matrix.at(i);

        for (int j = i + 1; j <= n; j++) {
            solution[i] -= Y_Matrix.at(i).at(j) * solution[j];
        }

        solution[i] /= Y_Matrix.at(i).at(i);
    }

    // ==========================================
    // PHASE 3: STORE NODE VOLTAGES
    // ==========================================
    // Indices 1 to (nodes.size() - 1) are our Node Voltages.
    // Indices >= nodes.size() are the currents flowing through the Voltage Sources!
    for (int i = 1; i < nodes.size(); i++) {
        nodes[i]->setVoltage(solution[i]);
    }
}

void Circuit::printResult() {
    std::cout << "\n=========================================\n";
    std::cout << "          FINAL SIMULATION RESULTS             \n";
    std::cout << "=========================================\n";

    // The Component Summary
    std::cout << "\n--- Component Summary ---\n";
    for(int l = 0; l < components.size(); l++) {
        components[l]->PrintOut();
    };

    // The Node Voltage Summary
    std::cout << "\n--- Node Voltage Summary ---\n";
    for(int m = 1; m < nodes.size(); m++) {
        std::cout << "Node " << nodes[m]->getId() << ": " << nodes[m]->getVoltage() << " V\n";
    }

    // The Branch Current Summary
    std::cout << "\n--- Branch Current Summary ---\n";
    int vIndex = nodes.size(); // Matches the MNA row order for Voltage Sources

    for (int i = 0; i < components.size(); i++) {
        Component* comp = components[i];

        int n1 = comp->get01()->getId();
        int n2 = comp->get02()->getId();
        double v1 = comp->get01()->getVoltage();
        double v2 = comp->get02()->getVoltage();

        // 1. Resistor Current (Ohm's Law: I = (V1 - V2) / R)
        if (Resistor* res = dynamic_cast<Resistor*>(comp)) {
            double current = (v1 - v2) * res->getConductance(); // Same as (v1 - v2) / R
            std::cout << res->getName() << " (Node " << n1 << " -> Node " << n2 << "): " 
                      << current << " A\n";
        }
        // 2. Current Source (Fixed Value)
        else if (CurrentSource* cSrc = dynamic_cast<CurrentSource*>(comp)) {
            std::cout << cSrc->getName() << " (Node " << n1 << " -> Node " << n2 << "): " 
                      << cSrc->getCurrent() << " A\n";
        }
        // 3. Voltage Source (Extracted from MNA Solution Vector)
        else if (VoltageSource* vSrc = dynamic_cast<VoltageSource*>(comp)) {
            // In MNA passive sign convention, current enters (+) terminal (n2) and leaves (-) terminal (n1)
            double current = solution.at(vIndex);
            std::cout << vSrc->getName() << " (Node " << n2 << " -> Node " << n1 << "): " 
                      << current << " A\n";
            vIndex++;
        }
    }
}