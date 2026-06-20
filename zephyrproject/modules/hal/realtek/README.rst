
Realtek HAL Module (hal_realtek)
################################

HAL Realtek (or ``hal_realtek``) is a collection of tools, low-level APIs, and hardware access functions for Realtek Devices, enabling support within the Zephyr RTOS ecosystem.

Currently, the ``hal_realtek`` repository supports two primary SoC series: **Ameba** and **Bee**.

Supported SoC Series
*******************

Ameba Series (ameba)
====================

The ``ameba`` directory contains the HAL for Ameba series SoCs.

This repository is a copy (not a fork) of the `ameba-rtos repository <https://github.com/Ameba-AIoT/ameba-rtos>`_ that contains Ameba SoCs.

After following the standard Zephyr guide for compilation, both app and bootloader images tailored for Ameba SoCs will be generated. Refer to this `tutorial <https://github.com/Ameba-AIoT/ameba-rtos/>`_ for Flashing these images and running on Ameba SoCs.

Bee Series (bee)
================

The ``bee`` directory hosts the HAL for Bee series SoCs. The sources in this directory are extracted from their respective SDKs:

* **RTL87x2G**: `rtkconnectivity/rtl87x2g_sdk <https://github.com/rtkconnectivity/rtl87x2g_sdk>`_

* **RTL8752H**: `rtkconnectivity/rtl8752h_sdk <https://github.com/rtkconnectivity/rtl8752h_sdk>`_

Maintenance & Synchronization Strategy
**************************************

Since the HALs for the **Ameba** and **Bee** series are maintained by different teams within Realtek, and additional SoC series may be added to ``hal_realtek`` in the future, there is no single upstream Git history for this repository.

Therefore, this module adheres to the **"Updating modules with a diff from upstream"** practice as defined in the `Zephyr Project Documentation <https://docs.zephyrproject.org/latest/develop/modules.html#allowed-practices>`_.