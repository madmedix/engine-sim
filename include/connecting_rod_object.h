#ifndef ATG_ENGINE_SIM_CONNECTING_ROD_OBJECT_H
#define ATG_ENGINE_SIM_CONNECTING_ROD_OBJECT_H

#include "simulation_object.h"

#include "connecting_rod.h"
#include "geometry_generator.h"

class ConnectingRodObject : public SimulationObject {
    public:
        ConnectingRodObject();
        virtual ~ConnectingRodObject();

        virtual void generateGeometry();
        virtual void render();
        virtual void process(float dt);
        virtual void destroy();

        ConnectingRod *m_connectingRod;

    protected:
        GeometryGenerator::GeometryIndices
            m_connectingRodBody;
};

#endif /* ATG_ENGINE_SIM_CONNECTING_ROD_OBJECT_H */
