/**
 *   LUST-Motion
 *
 *   https://github.com/openlust/LUST-motion
 *
 *   Copyright (C) 2025 theelims
 *
 *   All Rights Reserved. This software may be modified and distributed under
 *   the terms of the MIT license. See the LICENSE file for details.
 **/

#include <ESP32SvelteKit.h>
#include <PsychicHttpServer.h>

#include <StrokeEngine.h>
#include <StatusMonitor.h>

#include <services.hpp>

void setup()
{
    // start serial communication
    Serial.begin(CONSOLE_BAUD_RATE);

    // start ESP32-SvelteKit
    esp32sveltekit.begin();
    statusMonitor.begin();

    // start mDNS
    MDNS.addService("LUST-Service", "tcp", 80);
    MDNS.addServiceTxt("LUST-Service", "tcp", "FirmwareVersion", APP_VERSION);
    MDNS.addServiceTxt("LUST-Service", "tcp", "DeviceID", SettingValue::format("LUST-motion-#{unique_id}"));
    MDNS.addServiceTxt("LUST-Service", "tcp", "Service", "LUST-motion");

    // StrokeEngine Startup
    StrokeEngine.registerPatterns(patternTable, std::size(patternTable));

    // Sveltekit Service Startup
    motorConfigurationService.begin();
    strokeEngineControlService.begin();
    mqttBrokerSettingsService.begin();
    strokeEngineSafetyService.begin();
    strokeEngineEnvironmentService.begin();
    safeStateService.begin();
    serialState.begin(); // TODO - Activate only on LinMot variants (For space reasons)

    // Sveltekit Monitor / Streaming Startup
    esp32sveltekit.addLoopFunction([]() { statusMonitor.loop(); });
    dataStream.begin();
}

// Delete Arduino loop task, as it is not needed in this application
void loop() { vTaskDelete(NULL); }