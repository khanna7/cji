/**
 * PrepAgeFilter.cpp
 */

#include "Person.h"
#include "PrepFilter.h"

namespace TransModel {


PrepFilter::PrepFilter() {}

PrepFilter::~PrepFilter() {}

LTAgePrepFilter::LTAgePrepFilter(double age_threshold) : age_threshold_(age_threshold) {}
LTAgePrepFilter::~LTAgePrepFilter() {}

bool LTAgePrepFilter::apply(PersonPtr person) {
    return person->age() < age_threshold_;
}

double LTAgePrepFilter::calcPrepStopAdjustment() { 
    return 0;
}


GTEAgePrepFilter::GTEAgePrepFilter(double age_threshold, double max_age) : age_threshold_(age_threshold), gte_adjustment((1.0 / 365) * (1 / (max_age - age_threshold))) {}

GTEAgePrepFilter::~GTEAgePrepFilter() {}

bool GTEAgePrepFilter::apply(PersonPtr person) {
    return person->age() >= age_threshold_;
}

double GTEAgePrepFilter::calcPrepStopAdjustment() {
    return gte_adjustment;
}

NonSubstanceUsePrepFilter::NonSubstanceUsePrepFilter() {}

NonSubstanceUsePrepFilter::~NonSubstanceUsePrepFilter() {}

bool NonSubstanceUsePrepFilter::apply(PersonPtr person) {
    return !person->isSubstanceUser();
}

double NonSubstanceUsePrepFilter::calcPrepStopAdjustment() {
    return 0;
}

MethPrepFilter::MethPrepFilter() {}

MethPrepFilter::~MethPrepFilter() {}

bool MethPrepFilter::apply(PersonPtr person) {
    return person->isSubstanceUser(SubstanceUseType::METH);
}

double MethPrepFilter::calcPrepStopAdjustment() {
    return 0;
}

CrackPrepFilter::CrackPrepFilter() {}

CrackPrepFilter::~CrackPrepFilter() {}

bool CrackPrepFilter::apply(PersonPtr person) {
    return person->isSubstanceUser(SubstanceUseType::CRACK);
}

double CrackPrepFilter::calcPrepStopAdjustment() {
    return 0;
}

EcstasyPrepFilter::EcstasyPrepFilter() {}

EcstasyPrepFilter::~EcstasyPrepFilter() {}

bool EcstasyPrepFilter::apply(PersonPtr person) {
    return person->isSubstanceUser(SubstanceUseType::ECSTASY);
}

double EcstasyPrepFilter::calcPrepStopAdjustment() {
    return 0;
}
}
