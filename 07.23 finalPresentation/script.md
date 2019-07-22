
# Final Presentation

## Introduction

As professord Koumpis said, and as you probably all noticed :
"I'm crazy about Strava"

Focusing on Health, more specificly on Mental Health
Mister Koumpis was fearing that this kind of "Sport Tracking App and Devices" were bad for yout Mental Health
By non stop telling you what you shloud do, what you shoulnd't do, and what you did wrong

In my opinion, This is not possible with Strava
I would not describe it as a "Tracking" app, but rather as a "Sport Activity Recorder"

But, I think that an other problem might appear
You feel guilty if you don't do enough
Which can lead to overtraining

## Problem

How to detect and prevent OverTraining ?

## Process

Relative Effort (TRIMP) : How hard you worked

    Track heart rate level relative to maximum, attach a value to show exactly *how hard you worked*
    The more time you spend going full gas and the longer your activity, the higher the score
    Inspired by the concept of TRIMP (TRaining IMPulse) coined by Dr. Eric Bannister.

Fitness and Freshness

    Evaluation of your (fitness, fatigue, form) over the time

    Pros

        Over all your activities
        How hard you worked

    Cons

        Doesn't care about the intensity of the activity
        No overtraining alert

    Example : Heart Rate Box Plot

        Easy workout, easy heart rate
        Race, hard heart rate
        ..., hard heart rate : Easy workout !

Activity Intensity (ActInt) : How hard the Activity was

    Evaluate the difficulty of the activity based on speed and elevation gradient

ActInt & TRIMP Comparison

    Evaluate how (fit, trained, tired, overtrained) you are

    TRIMP   ActInt  Evaluation
    <       >       Better Fitness
    >       <       More Tired : OverTraining ?

    If you took it easier, or you were more performant, we can say that your fitness is improving
    But, if you worked harder, or you were less performant, we can say that your fatigue in increasing

Approach

    Learning

        Get GPX files from activities, Annotate

        Pre-process : compute and select meaningfull numbers : speed, elevation gradient, heart rate

        Train model

    Prediction

        Give GPX activity file
        System gives an evaluation

## Results

## Future Work

