#pragma once

class Node {
    private:
        int id;
        float voltage;

    public:
        // Constructor
        Node(int nodeId);

        // Getters
        int getId() const;
        float getVoltage() const;

        // Setters
        void setVoltage(float v);
};