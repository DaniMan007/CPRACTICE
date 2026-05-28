#pragma once

class Node {
    private:
        int id;
        float voltage;

    public:
        //Constructor
        Node(int nodeId, float voltage);

        //Getters
        int getId() const;
        float getVolatge() const;

        //Setters
        void setVolatge(float v);
};