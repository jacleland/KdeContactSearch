/**
 * Address Book record retrieval testing
 *
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
	}

	//Return the app.exec() result
	return result;
}
