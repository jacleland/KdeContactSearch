/*
 * Simple program that searches KDE5 contacts
 *
 * Copyright (C) 2020  James A. Cleland <jcleland@jamescleland.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

// Library includes
#include <iostream>

// KDE includes
#include <kcontacts/addressee.h>

// Project includes
#include "SearchTask.h"

/**
 * Copy constructor
 * @param other rvalue to copy from
 */
SearchTask::SearchTask(const SearchTask& other) :
	QObject()
{
	// Call assignment operator
	*this = other;
}

/**
 * Construct this instance with criterion and match type
 * @param criterion The criterion to be used (field to search)
 */
SearchTask::SearchTask(SearchCriterion criterion, ContactMatch matchType) :
	criterion_(criterion),
	matchType_(matchType),
	job_(nullptr)
{
}

/**
 * Destructor
 */
SearchTask::~SearchTask(){}

/**
 * Assignment operator
 * @param other rvalue to copy from
 * @return A reference to ourselves
 */
SearchTask& SearchTask::operator=(const SearchTask& other) {
	//Copy attributes from other
	this->criterion_ = other.criterion_;
	this->term_ = other.term_;
	this->matchType_ = other.matchType_;
	this->job_ = other.job_;
	
	//Return ref to ourselves
	return *this;
}

/**
 * Returns the criteria value for this SearchTask instance
 * @return The criterion value
 */
const SearchCriterion& SearchTask::criterion() {
	return criterion_;
}

/**
 * Sets criterion for searches
 * @param criterion Const reference to criterion for search
 */
void SearchTask::setCriterion(const SearchCriterion& criterion) {
	criterion_ = criterion;
}

/**
 * Return the match type for this search SearchTask
 * @return The match type
 */
const ContactMatch& SearchTask::matchType() const {
	return matchType_;
}

/**
 * Set the match type for this search SearchTask
 * @param matchType The match type to set
 */
void SearchTask::setMatchType(const ContactMatch& matchType) {
	matchType_ = matchType;
}

/**
 * Sets the term to be searched for according to criterion and match type
 * @param term a std::string reference containing the term to search for
 */
void SearchTask::setTerm(const std::string& term) {
	//TODO: Validate?
	
	//Convert std::string to QString
	term_ = QString::fromLocal8Bit(term.c_str());
}

/**
 * Begin search task
 */
void SearchTask::find() {
	//Create a search job for criteria values and set query using criterion,
	// value, and match type.
	job_ = new SearchJob((QObject*)this);
	job_->setQuery(criterion_, term_, matchType_);
	
	// Connect job result signal to search results handler and start async processing
	QObject::connect(job_, SIGNAL(result(KJob*)), SLOT(processResults(KJob*)));
	job_->start();
}

/**
 * Slot handler connected to SearchJob::result(KJob*) signal, process search
 * results.
 * @param job The result of the search job
 */
void SearchTask::processResults(KJob *job) {
	// Retrieve the list of contacts from the SearchJob
	if(job == nullptr) return;
	
	// Get the results and print each to stdout
	const KContacts::Addressee::List contacts =	dynamic_cast<SearchJob*>(job)->contacts();
	
	for(KContacts::Addressee addr : contacts) {
		// Print name to stdout
		QString fname = addr.givenName();
		QString lname = addr.familyName();
		
		//Get email list and set first address found or none
		QString email = QString::fromLocal8Bit("none");
		QStringList emails = addr.emails();
		if(emails.length() > 0) {
			email = emails[0];
		}
		
		std::cout << "\t"
		<< fname.toStdString().c_str()
		<< " " << lname.toStdString().c_str()
		<< " (" << email.toStdString().c_str()
		<< ")" << std::endl;
	}
	
	//Will cause core application to return from exec()
	emit finished();
}
