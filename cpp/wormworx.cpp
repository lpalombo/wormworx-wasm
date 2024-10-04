#include <emscripten/bind.h>
#include <vector>
#include "wormsim.h"

// Define constants if they're not in wormsim.h
#ifndef NUM_STEERING_NEURONS
#define NUM_STEERING_NEURONS 6  // Adjust this value as needed
#endif

#ifndef NUM_MOTOR_NEURONS
#define NUM_MOTOR_NEURONS 24  // Adjust this value as needed
#endif

#ifndef NUM_MUSCLES
#define NUM_MUSCLES 96  // Adjust this value as needed
#endif

class WormWorx {
public:
    WormWorx() {
        init();  // Initialize the simulation
    }

    ~WormWorx() {
        terminate();  // Clean up the simulation
    }

    void setSteeringSynapseWeights(const std::vector<double>& weights) {
        for (size_t i = 0; i < weights.size(); i++) {
            set_steering_synapse_weight(i, weights[i]);
        }
    }

    void step(double salt_stimulus) {
        ::step(salt_stimulus);
    }

    std::vector<double> getSteeringActivations() {
        std::vector<double> activations(NUM_STEERING_NEURONS);
        for (int i = 0; i < NUM_STEERING_NEURONS; i++) {
            activations[i] = get_steering_activation(i);
        }
        return activations;
    }

    std::vector<double> getDorsalMotorActivations() {
        std::vector<double> activations(NUM_MOTOR_NEURONS);
        for (int i = 0; i < NUM_MOTOR_NEURONS; i++) {
            activations[i] = get_dorsal_motor_activation(i);
        }
        return activations;
    }

    std::vector<double> getVentralMotorActivations() {
        std::vector<double> activations(NUM_MOTOR_NEURONS);
        for (int i = 0; i < NUM_MOTOR_NEURONS; i++) {
            activations[i] = get_ventral_motor_activation(i);
        }
        return activations;
    }

    std::vector<double> getDorsalMuscleActivations() {
        std::vector<double> activations(NUM_MUSCLES);
        for (int i = 0; i < NUM_MUSCLES; i++) {
            activations[i] = get_dorsal_muscle_activation(i);
        }
        return activations;
    }

    std::vector<double> getVentralMuscleActivations() {
        std::vector<double> activations(NUM_MUSCLES);
        for (int i = 0; i < NUM_MUSCLES; i++) {
            activations[i] = get_ventral_muscle_activation(i);
        }
        return activations;
    }

    std::vector<double> getBody() {
        std::vector<double> body(NBAR * 3);
        for (int i = 0; i < NBAR; ++i) {
            body[i * 3] = get_body_point(i * 3);
            body[i * 3 + 1] = get_body_point(i * 3 + 1);
            body[i * 3 + 2] = get_body_point(i * 3 + 2);
        }
        return body;
    }

    std::vector<double> getSegmentAngles() {
        std::vector<double> angles(12);
        for (int i = 0; i < 12; ++i) {
            angles[i] = get_segment_angle(i);
        }
        return angles;
    }
};

// Binding code
EMSCRIPTEN_BINDINGS(wormworx) {
    emscripten::class_<WormWorx>("WormWorx")
        .constructor<>()
        .function("setSteeringSynapseWeights", &WormWorx::setSteeringSynapseWeights)
        .function("step", &WormWorx::step)
        .function("getSteeringActivations", &WormWorx::getSteeringActivations)
        .function("getDorsalMotorActivations", &WormWorx::getDorsalMotorActivations)
        .function("getVentralMotorActivations", &WormWorx::getVentralMotorActivations)
        .function("getDorsalMuscleActivations", &WormWorx::getDorsalMuscleActivations)
        .function("getVentralMuscleActivations", &WormWorx::getVentralMuscleActivations)
        .function("getBody", &WormWorx::getBody)
        .function("getSegmentAngles", &WormWorx::getSegmentAngles);

    emscripten::register_vector<double>("VectorDouble");
}