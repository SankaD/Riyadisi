#pragma once

#include "EyeFeature.h"

EyeFeature::EyeFeature() : Feature()
{

}

PupilFeature *EyeFeature::getPupil()
{
    return &pupil;
}

void EyeFeature::clearFeature()
{
    Feature::clearFeature();
    pupil.clearFeature();
}