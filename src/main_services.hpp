
#include <ESP32SvelteKit.h>
#include <PsychicHttpServer.h>
#include <StrokeEngine.h>

#include <service/MqttBrokerSettingsService.h>
#include <service/StrokeEngineControlService.h>
#include <service/MotorConfigurationService.h>
#include <service/StrokeEngineEnvironmentService.h>
#include <service/StrokeEngineSafetyService.h>
#include <service/SafeStateService.h>
//#include <service/SerialStateService.hpp>
#include <service/RawDataStreaming.h> // TODO - This is not a service?
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

/* requires AsyncTCP to be restored                                                                                          
SerialStateService serialState(
    &server, 
    esp32sveltekit.getSecurityManager(), 
    esp32sveltekit.getFS()
  );
*/

DataStreamer dataStream = DataStreamer(&esp32sveltekit, &Stroker);
StatusMonitor statusMonitor = StatusMonitor(&esp32sveltekit);