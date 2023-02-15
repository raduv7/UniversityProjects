#pragma once
#pragma once
#include "activityRepository.h"

using namespace std;

#ifndef UNDO
#define UNDO


class UndoActions {

public:
	virtual void doUndo() = 0;

	/*
	* Virtual destructor
	*/
	virtual ~UndoActions() {};
};


class UndoAdd : public UndoActions {
private:
	Activity added_action;
	ActivityRepository& repo;
public:
	/*
	* Constructor for adding history
	*/
	UndoAdd(ActivityRepository& repo, const Activity& current_act) :repo{ repo }, added_action{ current_act }{};

	/*
	* Undo function for adding
	*/
	void doUndo() override;
};

class UndoRemove : public UndoActions {
private:
	Activity removed_action;
	ActivityRepository& repo;
public:
	/*
	* Constructor for removing history
	*/
	UndoRemove(ActivityRepository& repo, const Activity& current_act) : repo{ repo }, removed_action{ current_act }{};

	/*
	* Undo function for remove
	*/
	void doUndo() override;
};

class UndoChange : public UndoActions {
private:
	Activity old_action;
	Activity new_action;
	ActivityRepository& repo;
public:
	/*
	* Constructor for change function
	*/
	UndoChange(ActivityRepository& repo, const Activity& old_act, const Activity& new_act) :repo{ repo }, old_action{ old_act }, new_action{ new_act }{};

	/*
	* Undo function for change
	*/
	void doUndo() override;
};

#endif