#include "activityUndo.h"
#include <iostream>

void UndoAdd::doUndo() {
	repo.del(added_action.getName());
}

void UndoRemove::doUndo() {
	repo.add(removed_action);
}

void UndoChange::doUndo() {
	string line1, line2;
	new_action.activityToLine(line1);
	old_action.activityToLine(line2);
	// cout << line1 << '\n' << line2 << '\n';
	repo.del(new_action.getName());
	repo.add(old_action);
}
