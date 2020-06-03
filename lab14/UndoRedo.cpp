#include "UndoRedo.h"

void UndoRedoAdd::executeUndo()
{
	this->repo.deleteChore(chore.getTitle());
}

void UndoRedoAdd::executeRedo()
{
	this->repo.addChore(chore);
}

void UndoRedoDelete::executeUndo()
{
	this->repo.addChore(dchore);
}

void UndoRedoDelete::executeRedo()
{
	this->repo.deleteChore(this->dchore.getTitle());
}

void UndoRedoUpdate::executeUndo()
{
	this->repo.updateChore(oldChore);
}

void UndoRedoUpdate::executeRedo()
{
	this->repo.updateChore(newChore);
}
