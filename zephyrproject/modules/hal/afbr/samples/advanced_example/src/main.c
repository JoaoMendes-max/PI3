/*************************************************************************//**
 * @file
 * @brief       This file is part of the AFBR-S50 SDK example application.
 *
 * @copyright
 *
 * Copyright (c) 2023, Broadcom Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *****************************************************************************/

#include <stdio.h>
#include <api/argus_api.h>
#include <platform/argus_irq.h>

#define SPI_SLAVE 1

/*!***************************************************************************
 *  Global measurement data ready event counter.
 *
 *  Determines the number of measurement data ready events happened and thus
 *  the number of timer the #Argus_EvaluateData function must be called to
 *  free API internal date structures that buffer the raw sensor readout data.
 *
 *  The #Argus_EvaluateData function must be called outside of the interrupt
 *  callback scope (i.e. from the main thread/task) to avoid huge delays due
 *  to the heavy data evaluation.
 *
 *  Note that the #Argus_EvaluateData function must be called once for each
 *  callback event since it clears the internal state of the raw data buffer.
 *  If not called, the API gets stuck waiting for the raw data buffer to be
 *  freed and ready to be filled with new measurement data.
 *
 *  In automatic measurement mode, i.e. if the measurements are automatically
 *  triggered on a time based schedule from the periodic interrupt timer (PIT),
 *  the callback may occur faster than the #Argus_EvaluateData function gets
 *  called from the main thread/task. This usually happens at high frame rates
 *  or too much CPU load on the main thread/task. In that case, the API delays
 *  new measurements until the previous buffers are cleared. Since the API
 *  contains two distinct raw data buffers, this counter raises up to 2 in the
 *  worst case scenario.
 *****************************************************************************/
static volatile uint8_t myDataReadyEvents = 0;

/*!***************************************************************************
 * @brief   A callback function from the example code whenever an error occurs.
 *
 * @details The example code calls this function whenever an unexpected error
 *          occurs, for example, if an API function returns an error code.
 *
 *          This implementation of the function will print the error message.
 *          If specified, the program execution will be stopped with an
 *          infinite loop. Otherwise, the program will continue to run and the
 *          error is printed and ignored.
 *
 * @warning This is only a simple example implementation that does not handle
 *          errors in a production system. It is intended to demonstrate the
 *          usage of the API and to provide a starting point for custom
 *          applications.
 *
 *          This function needs to be replaced with a more sophisticated
 *          implementation to handle errors in a production system.
 *          For example, it could reset the device or try to recover from
 *          the error by re-initializing the device.
 *
 * @param   status The specified status to be checked for errors.
 * @param   stop Whether to stop the program (e.g. in case of a critical error).
 * @param   msg The associated error message to be printed in case of errors.
 *****************************************************************************/
void HandleError(status_t status, bool stop, char const * msg)
{
    /* Check for status < 0 and print message and halt the program execution. */
    if (status < STATUS_OK)
    {
        printf("ERROR (%d): %s\n", status, msg);
        if (stop)
        {
            printf(" --> Stopped execution due to a critical issue!\n"
                "     Check the hardware end reset the board!\n");
            while (1) __asm("nop"); // stop!
        }
    }
}

/*!***************************************************************************
 * @brief   Creates and initializes a new device instance.
 *
 * @param   slave The SPI slave identifier number that is passed to the S2PI
 *                layers by the API whenever it calls a function.
 *
 * @return  The pointer to the handle of the created device instance. Used to
 *          identify the calling instance in case of multiple devices.
 *****************************************************************************/
static argus_hnd_t* InitializeDevice(s2pi_slave_t slave)
{
    /* Get device instance already initialized with default settings by the OS */
    argus_hnd_t *device = Argus_GetHandle(SPI_SLAVE);
    HandleError(device ? STATUS_OK : ERROR_FAIL, true, "Argus_CreateHandle failed!");

    /* Adjust additional configuration parameters by invoking the dedicated API methods.
    * Note: The maximum frame rate is limited by the amount of data sent via UART.
    *       See #PrintResults function for more information. */
    status_t status = Argus_SetConfigurationFrameTime(device, 100000); // 0.1 second = 10 Hz
    HandleError(status, true, "Argus_SetConfigurationFrameTime failed!");

    return device;
}

/*!***************************************************************************
 * @brief   Measurement data ready callback function.
 *
 * @param   status The measurement/device status from the last measurement cycle.
 *
 * @param   device The pointer to the handle of the calling API instance. Used to
 *                 identify the calling instance in case of multiple devices.
 *
 * @return  Returns the \link #status_t status\endlink (#STATUS_OK on success).
 *****************************************************************************/
static status_t MeasurementReadyCallback(status_t status, argus_hnd_t * device)
{
    (void)device; // unused in this example...

    HandleError(status, false, "Measurement Ready Callback received error!");

    /* Count the data ready events, i.e. the number of times the
     * Argus_EvaluateData function must be called from main thread.
     *
     * Note: Since only a single device is used, the device parameter
     *       can be ignored. In case of multiple device, the device
     *       parameter determines the calling device instance.
     *
     * Note: Do not call the Argus_EvaluateMeasurement method
     *       from within this callback since it is invoked in
     *       a interrupt service routine and should return as
     *       soon as possible. */
    myDataReadyEvents++;

    return STATUS_OK;
}

/*!***************************************************************************
 * @brief   Prints measurement results via UART.
 *
 * @details Prints some measurement data via UART in the following format:
 *
 *          ```
 *          123.456789 s; Range: 123456 mm;  Amplitude: 1234 LSB; Quality: 100;  Status: 0
 *          ```
 *
 * @param   res A pointer to the latest measurement results structure.
 *****************************************************************************/
static void PrintResults(argus_results_t const * res)
{
    /* Print the recent measurement results:
     * 1. Time stamp in seconds since the last MCU reset.
     * 2. Range in mm (converting the Q9.22 value to mm).
     * 3. Amplitude in LSB (converting the UQ12.4 value to LSB).
     * 4. Signal Quality in % (100% = good signal).
     * 5. Status (0: OK, <0: Error, >0: Warning.
     *
     * Note: Sending data via UART creates a large delay which might prevent
     *       the API from reaching the full frame rate. This example sends
     *       approximately 80 characters per frame at 115200 bps which limits
     *       the max. frame rate of 144 fps:
     *       115200 bps / 10 [bauds-per-byte] / 80 [bytes-per-frame] = 144 fps */
    printf("%4d.%06d s; Range: %5d mm;  Amplitude: %4d LSB;  Quality: %3d;  Status: %d\n",
          res->TimeStamp.sec,
          res->TimeStamp.usec,
          res->Bin.Range / (Q9_22_ONE / 1000),
          res->Bin.Amplitude / UQ12_4_ONE,
          res->Bin.SignalQuality,
          res->Status);
}

/*!***************************************************************************
 * @brief   Prints information about the initialized devices.
 *
 * @param   device The pointer to the device handler.
 *****************************************************************************/
static void PrintDeviceInfo(argus_hnd_t * device)
{
    /* Print some information about current API and connected device. */
    const uint32_t value = Argus_GetAPIVersion();
    const uint8_t a = (uint8_t)((value >> 24) & 0xFFU);
    const uint8_t b = (uint8_t)((value >> 16) & 0xFFU);
    const uint8_t c = (uint8_t)(value & 0xFFFFU);
    const uint32_t id = Argus_GetChipID(device);
    const char * m = Argus_GetModuleName(device);

    printf("\n##### AFBR-S50 API - Advanced Example #########################\n"
          "  API Version: v%d.%d.%d\n"
          "  Chip ID:     %d\n"
          "  Module:      %s\n"
          "###############################################################\n\n",
          a, b, c, id, m);
}

int main(void)
{
    /* Instantiate and initialize the device handlers. */
    argus_hnd_t * device = InitializeDevice(SPI_SLAVE);

    /* Print a device information message. */
    PrintDeviceInfo(device);

    /* Start the measurement timers within the API module.
    * The callback is invoked every time a measurement has been finished.
    * The callback is used to schedule the data evaluation routine to the
    * main thread by the user.
    * Note that the timer based measurement is not implemented for multiple
    * instance yet! */
    status_t status = Argus_StartMeasurementTimer(device, &MeasurementReadyCallback);
    HandleError(status, true, "Argus_StartMeasurementTimer failed!");
    
    /* The program loop ... */
    for (;;)
    {
        /* Check if new measurement data is ready. */
        if (myDataReadyEvents)
        {
            IRQ_LOCK();
            myDataReadyEvents--;
            IRQ_UNLOCK();

            /* The measurement data structure. */
            argus_results_t res;

            /* Evaluate the raw measurement results. */
            status = Argus_EvaluateData(device, &res);
            HandleError(status, false, "Argus_EvaluateData failed!");

            /* Use the obtain results, e.g. print via UART. */
            PrintResults(&res);
        }
    }

    return 0;
}
