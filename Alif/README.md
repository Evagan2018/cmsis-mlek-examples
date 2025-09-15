# Examples for Alif Semicontuctor

The examples for Alif Semiconductor are configured for evaluation boards.

## JLink

When using the SEGGER JLink debug adapter ensure that JLink version 8.44 or higher is installed.

## SETOOLS

Before using examples on the board it is required to program the ATOC of the device
using the Alif SETOOLS.

Refer to the section [Usage](https://github.com/alifsemi/alif_ensemble-cmsis-dfp/blob/main/docs/Overview.md)
in the overview page of the Alif Semiconductor Ensemble DFP/BSP for information on how
to setup these tools.

In VS Code use the menu command **Terminal - Run Tasks** and execute one of the following:

- "Alif: Install M55_HE or M55_HP debug stubs (single core configuration)"
- "Alif: Install M55_HE and M55_HP debug stubs (dual core configuration)"

## [Examples for Ensemble E7 AI/ML AppKit](./AppKit_D3)

The [Alif AppKit-E7-AIML](https://www.keil.arm.com/boards/alif-semiconductor-appkit-e7-aiml-gen-2-140e28d/guide/) features a dual-core Cortex-M55 each paired with an Ethos-U55 NPU.

> TIP: [Webinar 3: ML and Dual-Core Debugging on Alif Ensemble E7](https://www.arm.com/resources/webinar/keil-studio) shows how to use this board.

> Note:
>
> - Configure J15-A & J15-B to position SE (Secure UART) to enable SETOOLS communication with the device.
> - Configure J15-A & J15-B to position U4 (UART4) to see printf messages from the application.

Example                            | Description
:----------------------------------|:---------------------------------
[Tensorflow_LiteRT_HelloWorld](https://www.keil.arm.com/packs/tensorflow-lite-micro-tensorflow/overview/) | Demonstrates integration and usage of the LiteRT stack
[MLEK_Audio](https://www.keil.arm.com/packs/cmsis-mlek-arm/overview/) | Keyword spotting (KWS) ML application running on M55_HE core and Ethos-U55
[MLEK_Video](https://www.keil.arm.com/packs/cmsis-mlek-arm/overview/) | Object detection  ML application running on M55_HP core and Ethos-U55
MLEK_AV_DualCore | Combines MLEK Audio and MLEK Video running both applications on separate cores

## CI Verification

A [GitHub Workflow](https://github.com/Arm-Examples/cmsis-mlek-examples/blob/main/.github/workflows/test_audio.yaml) exemplifies a verification process in a CI system. It compiles the application for [Arm Virtual Hardware FVP](https://github.com/ARM-software/AVH) and executes it. The output is stored as artifact.

In a similar way it could be also compiled for the hardware target.

> TIP: You may fork this repository to explore this workflow.
