
#include <ESP32SvelteKit.h>
#include <PsychicHttpServer.h>
#include <StrokeEngine.h>
#include <MqttBrokerSettingsService.h>
#include <StrokeEngineControlService.h>
#include <MotorConfigurationService.h>
#include <StrokeEngineEnvironmentService.h>
#include <StrokeEngineSafetyService.h>
#include <SafeStateService.h>
#include <service/SerialStateService.hpp>
#include <RawDataStreaming.h>
#include <StatusMonitor.h>


// StrokeEngine ###################################################################################
StrokeEngine Stroker;

// ESP32-SvelteKit #################################################################################
PsychicHttpServer server;

ESP32SvelteKit esp32sveltekit(&server, 130);

MqttBrokerSettingsService mqttBrokerSettingsService(
    &server,
    &esp32sveltekit
  );

StrokeEngineControlService strokeEngineControlService(
    &Stroker,
    &esp32sveltekit,
    &mqttBrokerSettingsService
  );

MotorConfigurationService motorConfigurationService(
    &Stroker,
    &esp32sveltekit
  );

SafeStateService safeStateService(
    &Stroker,
    &server,
    &esp32sveltekit,
    &mqttBrokerSettingsService
  );

StrokeEngineSafetyService strokeEngineSafetyService(
    &Stroker,
    &esp32sveltekit,
    &safeStateService
  );

StrokeEngineEnvironmentService strokeEngineEnvironmentService(
    &Stroker,
    &esp32sveltekit,
    &motorConfigurationService,
    &strokeEngineSafetyService,
    &mqttBrokerSettingsService
  );
                                                                                              
SerialStateService serialState(
    &server, 
    esp32sveltekit.getSecurityManager(), 
    esp32sveltekit.getFS()
  );

DataStreamer dataStream = DataStreamer(&esp32sveltekit, &Stroker);
StatusMonitor statusMonitor = StatusMonitor(&esp32sveltekit);