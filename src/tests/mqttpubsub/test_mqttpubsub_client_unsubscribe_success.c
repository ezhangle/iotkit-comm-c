/*
 * Copyright (c) 2014 Intel Corporation.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/** @file test_mqttpubsub_client_unsubscribe_success.c

 */

#include <stdio.h>
#include <MQTTAsync.h>
#include "iotkit-comm.h"

bool receivedMessage = false;

void message_callback(char *message, Context context) {
    printf("Message received:%s\n", message);
    receivedMessage = true;
}

int main(void) {
    ServiceQuery *serviceQuery = (ServiceQuery *)malloc(sizeof(ServiceQuery));
    if (serviceQuery != NULL) {
        serviceQuery->service_name = strdup("/foo");
        serviceQuery->address = strdup("localhost");
        serviceQuery->port = 1883;
        int result = init(serviceQuery, NULL);
        if (result == MQTTASYNC_SUCCESS) {
            puts("Successfully Connected to an MQTT Broker");
            receive(message_callback);
            result = subscribe("/foo"); //correct topic
            if (result == 0) {
                puts("Subscribed Successfully");
                puts("Waiting for messages on subscribed topic");
                result = unsubscribe("/foo");
                if(result == MQTTASYNC_SUCCESS) {
                    puts("Test Passed: Successfully unsubscribed topic");
                    exit(EXIT_SUCCESS);
                } else {
                    puts("Test Failed: Topic not found");
                }
            } else {
                puts("Test Failed: Could not subscribe");
            }
        } else {
            puts("Test Failed: Could not connect to MQTT Broker");
        }
        done();
        free(serviceQuery);
    }
    exit(EXIT_FAILURE);
}
