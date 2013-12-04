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

bool EyeFeature::isEyeOpen()
{
	return (state == EyeState::OPEN);
}
 
void EyeFeature::setEyeState ( EyeState state )
{
	this->state = state;
}