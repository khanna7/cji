/*
 * Person.h
 *
 *  Created on: Oct 8, 2015
 *      Author: nick
 */

#ifndef SRC_PERSON_H_
#define SRC_PERSON_H_

#include "Rcpp.h"
#include "DiseaseParameters.h"
#include "Diagnoser.h"
#include "GeometricDistribution.h"
#include "AdherenceCategory.h"
#include "PrepStatus.h"

namespace TransModel {

class PersonCreator;

class Person {

private:
	friend PersonCreator;

	int id_, steady_role_, casual_role_;
	float age_;
	bool circum_status_;
	InfectionParameters infection_parameters_;
	float infectivity_;
	bool dead_, diagnosed_, testable_;
	Diagnoser<GeometricDistribution> diagnoser_;
	AdherenceData art_adherence_, prep_adherence_;
	PrepStatus prep_status_;
	double prep_on_at;

public:
	Person(int id, float age, bool circum_status, int steady_role, int casual_role,
			Diagnoser<GeometricDistribution>& diagnoser);

	virtual ~Person();

	/**
	 * Gets the id of this person.
	 */

	int id() const {
		return id_;
	}

	int steady_role() const {
		return steady_role_;
	}

	int casual_role() const {
		return casual_role_;
	}

	/**
	 * Gets the age of this Person.
	 */
	float age() const {
		return age_;
	}

	bool isOnPrep() const {
		return prep_status_ == PrepStatus::ON;
	}

	double prepStart() const {
		return prep_on_at;
	}

	const InfectionParameters& infectionParameters() const {
		return infection_parameters_;
	}

	bool isCircumcised() const {
		return circum_status_;
	}

	bool isOnART() const {
		return infection_parameters_.art_status;
	}

	bool isInfected() const {
		return infection_parameters_.infection_status;
	}

	float infectivity() const {
		return infectivity_;
	}

	float timeSinceInfection() const {
		return infection_parameters_.time_since_infection;
	}

	const Diagnoser<GeometricDistribution> diagnoser() const {
		return diagnoser_;
	}

	void setArtAdherence(AdherenceData data) {
		art_adherence_ = data;
	}

	const AdherenceData artAdherence() const {
		return art_adherence_;
	}

	void setPrepAdherence(AdherenceData data) {
		prep_adherence_ = data;
	}

	const AdherenceData prepAdherence() const {
		return prep_adherence_;
	}

	PrepStatus prepStatus() const {
		return prep_status_;
	}
	void setViralLoad(float viral_load);

	void setCD4Count(float cd4_count);

	void setViralLoadARTSlope(float slope);

	void setInfectivity(float infectivity);

	void setAge(float age);

	void goOnPrep(double timestamp);

	void goOffPrep(PrepStatus off_status);

	/**
	 * Puts this Person on ART with the specified time stamp,
	 * setting the art status to true.
	 */
	void goOnART(float time_stamp);

	/**
	 * Takes this person off ART, setting the art status to false.
	 */
	void goOffART();

	/**
	 * Infects this Person and sets the duration of the infection,
	 * and the time of infection.
	 */
	void infect(float duration_of_infection, float time);

	/**
	 * Updates age, etc. of person., to be called each iteration of the model.
	 */
	void step(float size_of_timestep);

	/**
	 * Checks if person is dead of old age. This doesn't kill
	 * the person, it just checks.
	 */
	bool deadOfAge(int max_age);

	/**
	 * Checks if person is dead of AIDS. This doesn't kill
	 * the person, it just checks.
	 */
	bool deadOfInfection();

	void setDead(bool isDead) {
		dead_ = isDead;
	}

	bool isDead() const {
		return dead_;
	}

	bool isDiagnosed() const {
		return diagnosed_;
	}

	bool isTestable() const {
		return testable_;
	}

	bool diagnose(double tick);

	double timeUntilNextTest(double tick) const;

};

} /* namespace TransModel */

#endif /* SRC_PERSON_H_ */
