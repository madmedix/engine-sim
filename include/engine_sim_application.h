#ifndef ATG_ENGINE_SIM_ENGINE_SIM_APPLICATION_H
#define ATG_ENGINE_SIM_ENGINE_SIM_APPLICATION_H

#include "geometry_generator.h"
#include "engine_simulator.h"
#include "engine.h"
#include "simulation_object.h"

#include "delta.h"
#include "dtv.h"

#include <vector>

class EngineSimApplication {
    public:
        EngineSimApplication();
        virtual ~EngineSimApplication();

        void initialize(void *instance, ysContextObject::DeviceAPI api);
        void run();
        void destroy();

        void setCameraPosition(const ysVector &position) { m_cameraPosition = position; }
        void setCameraTarget(const ysVector &target) { m_cameraTarget = target; }
        void setCameraUp(const ysVector &up) { m_cameraUp = up; }

        void drawGenerated(const GeometryGenerator::GeometryIndices &indices);
        GeometryGenerator *getGeometryGenerator() { return &m_geometryGenerator; }

        dbasic::DefaultShaders *getShaders() { return &m_shaders; }

        void createObjects(Engine *engine);

    protected:
        void renderScene();

    protected:
        virtual void initialize();
        virtual void process(float dt);
        virtual void render();

        dbasic::ShaderSet m_shaderSet;
        dbasic::DefaultShaders m_shaders;

        dbasic::DeltaEngine m_engine;
        dbasic::AssetManager m_assetManager;

        ysVector m_cameraPosition;
        ysVector m_cameraTarget;
        ysVector m_cameraUp;

        std::string m_assetPath;

        ysGPUBuffer *m_geometryVertexBuffer;
        ysGPUBuffer *m_geometryIndexBuffer;

        GeometryGenerator m_geometryGenerator;

        std::vector<SimulationObject *> m_objects;
        Engine m_iceEngine;
        EngineSimulator m_simulator;

        bool m_paused;

    protected:
        void startRecording();
        void updateScreenSizeStability();
        bool readyToRecord();
        void stopRecording();
        void recordFrame();
        bool isRecording() const { return m_recording; }

        static constexpr int ScreenResolutionHistoryLength = 5;
        int m_screenResolution[ScreenResolutionHistoryLength][2];
        int m_screenResolutionIndex;
        bool m_recording;

        ysVector m_background;
        ysVector m_foreground;
        ysVector m_shadow;
        ysVector m_highlight1;
        ysVector m_highlight2;

#ifdef ATG_ENGINE_SIM_VIDEO_CAPTURE
        atg_dtv::Encoder m_encoder;
#endif /* ATG_ENGINE_SIM_VIDEO_CAPTURE */
};

#endif /* ATG_ENGINE_SIM_ENGINE_SIM_APPLICATION_H */
