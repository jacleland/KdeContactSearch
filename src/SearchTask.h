/*
 * <one line to give the library's name and an idea of what it does.>
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

#ifndef _SEARCHTASK_H
#define _SEARCHTASK_H

//Library includes
#include <string>
#include <iostream>

//KDE/QT5 includes
#include <QObject>
#include <QStringList>
#include <AkonadiCore/ExceptionBase>
#include <Akonadi/Contact/ContactSearchJob>

//Type definitions
using SearchJob 				= Akonadi::ContactSearchJob;
using SearchCriterion 	= SearchJob::Criterion;
using ContactMatch 			= SearchJob::Match;

/**
 * @todo write docs
 */
class SearchTask : public QObject {
	Q_OBJECT

public:
	/**
	 * Copy constructor
	 * @param other TODO
	 */
	SearchTask(const SearchTask& other);

	/**
	 * Construct with criterion and match type
	 * @param criterion specifies what field should be used to match value (default name or email)
	 * @param match the type of match to be performed (default starts with)
	 */
	explicit SearchTask(SearchCriterion criterion = SearchCriterion::NameOrEmail,
	 ContactMatch matchType = ContactMatch::StartsWithMatch);

	/**
	 * Destructor
	 */
	virtual ~SearchTask();

	/**
	 * Assignment operator
	 *
	 * @param other TODO
	 * @return TODO
	 */
	SearchTask& operator=(const SearchTask& other);

	/**
	 * Returns the criteria value for this SearchTask instance
	 * @return The criterion value
	 */
	const SearchCriterion& criterion();

	/**
   * Sets criterion for searches
   * @param criterion Const reference to criterion for search
   */
	void setCriterion(const SearchCriterion& criterion);

	/**
   * Return the match type for this search SearchTask
	 * @return The match type
   */
	const ContactMatch& matchType() const;

	/**
   * Set the match type for this search SearchTask
	 * @param matchType The match type to set
   */
	void setMatchType(const ContactMatch& matchType);

	/**
   * Sets the term to be searched for according to criterion and match type
	 * @param term a std::string reference containing the term to search for
   */
	void setTerm(const std::string& term);

public Q_SLOTS:
	/**
	 * Search the local address book for a contact matching the criteria
	 * specified by the search term assigned to this instance
	 */
	void find();

	/**
	 * Slot for handling search results
	 */
	void processResults(KJob *job);

Q_SIGNALS:
	void finished();

private:
	SearchCriterion				criterion_;			/*! Search criteria/field to search for text */
	ContactMatch					matchType_;			/*! Match type */
	QString								term_;					/*! The term to search for */
	SearchJob*						job_;						/*! The job representing the search to perform */
};


#endif //Include once
