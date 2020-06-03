#pragma once
#include<utility>
#include "FileRepository.h"

class UndoRedo {


public:
	virtual void executeUndo() = 0;
	virtual void executeRedo() = 0;
	virtual ~UndoRedo() {}

};

class UndoRedoAdd :public UndoRedo {

private:
	Chore chore;
	FileRepo& repo;
public:
	UndoRedoAdd(FileRepo& repo, const Chore& c) :repo(repo ), chore(c){}
	void executeUndo() override;
	void executeRedo() override;
};

class UndoRedoDelete :public UndoRedo {

private:
	Chore dchore;
	FileRepo& repo;
public:
	UndoRedoDelete(FileRepo& repo, const Chore& c) :repo(repo), dchore(c){}
	void executeUndo() override;
	void executeRedo() override;
};

class UndoRedoUpdate :public UndoRedo {

private:
	Chore oldChore;
	Chore newChore;
	FileRepo& repo;
public:
	UndoRedoUpdate(FileRepo& repo, const Chore& c,const Chore&c1) :repo(repo), oldChore(c), newChore(c1) {}
	void executeUndo() override;
	void executeRedo() override;
};
