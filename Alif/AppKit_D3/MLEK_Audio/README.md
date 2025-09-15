# Keyword spotting

This example can detect up to twelve keywords in the input audio stream. The
[audio file used](./resources/sample_audio.wav) contains the keyword "down" being spoken.

More details about the input for this example can be found [here](https://review.mlplatform.org/plugins/gitiles/ml/ethos-u/ml-embedded-evaluation-kit/+/refs/heads/main/docs/use_cases/kws.md#preprocessing-and-feature-extraction).

## CI Verification

A [GitHub Workflow](https://github.com/Arm-Examples/cmsis-mlek-examples/blob/main/.github/workflows/test_audio.yaml) exemplifies a verification process in a CI system. It compiles the application for [Arm Virtual Hardware FVP](https://github.com/ARM-software/AVH) and executes it. The output is stored as artifact.

In a similar way it could be also compiled for the hardware target.

> TIP: You may fork this repository to explore this workflow.