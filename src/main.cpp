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

// System includes
#include <iostream>

//Library includes
#include <QObject>
#include <QCoreApplication>
#include <QTimer>

//Project/Local includes
#include "SearchTask.h"

/**
 * 
 */
int main(int argc, char **argv) {
	//Locals
	QCoreApplication app(argc, argv);
	int result = -1;
	
	//Create a search task. We'll reuse the same search task instance and
	// update the search term for each individual search.
	SearchTask *task = new SearchTask();
	
	if(task != nullptr) {
		//Declare search term string
		std::string term = "";
		
		//First, connect the task::finished() signal to QCoreApplication's quit()
		// slot so we exit once the search results are returned and processed.
		QObject::connect(task, SIGNAL(finished()), &app, SLOT(quit()));
		
		//Read value from stdin
		std::cout << "Search Term? ";
		std::cin >> term;
		
		//Set the search term for the search task and queue this task's find()
		// to perform the contact search.
		task->setTerm(term);
		QTimer::singleShot(0, task, SLOT(find()));
		
		result = app.exec();
		
		//Clean up the heap-allocated search task instance
		delete task;
		task = nullptr;
	}
	
	//Return the app.exec() result
	return result;
}
